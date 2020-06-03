#include "model.hxx"
#include <catch.hxx>

TEST_CASE("play the game")
{
    Geometry geometry;
    Model m(geometry);
    CHECK( m.bricks_.size() == 100 );

    m.ball_.live_ = true;
    Ball old_ball = m.ball_;

    m.update(0);
    CHECK( m.ball_.center_ == old_ball.center_ + old_ball.velocity_ );

    m.update(0);
    CHECK( m.ball_.center_ == old_ball.center_ + 2 * old_ball.velocity_ );

    m.update(0);
    CHECK( m.ball_.center_ == old_ball.center_ + 3 * old_ball.velocity_ );
}

TEST_CASE("destroy one brick")
{
    Geometry geometry;
    Model m(geometry);
    m.bricks_.clear();
    m.bricks_.push_back({250, 200, 100, 20});
    m.ball_.live_ = true;
    m.ball_.center_ = {300, 400};
    m.ball_.velocity_ = {0, -50};

    Ball ball(m.ball_);

    m.update(0);
    ball = ball.next();
    CHECK( m.ball_ == ball );

    m.update(0);
    ball = ball.next();
    CHECK( m.ball_ == ball );

    m.update(0);
    ball = ball.next();
    CHECK( m.ball_ == ball );
    CHECK( m.bricks_.size() == 1 );

    m.update(0);
    ball.velocity_ *= -1;
    ball = ball.next();
    CHECK( m.ball_ == ball );
    CHECK( m.bricks_.empty() );
}

TEST_CASE("Paddle and the ball") {

    Geometry geometry;
    Model m(geometry);
    m.bricks_.clear();
    CHECK(m.ball_.center_.x == m.paddle_.x + m.paddle_.width / 2);


    m.paddle_to(100);
    CHECK(m.paddle_.x == 100);
    CHECK(m.ball_.center_.x == m.paddle_.x + m.paddle_.width / 2);

    m.paddle_to(m.geometry_.scene_dims.width);
    //CHECK(m.paddle_.x == m.geometry_.scene_dims.width - m.paddle_.width);
    CHECK(m.ball_.center_.x == m.paddle_.x + m.paddle_.width / 2);

}
TEST_CASE("Destroy Several Bricks"){

    Geometry geometry;
    Model m(geometry);
    m.bricks_.clear();
    m.bricks_.push_back({250, 200, 100, 20});
    m.bricks_.push_back({400, 200, 100, 20});
    m.bricks_.push_back({600, 200, 100, 20});
    m.ball_.live_ = true;
    m.ball_.center_ = {300, 400};
    m.ball_.velocity_ = {0, -50};
    Ball ball(m.ball_);

    m.update(0);
    ball = ball.next();
    CHECK( m.ball_ == ball );

    m.update(0);
    ball = ball.next();
    CHECK( m.ball_ == ball );

    m.update(0);
    ball = ball.next();
    CHECK( m.ball_ == ball );
    CHECK( m.bricks_.size() == 3 );

    m.update(0);
    ball.velocity_ *= -1;
    ball = ball.next();
    CHECK( m.ball_ == ball );
    CHECK_FALSE( m.bricks_.empty() );

}
TEST_CASE("Hitting top and bottom"){

    Geometry geometry;
    Model m(geometry);
    m.bricks_.clear();
    m.paddle_to(100);

    m.ball_.live_ = true;
    m.ball_.center_.y = m.geometry_.scene_dims.height - m.ball_.radius_ + 1;
    m.ball_.reflect_vertical();
    CHECK(m.ball_.hits_bottom(m.geometry_));
    m.update(0);
    CHECK_FALSE(m.ball_.live_);
    CHECK(m.ball_.center_.x == m.paddle_.x + m.paddle_.width / 2);

    CHECK_FALSE( m.ball_.hits_side(geometry) );
    m.ball_.live_ = true;
    m.ball_.center_.x = 1;
    CHECK( m.ball_.hits_side(geometry) );
    m.ball_.center_.x = geometry.scene_dims.width + 100;
    m.ball_.reflect_horizontal();
    ge211::Dimensions vel = m.ball_.velocity_;
    CHECK( m.ball_.hits_side(geometry) );
    m.update(0);
    CHECK(m.ball_.velocity_.width == -vel.width );
    m.ball_.center_.x = geometry.scene_dims.width / 2;
    CHECK_FALSE( m.ball_.hits_side(geometry) );

}
