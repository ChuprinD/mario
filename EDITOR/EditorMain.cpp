#include "EditorMain.hpp"

//-----------------------------------------------------------------------------
// TODO convert literal const to named const

int main()
    { 
    sf::RenderWindow window(sf::VideoMode (Window_size.x, Window_size.y), "SFML");
    window.setFramerateLimit (60);

    Window = &window;

    std::vector<int>background = {};
    Background = &background;

    Background -> resize(100);
    for (int i = 0; i < Background -> size(); i++)
        Background -> at(i) = Tile_type::Tile_nothing;

    sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f {Size_grid, Size_grid});
    rectangle.setOutlineColor(sf::Color::Black);
    rectangle.setOutlineThickness(1);

    sf::Texture grounds;
    if (!grounds.loadFromFile("../resources/ground.png")) printf ("I can't load ground.png");
    grounds.setSmooth (true);

    std::vector <Animation> grounds_animations = {{&grounds, {0,   0}, {Size_grid, Size_grid}, {0, 0}, 1},
                                                  {&grounds, {Size_grid,  0}, {Size_grid, Size_grid}, {0, 0}, 1},
                                                  {&grounds, {192, 0}, {Size_grid, Size_grid}, {0, 0}, 1}};

    GameObject ground (sf::Vector2i {0, 0},  &grounds_animations, Tile_type::Tile_nothing);

    Tile_type curAnimation = Tile_type::Tile_nothing;

    while (Window -> isOpen())
        {
        bool is_click = false;

        sf::Event event;
        while (Window -> pollEvent(event))
            {
             if (event.type == sf::Event::Closed)
                Window -> close();

            if (event.type == sf::Event::MouseButtonPressed)
                {
                if (event.mouseButton.button == sf::Mouse::Left)
                    {
                    is_click = true; 
                    }
                }
            }
        Window -> clear(sf::Color (200, 200, 200));

        createGrid(ground);
        
        for (int i = 0; i < Background -> size(); i++)
            {
            ground.pos_ = sf::Vector2i {i%10 * Size_grid, i/10  * Size_grid};
            ground.curAnimation_ = Background -> at(i);
            ground.draw();
            }
        
        drawPanel(ground, rectangle);

        const sf::Vector2i mouse_pos = sf::Mouse::getPosition(*Window);
        ground.pos_ = sf::Vector2i {mouse_pos.x/Size_grid * Size_grid, mouse_pos.y/Size_grid * Size_grid};

        if (Window_size.y <= ground.pos_.x && ground.pos_.x <= Window_size.x &&
            0   <= ground.pos_.y && ground.pos_.y <= Window_size.y  && is_click)
            {
            curAnimation = updatePanel(mouse_pos);
            }

        if (0 <= ground.pos_.x && ground.pos_.x <= 864 &&
            0 <= ground.pos_.y && ground.pos_.y <= 864)
                {
                ground.curAnimation_ = curAnimation;
                ground.draw(); 
                }

        if (0 <= ground.pos_.x && ground.pos_.x <= 864 &&
            0 <= ground.pos_.y && ground.pos_.y <= 864 && is_click)
            Background -> at(mouse_pos.x / Size_grid + mouse_pos.y / Size_grid * 10) = curAnimation;

        Window -> display();
        }
        
    FILE *file = nullptr;
    fopen_s(&file, "../resources/config/level.cfg", "w");
    if (file == nullptr)
        {
        printf("I can't load level.cfg");
        return 0;
        }

    for (int i = 0; i < Background -> size(); i++)
            {
            if (i % 10 == 0 and i != 0)
                fprintf_s(file, "\n");
            fprintf_s(file, "%2ld", Background -> at(i));
            }

    fclose(file);
    }

//=============================================================================

void createGrid (GameObject ground)
    {
    ground.curAnimation_ = Tile_rubber;
    for (int x = 0; x < Window_size.y; x += Size_grid)
        for (int y = 0; y < Window_size.y; y += Size_grid)
            {
            ground.pos_ = sf::Vector2i(x, y);
            ground.draw();
            }
    }   

//=============================================================================

 void drawPanel(GameObject ground, sf::RectangleShape rectangle)
    {
    //create grass
    ground.pos_ = sf::Vector2i(970, 10);
    ground.curAnimation_ = 1;
    ground.draw();

    //create ground
    ground.pos_ = sf::Vector2i(1076, 10);
    ground.curAnimation_ = 0;
    ground.draw();

    //create rubber
    ground.pos_ = sf::Vector2i(970, 116);
    ground.curAnimation_ = 2;
    ground.draw();
    }

//=============================================================================

Tile_type updatePanel(sf::Vector2i mouse_pos)
    {
    //check grass
    if (970 <= mouse_pos.x && mouse_pos.x <= 1066 &&
        10  <= mouse_pos.y && mouse_pos.y <= 106)
        return Tile_grass;

    //check ground
    if (1076 <= mouse_pos.x && mouse_pos.x <= 1172 &&
        10   <= mouse_pos.y && mouse_pos.y <= 106)
        return Tile_ground;

    //check rubber
    if (970 <= mouse_pos.x && mouse_pos.x <= 1066 &&
        116 <= mouse_pos.y && mouse_pos.y <= 212)
        return Tile_rubber;

    return Tile_nothing;
    }

//=============================================================================