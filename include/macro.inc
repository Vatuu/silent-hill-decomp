# Assembly Macros

.macro glabel label
    .global \label
    .balign 4
    \label:
.endm

.macro move a, b
    addu \a, \b, $zero
.endm

