## Code Conventions

### Format
Code uses the Allman indentation style, placing braces on separate lines with indentations of 4 spaces.

```C
s32 func_XXXXXXXX(s32 arg0)
{
    if (globalVariable0 == 1)
    {
        return arg0 == 1;
    }
    else if (globalVariable0 == 2)
    {
        return -1;
    }
    else
    {
        return arg0 > 5
    }
}
```

### Alignment

#### Structs and enums
When adding fields an entries to structs and enums, vertical alignment is applied.

Structs:
```C
...
s16                           field_XX
superDuperMegaLargeStructName largeStruct_XX
s64                           audioFilenameData_XX
strangeStruct                 haveYouSeenALilGirl_XX
...
```

Enums:
```C
...
myEnum_Black  = 0,
myEnum_White  = 1,
myEnum_Bed    = 2,
myEnum_Been   = 3,
myEnum_Orange = 4
...
```

#### Variables and struct fields
If a value is assigned to multiple stacked variables with names of varying lengths, vertical alignment of the `=` operator is applied.

```C
...
var_s0            = 0;
var_temp_a1      += 0;
g_DeltaTime0      = 0;
g_UncappedVBlanks = 0;
...
```

If three or more variables can be logically grouped, a newline is applied between them.

```C
...
var_a0      = 19;
var_s0      = 99;
var_s1      = true;
var_temp_a1 = 10;

g_GlobalVar.player_0.field_E3        = 0;
g_GlobalVar.player_0.health_20       = 0;
g_GlobalVar.playerSave_2024.field_F3 = 1;
...
```

If variable groups are mixed, they can be stacked together.

```C
...
var_a0                                      = 19;
var_s0                                      = 99;
g_StructNumberXXXX.player_0.field_E3        = 0;
g_StructNumberXXXX.player_0.health_20       = 0;
var_s1                                      = true;
var_temp_a1                                 = 10;
g_StructNumberXXXX.playerSave_2024.field_F3 = 1;
...
```

### Types
Custom primitive type aliases such as `s32`, `s16`, `u16`, etc. (defined in `include/types.h`) are used instead of the idiomatic ones available in C to ensure type sizes are always clear.

For pointers, `void* name` is preferred over `void *name`.

It is recommended to learn a little about fixed-point math, as *Silent Hill* uses it extensively due to the lack of a floating-point unit in the PSX hardware. Special macros (see `include/bodyprog/math/fixed_point.h`) are provided for high-level abstractions of Q formats to make the code more flexible and comprehensible.

### Constants
Use constants for commonly reused values to avoid magic.

```
#define INVENTORY_ITEM_COUNT_MAX 40

s32  inventoryItems[INVENTORY_ITEM_COUNT_MAX];
bool validInventoryItems[INVENTORY_ITEM_COUNT_MAX];
...
```

### Conditionals
Use parentheses judiciously to aid legibility (i.e. making the order of arithmetic operations clear or encapsulating bitwise checks).

For example:
```
// Don't do this.
if ((!(g_Player_Health + 1 * 2 == FP_HEALTH(30.0f))) && (g_Player_SomeFlag & (1 << 5)) && (g_Player_IsAlive == 1))


// Do this.
if ((g_player_Health + (1 * 2)) != FP_HEALTH(30.0f) && (g_Player_SomeFlag & (1 << 5)) && && g_Player_IsAlive == 1)
```

For boolean values, avoid using comparison operators.
Because the C language doesn't have a true `bool` type, a typedef is provided. Note that some boolean checks involving comparisons with values other than 0 still require a comparison operator in order for the compiled code to match.

For example:
```
// Don't do this.
if (g_Player_IsAlive == 0)

if (g_Player_IsAlive != 0)

if (g_Player_IsAlive == 1)

// Do this.
if (!g_Player_IsAlive)

if (g_Player_IsAlive)

if (g_Player_IsAlive == true)
```

### Organization Tools

#### Clang-format
The repository includes a `clang-format` configuration to help enforce code consistency. Git also has a command to handle formatting modified files.

Follow these steps prior to committing:

1. Stage modified files:</br>
   `git add src/`</br>
   `git add include/`</br>
2. Run clang-format through git:</br>
   `git clang-format`</br>
3. Review the changes with `git diff`, then re-stage and commit them:</br>
   `git add src/`

#### configs_formatter.py
A Python script is provided to rearrange registered symbol in `*.sym.txt` files based on addresses. Prior to committing, run it with `python3 tools/configs_formatter.py`.

## Naming Conventions
If the original name of a function, enum, or struct and most of its variables, entries, or fields are known, those names should be used.

If the original names are unknown, follow a systematic naming pattern.

### General
Function names are written in `PascalCase`, using non-contracted words and prefixed with the subsystem they belong to. The prefix allows functions to be grouped for visual reference.

`[SystemName]_[Noun][Verb]`</br>
`[SystemName]_[SubSystemName]_[Noun][Verb]`

### Functions
Function parameters are written in `camelCase` with the names contracted judiciously.

`Demo_GameGlobalsUpdate()`</br>
`Fs_QueueStartSeek(s32 fileIdx)`</br>
`GameState_KcetLogo_Update()`</br>
`Options_MainOptionsMenu_VolumeBarDraw(bool isSfx, u8 vol)`</br>

Acronyms and abbreviations are treated as words.

`Gfx_Function` instead of `GFX_Func`, `myId` instead of `myID`.

### Globals
Global variables are prefixed with `g_`. It's recommended to also use subsystem prefixes to avoid confusion with globals of other subsystems with similar names.

Examples:

`g_LastSaveIdx`</br>
`g_Inventory_IsUpClicked`</br>
`g_Player_AttackAnimIdx`

### Structures
Structs are prefixed with `s_` and named according to their purpose in `PascalCase`.

If a struct's purpose can't be deduced, name it after a related hex address:
* If used in a global variable: `s_[GlobalVariableHexAddress]`.
* If used as a parameter type in a function: `s_func_[FunctionHexAddress]`.
* If used in the field of another struct: `s_[ParentStructName]_[FieldHexOffset]`.

Struct fields are written in `camelCase` and suffixed with a hexadecimal offset. Keeping the offset as part of the name helps track each field's expected offset and allows to easily determine if any have moved around due to other changes.

If the field is part of a bitfield, the field offset should always be where the bitfield begins, with the decimal bit index of the field appended to it (e.g. bit 8 would use the same field offset as bit 0, but with `_8` appended) because assembly code normally loads bitfields from bit 0 and shifts/masks to retrieve values.

Fields known to be accessed but without a definitive purpose are named `field_[HexOffset]`, while fields completely unknown or which serve as padding are named `unk_[HexOffset]`. If the field is only used to store power-of-2 flag values, it can be named `flags_[HexOffset]`.

If the size of a struct is known definitively (e.g. from `bzero` usages or loops using the struct), use the `STATIC_ASSERT_SIZEOF` macro to enforce it.

Example:

```C
typedef struct _MyStruct
{
    s32      frameCounter_1C;
    s_Entity entities_20[6];
    s32      field_320;
    u8       __pad_324;
    s8       unk_325[3];
    u32      field_328_0 : 3;
    u32      field_328_3 : 5;
    u32      field_328_8 : 8; // Even though this starts at 8th bit, the offset is where the bitfield began.
} s_MyStruct;
STATIC_ASSERT_SIZEOF(s_MyStruct, 810);
```

### Enumerators
Enums are prefixed with `e_` and named according to their purpose in `PascalCase`. Entries are also written in `PascalCase`, prefixed with the enum's name.

Example:

```C
typedef enum _MyEnum
{
    MyEnum_Unk0          = 0,
    MyEnum_Something     = 1,
    MyEnum_SomethingElse = 2
} e_MyEnum;
```

### Defines/Macros
Macros are named according to their purpose. The format they should follow depends on their utility.
* Constants and constant-like macros: `SCREAMING_SNAKE_CASE`.
* Function-like macros: `PascalCase` with a subsystem prefix.
`camelCase` is used for macro parameters.

```C
#define MAP_MESSAGE_DISPLAY_ALL_LENGTH 400
```

```C
#define SCREEN_POSITION_X(percent) \
    (s32)((SCREEN_WIDTH) * ((percent) / 100.0f))
```

```C
#define Rng_TestProbabilityBits(bits) \
    (Rng_Rand16() & ((1 << (bits)) - 1))
```

## Comments
Use `/** */`-style comments for formal documentation and `//`-style comments for casual development notes. Example:

Structs (also applies for enums):
```C
/** @brief Stores my data.
 *
 * This struct stores my precious data no one should touch.
 */
typedef struct _MyStruct
{
    VECTOR3 position_0; /** The position of my house.
                         *
                         * Totally serious description of the data inside the value
                         * and its usage.
                         */
    s32     field_C;     // Maybe index?
} s_MyStruct;
```

Functions (also applies for macros):
``` C
s32 Math_MyFunc(s32 dist) // 0xXXXXXXXX
{
    // Normally this value is -1.
    if (dist >= 0)
    {
        return 0;
    }

    do {} while(0) // Hack.

    // Value might be enum entry from `e_MyEnum`, but it's unclear right now.
    return 0x10;
}
```

Documentation comments are included above declarations in \*.h files to explain the purposes of functions, global variables, enums, structs, and macros. They follow the Doxygen format.

Functions:
```C
/** @brief Makes Harry fly.
 *
 * Sets Harry's Y position to 100 world units.
 *
 * @param isFlying: Fly status.
 * @param yPos: Pointer to Harry's Y position.
 */
void Hero_SetFly(bool isFlying, int* yPos); // 0x80012345

/** @brief Checks enemy's state.
 *
 * Checks the current state of the enemy being passed through the argument.
 *
 * @param enemyPtr: Pointer to enemy's struct.
 * @return Value from `e_EnemyState`.
 */
s32 Enemy_StateCheck(s_EnemyStruct* enemyPtr); // 0x80012345
```

Global variables:
```C
/** @brief Current count of ammo the player has. */
extern s32 g_Player_WeaponCurrentAmmo; // 0x800A2345
```

The tags `@note`, `@unused` and `@bug` are used to tag anything noteworthy.

```C
/** @unused Some boolean statuses for each save slot.
 *
 * Apparently related to the color of the borders of the save file, but
 * appears nothing more than being constantly redifined to 1 or 0.
 */
extern s16 D_801E7514[2];

/** @brief Main player colision handler.
 *
 * @bug If the player attacks with the Katana and in middle of the movement,
 * he can be grabbed as collision behaves incorrectly.
 */
void Player_Colision(); // 0x8000XXXX

/** @brief Struct containing enemy data.
 *
 * @note Also used for NPCs.
 */
typedef struct _EnemyStruct
{
...
}
```
