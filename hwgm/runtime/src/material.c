#include "hwgm/material.h"

void hwgm_material_initialize(hwgm_material_t* material)
{
    material->shader_index = 0;
    material->textures     = NULL;
}

