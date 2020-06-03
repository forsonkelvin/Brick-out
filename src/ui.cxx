// YOU DEFINITELY NEED TO MODIFY THIS FILE.

#include "ui.hxx"

///
/// VIEW CONSTANTS
///

// Colors are red-green-blue(-alpha), each component
// from 0 to 255.
ge211::Color const ball_color    {255, 127, 127};
ge211::Color const paddle_color  {255, 255, 127};
ge211::Color const brick_color   {100, 100, 100};

///
/// VIEW FUNCTIONS
///

// Data members that are references cannot be initialized by assignment
// in the constructor body and must be initialized in a member
// initializer list.
Ui::Ui(Model& model)
        : model_(model)
{ }

ge211::Dimensions Ui::initial_window_dimensions() const
{
    return model_.geometry_.scene_dims;
}

// Use `Sprite_set::add_sprite(Sprite&, Position)` to add each sprite
// to `sprites`.
void Ui::draw(ge211::Sprite_set& sprites)
{
   sprites.add_sprite(ball_sprite_,model_.ball_.top_left());
   sprites.add_sprite(paddle_sprite_,model_.paddle_.top_left());
   for(Block brick: model_.bricks_){
       sprites.add_sprite(brick_sprite_, brick.top_left());
   }

}

///
/// CONTROLLER FUNCTIONS
///

// You can get a `Key` representing space with `ge211::Key::code(' ')`.
void Ui::on_key(ge211::Key key)
{
    if (key == ge211::Key::code('q'))
        quit();
    if (key == ge211::Key::code(' '))
        model_.launch();
}

// To get a random number, you should use a `ge211::Random` object,
// which provides the member function
//
//     int ge211::Random::between(int min, int max);
//
// which returns a random `int` from the closed interval [min, max].
//
// So how can we get access to a `ge211::Random` object? Our base class
// `ge211::Abstract_game` constructs and stores one for us, granting us
// by-reference access via its `get_random()` member function [1]. Hence,
//
//     get_random().between(10, 20)
//
// returns a random number between 10 and 20.
//
// [1] That may look like a free function call, not a member function
//     call, but it's actually being called on `this`, since members
//     of a base class (from which we derived our struct) are also
//     members of our struct.
//
void Ui::on_frame(double)
{
    int boost = get_random().between(-model_.geometry_.max_boost, model_
    .geometry_
    .max_boost );

    model_.update(boost);
}

// Makes the ball live via `Model::launch()`.
void Ui::on_mouse_up(ge211::Mouse_button, ge211::Position)
{
    model_.launch();
}

// Informs the model of the mouse position (and thus the desired paddle
// position) via `Model::paddle_to(Position)`.
void Ui::on_mouse_move(ge211::Position position)
{
    model_.paddle_to(position.x);
}
