#ifndef HWMC_READER_H_
#define HWMC_READER_H_

#include <hw/types.h>
#include <hw/string/string.h>
#include <hwm/vector3.h>
#include <hwm/vector4.h>
#include <hwm/matrix44.h>
#include <hwg/color4_f32.h>
#include <assimp/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum hwg_texture_type_t {
    HWG_TEXTURE_TYPE_UNKNOWN = -1,
    HWG_TEXTURE_TYPE_NONE = 0,
    HWG_TEXTURE_TYPE_DIFFUSE,
    HWG_TEXTURE_TYPE_SPECULAR,
    HWG_TEXTURE_TYPE_AMBIEND,
    HWG_TEXTURE_TYPE_EMISSIVE,
    HWG_TEXTURE_TYPE_HEIGHT,
    HWG_TEXTURE_TYPE_NORMAL,
    HWG_TEXTURE_TYPE_SHININESS,
    HWG_TEXTURE_TYPE_OPACITY,
    HWG_TEXTURE_TYPE_DISPLACEMENT,
    HWG_TEXTURE_TYPE_LIGHTMAP,
    HWG_TEXTURE_TYPE_REFLECTION,
} hwg_texture_type_t;

typedef enum hwg_texture_mapping_t {
    HWG_TEXTURE_MAPPING_UNKOWN = -1,
    HWG_TEXTURE_MAPPING_UV,
    HWG_TEXTURE_MAPPING_SPHERE,
    HWG_TEXTURE_MAPPING_CYLINDER,
    HWG_TEXTURE_MAPPING_BOX,
    HWG_TEXTURE_MAPPING_PLANE,
} hwg_texture_mapping_t;

typedef enum hwg_texture_wrap_t {
    HWG_TEXTURE_WRAP_UNKOWN = -1,
    HWG_TEXTURE_WRAP_REPEAT,
    HWG_TEXTURE_WRAP_CLAMP,
    HWG_TEXTURE_WRAP_DECAL,
    HWG_TEXTURE_WRAP_MIRROR,
} hwg_texture_wrap_t;

typedef enum hwg_texture_op_t {
    HWG_TEXTURE_OP_UNKOWN = -1,
    HWG_TEXTURE_OP_MULTIPLY = 0,
    HWG_TEXTURE_OP_ADD,
    HWG_TEXTURE_OP_SUBTRACT,
    HWG_TEXTURE_OP_DIVIDE,
    HWG_TEXTURE_OP_SMOOTH_ADD,
    HWG_TEXTURE_OP_SIGNED_ADD,
} hwg_texture_op_t;

typedef enum hwg_texture_flags_t {
    HWG_TEXTURE_FLAGS_INVERT       = (1 << 0),
    HWG_TEXTURE_FLAGS_USE_ALPHA    = (1 << 1),
    HWG_TEXTURE_FALGS_IGNORE_ALPHA = (1 << 2),
} hwg_texture_fags_t;

typedef struct reader_texture_t {
    char                  path[MAXLEN];
    hwg_texture_type_t    type;
    hwg_texture_mapping_t mapping;
    hwg_texture_wrap_t    wrap;
    hwg_texture_op_t      op;
    hwf32                 blend_factor;
    hwu32                 flags;
} reader_texture_t;

typedef struct reader_material_t {
    hwg_color4_f32_t  diffuse_color;
    hwg_color4_f32_t  specular_color;
    hwg_color4_f32_t  ambient_color;
    hwg_color4_f32_t  emissive_color;

    reader_texture_t* diffuse_textures;
    hwu32             diffuse_texture_count;
} reader_material_t;

typedef struct reader_mesh_t {
    hwm_vector3_t*    vertices;
    hwu32*            indices;
    hwm_vector3_t*    normals;
    hwm_vector3_t**   texcoords;
    hwm_vector4_t**   colors;
    hwu32             vertex_count;
    hwu32             index_count;
    hwu32             texcoord_layer_count;
    hwu32             color_layer_count;
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
extern void reader_node_finalize(reader_node_t* node);
extern void reader_mesh_initialize(reader_mesh_t* mesh);
extern void reader_mesh_finalize(reader_mesh_t* mesh);
extern void reader_material_initialize(reader_material_t* material);
extern void reader_material_finalize(reader_material_t* material);
extern void reader_texture_initialize(reader_texture_t* texture);
extern void reader_texture_finalize(reader_texture_t* texture);

extern void reader_initialize(reader_t* reader);
extern void reader_finalize(reader_t* reader);
extern hwbool reader_read(reader_t* reader, const char* input_path);

#ifdef __cplusplus
}
#endif

#endif

