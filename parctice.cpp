#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
#include <deque>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>

// ==========================================
// Song.h
// ==========================================
struct Song
{
    int id;
    std::string title;
    std::string artist;
    std::string genre;
};

// ==========================================
// PreferenceEngine.h
// ==========================================
struct GenreProfile
{
    double weight = 1.0;
    int consecutiveSkips = 0;
    int lockoutRemaining = 0; // songs left in the temporary lockout
    std::string lastAction = "Neutral";
};

struct ActionLogEntry
{
    std::string type; // "COMPLETE" or "SKIP"
    std::string genre;
};

struct PatternEvent
{
    std::string genre;
    std::string reason;
};

// Core adaptive logic: hash map preference scores + sliding window
// pattern detection + genre lockout + decay/recovery.
class PreferenceEngine
{
public:
    static constexpr int WINDOW_SIZE = 4;
    static constexpr int LOCKOUT_THRESHOLD = 2; // consecutive skips of same genre
    static constexpr int LOCKOUT_DURATION = 5;  // songs the genre stays blocked
    static constexpr double COMPLETE_BOOST = 0.25;
    static constexpr double SKIP_PENALTY = 0.40;
    static constexpr double DECAY_STEP = 0.15;
    static constexpr double MIN_WEIGHT = 0.10;
    static constexpr double MAX_WEIGHT = 2.00;
    static constexpr double BASELINE = 1.00;

    void registerGenre(const std::string &genre)
    {
        if (genres.find(genre) == genres.end())
            genres[genre] = GenreProfile{};
    }

    void onComplete(const std::string &genre)
    {
        registerGenre(genre);
        auto &p = genres[genre];
        p.weight = clamp(p.weight + COMPLETE_BOOST);
        p.consecutiveSkips = 0;
        p.lastAction = "Completed";
        pushAction({"COMPLETE", genre});
    }

    // Returns a PatternEvent if this skip triggered a new lockout, else empty genre.
    PatternEvent onSkip(const std::string &genre)
    {
        registerGenre(genre);
        auto &p = genres[genre];
        p.weight = clamp(p.weight - SKIP_PENALTY);
        p.consecutiveSkips++;
        p.lastAction = "Skipped";
        pushAction({"SKIP", genre});

        PatternEvent event;
        if (p.consecutiveSkips >= LOCKOUT_THRESHOLD && p.lockoutRemaining == 0)
        {
            p.lockoutRemaining = LOCKOUT_DURATION;
            event.genre = genre;
            event.reason = "Two " + genre + " tracks were skipped consecutively.";
        }
        return event;
    }

    void tick()
    {
        for (auto &[genre, p] : genres)
        {
            if (p.lockoutRemaining > 0)
            {
                p.lockoutRemaining--;
                if (p.weight < BASELINE)
                    p.weight = clamp(p.weight + DECAY_STEP);
                if (p.lockoutRemaining == 0)
                    p.consecutiveSkips = 0;
            }
            else if (p.weight < BASELINE)
            {
                p.weight = clamp(p.weight + DECAY_STEP * 0.5);
            }
            else if (p.weight > BASELINE)
            {
                p.weight = clamp(p.weight - DECAY_STEP * 0.25);
            }
        }
    }

    bool isLocked(const std::string &genre) const
    {
        auto it = genres.find(genre);
        return it != genres.end() && it->second.lockoutRemaining > 0;
    }

    double weightOf(const std::string &genre) const
    {
        auto it = genres.find(genre);
        return it != genres.end() ? it->second.weight : BASELINE;
    }

    const std::unordered_map<std::string, GenreProfile> &allGenres() const { return genres; }
    const std::deque<ActionLogEntry> &recentActions() const { return actionWindow; }

private:
    double clamp(double w) const
    {
        if (w < MIN_WEIGHT)
            return MIN_WEIGHT;
        if (w > MAX_WEIGHT)
            return MAX_WEIGHT;
        return w;
    }

    void pushAction(ActionLogEntry e)
    {
        actionWindow.push_back(std::move(e));
        while ((int)actionWindow.size() > WINDOW_SIZE)
            actionWindow.pop_front();
    }

    std::unordered_map<std::string, GenreProfile> genres;
    std::deque<ActionLogEntry> actionWindow;
};

// ==========================================
// QueueBuilder.h
// ==========================================
// Builds the "upcoming queue" by scoring every song in the library
// against current genre weights and taking the top N via a max-heap,
// skipping any genre that's currently locked out.
class QueueBuilder
{
public:
    struct Candidate
    {
        Song song;
        double score;
        bool operator<(const Candidate &other) const { return score < other.score; }
    };

    static std::vector<Candidate> build(const std::vector<Song> &library,
                                        const PreferenceEngine &engine,
                                        int count)
    {
        std::priority_queue<Candidate> pq;
        for (const auto &s : library)
        {
            if (engine.isLocked(s.genre))
                continue;
            pq.push({s, engine.weightOf(s.genre)});
        }
        std::vector<Candidate> result;
        while (!pq.empty() && (int)result.size() < count)
        {
            result.push_back(pq.top());
            pq.pop();
        }
        return result;
    }
};

// ==========================================
// MusicLibrary.h
// ==========================================
// Circular doubly linked list holding the full song catalog.
// Supports forward/backward traversal for "next/previous" playback,
// independent of whatever the smart-queue currently recommends.
class MusicLibrary
{
public:
    ~MusicLibrary() { clear(); }

    void addSong(const Song &song)
    {
        Node *node = new Node{song, nullptr, nullptr};
        if (!head)
        {
            head = node;
            node->next = node;
            node->prev = node;
        }
        else
        {
            Node *tail = head->prev;
            tail->next = node;
            node->prev = tail;
            node->next = head;
            head->prev = node;
        }
        count++;
    }

    // Snapshot of all songs in insertion order (used to feed the queue builder).
    std::vector<Song> allSongs() const
    {
        std::vector<Song> result;
        if (!head)
            return result;
        Node *cur = head;
        do
        {
            result.push_back(cur->song);
            cur = cur->next;
        } while (cur != head);
        return result;
    }

    Song *current() { return cursor ? &cursor->song : nullptr; }

    void startAt(int songId)
    {
        Node *cur = head;
        if (!cur)
            return;
        do
        {
            if (cur->song.id == songId)
            {
                cursor = cur;
                return;
            }
            cur = cur->next;
        } while (cur != head);
    }

    void advance()
    {
        if (cursor)
            cursor = cursor->next;
    }
    void rewind()
    {
        if (cursor)
            cursor = cursor->prev;
    }

    int size() const { return count; }

private:
    struct Node
    {
        Song song;
        Node *prev;
        Node *next;
    };

    void clear()
    {
        if (!head)
            return;
        Node *cur = head->next;
        while (cur != head)
        {
            Node *next = cur->next;
            delete cur;
            cur = next;
        }
        delete head;
        head = nullptr;
    }

    Node *head = nullptr;
    Node *cursor = nullptr;
    int count = 0;
};

// ==========================================
// main.cpp
// ==========================================
// ---- Simulated session stats for the summary panel ----
struct SessionStats
{
    int played = 0;
    int completed = 0;
    int skips = 0;
    int patternsDetected = 0;
    int lockouts = 0;
};

static void glfw_error_callback(int error, const char *description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

int main()
{
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;

    const char *glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    GLFWwindow *window = glfwCreateWindow(1100, 720, "Adaptive Music Shuffle Engine", nullptr, nullptr);
    if (!window)
        return 1;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // ---------------- Engine setup ----------------
    MusicLibrary library;
    PreferenceEngine engine;
    SessionStats stats;
    std::vector<std::string> notifications;

    std::vector<Song> seed = {
        {1, "Perfect", "Ed Sheeran", "Pop"},
        {2, "Shape of You", "Ed Sheeran", "Pop"},
        {3, "Levitating", "Dua Lipa", "Pop"},
        {4, "Yellow", "Coldplay", "Rock"},
        {5, "Bohemian Rhapsody", "Queen", "Rock"},
        {6, "Take Five", "Dave Brubeck", "Jazz"},
        {7, "Fly Me to the Moon", "Frank Sinatra", "Jazz"},
        {8, "Photograph", "Ed Sheeran", "Acoustic"},
        {9, "Clair de Lune", "Debussy", "Classical"},
        {10, "Canon in D", "Pachelbel", "Classical"},
    };
    for (auto &s : seed)
    {
        library.addSong(s);
        engine.registerGenre(s.genre);
    }

    std::vector<Song> allSongs = library.allSongs();
    auto upcoming = QueueBuilder::build(allSongs, engine, 5);

    Song nowPlaying = upcoming.empty() ? allSongs[0] : upcoming.front().song;
    if (!upcoming.empty())
        upcoming.erase(upcoming.begin());

    auto rebuildQueue = [&]()
    {
        upcoming = QueueBuilder::build(allSongs, engine, 5);
        // don't recommend the currently-playing song again immediately
        for (auto it = upcoming.begin(); it != upcoming.end(); ++it)
        {
            if (it->song.id == nowPlaying.id)
            {
                upcoming.erase(it);
                break;
            }
        }
    };

    auto advanceToNext = [&]()
    {
        rebuildQueue();
        if (!upcoming.empty())
        {
            nowPlaying = upcoming.front().song;
            upcoming.erase(upcoming.begin());
        }
        engine.tick();
        stats.played++;
        rebuildQueue();
    };

    // ---------------- Main loop ----------------
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGuiViewport *vp = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(vp->Pos);
        ImGui::SetNextWindowSize(vp->Size);
        ImGui::Begin("Adaptive Music Shuffle Engine", nullptr,
                     ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

        ImGui::TextColored(ImVec4(0.6f, 0.85f, 1.0f, 1), "ADAPTIVE MUSIC SHUFFLE ENGINE");
        ImGui::TextDisabled("Real-time preference learning - local C++ engine");
        ImGui::Separator();

        ImGui::Columns(2, "main_cols", true);
        ImGui::SetColumnWidth(0, 420);

        // ---- LEFT: Now Playing + controls ----
        ImGui::BeginChild("NowPlaying", ImVec2(0, 200), true);
        ImGui::Text("NOW PLAYING");
        ImGui::Separator();
        ImGui::Text("Song   : %s", nowPlaying.title.c_str());
        ImGui::Text("Artist : %s", nowPlaying.artist.c_str());
        ImGui::Text("Genre  : %s", nowPlaying.genre.c_str());
        ImGui::Text("Weight : %.2f", engine.weightOf(nowPlaying.genre));
        ImGui::Spacing();

        if (ImGui::Button("Listen to completion", ImVec2(200, 32)))
        {
            engine.onComplete(nowPlaying.genre);
            stats.completed++;
            notifications.insert(notifications.begin(),
                                 "Completed \"" + nowPlaying.title + "\" (+ preference for " + nowPlaying.genre + ")");
            advanceToNext();
        }
        ImGui::SameLine();
        if (ImGui::Button("Skip", ImVec2(120, 32)))
        {
            PatternEvent ev = engine.onSkip(nowPlaying.genre);
            stats.skips++;
            notifications.insert(notifications.begin(),
                                 "Skipped \"" + nowPlaying.title + "\" (- preference for " + nowPlaying.genre + ")");
            if (!ev.genre.empty())
            {
                stats.patternsDetected++;
                stats.lockouts++;
                notifications.insert(notifications.begin(),
                                     "LOCKOUT: " + ev.genre + " blocked for " +
                                         std::to_string(PreferenceEngine::LOCKOUT_DURATION) + " songs - " + ev.reason);
            }
            advanceToNext();
        }

        if (ImGui::Button("Simulate decay tick", ImVec2(200, 28)))
        {
            engine.tick();
            notifications.insert(notifications.begin(), "Time passed - weights drifting toward baseline.");
        }
        ImGui::EndChild();

        // ---- LEFT: Genre preference table ----
        ImGui::Text("GENRE PREFERENCES");
        ImGui::BeginChild("GenreTable", ImVec2(0, 220), true);
        if (ImGui::BeginTable("genres", 3, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg))
        {
            ImGui::TableSetupColumn("Genre");
            ImGui::TableSetupColumn("Weight");
            ImGui::TableSetupColumn("Status");
            ImGui::TableHeadersRow();
            for (auto &[genre, profile] : engine.allGenres())
            {
                ImGui::TableNextRow();
                ImGui::TableSetColumnIndex(0);
                ImGui::Text("%s", genre.c_str());
                ImGui::TableSetColumnIndex(1);
                float frac = (float)(profile.weight / PreferenceEngine::MAX_WEIGHT);
                ImVec4 barColor = profile.weight < 0.5   ? ImVec4(0.8f, 0.3f, 0.3f, 1)
                                  : profile.weight > 1.2 ? ImVec4(0.3f, 0.8f, 0.4f, 1)
                                                         : ImVec4(0.6f, 0.6f, 0.6f, 1);
                ImGui::PushStyleColor(ImGuiCol_PlotHistogram, barColor);
                ImGui::ProgressBar(frac, ImVec2(-1, 0), "");
                ImGui::PopStyleColor();
                ImGui::SameLine();
                ImGui::Text("%.2f", profile.weight);
                ImGui::TableSetColumnIndex(2);
                if (profile.lockoutRemaining > 0)
                {
                    ImGui::TextColored(ImVec4(1, 0.4f, 0.4f, 1), "LOCKED (%d)", profile.lockoutRemaining);
                }
                else
                {
                    ImGui::TextColored(ImVec4(0.6f, 1, 0.6f, 1), "NORMAL");
                }
            }
            ImGui::EndTable();
        }
        ImGui::EndChild();

        ImGui::NextColumn();

        // ---- RIGHT: Upcoming queue ----
        ImGui::Text("UPCOMING QUEUE  (priority-queue rebuilt on every action)");
        ImGui::BeginChild("Queue", ImVec2(0, 170), true);
        int i = 1;
        for (auto &c : upcoming)
        {
            ImGui::Text("%d. %-22s | %-10s | score %.2f", i++, c.song.title.c_str(), c.song.genre.c_str(), c.score);
        }
        if (upcoming.empty())
            ImGui::TextDisabled("(no eligible songs - everything locked out)");
        ImGui::EndChild();

        // ---- RIGHT: Sliding window of recent actions ----
        ImGui::Text("RECENT ACTIONS (sliding window, size %d)", PreferenceEngine::WINDOW_SIZE);
        ImGui::BeginChild("Window", ImVec2(0, 90), true);
        for (auto &a : engine.recentActions())
        {
            ImVec4 col = a.type == "SKIP" ? ImVec4(1, 0.6f, 0.4f, 1) : ImVec4(0.6f, 1, 0.6f, 1);
            ImGui::TextColored(col, "[%s: %s]", a.type.c_str(), a.genre.c_str());
        }
        ImGui::EndChild();

        // ---- RIGHT: Notifications / pattern log ----
        ImGui::Text("EVENT LOG");
        ImGui::BeginChild("Log", ImVec2(0, 130), true);
        for (auto &n : notifications)
            ImGui::TextWrapped("- %s", n.c_str());
        ImGui::EndChild();

        ImGui::Columns(1);
        ImGui::Separator();

        // ---- Footer: session stats ----
        ImGui::Text("Session  |  Played: %d   Completed: %d   Skips: %d   Patterns: %d   Lockouts: %d",
                    stats.played, stats.completed, stats.skips, stats.patternsDetected, stats.lockouts);

        ImGui::End();

        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.08f, 0.08f, 0.10f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}