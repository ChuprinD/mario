#include "UtilsMain.hpp"

struct Hitbox
    {
    sf::Vector2i pos;
    sf::Vector2i size; 
    };

int main ()
    {
    txCreateWindow (257, 257);

    FILE* file = nullptr;
    fopen_s (&file, "../resources/config/mario.hitbox", "w");
    if (file == nullptr)
        {
        txMessageBox("I can't load mario.hitbox");
        return 0;
        }
    fprintf_s (file, "{\n");

    HDC sprite = txLoadImage("../resources/mario.bmp");
    if(!sprite)
        txMessageBox ("I can't load mario1.bmp");

    for (int y = 0; y < 2; y++)//14; y++)
        {    
        for (int x = 0; x < 16; x++)
            {
            txSetFillColor (RGB (200, 200, 200));
            txClear();

            sf::Vector2i rect_pos_right = {0, 0};
            sf::Vector2i rect_pos_left  = {0, 0};

            txSetColor   (RGB (255, 0, 0));
            txAlphaBlend (txDC(), 0, 0, 256, 256, sprite, x * 256, y * 256); 

            rect_pos_left  = MoveBorder (0, 0, rect_pos_left, 0);
            rect_pos_left  = MoveBorder (0, 0, rect_pos_left, 1);

            rect_pos_right = MoveBorder (rect_pos_left.x, rect_pos_left.y, rect_pos_right, 2);
            rect_pos_right = MoveBorder (rect_pos_left.y, rect_pos_left.x, rect_pos_right, 3);

            std::cout << rect_pos_left.x << rect_pos_left.y;
            txSetFillColor(TX_NULL);
            txRectangle (rect_pos_left.x, rect_pos_left.y, rect_pos_right.x, rect_pos_right.y); 

            sf::Vector2i size = rect_pos_right - rect_pos_left;
            fprintf_s (file, "%s[%02i, %02i]: {%i, %i, %i, %i}",
                       ((x || y)? ",\n   " : "   "), y, x, rect_pos_left.x, rect_pos_left.y, size.x, size.y);

            txSleep();
            //(void) _getch();
            }
        }
    txDeleteDC (sprite);
    fprintf_s (file, "\n}");
    fclose (file);
    }

sf::Vector2i MoveBorder (int first_start, int second_start, sf::Vector2i rect_pos_left, int border)
    {
    if (border == 0 || border == 1)
        {
        for (int a = 0; a <= 256; a++)
            {
            for (int b = 0; b <= 256; b++)
                {
                COLORREF cur_color = 0;
                if (border == 0)
                    {
                    cur_color = txGetPixel(a, b);
                    }
                else
                    cur_color = txGetPixel(b, a);

                 if (cur_color != RGB(200, 200, 200))
                    {
                    if (border == 0)
                        rect_pos_left = {a - 1, rect_pos_left.y};
                    if (border == 1)
                        rect_pos_left = {rect_pos_left.x, a - 1};

                    return rect_pos_left;
                    }
                }
            }
        }
    if (border == 2 || border == 3)
        {
        bool ok = true;
        for (int a = first_start + 1; a <= 256; a++)
            {
            ok = true;
            for (int b = second_start + 1; b <= 256; b++)
                {
                COLORREF cur_color = 0;
                if (border == 2)
                    cur_color = txGetPixel(a, b);
                else
                    cur_color = txGetPixel(b, a);
                
                if (cur_color != RGB(200, 200, 200))
                    ok = false;
                }
            if (ok)
                {
                if (border == 2)
                    return {a, rect_pos_left.y};
                if (border == 3)
                    return {rect_pos_left.x, a};
                }
            }
        }
    return {-1, -1};
    }