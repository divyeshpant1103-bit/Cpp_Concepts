#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>

#include "Song.h"
#include "MusicLibrary.h"
#include "PreferenceEngine.h"
#include "QueueBuilder.h"

#include <string>
#include <vector>
#include <deque>

// ---- Simulated session stats for the summary panel ----
struct SessionStats {
    int played = 0;
    int completed = 0;
    int skips = 0;
    int patternsDetected = 0;
    int lockouts = 0;
};

static void glfw_error_callback(int error, const char* description) {
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

int main() {
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit()) return 1;

    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    GLFWwindow* window = glfwCreateWindow(1100, 720, "Adaptive Music Shuffle Engine", nullptr, nullptr);
    if (!window) return 1;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // ---------------- Engine setup ----------------
    MusicLibrary library;
    PreferenceEngine engine;
    SessionStats stats;
    std::vector<std::string> notifications;

    std::vector<Song> seed = {
        {1, "Perfect",              "Ed Sheeran",  "Pop"},
        {2, "Shape of You",         "Ed Sheeran",  "Pop"},
        {3, "Levitating",           "Dua Lipa",    "Pop"},
        {4, "Yellow",               "Coldplay",    "Rock"},
        {5, "Bohemian Rhapsody",    "Queen",       "Rock"},
        {6, "Take Five",            "Dave Brubeck","Jazz"},
        {7, "Fly Me to the Moon",   "Frank Sinatra","Jazz"},
        {8, "Photograph",           "Ed Sheeran",  "Acoustic"},
        {9, "Clair de Lune",        "Debussy",     "Classical"},
        {10,"Canon in D",           "Pachelbel",   "Classical"},
    };
    for (auto& s : seed) {
        library.addSong(s);
        engine.registerGenre(s.genre);
    }

    std::vector<Song> allSongs = library.allSongs();
    auto upcoming = QueueBuilder::build(allSongs, engine, 5);

    Song nowPlaying = upcoming.empty() ? allSongs[0] : upcoming.front().song;
    if (!upcoming.empty()) upcoming.erase(upcoming.begin());

    auto rebuildQueue = [&]() {
        upcoming = QueueBuilder::build(allSongs, engine, 5);
        // don't recommend the currently-playing song again immediately
        for (auto it = upcoming.begin(); it != upcoming.end(); ++it) {
            if (it->song.id == nowPlaying.id) { upcoming.erase(it); break; }
        }
    };

    auto advanceToNext = [&]() {
        rebuildQueue();
        if (!upcoming.empty()) {
            nowPlaying = upcoming.front().song;
            upcoming.erase(upcoming.begin());
        }
        engine.tick();
        stats.played++;
        rebuildQueue();
    };

    // ---------------- Main loop ----------------
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGuiViewport* vp = ImGui::GetMainViewport();
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

        if (ImGui::Button("Listen to completion", ImVec2(200, 32))) {
            engine.onComplete(nowPlaying.genre);
            stats.completed++;
            notifications.insert(notifications.begin(),
                "Completed \"" + nowPlaying.title + "\" (+ preference for " + nowPlaying.genre + ")");
            advanceToNext();
        }
        ImGui::SameLine();
        if (ImGui::Button("Skip", ImVec2(120, 32))) {
            PatternEvent ev = engine.onSkip(nowPlaying.genre);
            stats.skips++;
            notifications.insert(notifications.begin(),
                "Skipped \"" + nowPlaying.title + "\" (- preference for " + nowPlaying.genre + ")");
            if (!ev.genre.empty()) {
                stats.patternsDetected++;
                stats.lockouts++;
                notifications.insert(notifications.begin(),
                    "LOCKOUT: " + ev.genre + " blocked for " +
                    std::to_string(PreferenceEngine::LOCKOUT_DURATION) + " songs - " + ev.reason);
            }
            advanceToNext();
        }

        if (ImGui::Button("Simulate decay tick", ImVec2(200, 28))) {
            engine.tick();
            notifications.insert(notifications.begin(), "Time passed - weights drifting toward baseline.");
        }
        ImGui::EndChild();

        // ---- LEFT: Genre preference table ----
        ImGui::Text("GENRE PREFERENCES");
        ImGui::BeginChild("GenreTable", ImVec2(0, 220), true);
        if (ImGui::BeginTable("genres", 3, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg)) {
            ImGui::TableSetupColumn("Genre");
            ImGui::TableSetupColumn("Weight");
            ImGui::TableSetupColumn("Status");
            ImGui::TableHeadersRow();
            for (auto& [genre, profile] : engine.allGenres()) {
                ImGui::TableNextRow();
                ImGui::TableSetColumnIndex(0);
                ImGui::Text("%s", genre.c_str());
                ImGui::TableSetColumnIndex(1);
                float frac = (float)(profile.weight / PreferenceEngine::MAX_WEIGHT);
                ImVec4 barColor = profile.weight < 0.5 ? ImVec4(0.8f,0.3f,0.3f,1)
                                 : profile.weight > 1.2 ? ImVec4(0.3f,0.8f,0.4f,1)
                                 : ImVec4(0.6f,0.6f,0.6f,1);
                ImGui::PushStyleColor(ImGuiCol_PlotHistogram, barColor);
                ImGui::ProgressBar(frac, ImVec2(-1, 0), "");
                ImGui::PopStyleColor();
                ImGui::SameLine();
                ImGui::Text("%.2f", profile.weight);
                ImGui::TableSetColumnIndex(2);
                if (profile.lockoutRemaining > 0) {
                    ImGui::TextColored(ImVec4(1,0.4f,0.4f,1), "LOCKED (%d)", profile.lockoutRemaining);
                } else {
                    ImGui::TextColored(ImVec4(0.6f,1,0.6f,1), "NORMAL");
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
        for (auto& c : upcoming) {
            ImGui::Text("%d. %-22s | %-10s | score %.2f", i++, c.song.title.c_str(), c.song.genre.c_str(), c.score);
        }
        if (upcoming.empty()) ImGui::TextDisabled("(no eligible songs - everything locked out)");
        ImGui::EndChild();

        // ---- RIGHT: Sliding window of recent actions ----
        ImGui::Text("RECENT ACTIONS (sliding window, size %d)", PreferenceEngine::WINDOW_SIZE);
        ImGui::BeginChild("Window", ImVec2(0, 90), true);
        for (auto& a : engine.recentActions()) {
            ImVec4 col = a.type == "SKIP" ? ImVec4(1,0.6f,0.4f,1) : ImVec4(0.6f,1,0.6f,1);
            ImGui::TextColored(col, "[%s: %s]", a.type.c_str(), a.genre.c_str());
        }
        ImGui::EndChild();

        // ---- RIGHT: Notifications / pattern log ----
        ImGui::Text("EVENT LOG");
        ImGui::BeginChild("Log", ImVec2(0, 130), true);
        for (auto& n : notifications) ImGui::TextWrapped("- %s", n.c_str());
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
