#ifndef GAME_PHYSICS_STRUCTS
#define GAME_PHYSICS_STRUCTS

typedef enum COLLISION_DIRECTION  {
    noCollision = -1,
    nCollision = 0,
    nECollision,
    eCollision,
    sECollision,
    sCollision,
    sWCollision,
    wCollision,
    nWCollision
}CollisionDirection;

typedef enum GRAVITY_DIRECTION {
    noGravity = 8,
    northGravity = 2,
    northEastGravity = 1,
    eastGravity = 0,
    southEastGravity = 7,
    southGravity = 6,
    southWestGravity = 5,
    westGravity = 4,
    northWestGravity = 3
} GravityDirection;

//#define USE_FRICTION
// friction = 0.1
#ifdef TARGET_C64
#define FRICTION FPMAKE(1,0)
#define PADDLE_FROM_BALL_CONTRIBUTION FPMAKE(1,0)
#define BALL_PADDLE_FRICTION FPMAKE(0,12)
#define PADDLE_BOUNCINESS FPMAKE(0, 12)
#define COURT_PADDLE_BOUNCINESS FPMAKE(0, 9)
#define BALL_BOUNCINESS FPMAKE(0,6)
#define MAX_BALL_SPEED_X FPMAKE(2,0)
#define MAX_BALL_SPEED_Y FPMAKE(2,0)
#define MIN_BALL_SPEED_X (-1*MAX_BALL_SPEED_X)
#define MIN_BALL_SPEED_Y (-1*MAX_BALL_SPEED_Y)
#define MAX_INITIAL_BALL_SPEED_X FPMAKE(0, 14)
#define MAX_INITIAL_BALL_SPEED_Y FPMAKE(0, 7)
#define MIN_INITIAL_BALL_SPEED_X (-1*MAX_INITIAL_BALL_SPEED_X)
#define MIN_INITIAL_BALL_SPEED_Y (-1*MAX_INITIAL_BALL_SPEED_Y)
#define MAX_PADDLE_SPEED_X FPMAKE(1,0)
#define MAX_PADDLE_SPEED_Y FPMAKE(1,0)
#define MIN_PADDLE_SPEED_X (-1*MAX_PADDLE_SPEED_X)
#define MIN_PADDLE_SPEED_Y (-1*MAX_PADDLE_SPEED_Y)
#define BASE_GRAVITY FPMAKE(0,1)


#else
#define FRICTION 0xf332
#endif





#endif
