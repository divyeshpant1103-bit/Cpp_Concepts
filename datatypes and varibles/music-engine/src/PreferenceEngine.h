#pragma once
#include <string>
#include <unordered_map>
#include <deque>
#include <vector>

struct GenreProfile {
    double weight = 1.0;
    int consecutiveSkips = 0;
    int lockoutRemaining = 0;   // songs left in the temporary lockout
    std::string lastAction = "Neutral";
};

struct ActionLogEntry {
    std::string type;   // "COMPLETE" or "SKIP"
    std::string genre;
};

struct PatternEvent {
    std::string genre;
    std::string reason;
};

// Core adaptive logic: hash map preference scores + sliding window
// pattern detection + genre lockout + decay/recovery.
// Deliberately has zero rendering code so it can be reused by any
// front end (console, ImGui, Qt, tests, ...).
class PreferenceEngine {
public:
    static constexpr int WINDOW_SIZE       = 4;
    static constexpr int LOCKOUT_THRESHOLD = 2;    // consecutive skips of same genre
    static constexpr int LOCKOUT_DURATION  = 5;    // songs the genre stays blocked
    static constexpr double COMPLETE_BOOST = 0.25;
    static constexpr double SKIP_PENALTY   = 0.40;
    static constexpr double DECAY_STEP     = 0.15;
    static constexpr double MIN_WEIGHT     = 0.10;
    static constexpr double MAX_WEIGHT     = 2.00;
    static constexpr double BASELINE       = 1.00;

    void registerGenre(const std::string& genre) {
        if (genres.find(genre) == genres.end())
            genres[genre] = GenreProfile{};
    }

    void onComplete(const std::string& genre) {
        registerGenre(genre);
        auto& p = genres[genre];
        p.weight = clamp(p.weight + COMPLETE_BOOST);
        p.consecutiveSkips = 0;
        p.lastAction = "Completed";
        pushAction({"COMPLETE", genre});
    }

    // Returns a PatternEvent if this skip triggered a new lockout, else empty genre.
    PatternEvent onSkip(const std::string& genre) {
        registerGenre(genre);
        auto& p = genres[genre];
        p.weight = clamp(p.weight - SKIP_PENALTY);
        p.consecutiveSkips++;
        p.lastAction = "Skipped";
        pushAction({"SKIP", genre});

        PatternEvent event;
        if (p.consecutiveSkips >= LOCKOUT_THRESHOLD && p.lockoutRemaining == 0) {
            p.lockoutRemaining = LOCKOUT_DURATION;
            event.genre = genre;
            event.reason = "Two " + genre + " tracks were skipped consecutively.";
        }
        return event;
    }

    // Call once per song played, to age out lockouts and let weights
    // drift back toward baseline (preference decay / recovery).
    void tick() {
        for (auto& [genre, p] : genres) {
            if (p.lockoutRemaining > 0) {
                p.lockoutRemaining--;
                if (p.weight < BASELINE) p.weight = clamp(p.weight + DECAY_STEP);
                if (p.lockoutRemaining == 0) p.consecutiveSkips = 0;
            } else if (p.weight < BASELINE) {
                p.weight = clamp(p.weight + DECAY_STEP * 0.5);
            } else if (p.weight > BASELINE) {
                p.weight = clamp(p.weight - DECAY_STEP * 0.25);
            }
        }
    }

    bool isLocked(const std::string& genre) const {
        auto it = genres.find(genre);
        return it != genres.end() && it->second.lockoutRemaining > 0;
    }

    double weightOf(const std::string& genre) const {
        auto it = genres.find(genre);
        return it != genres.end() ? it->second.weight : BASELINE;
    }

    const std::unordered_map<std::string, GenreProfile>& allGenres() const { return genres; }
    const std::deque<ActionLogEntry>& recentActions() const { return actionWindow; }

private:
    double clamp(double w) const {
        if (w < MIN_WEIGHT) return MIN_WEIGHT;
        if (w > MAX_WEIGHT) return MAX_WEIGHT;
        return w;
    }

    void pushAction(ActionLogEntry e) {
        actionWindow.push_back(std::move(e));
        while ((int)actionWindow.size() > WINDOW_SIZE) actionWindow.pop_front();
    }

    std::unordered_map<std::string, GenreProfile> genres;
    std::deque<ActionLogEntry> actionWindow;
};
