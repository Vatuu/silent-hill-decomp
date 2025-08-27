## Code Conventions

A summary of conventions used in the project is provided below, we also include a `clang-format` configuration that can help maintain consistent code style.

Clang-format can be ran through git after staging changed files, `git clang-format` will reformat those files and leave any new formatted changes unstaged, you can then review the changes made with `git diff`, and then stage them with `git add`.

### Indentation
Code should use the Allman indentation style, placing braces on separate lines with indentations of 4 spaces.

### Pointers
Placing the asterisk with the type name is preferred, e.g. `void* name` over `void *name`.

### Naming Conventions
If a function, structure, or field's name is already known from an SDK library or from the symbols of another game, that name should be used.
Otherwise, names can follow the formats below.

#### Functions
Function names should be written in PascalCase as follows:

`[SystemName]_[Noun][Verb]`

Example:

`Demo_GameGlobalsUpdate`  
`Fs_FileRead`

This allows functions to be grouped and sorted alphabetically, which can be useful when looking at the game in a disassembler.

Function parameters and locals should be written in `camelCase` without an offset suffix.

#### Globals
Global variables should be prefixed with `g_` and follow a similar format to function names. Example:

`g_SysWork`  
`g_Demo_PrevRandSeed`

#### Structures and Enums
Struct names should be prefixed with `s_` and named according to their purpose. If the purpose is unknown, it can be associated with a static address: `s_[HexAddress]`, or a function that's known to use/initialize it: `s_func_[HexAddress]`.

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

Enum names should be prefixed with `e_` and named according to their purpose. Entries should be written in `PascalCase`, prefixed with the enum's name.

Example:

```C
typedef enum _MyEnum
{
    MyEnum_Unk0          = 0,
    MyEnum_Something     = 1,
    MyEnum_SomethingElse = 2
} e_MyEnum;
```

#### Miscellaneous
Acronyms and abbreviations should be treated as words. Example:

`GfxFunc` instead of `GFXFunc`, `myId` instead of `myID`.

Custom primitive type aliases should be used (`s32`, `u32`, `s16`, etc.) instead of the defaults of the language to ensure type sizes are always clear.

### Commenting

Comments should be included above declarations in .h files to explain the purposes of functions, structures, and global variables.

Doxygen-style tags should be included in the comment, `@brief A summary of the function`, `@param paramName Description of the parameter`, `@return Description of what is returned`.

Code that appears to be unused by the game can also be tagged with `@unused`.

Use `/** */`-style comments for formal documentation and `//`-style comments for casual development notes. Examples:

```C
/** @brief Stores my data. */
typedef struct _MyStruct
{
    VECTOR3 position_0; /** Q27.4 */
    s32     field_C;    // Maybe index?
} s_MyStruct;

/** @brief Do something.
 *
 * This function does something.
 *
 * @param dist My distance.
 * @return 0 if `dist` is greater than or equal to 0,
 *         0x10 otherwise.
 */
static inline s32 Math_MyFunc(s32 dist)
{
    if (dist >= 0)
    {
        return 0;
    }

    // Value might be enum entry from `e_MyEnum`, but it's unclear right now.
    return 0x10;
}
```
