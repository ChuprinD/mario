
#include "GameMain.hpp"

int main()
    {
    sf::RenderWindow window(sf::VideoMode (Window_size.y, Window_size.y), "SFML");
    window.setFramerateLimit (30);

    Window = &window;

    std::vector<int>background = {};
    Background = &background;
    
    sf::Texture marios;
    if (!marios.loadFromFile ("../resources/mario.png")) printf ("I can't load mario.png");
    marios.setSmooth (true);                        

    enum mario_types_animation {m_jump, m_rotation_right, m_stars, m_stay, m_runR, m_runL, m_fall};

    sf::Texture stars;
    if (!stars.loadFromFile ("../resources/stars.png")) printf ("I can't load stars.png");
    stars.setSmooth (true);

    sf::Texture frogs;
    if (!frogs.loadFromFile ("../resources/frogs.png")) printf ("I can't load frogs.png");
    frogs.setSmooth (true);

    enum frog_types_animation {f_jump, f_star, f_rotation_right};

    sf::Texture grounds;
    if (!grounds.loadFromFile("../resources/ground.png")) printf ("I can't load ground.png");
    grounds.setSmooth (true);

    enum ground_types_animation {g_set_ground, g_set_grass};

    std::vector <Animation> marios_animations = {{&marios, {0       , 256 * 10}, {256, 256}, {0,    0}, 12},
                                                 {&marios, {0       , 256 * 12}, {256, 256}, {0,    0}, 12},
                                                 { &stars, {0       ,        0}, {35 ,  35}, {0, -100},  6},
                                                 {&marios, {0       , 256 *  0}, {256, 256}, {0,    0}, 16},
                                                 {&marios, {0       , 256 *  4}, {256, 256}, {0,    0}, 16},
                                                 {&marios, {0       , 256 *  5}, {256, 256}, {0,    0}, 16},
                                                 {&marios, {11 * 256, 256 *  2}, {256, 256}, {0,    0},  4}};

    std::vector <Animation> frogs_animations = {{&frogs, {0, 0}, {100, 100}, {0,   0},  4, 3},
                                                {&stars, {0, 0}, { 35,  35}, {0, -50},  6, 3}};

    std::vector <Animation> grounds_animations = {{&grounds, {0,  0}, {Size_grid, Size_grid}, {0, 0}, 1}, {&grounds, {Size_grid, 0}, {Size_grid, Size_grid}, {0, 0}, 1}, {&grounds, {192, 0}, {Size_grid, Size_grid}, {0, 0}, 1}};

    GameObject mario  (sf::Vector2i {600, 10}, &marios_animations, mario_types_animation::m_stay);
    GameObject frog   (sf::Vector2i {800, 551},  &frogs_animations, frog_types_animation::f_jump);
    GameObject ground (sf::Vector2i {0, 0},  &grounds_animations, ground_types_animation::g_set_ground);

   // mario.setOrigin (sf::Vector2f {256 / 2, 256 / 2});
   // frog.setOrigin (sf::Vector2f {100 / 2, 100 / 2});
    
    FILE *file = nullptr;
    fopen_s(&file, "../resources/config/level.cfg", "r");
    if (file == nullptr)
        {
        printf ("I can't open level.cfg");
        return 0;
        }

    Background -> resize(0);
    bool is_level_clear = true;

    for (int i = 0; i < 100; i++)
        {
        int type_grass;
        fscanf_s(file, "%2i", &type_grass);
        if (type_grass != -1)
            is_level_clear = false;
        Background -> push_back(type_grass);
        }

    fclose(file);

    if (is_level_clear)
        {
        fopen_s(&file, "../resources/config/default_level.cfg", "r");
        if (file == nullptr)
            {
            printf ("I can't open default_level.cfg");
            return 0;
            }

        Background -> resize(0);

        for (int i = 0; i < 100; i++)
                {
                int type_grass;
                fscanf_s(file, "%2i", &type_grass);
                Background -> push_back(type_grass);
                }

        fclose(file);
        } 

    while (Window -> isOpen())
        {
        sf::Event event;
        while (Window -> pollEvent(event))
            {
            if (event.type == sf::Event::Closed)
                Window -> close();
            }
        Window -> clear(sf::Color (200, 200, 200));
        for (int i = 0; i < Background -> size(); i++)
            {
            if (Background -> at(i) != -1)
                {
                ground.pos_ = sf::Vector2i {i%10 * Size_grid, i/10 * Size_grid};
                ground.curAnimation_ = Background -> at(i);
                ground.draw();
                ground.control();
                }
            }
            
        mario.draw ();
        mario.physics();
        mario.control();
        frog.draw (); 
        frog.control();   
        
        Window -> display();
        } 
    Window = nullptr;
    Background = nullptr;
    }