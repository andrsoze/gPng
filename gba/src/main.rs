#![no_std]
#![no_main]
#![cfg_attr(test, feature(custom_test_frameworks))]
#![cfg_attr(test, reexport_test_harness_main = "test_main")]
#![cfg_attr(test, test_runner(agb::test_runner::test_runner))]

extern crate alloc;

mod game;
mod graphics;
mod player;

use agb::Gba;
use game::{GameState, PlayState};

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

        // Wait for VBlank before updating OAM / flipping
        agb::halt();
    }
}
