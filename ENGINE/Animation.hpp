#pragma once

#include "../include/SFML.hpp"
#include "../ENGINE/Engine.hpp"

class Animation
    {
    public:
        sf::Texture* texture_;
        sf::Sprite sprite_;

        sf::Vector2i pos_, size_;
        sf::Vector2i difference_pos_;
        int frame_;
        int nFrames_;
        int speed_;

        Animation ():
            texture_ (nullptr),
            pos_ ({-1, -1}),
            size_ ({-1, -1}),
            difference_pos_ ({0, 0}),
            sprite_ (),
            frame_ (0),
            nFrames_ (0),
            speed_ (1)
            {}

        Animation (sf::Texture* texture, sf::Vector2i pos, sf::Vector2i size, sf::Vector2i difference_pos, int nFrames, int speed = 1):
            texture_ (texture),
            pos_ (pos),
            size_ (size),
            sprite_ (*texture),
            difference_pos_ (difference_pos),
            frame_ (0),
            nFrames_ (nFrames),
            speed_ (speed)
            {
            }

        void draw(sf::Vector2i pos);
    };
