#include "cube.h"

Cube *Cube_create(char face)
{
    assert(face != NULL);

    Cube *cube = (Cube *)calloc(1, sizeof(Cube));
    AssertNew(cube);

    cube->actual_face = face;
    cube->has_hache=false;
    cube->has_key=false;

    return cube;
}

bool Has_Hache(Cube *self){
    return (self->has_hache);
}

bool Has_Key(Cube *self){
    return (self->has_key);
}