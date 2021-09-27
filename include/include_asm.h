#ifndef INCLUDE_ASM_H
#define INCLUDE_ASM_H

#define STRINGIFY_(x) #x
#define STRINGIFY(x) STRINGIFY_(x)

#ifndef PERMUTER

#ifndef INCLUDE_ASM

#define TARGET bootloader
// #ifdef TARGET_BOOTLOADER
// #else
// #endif

#define INCLUDE_ASM(TYPE, FOLDER, NAME, ARGS...) \
__asm__( \
    ".section .text\n" \
    "\t.align\t2\n" \
    "\t.globl\t"#NAME"\n" \
    "\t.ent\t"#NAME"\n" \
    #NAME ":\n" \
    ".include \"asm/"STRINGIFY(TARGET)"/nonmatchings/"FOLDER"/"#NAME".s\"\n" \
    "\t.set reorder\n" \
    "\t.set at\n" \
    "\t.end\t"#NAME \
);
#endif

// omit .global
__asm__(".include \"include/include_asm.inc\"\n");

#else
#define INCLUDE_ASM(TYPE, FOLDER, NAME, ARGS...)
#endif


#endif
