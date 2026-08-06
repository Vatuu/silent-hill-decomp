meta:
  id: dat
  title: Silent Hill (PSX) Demo Playback Format
  file-extension: dat
  endian: le
  encoding: ASCII

doc: |
  DAT is the demo playback format used in Silent Hill. This spec covers all
  `MISC/PLAY****.DAT` files.

seq:
  - id: analog_controller
    type: analog_controller

  - id: game_state_expected
    type: s1

  - id: video_present_interval
    type: s1

  - id: unk_a
    size: 2

  - id: rand_seed
    type: u4

types:
  analog_controller:
    seq:
      - id: status
        type: u1

      - id: received_bytes
        type: b4

      - id: terminal_type
        type: b4

      - id: digital_buttons
        type: u2

      - id: right_x
        type: u1

      - id: right_y
        type: u1

      - id: left_x
        type: u1

      - id: left_y
        type: u1
