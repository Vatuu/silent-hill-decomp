meta:
  id: ipd
  title: Silent Hill 1 Map Model Format
  file-extension: ipd
  endian: le
  encoding: ASCII

doc: |
  IPD is the 3D model format containing instanced map models and collision data
  used in Silent Hill (PSX).

seq:
  - id: header
    type: ipd_header

  - id: collision
    type: ipd_collision_info

instances:
  lm_body:
    pos: header.lm_header_offset
    type: lm_body(header.lm_header_offset)

types:
  # ===
  # IPD
  # ===

  ipd_header:
    seq:
      - id: magic
        contents: [0x14]

      - id: is_initialized
        type: u1

      - id: level_grid_x
        type: s1

      - id: level_grid_y
        type: s1

      - id: lm_header_offset
        type: u4

      - id: model_count
        type: u1

      - id: model_buffer_count
        type: u1

      - id: model_order_count
        type: u1

      - id: unk_b
        size: 1

      - id: unk_c
        size: 8

      - id: model_info_offset
        type: u4

      - id: model_buffers_offset
        type: u4

      - id: textures_offset
        type: u1

      - id: unk_1d
        size: 3

      - id: unk_20
        size: 48

      - id: model_order_ptr_offset
        type: u4

    instances:
      model_infos:
        pos: model_info_offset
        type: ipd_model_info
        repeat: expr
        repeat-expr: model_count
      
      model_buffers:
        pos: model_buffers_offset
        type: ipd_model_buffer
        repeat: expr
        repeat-expr: model_buffer_count

  ipd_collision_info:
    seq:
      - id: position_x
        type: s4

      - id: position_z
        type: s4

      - id: coll_point_count
        type: b8

      - id: ptr_10_count
        type: b8

      - id: ptr_14_count
        type: b8

      - id: ptr_18_count
        type: b8

      - id: collision_vertices_ptr
        type: u4

      - id: ptr_10
        type: u4

      - id: ptr_14
        type: u4

      - id: ptr_18
        type: u4

      - id: subcell_size
        type: s2

      - id: subcell_x_count
        type: u1

      - id: subcell_z_count
        type: u1

      - id: cell_ranges_ptr
        type: u4

      - id: field_24
        type: u2

      - id: field_26
        type: u2

      - id: ptr_28
        type: u4

      - id: ptr_2c
        type: u4

      - id: unk_loaded_count
        type: u1

      - id: unk_31
        size: 3

      - id: field_34
        size: 256

  ipd_model_info:
    seq:
      - id: is_global_plm
        type: u1

      - id: unk_1
        size: 3

      - id: name
        type: strz
        size: 8

      - id: model_header_offset
        type: u4

  ipd_model_buffer:
    seq:
      - id: field_0
        type: u1

      - id: field_1
        type: u1

      - id: subcell_count
        type: u1

      - size: 1

      - id: min_x
        type: s2

      - id: max_x
        type: s2

      - id: min_z
        type: s2

      - id: max_z
        type: s2

      - id: field_ptr_c_offset
        type: u4

      - id: field_ptr_10_offset
        type: u4

      - id: subcell_positions_ptr_offset
        type: u4

  # ========
  # PLM (LM)
  # ========

  lm_body:
    params:
      - id: base_offset
        type: u4
    seq:
      - id: magic
        contents: [0x30]

      - id: version
        type: u1

      - id: is_initialized
        type: u1

      - id: material_count
        type: u1

      - id: materials_offset
        type: u4

      - id: model_count
        type: u1

      - id: unk_9
        size: 3

      - id: model_headers_offset
        type: u4

      - id: model_order_offset
        type: u4
    
    instances:
      materials:
        pos: base_offset + materials_offset
        type: material
        repeat: expr
        repeat-expr: material_count
      
      models:
        pos: base_offset + model_headers_offset
        type: model_header(base_offset)
        repeat: expr
        repeat-expr: model_count
      
      model_order:
        pos: base_offset + model_order_offset
        type: u1
        repeat: expr
        repeat-expr: model_count

  material:
    seq:
      - id: name
        type: strz
        size: 8

      - id: offset_texture
        type: u4

      - id: field_c
        type: u1

      - id: unk_d
        type: u1

      - id: field_e
        type: u1

      - id: field_f
        type: u1

      - id: field_10
        type: u2

      - id: field_12
        type: u2

      - id: field_14
        type: u2

      - id: field_16
        type: u2

  model_header:
    params:
      - id: base_offset
        type: u4
    seq:
      - id: name
        type: strz
        size: 8

      - id: mesh_count
        type: u1

      - id: vertex_offset
        type: u1

      - id: normal_offset
        type: u1

      - id: bitfield_b
        type: u1

      - id: mesh_headers_offset
        type: u4
    
    instances:
      mesh_headers:
        pos: base_offset + mesh_headers_offset
        type: mesh_header(base_offset)
        repeat: expr
        repeat-expr: mesh_count

  mesh_header:
    params:
      - id: base_offset
        type: u4
    seq:
      - id: primitive_count
        type: u1

      - id: vertex_count
        type: u1

      - id: normal_count
        type: u1

      - id: unk_count
        type: u1

      - id: primitives_offset
        type: u4

      - id: vertices_xz_offset
        type: u4

      - id: verticez_z_offset
        type: u4

      - id: normals_offset
        type: u4

      - id: unk_ptrs_offset
        type: u4

    instances:
      primitives:
        pos: base_offset + primitives_offset
        type: primitive
        repeat: expr
        repeat-expr: primitive_count
      
      vertices_xy:
        pos: base_offset + vertices_xz_offset
        type: svector_2
        repeat: expr
        repeat-expr: vertex_count
      
      vertices_z:
        pos: base_offset + verticez_z_offset
        type: s2
        repeat: expr
        repeat-expr: vertex_count
        
      normals:
        pos: base_offset + normals_offset
        type: normal
        repeat: expr
        repeat-expr: normal_count

  # ======
  # Common
  # ======

  primitive:
    seq:
      - id: u0
        type: u1

      - id: v0
        type: u1

      - id: bits0
        type: u2

      - id: u1
        type: u1

      - id: v1
        type: u1

      - id: bits1
        type: u2

      - id: u2
        type: u1

      - id: v2
        type: u1

      - id: u3
        type: u1

      - id: v3
        type: u1

      - id: face0
        type: u1

      - id: face1
        type: u1

      - id: face2
        type: u1

      - id: face3
        type: u1

      - id: unk_10
        size: 4

  svector_2:
    seq:
      - id: x
        type: s2

      - id: y
        type: s2

  normal:
    seq:
      - id: x
        type: s1

      - id: y
        type: s1

      - id: z
        type: s1

      - id: count
        type: u1
