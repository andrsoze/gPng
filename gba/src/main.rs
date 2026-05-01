#![no_std]
#![no_main]
#![cfg_attr(test, feature(custom_test_frameworks))]
#![cfg_attr(test, reexport_test_harness_main = "test_main")]
#![cfg_attr(test, test_runner(agb::test_runner::test_runner))]

extern crate alloc;

mod game;
mod graphics;
mod player;
mod splash;

use agb::Gba;
use game::{GameState, PlayState};
use splash::SplashScreen;

#[agb::entry]
fn main(mut gba: Gba) -> ! {
    let mut input = agb::input::ButtonController::new();
    let mut gfx = gba.graphics.get();

    let mut splash = SplashScreen::new();
    let mut state = GameState::Title;

    loop {
        input.update();

        let mut frame = gfx.frame();

        match &mut state {
            GameState::Title => {
                splash.show(&mut frame);

                // Any button press moves to the game
                if input.is_just_pressed(agb::input::Button::Start) {
                    state = GameState::Playing(PlayState::new());
                }
            }
            GameState::Playing(play) => {
                player::handle_input(&input, play);
                play.update();
                graphics::render(play);
            }
            GameState::Winner(_) => {}
        }

        frame.commit();
    }
}
