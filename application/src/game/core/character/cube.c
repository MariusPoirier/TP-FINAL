#include "cube.h"

Cube Cube_create()
{

    Cube cube;

    cube.under = KEY_HOLE;
    cube.right = AXE;
    cube.left = SHIELD;
    cube.behind = BACKPACK;
    cube.front = FACE;
    cube.over = HEAD;


    cube.axe = false;
    cube.key = false;


    return cube;
}

void Cube_print(Cube cube)
{
    printf("under\t: %d\nover\t: %d\nleft\t: %d\nbehind\t: %d\nright\t: %d\nfront\t: %d\n\n"
        , cube.under, cube.over, cube.left, cube.behind, cube.right, cube.front);
}

void Cube_rota_right(Cube* cube)
{
    Face_Value temp = cube->left;
    cube->left = cube->behind;
    cube->behind = cube->right;
    cube->right = cube->front;
    cube->front = temp;

}

void Cube_rota_left(Cube* cube)
{
    Face_Value temp = cube->left;
    cube->left = cube->front;
    cube->front = cube->right;
    cube->right = cube->behind;
    cube->behind = temp;

}

void Cube_left(Cube* cube)
{
    Face_Value temp = cube->under;
    cube->under = cube->left;
    cube->left = cube->over;
    cube->over = cube->right;
    cube->right = temp;
    cube->j -= 1;
}

void Cube_behind(Cube* cube)
{
    Face_Value temp = cube->under;
    cube->under = cube->behind;
    cube->behind = cube->over;
    cube->over = cube->front;
    cube->front = temp;
    cube->i -= 1;

}
void Cube_right(Cube* cube)
{
    Face_Value temp = cube->under;
    cube->under = cube->right;
    cube->right = cube->over;
    cube->over = cube->left;
    cube->left = temp;
    cube->j += 1;

}
void Cube_front(Cube* cube)
{
    Face_Value temp = cube->under;
    cube->under = cube->front;
    cube->front = cube->over;
    cube->over = cube->behind;
    cube->behind = temp;
    cube->i += 1;

}

int getCubeI(Cube cube)
{
    return cube.i;
}

int getCubeJ(Cube cube)
{
    return cube.j;
}

void Cube_SetNorth(Cube* cube)
{
    Cube_rota_right(cube);
    Cube_rota_right(cube);
}

void Cube_SetWest(Cube* cube)
{
    Cube_rota_left(cube);
}

void Cube_SetEast(Cube* cube)
{
    Cube_rota_right(cube);
}

void Cube_SetSouth(Cube* cube)
{
    // South = default
}

bool Cube_axe(Cube self)
{
    return (self.axe);
}

bool Cube_key(Cube self)
{
    return (self.key);
}
