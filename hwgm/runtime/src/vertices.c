#include "hwgm/vertices.h"

void hwgm_vertices_initialize(hwgm_vertices_t* vertices)
{
    vertices->vertex_count = 0;
    vertices->vertices     = NULL;
    vertices->uvs          = NULL;
    vertices->normals      = NULL;
}

