// GBA screen is 240x160 pixels
pub const SCREEN_WIDTH: i16 = 240;
pub const SCREEN_HEIGHT: i16 = 160;

pub const BALL_SIZE: i16 = 8;
pub const PADDLE_WIDTH: i16 = 8;
pub const PADDLE_HEIGHT: i16 = 24;

pub const FINAL_SCORE: u8 = 3;

pub struct Ball {
    pub x: i16,
    pub y: i16,
    pub vx: i16,
    pub vy: i16,
}

pub struct Paddle {
    pub x: i16,
    pub y: i16,
}

pub enum GravityDirection {
    Up,
    Down,
    Left,
    Right,
}

pub enum GameState {
    Title,
    Playing(PlayState),
    Winner(u8),
}

pub struct PlayState {
    pub ball: Ball,
    pub paddle1: Paddle,
    pub paddle2: Paddle,
    pub score1: u8,
    pub score2: u8,
    pub gravity: GravityDirection,
}

impl PlayState {
    pub fn new() -> Self {
        PlayState {
            ball: Ball {
                x: SCREEN_WIDTH / 2,
                y: SCREEN_HEIGHT / 2,
                vx: 2,
                vy: 1,
            },
            paddle1: Paddle { x: 8, y: SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2 },
            paddle2: Paddle { x: SCREEN_WIDTH - 8 - PADDLE_WIDTH, y: SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2 },
            score1: 0,
            score2: 0,
            gravity: GravityDirection::Down,
        }
    }

    pub fn update(&mut self) {
        self.apply_gravity();
        self.move_ball();
        self.check_wall_collisions();
        // TODO: paddle collision, scoring
    }

    fn apply_gravity(&mut self) {
        match self.gravity {
            GravityDirection::Down => self.ball.vy += 0, // TODO: add fixed-point gravity
            GravityDirection::Up => self.ball.vy -= 0,
            GravityDirection::Left => self.ball.vx -= 0,
            GravityDirection::Right => self.ball.vx += 0,
        }
    }

    fn move_ball(&mut self) {
        self.ball.x += self.ball.vx;
        self.ball.y += self.ball.vy;
    }

    fn check_wall_collisions(&mut self) {
        if self.ball.y <= 0 || self.ball.y >= SCREEN_HEIGHT - BALL_SIZE {
            self.ball.vy = -self.ball.vy;
        }
    }
}
