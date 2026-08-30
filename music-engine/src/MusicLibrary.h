#pragma once
#include "Song.h"
#include <vector>

// Circular doubly linked list holding the full song catalog.
// Supports forward/backward traversal for "next/previous" playback,
// independent of whatever the smart-queue currently recommends.
class MusicLibrary {
public:
    ~MusicLibrary() { clear(); }

    void addSong(const Song& song) {
        Node* node = new Node{song, nullptr, nullptr};
        if (!head) {
            head = node;
            node->next = node;
            node->prev = node;
        } else {
            Node* tail = head->prev;
            tail->next = node;
            node->prev = tail;
            node->next = head;
            head->prev = node;
        }
        count++;
    }

    // Snapshot of all songs in insertion order (used to feed the queue builder).
    std::vector<Song> allSongs() const {
        std::vector<Song> result;
        if (!head) return result;
        Node* cur = head;
        do {
            result.push_back(cur->song);
            cur = cur->next;
        } while (cur != head);
        return result;
    }

    Song* current() { return cursor ? &cursor->song : nullptr; }

    void startAt(int songId) {
        Node* cur = head;
        if (!cur) return;
        do {
            if (cur->song.id == songId) { cursor = cur; return; }
            cur = cur->next;
        } while (cur != head);
    }

    void advance() { if (cursor) cursor = cursor->next; }
    void rewind()  { if (cursor) cursor = cursor->prev; }

    int size() const { return count; }

private:
    struct Node {
        Song song;
        Node* prev;
        Node* next;
    };

    void clear() {
        if (!head) return;
        Node* cur = head->next;
        while (cur != head) {
            Node* next = cur->next;
            delete cur;
            cur = next;
        }
        delete head;
        head = nullptr;
    }

    Node* head = nullptr;
    Node* cursor = nullptr;
    int count = 0;
};
