use agb::input::{Button, ButtonController};

use crate::game::{PlayState, SCREEN_HEIGHT, PADDLE_HEIGHT};

const PADDLE_SPEED: i16 = 2;

pub fn handle_input(input: &ButtonController, state: &mut PlayState) {
    handle_player1(input, state);
    handle_player2(input, state);
}

fn handle_player1(input: &ButtonController, state: &mut PlayState) {
    if input.is_pressed(Button::Up) {
        state.paddle1.y = (state.paddle1.y - PADDLE_SPEED).max(0);
    }
    if input.is_pressed(Button::Down) {
        state.paddle1.y = (state.paddle1.y + PADDLE_SPEED).min(SCREEN_HEIGHT - PADDLE_HEIGHT);
    }
}

fn handle_player2(input: &ButtonController, state: &mut PlayState) {
    // TODO: second player via link cable or AI
    let _ = state;
}
