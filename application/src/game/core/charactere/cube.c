#include "cube.h"

Face* Face_create(int code)
{
    Face* p = (Face*)calloc(1, sizeof(Face));
    p->code = code;
    return p;

}

Cube* Cube_create()
{

    Cube* cube = (Cube*)calloc(1, sizeof(Cube));
    AssertNew(cube);


    cube->under = Face_create(1);
    cube->right = Face_create(2);
    cube->left = Face_create(3);
    cube->behind = Face_create(4);
    cube->front = Face_create(5);
    cube->over = Face_create(6);


    cube->has_hache = false;
    cube->has_key = false;

    return cube;
}

void Cube_print(Cube* cube)
{
    printf("under\t: %d\nover\t: %d\nleft\t: %d\nbehind\t: %d\nright\t: %d\nfront\t: %d\n\n"
        , cube->under->code, cube->over->code, cube->left->code, cube->behind->code, cube->right->code, cube->front->code);
}

void Cube_rota_right(Cube* cube)
{
    Face* temp = cube->left;
    cube->left = cube->behind;
    cube->behind = cube->right;
    cube->right = cube->front;
    cube->front = temp;

}

void Cube_rota_left(Cube* cube)
{
    Face* temp = cube->left;
    cube->left = cube->front;
    cube->front = cube->right;
    cube->right = cube->behind;
    cube->behind = temp;

}

void Cube_left(Cube* cube)
{
    Face* temp = cube->under;
    cube->under = cube->left;
    cube->left = cube->over;
    cube->over = cube->right;
    cube->right = temp;
    cube->j -= 1;
}

void Cube_behind(Cube* cube)
{
    Face* temp = cube->under;
    cube->under = cube->behind;
    cube->behind = cube->over;
    cube->over = cube->front;
    cube->front = temp;
    cube->i -= 1;

}
void Cube_right(Cube* cube)
{
    Face* temp = cube->under;
    cube->under = cube->right;
    cube->right = cube->over;
    cube->over = cube->left;
    cube->left = temp;
    cube->j += 1;

}
void Cube_front(Cube* cube)
{
    Face* temp = cube->under;
    cube->under = cube->front;
    cube->front = cube->over;
    cube->over = cube->behind;
    cube->behind = temp;
    cube->i += 1;

}

int getCubeI(Cube* cube)
{
    return cube->i;
}

int getCubeJ(Cube* cube)
{
    return cube->j;
}

void Set_Cube_North(Cube* cube)
{
    Cube_rota_right(cube);
    Cube_rota_right(cube);
}

void Set_Cube_Left(Cube* cube)
{
    Cube_rota_left(cube);
}

void Set_Cube_Right(Cube* cube)
{
    Cube_rota_right(cube);
}

void Set_Cube_South(Cube* cube)
{
    // South = default
}

bool Has_Hache(Cube* self)
{
    return (self->has_hache);
}

bool Has_Key(Cube* self)
{
    return (self->has_key);
}
