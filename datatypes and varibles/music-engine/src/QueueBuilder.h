#pragma once
#include "Song.h"
#include "PreferenceEngine.h"
#include <vector>
#include <queue>

// Builds the "upcoming queue" by scoring every song in the library
// against current genre weights and taking the top N via a max-heap,
// skipping any genre that's currently locked out.
class QueueBuilder {
public:
    struct Candidate {
        Song song;
        double score;
        bool operator<(const Candidate& other) const { return score < other.score; }
    };

    static std::vector<Candidate> build(const std::vector<Song>& library,
                                         const PreferenceEngine& engine,
                                         int count) {
        std::priority_queue<Candidate> pq;
        for (const auto& s : library) {
            if (engine.isLocked(s.genre)) continue;
            pq.push({s, engine.weightOf(s.genre)});
        }
        std::vector<Candidate> result;
        while (!pq.empty() && (int)result.size() < count) {
            result.push_back(pq.top());
            pq.pop();
        }
        return result;
    }
};
