# Assembly Macros

.macro glabel label
    .global \label
    .balign 4
    \label:
.endm
