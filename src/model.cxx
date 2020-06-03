// YOU DEFINITELY NEED TO MODIFY THIS FILE.

#include "model.hxx"

// Constructs a model from the given `Geometry`. Note
// that the `Geometry` is passed by `const&` but `Model`
// saves its own copy of it.
//
// The `geometry_`, `paddle_`, and `ball_` member variables need
// to be initialized in an initialization list, not in the body
// of the constructor. And:
//
//   - The paddle needs to be initialized with its top-left
//     at `geometry_.paddle_top_left0()` and with dimensions
//     `geometry_.paddle_dims`. The *static factory function*
//     `Block::from_top_left(Position, Dimensions)` can be used
//     to construct the `Block` you want.
//
//   - The ball needs to be initialized with the state of the paddle
//     and the geometry.
//
// Then in the body of the constructor, we need to push_back
// `geometry_.brick_rows * geometry_.brick_cols` into the `bricks_`
// vector. In details:
//
//   - Each brick should have dimensions `geometry_.brick_dims()`
//
//   - The first (top-left-most) brick should have its top left
//     at the position {geometry_.side_margin, geometry_.top_margin}.
//
//   - You will need nested loops to create all the bricks in each
//     row and column, but note that the order doesn't matter.
//
//   - The offset between each brick and the next is given by the
//     dimensions of each brick plus `geometry_.brick_spacing`.
//     Or in other words, the x offset is `geometry_.brick_spacing.width
//     + geometry_.brick_dims().width`, and the y offset is the same
//     but with heights.
//
Model::Model(Geometry const& geometry)
        : geometry_(geometry)
        , paddle_(Block::from_top_left(geometry_.paddle_top_left0(),
                                       geometry_.paddle_dims))
        , ball_(paddle_, geometry_)
{   Block brick;
    brick = Block ::from_top_left({geometry_.side_margin , geometry_.top_margin
             }, geometry_.brick_dims());

    for(int i = 0; i < geometry_.brick_rows; ++i){
        brick.x +=  geometry_.brick_spacing.width + geometry_.brick_dims()
                .width;
        for(int j = 0; j < geometry_.brick_cols; ++j){
            brick.y +=  geometry_.brick_spacing.height + geometry_
                    .brick_dims().height;
            bricks_.push_back(brick);
        }
        brick.y = geometry_.top_margin;
    }
}

// Freebie.
void Model::launch()
{
    ball_.live_ = true;
}

// Warning! Until you write code inside these member functions
// that uses at least one member variable, CLion is likely to
// insist that you can make this function static. Don’t believe
// it! You’ll regret the change if you do once you want to
// access member variables, since a static member function
// doesn’t have access to an instance. (You should delete this
// warning after you’ve read it.)
//
// TL;DR: Don't go adding `static` to members.

// If the ball isn't live then you need to make it track the paddle,
// which is best done by constructing a new `Ball` and assigning it to
// `ball_`.
void Model::paddle_to(int x)
{
    paddle_.x = x;
    if(!ball_.live_ ){
        ball_ = Ball(paddle_,
                geometry_);
    }
}

// The description in model.hxx is pretty detailed. I'm not sure
// what else I can say. You probably just want to call
// `Ball::next() const` twice: once speculatively as soon as you
// know the ball's live, and again at the end, storing the result
// back to the ball that time.
void Model::update(int boost)
{
    if(ball_.live_){
        Ball ball(ball_.next());
        if(ball.hits_bottom(geometry_)){
            ball_.live_ = false;
            ball_ = Ball(paddle_,geometry_);
            return;
        }
        if(ball.hits_top(geometry_)){
            ball_.reflect_vertical();
        }
        if(ball.hits_side(geometry_)){
            ball_.reflect_horizontal();
        }
        if (ball.destroy_brick(bricks_)){
            ball_.reflect_horizontal();
            ball_.reflect_vertical();
        }
        if (ball.hits_block(paddle_)){
            ball_.reflect_vertical();
            ball_.velocity_.width += boost;
        }
        ball_ = ball_.next();
    }
}
