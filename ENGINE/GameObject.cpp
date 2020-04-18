#include "GameObject.hpp"

//-----------------------------------------------------------------------------

bool intersection (sf::IntRect rect1, sf::IntRect rect2);
sf::IntRect rectFrom (sf::Vector2i pos, sf::Vector2i size);

//-----------------------------------------------------------------------------

void GameObject::control()
    {
    const sf::Vector2i tile  = sf::Vector2i{int(pos_.x / Size_grid), int(pos_.y / Size_grid)};   
        
    sf::Vector2f origin_pos = {animations_[curAnimation_].sprite_.getOrigin().x + pos_.x, animations_[curAnimation_].sprite_.getOrigin().y + pos_.y};
    draw_origin (origin_pos, 5);
    draw_rect (config_, animations_[curAnimation_].pos_, animations_[curAnimation_].nFrames_, animations_[curAnimation_].frame_, pos_);
    //draw_rect (sf::Vector2i(0, 0), sf::Vector2i(100, 100));

    const sf::IntRect object = rectFrom(animations_[curAnimation_].pos_, animations_[curAnimation_].size_);

    const sf::IntRect bottom = rectFrom(pos_, animations_[curAnimation_].size_);
    const sf::IntRect left   = rectFrom(sf::Vector2i{(tile.x - 1) * Size_grid, tile.y * Size_grid}, sf::Vector2i(Size_grid, Size_grid));
    const sf::IntRect right  = rectFrom(sf::Vector2i{(tile.x + 1) * Size_grid, tile.y * Size_grid}, sf::Vector2i(Size_grid, Size_grid));

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && intersection(object, bottom))
        {
        curAnimation_ = 4;//!!!0
        pos_.y -= 144;
        }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && intersection(object, left))
        {
        curAnimation_ = 5;
        pos_.x -= 15;
        }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && intersection(object, right))
        {
        curAnimation_ = 4;
        pos_.x += 15;
        }
    }

//========================================================================================================

void GameObject::physics()
    {    
    const int magicVariable = 2;
    if (Background -> at(int (pos_.x / Size_grid) + int ((pos_.y + animations_[0].size_.y / 2 - magicVariable) / Size_grid) * 10) == -1)
        {
        pos_.y += 20;
        curAnimation_ = 6;
        }
    else
        {
        curAnimation_ = 3;
        }
    }

//========================================================================================================

void GameObject::draw()
    {
    if (curAnimation_ != Animation_Nothing)
        animations_[curAnimation_].draw(pos_);
    }

//========================================================================================================

void GameObject::setOrigin(sf::Vector2f origin)
    {
    for (int i = 0; i < animations_.size(); i++)
        {
        animations_[i].sprite_.setOrigin(origin);
        }
    }

//========================================================================================================

bool intersection (sf::IntRect rect1, sf::IntRect rect2)
    {
    const int left    = std::max(rect1.left, rect2.left);
    const int top     = std::min(rect1.top, rect2.top);
    const int right   = std::min(rect1.left + rect1.width, rect2.left + rect2.width);
    const int bottom  = std::max(rect1.top - rect1.height, rect2.left - rect2.height);

    const int width = right - left;
    const int height = top - bottom;

    if (width < 2 || height < 2)
        return true;

    return false;
    }

//========================================================================================================

sf::IntRect rectFrom (sf::Vector2i pos, sf::Vector2i size)
    {
    return sf::IntRect(pos, size);
    }

//========================================================================================================

void draw_rect(Config config, sf::Vector2i posAnimation, int nFrames, int frame, sf::Vector2i pos)
    {
    $_(frame); $(posAnimation.y);
    sf::IntRect cur = config.hitboxes[frame + posAnimation.x + posAnimation.y * nFrames];
    sf::RectangleShape recTile;
    recTile.setSize(sf::Vector2f{float (cur.width), float (cur.height)});
    recTile.setFillColor(sf::Color::Color(0, 0, 0, 0));
    recTile.setOutlineThickness(1);
    recTile.setOutlineColor(sf::Color::Red);
    recTile.setPosition(sf::Vector2f{float (cur.left + pos.x), float(cur.top + pos.y)});
    Window -> draw(recTile);
    }

void draw_origin(sf::Vector2f pos, int radius)
    {
    sf::CircleShape origin;
    origin.setPosition(pos);
    origin.setFillColor(sf::Color::Red);
    origin.setRadius(float (radius));
    origin.setOrigin(float (radius), float (radius));
    Window -> draw(origin);
    }