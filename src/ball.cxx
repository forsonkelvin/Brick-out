// YOU DEFINITELY NEED TO MODIFY THIS FILE.

#include "ball.hxx"
#include "geometry.hxx"

// Computes where the ball should be when it's stuck to the paddle:
// centered above it, 1 pixel up.
static ge211::Position above_block(Block const& block,
                                   Geometry const& geometry)
{
    return block.top_left().right_by(block.width * 0.5).up_by(1 + geometry.ball_radius);
}

// It won't compile without this, so you get it for free.
Ball::Ball(Block const& paddle, Geometry const& geometry)
        : radius_   (geometry.ball_radius)
        , velocity_ (geometry.ball_velocity0)
        , center_   (above_block(paddle, geometry))
        , live_     (false)
{ }

ge211::Position Ball::top_left() const
{
    return {center_.x - radius_, center_.y - radius_};
}

bool Ball::hits_bottom(Geometry const& geometry) const
{
    return (center_.y + radius_) > geometry.scene_dims.height;
}

bool Ball::hits_top(Geometry const&) const
{
    return (center_.y - radius_) < 0;
}

bool Ball::hits_side(Geometry const& geometry) const
{
    return (center_.x - radius_) < 0 || (center_.x + radius_) > geometry
    .scene_dims.width;
}

Ball Ball::next() const
{
    Ball result(*this);
    result.center_ += velocity_;
    return result;
}

bool Ball::hits_block(Block const& block) const
{
    return !(block.bottom_right().y < top_left().y ||
    block.bottom_right().x < top_left().x ||
    center_.x + radius_ < block.top_left().x ||
    center_.y + radius_ < block.top_left().y);
}

void Ball::reflect_vertical()
{
    velocity_.height *= -1;
}

void Ball::reflect_horizontal()
{
    velocity_.width *= -1;
}

bool Ball::destroy_brick(std::vector<Block>& bricks) const
{
    for(Block& block: bricks){
        if(hits_block(block)){
            std::swap( block, bricks.back());
            bricks.pop_back();
            return true;
        }
    }
    return false;
}

bool operator==(Ball const& b1, Ball const& b2)
{
    return ((b1.radius_ == b2.radius_) && (b1.center_ == b2.center_) && (b1
    .velocity_ == b2.velocity_) && (b1.live_ == b2.live_));
}

bool operator!=(Ball const& b1, Ball const& b2)
{
    return !(b1 == b2);
}
