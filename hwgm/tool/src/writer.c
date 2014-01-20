﻿#include "writer.h"
#include <hw/types.h>
#include <hwm/vector3.h>

typedef struct context_t {
    hwu32 node_count;
    hwu32 mesh_count;
    hwu32 material_count;
    hwu32 texture_count;
    hwu32 vertices_count;

    hwu32 node_total_size;
    hwu32 mesh_total_size;
    hwu32 material_total_size;
    hwu32 texture_total_size;
    hwu32 vertices_total_size;

    hwu32 node_pos;
    hwu32 mesh_pos;
    hwu32 material_pos;
    hwu32 texture_pos;
    hwu32 vertex_pos;

    hwu8* nodes;
    hwu8* meshes;
    hwu8* materials;
    hwu8* textures;
    hwu8* vertices;

    hwgm_model_t model;
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

static void             read(context_t* context, const reader_t* reader);
static hwgm_node_t*     read_node(context_t* context, const reader_node_t* node);
static hwgm_mesh_t*     read_mesh(context_t* context, const reader_mesh_t* mesh);
static hwgm_vertices_t* read_vertices(context_t* context, const reader_mesh_t* mesh);
static hwgm_material_t* read_material(context_t* context, const reader_material_t* material);
static hwgm_texture_t*  read_texture(context_t* context, const reader_texture_t* texture);

static hwu32 calc_size_node(const reader_node_t* node);
static hwu32 calc_size_mesh(const reader_mesh_t* mesh);
static hwu32 calc_size_vertices(const reader_mesh_t* mesh);
static hwu32 calc_size_material(const reader_material_t* material);
static hwu32 calc_size_texture(const reader_texture_t* texture);

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
    context->node_count     = 0;
    context->mesh_count     = 0;
    context->material_count = 0;
    context->texture_count  = 0;
    context->vertices_count = 0;

    context->node_total_size     = 0;
    context->mesh_total_size     = 0;
    context->material_total_size = 0;
    context->texture_total_size  = 0;
    context->vertices_total_size = 0;

    context->nodes     = NULL;
    context->meshes    = NULL;
    context->materials = NULL;
    context->textures  = NULL;
    context->vertices  = NULL;

    hwgm_model_initialize(&context->model);
}

void context_finalize(context_t* context)
{
    HW_SAFE_FREE(context->vertices);
    HW_SAFE_FREE(context->textures);
    HW_SAFE_FREE(context->materials);
    HW_SAFE_FREE(context->meshes);
    HW_SAFE_FREE(context->nodes);

    context_initialize(context);
}

void calc_work(context_t* context, const reader_t* reader)
{
    calc_work_node(context, &reader->root);
}

void calc_work_node(context_t* context, const reader_node_t* node)
{
    hwu32 i;

    for(i = 0; i < node->mesh_count; ++i) {
        calc_work_mesh(context, node->meshes + i);
    }

    for(i = 0; i < node->child_count; ++i) {
        calc_wrork_node(writer, node->children + i);
    }

    context->node_total_size += calc_size_node(node);
    context->node_count      += 1;
}

void calc_work_mesh(context_t* context, const reader_mesh_t* mesh)
{
    calc_work_vertices(context, mesh);
    calc_work_material(context, &mesh->material);

    context->mesh_total_size += calc_size_mesh(mesh);
    context->mesh_count      += 1;
}

void calc_work_vertices(context_t* context, const reader_mesh_t* mesh)
{
    context->vertices_total_size += calc_size_vertices(mesh);
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
}

hwgm_node_t* read_node(context_t* context, const reader_node_t* node)
{
    hwgm_node_t* out  = NULL;
    hwgm_mesh_t* mesh = NULL;
    hwgm_node_t* node = NULL;
    hwu32        size = 0;
    hwu32        i;

    out = (hwgm_node_t*)(context->nodes + context->node_pos);
    hwgm_node_initialize(out);

    for(i = 0; i < node->mesh_count; ++i) {
        mesh = read_mesh(context, node->meshes + i);
        out->meshes[i] = mesh;
    }

    for(i = 0; i < node->child_count; ++i) {
        node = hwgm_read_node(context, node->childs + i);
        out->children[i] = node;
    }

    out->mesh_count  = node->mesh_count;
    out->child_count = node->child_count;

    context->node_pos += calc_size_node(node);

    return out;
}

void read_mesh(context_t* context, const reader_mesh_t* mesh)
{
    hwgm_mesh_t*     out      = NULL;
    hwgm_vertices_t* vertices = NULL;
    hwgm_material_t* material = NULL;

    out = (hwgm_mesh_t*)(context->meshes + context->mesh_pos);
    hwgm_mesh_initialize(out);
    
    vertices = read_vertices(context, mesh);
    out->vertices = vertices;

    material = read_material(context, &mesh->material);
    out->material = material;

    context->mesh_pos += calc_size_mesh(mesh);

    return out;
}

void read_vertices(context_t* context, const reader_mesh_t* mesh)
{
    hwgm_vertices_t* out      = NULL;
    hws16*           vertices = NULL;
    hwu16*           uvs      = NULL;
    hws16*           normals  = NULL;
    hwu8*            pos      = NULL;
    hwu32            i;

    out = (hwgm_vertices_t*)(context->vertices + context->vertices_pos);
    hwgm_vertices_initialize(out);

    /* 頂点格納位置を計算、格納
     * 頂点情報は必須 */
    pos      = (hwu8*)context->vertices + sizeof(hwgm_vertices_t);
    vertices = (hws16*)pos;
    for(i = 0; i < mesh->vertex_count; i += 3) {
        const hwm_vector3_t* v = mesh->vertices + i;
              hws16          x = 0;
              hws16          y = 0;
              hws16          z = 0;

        vertices[i + 0] = x;
        vertices[i + 1] = y;
        vertices[i + 2] = z;
    }
    pos += sizeof(hws16) * 3 * mesh->vertex_count;

    /* テクスチャ座標格納位置を計算、格納 */
    if(mesh->texcoords != NULL && mesh->texcoord_layer_count > 0) {
        uvs  = (hwu16*)pos;
        pos += sizeof(hwu16) * 2 * mesh->vertex_count;
    }

    /* 法線位置格納位置を計算、格納 */
    if(mesh->normals != NULL) {
        normals = (hws16*)pos;
        pos    += sizeof(hws16) * 3 * mesh->vertex_count;
    }
}

void read_material(hwg_material_t* out, const reader_material_t* material)
{
}

void read_texture(hwgm_texture_t* out, const reader_texture_t* texture)
{
}

hwu32 calc_size_node(const reader_node_t* node)
{
    hwu32 size = 0;

    size += sizeof(hwgm_node_t);
    size += sizeof(hwgm_mesh_t*) * node->mesh_count;
    size += sizeof(hwgm_node_t*) * node->child_count;

    return size;
}

hwu32 calc_size_mesh(const reader_mesh_t* mesh)
{
    hwu32 size = 0;

    size += sizeof(hwgm_mesh_t);

    return size;
}

hwu32 calc_size_vertices(const reader_mesh_t* mesh)
{
    hwu32 size = 0;

    size += sizeof(hwgm_vertices_t);
    size += sizeof(hws16) * 3 * mesh->vertex_count;

    if(mesh->texcoords != NULL && mesh->texcoord_layer_count > 0) {
        size += sizeof(hwu16) * 2 * mesh->vertex_count;
    }

    if(mesh->normals != NULL) {
        size += sizeof(hws16) * 3 * mesh->vertex_count;
    }

    return size;
}

hwu32 calc_size_material(const reader_material_t* material)
{
    hwu32 size = 0;

    size += sizeof(hwgm_material_t);
    size += sizeof(hwgm_texture_t*) * material->diffuse_texture_count;

    return size;
}

hwu32 calc_size_texture(const reader_texture_t* texture)
{
    hwu32 size = 0;

    size += sizeof(hwgm_texture_t);

    return size;
}

void calc_bounding_box_from_tree(hwm_vector3_t* min, hwm_vector3_t* max, const reader_node_t* root)
{
    hwm_vector3_t result_min;
    hwm_vector3_t result_max;
    hwu32         i;

    hwm_vector3_set_scaler(&result_min, FLOAT_MAX);
    hwm_vector3_set_scaler(&result_max, -FLOAT_MAX);

    if(root != NULL) {
        calc_bounding_box_from_node(&result_min, &result_max, root);

        for(i = 0; i < root->child_count; ++i) {
            const reader_node_t* node = root->children + i;
                  hwm_vector3_t  node_min;
                  hwm_vector3_t  node_max;

            calc_bounding_box_from_node(&node_min, &node_max, node);
            hwm_vector3_min(&result_min, &result_min, &node_min);
            hwm_vector3_max(&result_max, &result_max, &node_max);
        }
    }

    if(min != NULL) {
        *min = result_min;
    }

    if(max != NULL) {
        *max = result_max;
    }
}

void calc_bounding_box_from_node(hwm_vector3_t* min, hwm_vector3_t* max, const reader_node_t* node)
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

            calc_bounding_box_from_vertices(&mesh_min, &mesh_max, mesh->vertices, mesh->vertex_count);
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

