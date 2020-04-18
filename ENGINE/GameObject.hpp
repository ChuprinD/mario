#pragma once

#include "../include/config.hpp"
#include "../ENGINE/Engine.hpp"
#include "Animation.hpp"

const int Animation_Nothing = -1;

class GameObject
    {
    public:
        sf::Vector2i pos_;
        std::vector <Animation> animations_;
        int curAnimation_;

        GameObject (sf::Vector2i pos, std::vector <Animation>* animations, int curAnimation):
            pos_ (pos),
            animations_ ((animations)? *animations : std::vector <Animation> ()),
            curAnimation_ (curAnimation)
            {}

        void control();
        void physics();
        void draw();
        void setOrigin (sf::Vector2f origin);
    };

void draw_rect(sf::Vector2i pos, sf::Vector2i size);
void draw_origin(sf::Vector2f pos, int radius);