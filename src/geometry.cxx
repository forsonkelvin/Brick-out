/*******************************************/
/*** DO NOT CHANGE ANYTHING IN THIS FILE ***/
/*******************************************/

#include "geometry.hxx"

// This is the default (and only) constructor for `Geometry`. It determines
// all the default values of all the member variables.
Geometry::Geometry() noexcept
        : brick_cols     {   10 }
        , brick_rows     {   10 }
        , top_margin     {  100 }
        , side_margin    {  170 }
        , brick_depth    {  300 }
        , bottom_margin  {   50 }
        , ball_radius    {    5 }
        , max_boost      {    4 }
        , ball_velocity0 {    3, -10 }
        , brick_spacing  {   10,   5 }
        , scene_dims     { 1024, 768 }
        , paddle_dims    {  100,  20 }
{ }

ge211::Position Geometry::paddle_top_left0() const noexcept
{
    return { scene_dims.width / 2,
             scene_dims.height - bottom_margin - paddle_dims.height };
}

// Computes how large each brick can be (in a given dimension), given the
// total number of pixels available in that dimension, the number of bricks
// in that dimensions, and the number of space pixels to leave in between.
//
// PRECONDITION: divisor > 0
static int div_w_spacing(int total, int divisor, int space)
{
    if (divisor > 0)
        return (total - (divisor - 1) * space) / divisor;

    throw ge211::Client_logic_error("need at least 1 row & 1 column");
}

// Computes the dimensions of each brick from the other parameters.
ge211::Dimensions Geometry::brick_dims() const noexcept
{
    ge211::Dimensions field{scene_dims.width - 2 * side_margin,
                            brick_depth - top_margin};
    int width  = div_w_spacing(field.width, brick_cols, brick_spacing.width);
    int height = div_w_spacing(field.height, brick_rows, brick_spacing.height);
    return {width, height};
}


