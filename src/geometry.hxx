/*******************************************/
/*** DO NOT CHANGE ANYTHING IN THIS FILE ***/
/*******************************************/

// Defines a struct to hold model geometry parameters. You should try
// different values to ensure that your model and UI adjust
// appropriately. You can do this by creating an instance and then assigning
// its parameters before constructing a `Model`:
//
//     Geometry geometry;
//     geometry.brick_cols = 15;
//     geometry.ball_radius *= 2;
//     Model model(geometry);
//

#pragma once

#include <ge211.hxx>

struct Geometry
{
    // Constructs an instance with the default parameters.
    Geometry() noexcept;

    // The dimensions of the whole window:
    ge211::Dimensions scene_dims;

    // The dimensions of the paddle (the block at the bottom):
    ge211::Dimensions paddle_dims;

    // Number of columns of bricks:
    int brick_cols;

    // Number of rows of bricks:
    int brick_rows;

    // The number of pixels of space between each column and row of
    // bricks:
    ge211::Dimensions brick_spacing;

    // The radius of the ball:
    int ball_radius;

    // The ball's initial velocity {width, height}:
    ge211::Dimensions ball_velocity0;

    // The maximum amount that bouncing off the paddle boosts the ball's x
    // velocity component:
    int max_boost;

    // Number of pixels from top of screen to top of brick formation:
    int top_margin;

    // Number of pixels from sides of screen to sides of brick formation:
    int side_margin;

    // Number of pixels from *top* of screen to *bottom* of brick formation.
    int brick_depth;

    // Number of pixels from bottom of screen to bottom of paddle.
    int bottom_margin;

    // The initial position of the paddle. This is a member function because
    // it's computed from the other properties.
    ge211::Position paddle_top_left0() const noexcept;

    // The dimensions of each brick. Also computed from the other properties.
    //
    // PRECONDITIONS (asserted):
    //  - brick_cols > 0
    //  - brick_rows > 0
    ge211::Dimensions brick_dims() const noexcept;
};

