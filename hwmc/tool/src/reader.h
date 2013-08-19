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
    hwm_vector3_t*     vertices;
    hwm_vector3_t*     normals;
    hwm_vector3_t*     texcoords;
    hwu32              vertex_count;
    reader_material_t* materials;
    hwu32              material_count;
    hwm_matrix44_t     local_transform;
} reader_mesh_t;

typedef struct reader_t {
    reader_mesh_t* meshs;
    hwu32          mesh_count;
} reader_t;

extern void reader_initialize(reader_t* reader);
extern void reader_finalize(reader_t* reader);
extern hwbool reader_read(reader_t* reader, const char* input_path);

#ifdef __cplusplus
}
#endif

#endif

