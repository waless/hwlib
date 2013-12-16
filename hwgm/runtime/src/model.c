#include "hwgm/model.h"
#include "hwgm/hwgm.h"

static const char* CODE      = "HWGM";
static const char* VERSION   = "000.000";

void hwgm_model_initialize(hwgm_model_t* model)
{
    work->root           = NULL;
    work->node_count     = 0;
    work->mesh_count     = 0;
    work->material_count = 0;
    work->texture_count  = 0;
    work->vertices_count = 0;
    work->nodes          = NULL;
    work->meshes         = NULL;
    work->materials      = NULL;
    work->textures       = NULL;
    work->vertices       = NULL;

    memcpy(work->code, CODE, sizeof(work->code));
    memcpy(work->vrsion, VERSION, sizeof(work->version));
}

