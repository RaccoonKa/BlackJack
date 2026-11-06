# 🃏 Blackjack: GUI Edition — "The `#define NOMINMAX` Incident"

Welcome to the **deluxe version** of the legendary console blackjack — now with **graphics, sounds, and questionable architectural decisions**! This is what happens when a beginner discovers SFML before discovering design patterns.

## What is this?

It's the same blackjack, but now with:
- 🎨 Fancy textures (cards, chips, "devushkas" 👀)
- 🎵 Background music (three whole tracks!)
- 🖱️ Custom cursors
- ⚙️ A settings menu with a volume slider
- 📜 A rules screen (in English, written by someone clearly fighting auto-translate)
- 🖥️ **Fullscreen by default** (bold move)

And all of it — **in one single `main()` function**. Yes, really. All ~1500 lines. No `class Game`, no `class StateMachine`, no `class Anything` — just one majestic `main()` and a `while (window.isOpen())` loop that knows too much.

## ⚠️ The `#define NOMINMAX` Situation

Legend has it that the entire game **depends on one single line**:

```cpp
#define NOMINMAX
```

Without it, `std::min` and `std::max` get into a fistfight with Windows.h macros, and the project **refuses to compile**. Remove that line and watch the compiler throw a tantrum like a toddler whose ice cream fell. This is not a bug — it's the **load-bearing `#define`** of the entire application.

> "One does not simply remove `#define NOMINMAX`."
> — The author, probably

## Features (Yes, There Are Actual Features!)

- **Betting system** — chips from 100 to 10,000. Start with 10,000. Lose it all? Don't worry, the game takes pity on you and refunds 2,500. Real casinos hate this one trick!
- **Animated card dealing** — cards appear with a 2-second `Sleep(2005)`. Why 2005? Don't ask.
- **Dealer AI** — draws cards if his score is `<=` player's score. Simple, elegant, and slightly suicidal.
- **Score tracking** — live updates for both player and dealer.
- **Win/Lose/Push detection** — surprisingly thorough logic, buried deep in an `else if` chain.
- **Three visual themes** — Red, Green, Blue. Each with its own music. Each with its own cursor color!
- **Mute button** — works, but only if you click exactly where it is.
- **"Soon!" 2-player mode** — a promise. A dream. A "TODO" rendered as a PNG.

## The Architecture (Term Used Very Loosely)

```
main()
├── load every texture ever
├── load every font ever
├── declare 200 variables
├── while (window.isOpen())
│   ├── if (menu)
│   │   └── if (showPlay) ... else if (showRules) ... else if (showSettings) ...
│   ├── if (game)
│   │   ├── if (chosing_bet) ...
│   │   ├── else if (first_move) ...
│   │   ├── else if (!dealers_move) ...
│   │   ├── else if (dealers_move) ...
│   │   └── { check_win }  // anonymous scope, why not
│   └── draw cursor
└── delete 6 buttons
```

This is a **State Machine**, if you squint hard enough. A very, very blurry state machine. Through dirty glasses. In the dark.

## Known "Features"

- The dealer score text uses `player_score_str` in its initializer. Does it matter? No, because it gets overwritten. Is it a bug? **Philosophically, yes.**
- `Sleep(2005)` — not 2000, not 2010. **2005**. The year the author discovered My Chemical Romance? We'll never know.
- The `Button::check_mouse_click()` method checks `position.x + normal.x` for **both** x and y axes. It works. Somehow.
- The rules text says "A digit has a value in its hand that exceeds the amount in dealer hand" — pure poetry.
- Authors screen contains **raccoon images**. This is intentional. Probably.
- `jump` variable exists. Its purpose is to `Sleep(500)` once. Then it becomes `false` forever. It's a metaphor for life.

## Why Does This Exist?

Because the author:
1. Learned SFML before learning OOP
2. Learned OOP after building this, as a coping mechanism
3. Now looks at this code and feels a mix of pride and existential dread

**This is the origin story.** The console blackjack was the tutorial. This is the first boss fight. The next version — with classes, CMake, and actual architecture — is the redemption arc.

## How to Build?

You'll need:
- **SFML** (probably 2.5, since 3.0 wasn't a thing yet)
- **Windows.h** (obviously, or `NOMINMAX` wouldn't be a hero)
- **A C++ compiler** with enough patience
- **Assets folder** with all textures (good luck finding them, hope they're in the repo)

```bash
# CMake users:
mkdir build && cd build
cmake ..
cmake --build .

# Windows users who prefer pain:
# Just open it in Visual Studio and hope.
```

## Asset Requirements

The game expects these files (and if any are missing, you get a `return 404` — yes, an HTTP code from a desktop app):

```
assets/
├── cards/          (13 card textures + 3 shirt colors)
├── chips/          (6 chip denominations)
├── backgrounds/    (3 theme backgrounds)
├── different/      (fonts, ornaments, devushkas, raccoon, cursors, musics...)
```

If `raccoonka.png` is missing, the game refuses to launch. **This is non-negotiable.**

## Fun Fact

The `return 404` when an asset fails to load is technically an HTTP error code. The author didn't know what a return code was. They just thought 404 looked cool. **They were right.**

## License

MIT (Make It Terrifying). 

**Warning:** Removing `#define NOMINMAX` will void your warranty, your sanity, and your compilation.

---

*P.S. If you're wondering why every single `if` block re-declares textures instead of loading them once — the answer is "because." Because the author was young. Because the author was full of hope. Because the author believed that `sf::Texture tmptexture;` inside a function called every frame was a totally reasonable thing to do. It is not. But it works.*

*P.P.S. The `devushka1.png` and `devushka2.png` are still in the repo. We don't talk about them. But they're part of the lore now.*
