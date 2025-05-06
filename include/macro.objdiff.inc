.macro glabel label
    .global \label
    .type \label, @function
    \label:
.endm

.macro dlabel label
    .global \label
    \label:
.endm

/* macro.objdiff.inc: removed .global line from jlabel */
.macro jlabel label
    \label:
.endm

.macro move a, b
    addu \a, \b, $zero
.endm

.include "gte.inc"
