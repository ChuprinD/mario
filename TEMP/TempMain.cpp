#define _CRT_SECURE_NO_WARNINGS
#include "TempMain.hpp"



int main()
    {
    FILE* file = nullptr;

    fopen_s (&file, "hitboxes", "r");
    if (file == nullptr)
        return 0;

    int x = 0, y = 0;
    sf::Vector2i pos = {0 , 0}, size = {0,  0};
    fscanf_s (file, " { ");

    while (!feof(file))
        {
        char str [100] = "";
        fgets (str, sizeof(str), file);
     
        std::sscanf (str, " [ %i , %i ] : { %i , %i , %i , %i } ,", &x, &y, &pos.x, &pos.y, &size.x, &size.y);
        $_ (x), $_ (y), $_ (pos.x), $_ (pos.y), $_ (size.x), $ (size.y);
        }
    
    //[00, 00]: {84, 67, 85, 182},
    return 0;
    }
