meta:
  id: anm
  title: Silent Hill 1 Animation Format
  file-extension: anm
  endian: le

doc: |
  ANM is the proprietary 3D animation format of Silent Hill (PSX).

  The body is a list of frames, each frame containing a section of translations
  for the first `num_translation_bones` bones, followed by a section of rotations
  for the next `num_rotation_bones` bones.

  The header contains base translations for all bones, as well as a magic value
  that is the offset to the first frame.

seq:
  - id: magic
    type: s2

  - id: num_rotations
    type: u1

  - id: num_translations
    type: u1

  - id: frame_size
    type: s2
    valid:
      eq: num_rotations * 9 + num_translations * 3

  - id: num_bones
    type: s2

  - id: flags
    type: s4

  - id: end_ofs
    type: s4

  - id: num_frames
    type: u2

  - id: scale_log2
    type: u1
    doc: translations are scaled by 1 << scale_log2

  - type: u1

  - id: bones
    type: bone
    repeat: expr
    repeat-expr: num_bones

instances:
  frames:
    type: frame(_index)
    pos: magic
    repeat: expr
    repeat-expr: num_frames

  transforms_per_frame:
    value: num_rotations + num_translations

types:
  frame:
    params:
      - id: frame_index
        type: u2
    seq:
      - id: translations
        type: translation
        repeat: expr
        repeat-expr: _root.num_translations
      - id: rotations
        type: rotation
        repeat: expr
        repeat-expr: _root.num_rotations

  bone:
    seq:
      - id: parent
        type: s1

      - id: rotation_index
        type: s1

      - id: translation_index
        type: s1

      - id: bind_translation
        type: translation

  translation:
    seq:
      - id: x
        type: s1
      - id: y
        type: s1
      - id: z
        type: s1

  rotation:
    doc: 3x3 matrix, signed fixed point with 7 fraction bits
    seq:
      - id: value
        type: s1
        repeat: expr
        repeat-expr: 9
