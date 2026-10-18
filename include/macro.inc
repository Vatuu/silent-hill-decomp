# This file is used by modern gas.
# Defines the expected assembly macros

# Evaluate this file only once in case it's included more than once
.ifndef _MACRO_INC_GUARD
.internal _MACRO_INC_GUARD
.set _MACRO_INC_GUARD, 1

# A function symbol.
.macro glabel label, visibility=global
    .\visibility \label
    .type \label, @function
    \label:
        .ent \label
.endm

# The end of a function symbol.
.macro endlabel label
    .size \label, . - \label
    .end \label
.endm

# An alternative entry to a function.
.macro alabel label, visibility=global
    .\visibility \label
    .type \label, @function
    \label:
        .aent \label
.endm

# A label referenced by an error handler table.
.macro ehlabel label, visibility=global
    .\visibility \label
    \label:
.endm

# A label referenced by a jumptable.
# (Changed to local instead of global to make sure the "expected" objects don't export them as global symbols
# objdiff would try looking for that symbol name in our C-compiled obj, but compiler doesn't emit jtbl_* syms
# and since it couldn't be matched up to our obj, it'd then treat the data itself as unmatched...)
# TODO: Find how other projects handle this with their data comparisons too.
.macro jlabel label, visibility=local
    .ifdef JLABEL_LOCAL
    .\visibility \label
    .else
    .global \label
    .endif
    \label:
.endm

# A data symbol.
.macro dlabel label, visibility=global
    .\visibility \label
    .type \label, @object
    \label:
.endm

# End of a data symbol.
.macro enddlabel label
    .size \label, . - \label
.endm


# Label to signal the symbol haven't been matched yet.
.macro nonmatching label, size=1
    .global \label\().NON_MATCHING
    .type \label\().NON_MATCHING, @object
    .size \label\().NON_MATCHING, \size
    \label\().NON_MATCHING:
.endm

.include "gte_macros.inc"

.endif
