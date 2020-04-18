#pragma once

#include "../include/config.hpp"
#include "../ENGINE/Engine.hpp"
#include "Animation.hpp"
#include <vector>

const int Animation_Nothing = -1;

struct Config
    {
    std::vector <sf::IntRect> hitboxes = {};
    };

class GameObject
    {
    public:
        sf::Vector2i pos_;
        std::vector <Animation> animations_;
        int curAnimation_;
        Config config_;

        GameObject (sf::Vector2i pos, std::vector <Animation>* animations, int curAnimation, Config config):
            pos_ (pos),
            animations_ ((animations)? *animations : std::vector <Animation> ()),
            curAnimation_ (curAnimation),
            config_ (config)
            {}

        void control();
        void physics();
        void draw();
        void setOrigin (sf::Vector2f origin);
    };

void draw_rect(Config config, sf::Vector2i posAnimation, int nFrames, int frame, sf::Vector2i pos);
void draw_origin(sf::Vector2f pos, int radius);