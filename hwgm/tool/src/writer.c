#include "writer.h"
#include <hw/types.h>
#include <hwm/vector3.h>

typedef struct context_t {
    hwu32 model_count;
    hwu32 node_count;
    hwu32 mesh_count;
    hwu32 material_count;
    hwu32 texture_count;
    hwu32 vertices_count;

    hwu32 model_total_size;
    hwu32 node_total_size;
    hwu32 mesh_total_size;
    hwu32 material_total_size;
    hwu32 texture_total_size;
    hwu32 vertices_total_size;

    hwu8* models;
    hwu8* nodes;
    hwu8* meshes;
    hwu8* materials;
    hwu8* textures;
    hwu8* vertices;
} context_t;

static void context_initialize(context_t* context);
static void context_finalize(context_t* context);

static void calc_work(context_t* context, const reader_t* reader);
static void calc_work_node(context_t* context, const reader_node_t* node);
static void calc_work_mesh(context_t* context, const reader_mesh_t* mesh);
static void calc_work_vertices(context_t* context, const reader_mesh_t* mesh);
static void calc_work_material(context_t* context, const reader_material_t* material);
static void calc_work_texture(context_t* context, const reader_texture_t* texture);

static void allocate_work(context_t* context);

static void read(context_t* context, const reader_t* reader);
static void read_node(context_t* context, const reader_node_t* node);
static void read_mesh(context_t* context, const reader_mesh_t* mesh);
static void read_material(context_t* context, const reader_material_t* material);
static void read_texture(context_t* context, const reader_texture_t* texture);

static void calc_bounding_box_from_node(hwm_vector3_t* min, hwm_vector3_t* max, const reader_node_t* node);
static void calc_bounding_box_from_vertices(hwm_vector3_t* min, hwm_vector3_t* max, const hwm_vector3_t* vertices, hwu32 count);

void writer_run(const reader_t* reader)
{
    context_t context;

    context_initialize(&context);
    calc_work(&context, reader);
    allocate_work(&context);
}

void context_initialize(context_t* context)
{
    context->model_count    = 0;
    context->node_count     = 0;
    context->mesh_count     = 0;
    context->material_count = 0;
    context->texture_count  = 0;
    context->vertices_count = 0;

    context->model_total_size    = 0;
    context->node_total_size     = 0;
    context->mesh_total_size     = 0;
    context->material_total_size = 0;
    context->texture_total_size  = 0;
    context->vertices_total_size = 0;

    context->models    = NULL;
    context->nodes     = NULL;
    context->meshes    = NULL;
    context->materials = NULL;
    context->textures  = NULL;
    context->vertices  = NULL;
}

void context_finalize(context_t* context)
{
    HW_SAFE_FREE(context->vertices);
    HW_SAFE_FREE(context->textures);
    HW_SAFE_FREE(context->materials);
    HW_SAFE_FREE(context->meshes);
    HW_SAFE_FREE(context->nodes);
    HW_SAFE_FREE(context->models);

    context_initialize(context);
}

void calc_work(context_t* context, const reader_t* reader)
{
    hwu32 size = 0;

    size += sizeof(hwgm_model_t);

    calc_work_node(context, &reader->root);

    context->model_total_size += size;
    context->model_count      += 1;
}

void calc_work_node(context_t* context, const reader_node_t* node)
{
    hwu32 size = 0;
    hwu32 i;

    size += sizeof(hwgm_node_t);
    size += sizeof(hwgm_mesh_t*) * node->mesh_count;
    size += sizeof(hwgm_node_t*) * node->child_count;

    for(i = 0; i < node->mesh_count; ++i) {
        calc_work_mesh(context, node->meshes + i);
    }

    for(i = 0; i < node->child_count; ++i) {
        calc_wrork_nde(writer, node->children + i);
    }

    context->node_total_size += size;
    context->node_count      += 1;
}

void calc_work_mesh(context_t* context, const reader_mesh_t* mesh)
{
    hwu32 size = 0;

    size += sizeof(hwgm_mesh_t);

    calc_work_vertices(context, mesh);
    calc_work_material(context, &mesh->material);

    context->mesh_total_size += size;
    context->mesh_count      += 1;
}

void calc_work_vertices(context_t* context, const reader_mesh_t* mesh)
{
    hwu32 size = 0;

    size += sizeof(hwgm_vertices_t);
    size += sizeof(hws16) * 3 * mesh->vertex_count;
    size += sizeof(hws16) * 3 * mesh->vertex_count;
    size += sizeof(hwu16) * 2 * mesh->vertex_count;

    context->vertices_total_size += size;
    context->vertices_count      += 1;
}

void calc_work_material(context_t* context, const reader_material_t* material)
{
    hwu32 size = 0;
    hwu32 i;

    size += sizeof(hwgm_material_t);
    size += sizeof(hwgm_texture_t*) * material->diffuse_texture_count;

    for(i = 0; i < material->diffuse_texture_count; ++i) {
        calc_work_texture(context, &material->diffuse_textures + i);
    }

    context->material_total_size += size;
    context->material_count      += 1;
}

void calc_work_texture(context_t* context, const reader_texture_t* texture)
{
    hwu32 size = 0;
    hwu32 i;

    size += sizeof(hwgm_texture_t);

    context->texture_total_size += size;
    context->texture_count      += 1;
}

void allocate_work(context_t* context)
{
    if(context->model_count > 0) {
        context->models = (hwgm_model_t*)hw_malloc(context->model_total_size);
    }

    if(context->node_count > 0) {
        context->nodes = (hwgm_node_t*)hw_malloc(context->node_total_size);
    }

    if(context->mesh_count > 0) {
        context->meshes = (hwgm_mesh_t*)hw_malloc(context->mesh_total_size);
    }

    if(context->material_count > 0) {
        context->maerials = (hwgm_material_t*)hw_malloc(context->material_total_size);
    }

    if(context->texture_count > 0) {
        context->textures = (hwgm_texture_t*)hw_malloc(context->texture_total_size);
    }

    if(context->vertices_count > 0) {
        context->vertices = (hwgm_vertices_t*)hw_mallc(context->vertices_total_size);
    }
}

void read(context_t* context, const reader_t* reader)
{
    hwu32 i;

    for(i = 0; i < context->model_count; ++i) {
    }
}

void read_node(context_t* context, const reader_node_t* node)
{
}

void read_mesh(context_t* context, const reader_mesh_t* mesh)
{
}

void read_material(context_t* context, const reader_material_t* material)
{
}

void read_texture(context_t* context, const reader_texture_t* texture)
{
}

void calc_bounding_box_from_node(hwm_vector3_t* min, hwm_vector3_t* max, const hwm_vector3_t* node)
{
    hwm_vector3_t node_min;
    hwm_vector3_t node_max;
    hwu32         i;

    hwm_vector3_set_scaler(&node_min, FLOAT_MAX);
    hwm_vector3_set_scaler(&node_max, -FLOAT_MAX);

    if(node != NULL) {
        for(i = 0; i < node->mesh_count; ++i) {
            const reader_mesh_t* mesh = node->meshes + i;
                  hwm_vector3_t  mesh_min;
                  hwm_vector3_t  mesh_max;

            calc_bounding_box(&mesh_min, &mesh_max, mesh->vertices, mesh->vertex_count);
            hwm_vector3_min(&node_min, &node_min, &mesh_min);
            hwm_vector3_max(&node_max, &node_max, &mesh_max);
        }
    }

    if(min != NULL) {
        *min = node_min;
    }

    if(max != NULL) {
        *max = node_max;
    }
}

void calc_bounding_box_from_vertices(hwm_vector3_t* min, hwm_vector3_t* max, const hwm_vector3_t* vertices, hwu32 count)
{
    hwm_vector3_t vertices_min;
    hwm_vector3_t vertices_max;
    hwu32         i;

    hwm_vector3_set_scaler(&vertices_min, FLOAT_MAX);
    hwm_vector3_set_scaler(&vertices_max, -FLOAT_MAX);
    
    for(i = 0; i < count; ++i) {
        const hwm_vector3_t* v = vertices + i;
        
        hwm_vector3_min(&vertices_min, &vertices_min, &v);
        hwm_vector3_max(&vertices_max, &vertices_max, &v);
    }

    if(min != NULL) {
        *min = vertices_min;
    }

    if(max != NULL) {
        *max = vertices_max;
    }
}

