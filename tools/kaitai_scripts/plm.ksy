meta:
  id: plm
  title: Silent Hill (PSX) Global Map Prop Model Format
  file-extension: plm
  endian: le
  encoding: ASCII
  imports:
    - lm

doc: |
  PLM is the 3D model format used for global map props in Silent Hill.
  The base format is LM.

  Unlike an ILM, bone IDs store the first two `char`s of bone names instead of
  indices.

seq:
  - id: lm
    type: lm(0)
