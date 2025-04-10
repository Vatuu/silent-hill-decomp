## Code Conventions
Code should use the Allman indentation style, placing braces on separate lines with indentations of 4 spaces. For pointers, `void* name` is preferred over `void *name`.

Comments should be included above declarations in .h files to explain the purposes of functions, structures, and global variables. Example:

```C
/** @brief Make Harry fly (not a real function).
 * 
 * This function sets Harry's Y position to 100 world units.
 *
 * @param isFlying Fly status.
 * @param yPos Pointer to Harry's Y position.
 */
void Hero_SetFly(bool isFlying, int* yPos) // 0x80012345
{
    if (isFlying)
    {
        *yPos = 100;
    }
}
```

#### Clang-format
The repository includes a `clang-format` configuration to help ensure code consistency. Git also has a command to handle formatting any modified files.

We'd appreciate it if you could follow these steps prior to committing:

1. Stage modified files:  
   `git add src/`  
   `git add include/`
2. Run clang-format through git:  
   `git clang-format`
3. Review the changes with `git diff`, then re-stage and commit them:  
   `git add src/`

## Naming Conventions
If a function, structure, or field's name is already known from an SDK library or from the symbols of another game, that name should be used.
Otherwise, names can follow the formats below.

### Functions
Function names should be written in PascalCase as follows:

`[SystemName]_[Noun][Verb]`

Example:

`Demo_GameGlobalsUpdate`  
`Fs_FileRead`

This allows functions to be grouped and sorted alphabetically, which can be useful when looking at the game in a disassembler.

Function parameters should be written in `camelCase` without an offset suffix.

### Globals
Global variables should be prefixed with `g_` and follow a similar format to function names. Example:

`g_SysWork`  
`g_Demo_PrevRandSeed`

### Structures and Enums
Struct names should be prefixed with `s_` and named according to their purpose. If the purpose is unknown, it can be associated with a static address: `s_[HexAddress]`.

Structure fields should be written in `camelCase` with a hex offset suffix. Keeping the offset as part of the name is useful in tracking each field's expected offset and more easily determining when any have moved around due to other changes. Fields known to be accessed but without a known purpose should be named `field_[HexOffset]`, while fields that are completely unknown or which serve as padding should be named as `unk_[HexOffset]` or `pad_[HexOffset]`. If the size of a struct is known, the `STATIC_ASSERT_SIZEOF` macro can be used to enforce it.

Additionally, names should be aligned with indentations.

Example:

```C
typedef struct _MyStruct
{
    s32      frameCounter_1C;
    s_Entity entities_20[6];
    s32      field_320;
    u8       pad_324;
    s8       unk_325[2];
} s_MyStruct;
STATIC_ASSERT_SIZEOF(s_MyStruct, 806);
```

Enum names should be prefixed with `e_` and named according to their purpose. Entries should be written in `PamelCase`, prefixed with the enum's name.

Example:

```C
typedef enum _MyEnum
{
    MyEnum_Unk0          0,
    MyEnum_Something     1,
    MyEnum_SomethingElse 2
} e_MyEnum;
```

### Miscellaneous
Acronyms and abbreviations should be treated as words. Example:

`GfxFunc` instead of `GFXFunc`, `myId` instead of `myID`.

Custom primitive type aliases should be used (`s32`, `u32`, `s16`, etc.) instead of the defaults of the language to ensure type sizes are always clear.
