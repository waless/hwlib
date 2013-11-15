#ifndef HWGM_H_
#define HWGM_H_

#define HWGM_NODE_NAME_MAX 64
#define HWGM_INVALID_INDEX 0xFFFFFFFF

typedef struct hwgm_vertices_t {
    hwu16 vertex_count;
    hws16 vertices[];
    hwu16 uvs[];
    hws16 normals[];
} hwgm_vertex_t;

typedef struct hwgm_texture_t {
    hwu32 index;
    hwu32 type;
    hwu32 wrap;
} hwgm_texture_t;

typedef struct hwgm_material_t {
    hwu32 shader_index;
    hwu32 texture_index;
} hwgm_material_t;

typedef struct hwgm_mesh_t {
    hwgm_vertex_t*   vertices;
    hwgm_material_t* material;
} hwgm_mesh_t;

typedef struct hwgm_node_t {
    hwu8           name[HWGM_NODE_NAME_MAX];
    hwm_matrix44_t transform;
    hwu16          radius;
    hwu8           mesh_count;
    hwu8           child_count;

    hwgm_mesh_t**  meshes;
    hwgm_node_t**  children;
} hwgm_node_t;

typedef struct hwgm_model_t {
    hws8  code[4];
    hwu8  major_version;
    hwu8  minor_version;

    hwgm_node_t* root;

    hwgm_node_t*     nodes;
    hwgm_mesh_t*     meshes;
    hwgm_material_t* materials;
    hwgm_vertices_t* vertices;
} hwgm_model_t;

#endif

