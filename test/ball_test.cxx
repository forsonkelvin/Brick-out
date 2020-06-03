#include "ball.hxx"
#include "model.hxx"
#include <catch.hxx>

Block const paddle{100, 400, 100, 20};

TEST_CASE("Ball::Ball")
{
    Geometry geometry;
    Ball ball(paddle, geometry);

    CHECK( ball.center_.x == 150 );
    CHECK( ball.center_.y == 394 );
}

TEST_CASE("Ball::hits_side")
{
    Geometry geometry;
    Ball ball(paddle, geometry);

    CHECK_FALSE( ball.hits_side(geometry) );
    ball.center_.x = 1;
    CHECK( ball.hits_side(geometry) );
    ball.center_.x = geometry.scene_dims.width - 1;
    CHECK( ball.hits_side(geometry) );
    ball.center_.x = geometry.scene_dims.width / 2;
    CHECK_FALSE( ball.hits_side(geometry) );
}
