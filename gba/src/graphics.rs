// GBA graphics use Mode 0: tiled backgrounds + OBJ (sprite) layer
//
// The plan:
//   - Background layer 0: arena (court lines, border)
//   - OBJ (sprites): ball and paddles
//
// agb sprite workflow:
//   1. Define sprite pixels via include_aseprite!() or include_gfx!() at compile time
//   2. Get an OamIterator from the GraphicsFrame each VBlank
//   3. Set position and show each sprite
//
// For now this module holds the render call structure; actual sprite data
// and tile definitions will be added once assets exist.

use crate::game::PlayState;

pub fn render(state: &PlayState) {
    draw_ball(state);
    draw_paddles(state);
}

fn draw_ball(state: &PlayState) {
    // TODO: get OamIterator from frame, create object from sprite tag, set position
    //   obj.set_x(state.ball.x as u16).set_y(state.ball.y as u16).show();
    let _ = state;
}

fn draw_paddles(state: &PlayState) {
    // TODO: same pattern as draw_ball for each paddle
    let _ = state;
}
