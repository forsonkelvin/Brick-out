// IT MIGHT BE OKAY TO MODIFY THIS FILE, BUT YOU PROBABLY DON'T
// WANT TO.
//
// Defines the structure and resources of the user interface.
//

#pragma once

#include "model.hxx"
#include <ge211.hxx>

///
/// VIEW CONSTANTS
///

// These constants are defined in `ui.cpp` but declared here so that
// we care refer to them when initializing the sprites below.
//
// The keyword `extern` is what prevents this declaration from being
// a definition. That is, this declaration informs subsequent code about
// the existence of these constants without actually defining them here.
extern ge211::Color const ball_color, paddle_color, brick_color;

///
/// MAIN UI STRUCT
///

struct Ui : ge211::Abstract_game
{
    ///
    /// CONSTRUCTOR
    ///

    // Constructs a `Ui` given a reference to the model that stores
    // the actual state of the game.
    //
    // The word `explicit` means that this constructor doesn't define an
    // implicit conversion whereby you could pass a `Model` to a function
    // that expects a `Ui` and have it work.
    explicit Ui(Model&);

    ///
    /// MEMBER FUNCTIONS (for the view)
    ///

    // Returns the size of the window as given by `geometry_.scene_dims`.
    //
    // (GE211 calls this to find out how big to make the window.)
    ge211::Dimensions initial_window_dimensions() const override;

    // Renders all the game entities to the screen. In particular,
    // ball_sprite_ is placed at the ball's bounding box's top-left,
    // paddle_sprite_ is placed where the model says the paddle is,
    // and brick_sprite_ is placed for each brick in model_.bricks.
    void draw(ge211::Sprite_set&) override;

    ///
    /// MEMBER FUNCTIONS (for the controller)
    ///

    // Defines how the game responds to key events. There are two keys
    // recognized:
    //
    //  - On 'q', quits.
    //
    //  - On ' ', tells the model to launch the ball.
    void on_key(ge211::Key) override;

    // Defines how the game responds to mouse clicks (which is by telling
    // the model to launch the ball).
    void on_mouse_up(ge211::Mouse_button, ge211::Position) override;

    // Defines how the game responds to mouse motion (which is by telling
    // the model to change the x coordinate of the paddle).
    void on_mouse_move(ge211::Position) override;

    // Updates the model to reflect the passage of time, by calling
    // `Model::update`.
    //
    // While this function is passed `dt`, the elapsed time in seconds since the
    // previous frame, we aren't using that for now.
    //
    // Instead, the main job of `on_frame` is to pick a random `int` to
    // pass to `Model::update(int)`, which uses that `int` to "boost"
    // the velocity of the ball if it should happen to hit the paddle
    // during this frame. The `int` passed to `Model::update(int)` should
    // be chosen randomly from the closed interval
    //
    //     [ -model_.geometry_.max_boost, model_.geometry_.max_boost ].
    //
    void on_frame(double dt) override;

    ///
    /// MEMBER VARIABLE (model reference)
    ///

    // This is a reference to the model. It means that the UI doesn't
    // own the model but has access to it. Thus, the client of the UI
    // (brick_out.cpp) must create a `Model` first and then pass that by
    // reference to the `Ui` constructor.
    Model& model_;

    ///
    /// MEMBER VARIABLES (for the view)
    ///

    // These three definitions create the sprites that we need to
    // display the circle, the paddle, and the bricks to the screen.
    // Each depends on the geometry, which it can access via the `model_`
    // member variable. Member variables are initialized in order, which
    // means that `model_` will be properly initialized before we use it
    // here.

    ge211::Circle_sprite    const
            ball_sprite_    {model_.geometry_.ball_radius,  ball_color};

    ge211::Rectangle_sprite const
            paddle_sprite_  {model_.geometry_.paddle_dims, paddle_color};

    ge211::Rectangle_sprite const
            brick_sprite_   {model_.geometry_.brick_dims(), brick_color};
};
