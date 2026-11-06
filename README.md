# 🃏 Blackjack: From Console Chaos to GUI Cringe — The Complete Saga

Welcome to the repository where a single blackjack game went through **three distinct evolutionary stages** — and somehow survived all of them. This is not just a project. This is a **journey**. A journey through `if-else` spaghetti, load-bearing `#define`s, and the beautiful naivety of someone who learned to code before learning to architect.

## 📖 The Story

Once upon a time, a developer decided to make a blackjack game "for fun." What followed was a trilogy of questionable decisions, each more ambitious — and more structurally terrifying — than the last.

This repository contains **all versions** of that journey:

| Version | Status | Architecture | Vibes |
|---------|--------|-------------|-------|
| **Console Edition** | ✅ Working | `if-else` spaghetti | Pure, honest chaos |
| **GUI Edition (SFML)** | ✅ Working | One `main()`, zero mercy | Ambitious cringe |
| **CMake Edition** | 🚧 Coming | Actual structure? | Redemption arc |

---

## 🖥️ Version 1: Console Blackjack — "The Origin Story"

**The humble beginning.** A console blackjack game written by someone who had heard of functions but was deeply suspicious of classes.

### Features
- ✅ It works. Don't ask how.
- ✅ Fully playable blackjack
- ✅ 100% test coverage (tested drunk at 3 AM)
- ❌ No classes (why would you need them?)
- ❌ No design patterns (the only pattern is "spaghetti")
- ✅ Every `else if` is a chapter in a novel

### Technical Highlights
- **Architecture:** If-Else Driven Development (IEDD)
- **Code Complexity:** O(n²) in nested conditionals
- **Classes:** none. Why bother when you've got `int playerScore` and self-belief?
- **C++ Standard:** whichever one compiled that day

### Philosophy
> "If it looks dumb but it works — it's not dumb."
> — Ancient Programmer Wisdom

---

## 🎨 Version 2: GUI Blackjack (SFML) — "The `#define NOMINMAX` Incident"

**The ambitious sequel.** Our hero discovered SFML before discovering OOP, and the result is a **~1500-line `main()` function** with textures, music, custom cursors, three visual themes, and a raccoon.

### Features
- 🎨 Fancy textures (cards, chips, "devushkas" 👀)
- 🎵 Background music (three tracks, three themes)
- 🖱️ Custom cursors (one per theme!)
- ⚙️ Settings menu with a working volume slider
- 📜 Rules screen (auto-translate poetry)
- 🖥️ Fullscreen by default (bold move)
- 🦝 A raccoon on the authors screen (non-negotiable)
- ❌ 2-player mode — promised as "Soon!" in PNG form

### ⚠️ The Load-Bearing `#define`

The entire game depends on one sacred line:

```cpp
#define NOMINMAX
```

Remove it and `std::min`/`std::max` get into a fistfight with Windows.h macros. The compiler throws a tantrum. The game refuses to build. **One does not simply remove `#define NOMINMAX`.**

### The Architecture (Term Used Very Loosely)

```
main()
├── load every texture ever
├── load every font ever
├── declare 200 variables
├── while (window.isOpen())
│   ├── if (menu)
│   │   └── if (showPlay) ... else if (showRules) ...
│   ├── if (game)
│   │   ├── if (chosing_bet) ...
│   │   ├── else if (first_move) ...
│   │   ├── else if (dealers_move) ...
│   │   └── { check_win }  // anonymous scope, why not
│   └── draw cursor
└── delete 6 buttons
```

This is a **State Machine**, if you squint hard enough. Through dirty glasses. In the dark.

### Known "Features"
- `Sleep(2005)` — not 2000, not 2010. **2005.** We'll never know why.
- The dealer score text initializes with `player_score_str`. Does it matter? No. Is it a bug? **Philosophically, yes.**
- `return 404` when an asset fails to load — an HTTP error code from a desktop app. The author thought 404 looked cool. **They were right.**
- Variable named `jump` exists solely to `Sleep(500)` once, then become `false` forever. A metaphor for life.

### Philosophy
> "Every texture is re-loaded every frame, because that's what the tutorial said."
> — The author, full of hope

---

## 🔧 Version 3: CMake Edition — "The Redemption Arc"

**Work in progress.** The version where our hero finally discovered design patterns, class hierarchies, and the concept of not putting everything in `main()`.

Coming soon:
- ✅ Actual OOP
- ✅ CMake build system
- ✅ Probably still has a raccoon somewhere

---

## 🚀 How to Build

### Console Edition
```bash
g++ main.cpp -o blackjack
./blackjack
```
*If it doesn't compile — your compiler is too new. Find an older one.*

### GUI Edition (SFML)
```bash
mkdir build && cd build
cmake ..
cmake --build .
```
*Requires SFML (probably 2.5), Windows.h, and enough patience.*

### Asset Requirements
The GUI version expects a full `assets/` folder:
```
assets/
├── cards/          (13 cards + 3 shirt colors)
├── chips/          (6 denominations)
├── backgrounds/    (3 themes)
└── different/      (fonts, ornaments, devushkas, raccoon, cursors, music...)
```
**If `raccoonka.png` is missing, the game refuses to launch. This is non-negotiable.**

---

## 🧠 Lessons Learned

1. **OOP exists for a reason.** The GUI version is the proof.
2. **`#define NOMINMAX` is load-bearing.** Respect it.
3. **You can absolutely put 1500 lines in `main()`.** You just shouldn't.
4. **Every project has a raccoon phase.** Some of us just commit it to git.
5. **The console version works.** The GUI version works. Somehow, against all odds, **this repo works.**

---

## 📜 License

MIT (Make It Terrifying).

Do whatever you want, but if it breaks — that's on you. I warned you.

**Warning:** Removing `#define NOMINMAX` will void your warranty, your sanity, and your compilation.

---

## 🦝 Final Words

This repository is a **time capsule**. It's what happens when someone learns to code by *doing* — with no mentor, no code review, and no fear. The console version is honest. The GUI version is ambitious. The CMake version is redemption.

Three versions. One game. Infinite `else if`.

*If you're reading this code and your eye is twitching — that's normal. It's called "programmer PTSD." It'll pass with time. Or it won't.*

**Welcome to the saga. Enjoy the cringe. Respect the raccoon.**

---

*P.S. `devushka1.png` and `devushka2.png` are still in the repo. We don't talk about them. But they're part of the lore now.*
