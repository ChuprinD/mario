#pragma once

//-----------------------------------------------------------------------------

#include "../include/SFML.hpp"
#include "../include/config.hpp"
#include "../ENGINE/Engine.hpp"
#include "../ENGINE/GameObject.hpp"                                           

//-----------------------------------------------------------------------------

enum Tile_type {Tile_nothing = -1, Tile_ground = 0, Tile_grass = 1, Tile_rubber = 2};

//-----------------------------------------------------------------------------

void createGrid (GameObject ground);
void drawPanel (GameObject ground, sf::RectangleShape rectangle);
Tile_type updatePanel (sf::Vector2i mouse_pos);
