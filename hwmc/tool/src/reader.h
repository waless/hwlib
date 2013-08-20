#ifndef HWMC_READER_H_
#define HWMC_READER_H_

#include <hw/types.h>
#include <hwm/vector3.h>
#include <hwm/matrix44.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct reader_texture_t {
    const char* path;
} reader_texture_t;

typedef struct reader_material_t {
    reader_texture_t* textures;
    hwu32             texture_count;
} reader_material_t;

typedef struct reader_mesh_t {
    hwm_vector3_t*    vertices;
    hwu32*            indices;
    hwm_vector3_t*    normals;
    hwm_vector3_t*    texcoords;
    hwu32             vertex_count;
    hwu32             index_count;
    reader_material_t material;
} reader_mesh_t;

typedef struct reader_node_t {
    reader_mesh_t*        meshes;
    hwu32                 mesh_count;
    hwm_matrix44_t        local_transform;
    struct reader_node_t* children;
    hwu32                 child_count;
} reader_node_t;

typedef struct reader_t {
    reader_node_t root;
} reader_t;

extern void reader_node_initialize(reader_node_t* node);
extern void reader_mesh_initialize(reader_mesh_t* mesh);
extern void reader_material_initialize(reader_material_t* material);
extern void reader_texture_initialize(reader_texture_t* texture);

extern void reader_initialize(reader_t* reader);
extern void reader_finalize(reader_t* reader);
extern hwbool reader_read(reader_t* reader, const char* input_path);

#ifdef __cplusplus
}
#endif

#endif

