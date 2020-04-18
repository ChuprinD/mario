#include "Animation.hpp"

//-----------------------------------------------------------------------------

void Animation::draw(sf::Vector2i pos)
    {
    sprite_.setTextureRect (sf::IntRect(pos_.x * 256 + frame_/speed_ * size_.x, pos_.y * 256, size_.x, size_.y));
    sprite_.setPosition (float (pos.x + difference_pos_.x), float (pos.y + difference_pos_.y));

    Window -> draw(sprite_);

    frame_++;
    frame_ %= (nFrames_ * speed_);
    }