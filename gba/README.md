# gPng GBA — Rust port scaffolding

A port of the original C64 gravity pong game to the Game Boy Advance, written
in Rust using the [agb](https://agbrs.dev/) library.

## Prerequisites

```
rustup update nightly
cargo build
```

To run in the mGBA emulator: `cargo run` (requires `mgba-qt` in PATH).

---

## Why this looks different from normal Rust

The top of `main.rs` has two attributes you won't see in ordinary programs:

```rust
#![no_std]
#![no_main]
```

The GBA has no operating system. `no_std` means we don't link the standard
library (no filesystem, no heap by default, no threads). `no_main` means Rust
won't generate its usual startup code — agb provides its own via the
`#[agb::entry]` macro, which sets up the hardware and then calls our `main`.

We do get a heap via `extern crate alloc`, which agb wires up for us. That
lets us use `Vec`, `Box`, `String`, etc. even without std.

---

## The build target

The GBA runs an ARM7TDMI processor. The Rust target for it is
`thumbv4t-none-eabi` — a bare-metal ARM target with no OS (`none`) and the
ARM EABI calling convention. Because it's a Tier 3 target, it requires nightly
Rust and `build-std` (we compile `core` and `alloc` from source).

`.cargo/config.toml` sets this as the default target so you never need to pass
`--target` manually.

---

## Project structure

```
src/
  main.rs      — entry point and game loop
  game.rs      — game state: ball, paddles, scoring, physics stubs
  player.rs    — reads GBA buttons, moves paddle1
  graphics.rs  — rendering stubs (sprites + background, not yet wired up)
```

### `main.rs` — the game loop

```rust
#[agb::entry]
fn main(mut gba: Gba) -> ! {
    let mut input = agb::input::ButtonController::new();
    let mut state = GameState::Playing(PlayState::new());

    loop {
        input.update();

        if let GameState::Playing(ref mut play) = state {
            player::handle_input(&input, play);
            play.update();
            graphics::render(play);
        }

        agb::halt();
    }
}
```

`agb::halt()` suspends the CPU until the next VBlank interrupt — the moment
the screen finishes drawing and is ready for the next frame. On the GBA this
fires 60 times per second. The loop therefore runs at 60 fps without any
manual timing.

`-> !` means the function never returns. There's nothing to return *to* on
bare metal, so the type system enforces it.

### `game.rs` — state and physics

`GameState` is an enum with three variants:

```rust
pub enum GameState {
    Title,
    Playing(PlayState),
    Winner(u8),   // player number who won
}
```

This is idiomatic Rust for a state machine: each variant can carry different
data, and `match` forces you to handle all cases. Compare this to the C64
version's `GPngState` enum.

`PlayState` holds everything that changes during a round — ball, both paddles,
scores, and the current gravity direction. Gravity is also an enum:

```rust
pub enum GravityDirection { Up, Down, Left, Right }
```

The `match` in `apply_gravity()` shows a common Rust pattern: exhaustive
branching where the compiler will error if you add a variant and forget to
handle it.

Physics uses plain `i16` for positions and velocities. The original C64 code
used fixed-point integers (`FPMAKE` macro). The GBA has no FPU either, so
we'll do the same — `agb` ships `agb_fixnum` for this, which we'll wire in
when adding real gravity.

### `player.rs` — input

```rust
if input.is_pressed(Button::Up) {
    state.paddle1.y = (state.paddle1.y - PADDLE_SPEED).max(0);
}
```

`ButtonController::is_pressed` returns true every frame the button is held.
`is_just_pressed` would return true only on the first frame. The `.max(0)`
clamps the paddle to the top of the screen — Rust's integer methods like
`max`, `min`, and `saturating_add` are a clean alternative to if-guards.

Player 2 input is a stub. Options: second player on the same GBA via unused
buttons (L/R vs A/B), link cable multiplayer, or an AI.

### `graphics.rs` — rendering (stub)

The GBA has two graphics systems that work together:

**Backgrounds (BG)** — up to four layers of tiles. Each tile is an 8×8 block
of pixels defined in VRAM. We'll use one background layer for the arena.

**OBJ (sprites)** — hardware sprites composited on top of backgrounds. The
GBA supports up to 128 sprites. Ball and paddles will be OBJ sprites.

agb's workflow for sprites:

1. Embed pixel data at compile time with `include_aseprite!()` or
   `include_gfx!()` — this runs at build time and converts PNG/Aseprite files
   into GBA tile format.
2. Each frame, get an `OamIterator` from the graphics frame, create an object
   from a sprite tag, set its x/y, and call `.show()`.

The module currently has the structure in place but passes `let _ = state` as
a placeholder until assets exist.

---

## GBA screen

- Resolution: **240×160** pixels
- Pixel origin: top-left (0, 0)
- Sprites are positioned by their top-left corner
- The screen refresh rate is **59.73 Hz** (close enough to treat as 60)

Paddle positions in `PlayState::new()` place them near the left and right
edges, vertically centred — same layout as the C64 version.

---

## Next steps

- [ ] Add fixed-point gravity using `agb_fixnum`
- [ ] Draw the ball and paddles (create sprite assets, wire up OAM)
- [ ] Add a tiled background for the arena
- [ ] Implement paddle collision and scoring
- [ ] Title and winner screens (the other `GameState` variants)
- [ ] Player 2 input or simple AI
