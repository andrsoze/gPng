#ifndef COMMON_TEST_H
#define COMMON_TEST_H

typedef enum START_STATE {
    straightLeft = 0,
    straightRight,
    straightLeftPaddleTopCollision,
    straightLeftPaddleBottomCollision,
    straightLeftPaddleNonTopCollision,

    straightRightPaddleTopCollision,
    straightRightPaddleBottomCollision,
    straightRightNonTopCollision,

    straightRightPaddleRearCollision,
    straightLeftPaddleRearCollision,
    //graphics tests
    paddlesMaxHorizontal = 32,
    paddlesMaxNorth = 33,
    paddlesMaxSouth = 34,
    noStartState = 99
} StartState;


#endif
