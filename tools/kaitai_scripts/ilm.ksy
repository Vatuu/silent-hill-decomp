meta:
  id: ilm
  title: Silent Hill 1 Skeletal Model Format
  file-extension: ilm
  endian: le
  encoding: ASCII

doc: |
  ILM is the skeletal 3D model format used in Silent Hill (PSX).

  The header contains a table of objects, each with a name, ID, and offset to
  its body. Each body contains vertex and primitive data.

  Note that the vertices are stored untransformed; the anm format is necessary
  to render the model correctly.

seq:
  - id: magic
    contents: [0x30, 0x06]

  - id: is_initialized
    type: u1

  - type: u1

  - id: name_ofs
    type: u4
    valid: 0x14

  - id: num_objs
    type: u4

  - id: objs_ofs
    type: u4

  - id: id_table_ofs
    type: u4

  - id: name
    type: strz

instances:
  objs:
    pos: objs_ofs
    type: obj
    repeat: expr
    repeat-expr: num_objs

  id_table:
    pos: id_table_ofs
    type: u1
    repeat: expr
    repeat-expr: num_objs

types:
  obj:
    seq:
      - id: bone_index_ascii
        type: str
        size: 2

      - id: name
        type: strz
        size: 6

      - type: u1

      - id: base_index
        type: u1
        doc: all quad/triangle indices for the object are offset by this value

      - id: normal_base_index
        type: u1

      - type: u1

      - id: ofs
        type: u4

    instances:
      bone_index:
        value: bone_index_ascii.to_i

      body:
        pos: ofs
        type: obj_body

  obj_body:
    seq:
      - id: num_prims
        type: u1
      - id: num_vertices
        type: u1
      - id: num_normals
        type: u1
      - type: u1
      - id: prims_ofs
        type: u4
      - id: vertex_xy_ofs
        type: u4
      - id: vertex_z_ofs
        type: u4
      - id: normals_ofs
        type: u4
      - id: next_ofs
        type: u4

    instances:
      prims:
        pos: prims_ofs
        type: index_packet
        repeat: expr
        repeat-expr: num_prims
      vertex_xy:
        pos: vertex_xy_ofs
        type: s2
        repeat: expr
        repeat-expr: num_vertices * 2
      vertex_z:
        pos: vertex_z_ofs
        type: s2
        repeat: expr
        repeat-expr: num_vertices
      normals:
        pos: normals_ofs
        type: svector
        repeat: expr
        repeat-expr: num_normals

  index_packet:
    seq:
      - id: uv0
        type: uv

      - id: clut_index
        type: clut_index

      - id: uv1
        type: uv

      - id: tpage_info
        type: s2

      - id: uv2
        type: uv

      - id: uv3
        type: uv

      - id: indices
        type: prim_indices

      - id: normal_indices
        type: prim_indices

  uv:
    seq:
      - id: u
        type: u1
      - id: v
        type: u1

  prim_indices:
    seq:
      - id: v0
        type: u1
      - id: v1
        type: u1
      - id: v2
        type: u1
      - id: v3
        type: u1

  xy_pair:
    seq:
      - id: x
        type: s2
      - id: y
        type: s2

  svector:
    seq:
      - id: x_int
        type: s1
      - id: y_int
        type: s1
      - id: z_int
        type: s1
      - id: count
        type: u1
    instances:
      x:
        value: x_int.as<f4> / 128.0
      y:
        value: y_int.as<f4> / 128.0
      z:
        value: z_int.as<f4> / 128.0
      length_sq:
        value: x*x + y*y + z*z

  clut_index:
    seq:
      - id: value
        type: s2

    instances:
      x:
        value: (value & 0x3f) * 0x10
      y:
        value: (value >> 6) & 0x1FF
