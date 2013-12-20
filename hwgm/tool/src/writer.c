#include "writer.h"
#include <hw/types.h>
#include <hwm/vector3.h>

static void count_up_node(writer_t* writer, const reader_node_t* node);
static void count_up_mesh(writer_t* writer, const reader_mesh_t* mesh);
static void count_up_material(writer_t* writer, const reader_material_t* material);
static void count_up_texture(writer_t* writer, const reader_texture_t* texture);
static void calc_bounding_box_from_node(hwm_vector3_t* min, hwm_vector3_t* max, const reader_node_t* node);
static void calc_bounding_box_from_vertices(hwm_vector3_t* min, hwm_vector3_t* max, const hwm_vector3_t* vertices, hwu32 count);

void writer_initialize(writer_t* writer)
{
    writer->node_count     = 0;
    writer->mesh_count     = 0;
    writer->material_count = 0;
    writer->texture_count  = 0;
    writer->vertices_count = 0;

    writer->nodes     = NULL;
    writer->meshes    = NULL;
    writer->materials = NULL;
    writer->textures  = NULL;
    writer->vertices  = NULL;
}

void writer_finalize(writer_t* writer)
{
}

void writer_run(writer_t* writer, const reader_t* reader)
{
    count_up_node(writer, &reader->root);
}

void countup_node(writer_t* writer, const reader_node_t* node)
{
    hwu32 i;

    writer->node_count += 1;

    for(i = 0; i < node->mesh_count; ++i) {
        count_up_mesh(writer, node->meshes + i);
    }

    for(i = 0; i < node->child_count; ++i) {
        count_up_node(writer, node->children + i);
    }
}

void count_up_mesh(writer_t* writer, const reader_mesh_t* mesh)
{
    writer->mesh_count += 1;
    count_up_material(writer, &mesh->material);
}

void count_up_material(writer_t* writer, const reader_material_t* material)
{
    writer->material_count += 1;
    count_up_texture(writer, &mesh->texture);
}

void count_up_texture(writer_t* writer, const reader_texture_t* texture)
{
    writer->texture_count += 1;
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

void calc_bounding_box(hwm_vector3_t* min, hwm_vector3_t* max, const hwm_vector3_t* vertices, hwu32 count)
{
    hwm_vector3_t vertices_min;
    hwm_vector3_t vertices_max;
    hwu32         i;

    hwm_vector3_set_scaler(&vertices_min, FLOAT_MAX);
    hwm_vector3_set_scaler(&vertices_max, -FLOAT_MAX);
    
    for(i = 0; i < count; ++i) {
        const hwm_vertex_t* v = vertices + i;
        
        hwm_vector3_min(&vertices_min, &vertices_min, &v);
        hwm_vector3_max(&vertices_max, &vertices_max, &v);
    }

    if(min != NULL) {
        *min = min;
    }

    if(max != NULL) {
        *max = max;
    }
}

