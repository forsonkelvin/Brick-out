/*******************************************/
/*** DO NOT CHANGE ANYTHING IN THIS FILE ***/
/*******************************************/

// Defines a struct for modeling the ball.

#pragma once

#include "geometry.hxx"
#include <ge211.hxx>

// We will represent blocks (the bricks and the paddle) as GE211
// `Rectangle`s. This is a struct that could be defined like so:
//
//     struct Rectangle
//     {
//         int x;  // x coordinate of left side
//         int y;  // y coordinate of top
//         int width;
//         int height;
//     };
using Block = ge211::Rectangle;

// This struct is used to represent the state of the ball. In particular, we
// need to know how big the ball is (radius_), whether it's moving or
// stopped (live_), where it is (center_), and where it's going (velocity_).
//
// Note that `velocity_` is a ge211::Dimensions, which means it has two
// `int` member variables, `width` and `height`, which are the rates of
// change in the x and y dimensions, respectively. In particular, in
// each "frame" `center_` gets shifted by `velocity_`. A `Dimensions`
// added to a `Position` yields a shifted `Position`, so this may be
// written as
//
//     a_ball.position_ += a_ball.velocity_;
//
struct Ball
{
    ///
    /// CONSTRUCTOR
    ///

    // Constructs a new ball. It needs to know where the paddle is (so it
    // can position itself right above it), and the geometry (which includes
    // the ball's radius and initial velocity). The ball starts dead--not
    // moving and positioned 1 pixel above the center of the paddle.
    //
    // In addition to constructing the ball in the model in the first place,
    // this can also be used to reset the ball by creating a new ball to
    // assign over it:
    //
    //     ball_ = Ball(paddle_, geometry_);
    Ball(Block const& paddle, Geometry const&);

    ///
    /// MEMBER FUNCTIONS
    ///

    // Returns the position of the top-left corner of the ball's "bounding
    // box", meaning the smallest rectangle in which is can be enclosed.
    // This is useful to the UI because sprites are positioned based on
    // their top-left corners.
    ge211::Position top_left() const;

    // Returns a new ball like this one but whose position has been
    // updated by adding on the velocity. This is useful because the
    // model's algorithm for collision detection involves speculatively
    // moving the ball and checking where it would end up, before
    // actually moving it.
    //
    // This can also be used to actually move it, via assignment:
    //
    //    ball_ = ball_.next();
    //
    Ball next() const;

    // These functions all perform collision detection by telling us whether
    // this ball is *past* the given edge.
    bool hits_top(Geometry const&) const;
    bool hits_bottom(Geometry const&) const;
    bool hits_side(Geometry const&) const;

    // Collision detection for blocks. Returns whether the circle's
    // bounding box intersects with the given block.
    //
    // Intersection between a circle and a rectangle is tricky, so we
    // will approximate it with the intersection of two rectangles.
    bool hits_block(Block const&) const;

    // Collision detection between the ball and the whole vector of bricks.
    // If the ball collides with some brick then that brick is removed and
    // the functions returns true. (The ball may collide with more than
    // one brick, but the function should return after the first collision
    // is found.) If there is no collision then the function returns false.
    bool destroy_brick(std::vector<Block>& bricks) const;

    // Negates the vertical component of this ball's velocity.
    void reflect_vertical();

    // Negates the horizontal component of this ball's velocity.
    void reflect_horizontal();

    ///
    /// MEMBER VARIABLES
    ///

    // The radius of the ball.
    int               radius_;

    // The velocity of the ball in pixels per tick.
    ge211::Dimensions velocity_;

    // The position of the center of the ball.
    ge211::Position   center_;

    // Whether the ball is moving freely (true) or stuck to the top of the
    // paddle (false).
    bool              live_;
};

// Compares two `Ball`s for equality. This may be useful for testing.
//
// Two `Ball`s are equal if all their member variables are pairwise
// equal.
bool operator==(Ball const&, Ball const&);

// Inequality for `Ball`s.
bool operator!=(Ball const&, Ball const&);

