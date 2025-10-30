#ifndef _INCLUDE_ASM_H
#define _INCLUDE_ASM_H

#if !defined(SPLAT) && !defined(M2CTX) && !defined(PERMUTER) && !defined(SKIP_ASM)

        #ifndef INCLUDE_ASM
                #define INCLUDE_ASM(FOLDER, NAME) \
                void __maspsx_include_asm_hack_##NAME() { \
                        __asm__( \
                        ".text # maspsx-keep \n" \
                        "\t.align\t2 # maspsx-keep\n" \
                        "\t.set noreorder # maspsx-keep\n" \
                        "\t.set noat # maspsx-keep\n" \
                        ".include \""FOLDER"/"#NAME".s\" # maspsx-keep\n" \
                        "\t.set reorder # maspsx-keep\n" \
                        "\t.set at # maspsx-keep\n" \
                        ); \
                }
        #endif

        #ifndef INCLUDE_RODATA
                #define INCLUDE_RODATA(FOLDER, NAME)                                                 \
                        __asm__(".section .rodata\n"                                                 \
                                "\t.include \"" FOLDER "/" #NAME ".s\"\n"                            \
                                ".section .text")
        #endif

        __asm__(".include \"macro.inc\"\n"
                "\t.set\treorder\n"
                "\t.set\tat\n");

#else
        #ifndef INCLUDE_ASM
                #define INCLUDE_ASM(FOLDER, NAME)
        #endif
        #ifndef INCLUDE_RODATA
                #define INCLUDE_RODATA(FOLDER, NAME)
        #endif
#endif

#endif
