## Code Conventions
Code should use the Allman indentation style, placing braces on separate lines with indentations of 4 spaces. For pointers, `void* name` is preferred over `void *name`.

Comments should be included above declarations in .h files to explain the purposes of functions, structures, and global variables. Example:

```C
/**
 * @brief Make Harry fly (not a real function).
 * 
 * This function sets Harry's Y position to 100 world units.
 *
 * @param isFlying Fly status.
 * @param yPos Pointer to Harry's Y position.
 */
void Hero_SetFly(bool isFlying, int* yPos) // 0x81234567
{
    if (isFlying)
    {
        *yPos = 100;
    }
}
```

#### Clang-format
Our repository includes a `clang-format` configuration to help ensure code consistency. Git also has support for automatically formatting modified files.

We’d appreciate it if you could follow these steps prior to committing:

1. Stage modified files:  
   `git add src/`  
   `git add include/`
2. Run clang-format through git:  
   `git clang-format`
3. Review the changes with `git diff`, then re-stage and commit them:  
   `git add src/`

## Naming Conventions
If a function, structure, or field's name is already known from an SDK library or from the symbols of another game, that name should be used.
Guesses for names should follow the formats below.

### Functions
Function names should be written in PascalCase, following this format:

`[SystemName]_[Noun][Verb]`

For example:

`Demo_GameGlobalsUpdate`  
`Fs_FileRead`

This allows functions to be grouped and sorted alphabetically, which can be useful when looking at the game in a disassembler.

Function parameters should be written in `camelCase` without an offset suffix.

### Globals
Global variables should be prefixed with `g_` and follow a similar format to function names. Example:

`g_SysWork`  
`g_Demo_PrevRandSeed`

### Structures
Struct names should be prefixed with `s_` and named according to their purpose. If the usage is unknown, they can be named categorically according to the system they belong to: `s_CreditsStruct0`. If a struct is only held at a static address, `s_[HexAddress]` can be used.

Fields inside structures should be written in `camelCase` with a hex offset suffix. Keeping the offset as part of the name is useful in tracking each field's expected offset and more easily determining when any have moved around due to other changes. Additionally, names should be aligned with indentations. Example:

```C
typedef struct
{
    int      frameCounter_1C;
    s_Entity entities_20[6];
    int      field_320;
    int      pad_324;
} s_MyStruct;
```

Fields known to be accessed but without a known purpose should be named `field_[HexOffset]`, while fields that are completely unknown or which serve as padding should be named as `unk_[HexOffset]`
or `pad_[HexOffset]`.
