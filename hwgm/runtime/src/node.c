#include "hwgm/node.h"

void hwgm_node_initialize(hwgm_node_t* node)
{
    node->radius      = 0.0f;
    node->mesh_count  = 0;
    node->child_count = 0;
    node->meses       = NULL;
    node->children    = NULL;
}

