# Adaptive Music Shuffle Engine — GUI Prototype

A working prototype matching your project spec: preference learning via hash map,
sliding-window skip-pattern detection, genre lockout, max-heap queue rebuilding,
and preference decay — with a Dear ImGui dashboard instead of a console loop.

## Architecture

```
src/
  Song.h             Plain data: id, title, artist, genre
  MusicLibrary.h      Circular doubly linked list holding the song catalog
  PreferenceEngine.h  Hash map of genre -> weight/status, sliding window of
                       recent actions, lockout detection, decay/recovery
  QueueBuilder.h       Max-heap (priority_queue) that scores songs by current
                       genre weight and returns the top N, skipping lockouts
  main.cpp             GLFW + Dear ImGui GUI layer — calls into the engine,
                       never contains adaptive logic itself
```

The split is deliberate: `PreferenceEngine`, `MusicLibrary`, and `QueueBuilder`
have zero rendering code. You could swap `main.cpp` for a console loop, a Qt
window, or a unit test file and the DSA logic underneath doesn't change —
which is the part your mentor will actually be evaluating.

## What it demonstrates live

- Click **Listen to completion** → genre weight rises, table updates, queue
  re-sorts by the max-heap.
- Click **Skip** twice in a row on the same genre → **LOCKOUT ACTIVATED**,
  that genre disappears from the upcoming queue for 5 songs.
- **Simulate decay tick** → locked/suppressed genres drift back toward
  baseline weight (1.00) over time, same as the "Preference Decay Simulation"
  in your sample output.
- Sliding window panel shows the last 4 actions, same as your console mockup.

## Build instructions

Requires CMake ≥ 3.16 and a C++17 compiler. GLFW and Dear ImGui are pulled
automatically via `FetchContent` — no manual downloads needed, but you do
need internet access on first build.

### Linux
```bash
sudo apt install cmake g++ libgl1-mesa-dev libx11-dev libxrandr-dev \
                  libxinerama-dev libxcursor-dev libxi-dev
cmake -B build
cmake --build build -j
./build/shuffle_engine
```

### Windows (Visual Studio)
```bash
cmake -B build -G "Visual Studio 17 2022"
cmake --build build --config Release
build\Release\shuffle_engine.exe
```

### macOS
```bash
brew install cmake
cmake -B build
cmake --build build -j
./build/shuffle_engine
```

## Extending it toward your full spec

Things worth adding next, roughly in order of DSA payoff:

1. **Artist-level preference**, not just genre — same hash map pattern, keyed
   on `artist` in addition to `genre`.
2. **Configurable lockout duration/threshold** exposed as ImGui sliders, so
   you can demo tuning live for your mentor instead of hardcoding constants.
3. **Persistent library editing** — an "Add Song" form (`ImGui::InputText`)
   that pushes into `MusicLibrary`, since right now it's seeded once at
   startup.
4. **Play/pause + real audio** — out of scope for the PBL's DSA focus, but if
   you want actual sound, `miniaudio` (single header) is the lightest add-on.
