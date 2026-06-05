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

      - size: 9

      - id: model_info_offset
        type: u4

      - id: model_buffers_offset
        type: u4

      - id: texture_count
        type: u1

      - id: unk_1d
        size: 51

      - id: model_order_list_offset
        type: u4

      - id: collision_data
        type: ipd_collision_data

    instances:
      lm_header:
        pos: lm_header_offset
        type: lm_header(lm_header_offset)

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

  ipd_model_info:
    seq:
      - id: is_global_plm
        type: u1

      - size: 3

      - id: name
        type: strz
        size: 8

      - id: model_header_offset
        type: u4

  ipd_model_buffer:
    seq:
      - id: model_instance_count
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

      - id: model_instances_offset
        type: u4

      - id: field_10_offset
        type: u4
        doc: Q7.8

      - id: subcell_positions_offset
        type: u4
        doc: Q7.8

  ipd_collision_data:
    seq:
      - id: position_x
        type: s4
        doc: Q23.8

      - id: position_z
        type: s4
        doc: Q23.8

      - id: split_vertex_count
        type: b8

      - id: surface_count
        type: b8

      - id: subcell_count
        type: b8

      - id: ptr_18_count
        type: b8

      - id: split_vertices_offset
        type: u4

      - id: surfaces_offset
        type: u4

      - id: subcells_offset
        type: u4

      - id: ptrs_18_offset
        type: u4

      - id: subcell_size
        type: s2

      - id: subcell_x_count
        type: u1

      - id: subcell_z_count
        type: u1

      - id: subcell_ranges_offset
        type: u4

      - id: field_24
        type: u2

      - id: field_26
        type: u2

      - id: ptr_28
        type: u4

      - id: ptr_2c
        type: u4

      - id: subcell_check_count
        type: u1

      - size: 3

      - id: field_34
        size: 256

    instances:
      split_vertices:
        pos: split_vertices_offset
        type: svector_3
        repeat: expr
        repeat-expr: split_vertex_count
        doc: TODO Wrong offset.

      surfaces:
        pos: surfaces_offset
        type: ipd_coll_surface
        repeat: expr
        repeat-expr: surface_count
        doc: TODO Wrong offset.

      subcells:
        pos: subcells_offset
        type: ipd_subcell
        repeat: expr
        repeat-expr: subcell_count
        doc: TODO Wrong offset.

      ptrs_18:
        pos: ptrs_18_offset
        type: ipd_coll_data_18
        repeat: expr
        repeat-expr: ptr_18_count
        doc: TODO Wrong offset.

      subcell_ranges:
        pos: subcell_ranges_offset
        type: ipd_coll_subcell_range
        repeat: expr
        repeat-expr: subcell_size
        doc: TODO Wrong offset. Also which field has the count??

  # =========
  # COLLISION
  # =========

  ipd_coll_surface:
    seq:
      - id: field_0
        type: s2

      - id: field_2
        type: s2

      - id: field_4
        type: s2

      - id: ground_type
        type: b5

      - id: disable_height
        type: b3

      - id: field_5_8
        type: b3

      - id: field_6_11
        type: b4

      - id: tilt_angle_x
        type: s2

      - id: tilt_angle_z
        type: s2

  ipd_subcell:
    seq:
      - id: field_0_0
        type: b14

      - id: field_0_14
        type: b2

      - id: field_2_0
        type: b14

      - id: field_2_14
        type: b2

      - id: split_vertex_idx_0
        type: u1

      - id: split_vertex_idx_1
        type: u1

      - id: surface_idx_0
        type: u1

      - id: surface_idx_1
        type: u1

  ipd_coll_data_18:
    seq:
      - id: ground_type
        type: b5

      - id: disable_height
        type: b3

      - id: field_0_8
        type: b4

      - id: field_0_12
        type: b3

      - id: field_0_15
        type: b1

      - id: offset
        type: svector_3

      - id: field_8
        type: u2

  ipd_coll_subcell_range:
    seq:
      - id: field_0
        type: s2

      - id: field_2
        type: s2
  
  # ========
  # PLM (LM)
  # ========

  lm_header:
    params:
      - id: base_offset
        type: u4

    seq:
      - id: magic
        contents: [0x30]

      - id: version
        type: u1

      - id: is_loaded
        type: u1

      - id: material_count
        type: u1

      - id: materials_offset
        type: u4

      - id: model_count
        type: u1

      - size: 3

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

      - id: field_b_0
        type: b1

      - id: field_b_1
        type: b3

      - id: field_b_4
        type: b2

      - id: field_b_6
        type: b2

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

      - id: unk_ptrs_14_offset
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

  svector_3:
    seq:
      - id: x
        type: s2

      - id: y
        type: s2

      - id: z
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
