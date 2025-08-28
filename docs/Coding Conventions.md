## Code Conventions

### Format
Code should use the Allman indentation style, placing braces on separate lines with indentations of 4 spaces.

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
When adding fields from structs and enums align assignment should be applied.

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
In case a value is assigned for multiple local and global variables with different size names that are next to each other then they should be joined and apply align assignment.

```C
...
var_s0            = 0;
var_temp_a1       = 0;
g_DeltaTime0      = 0;
g_UncappedVBlanks = 0;
...
```

If after three continuous variable assignment, two or more struct fields values are assigned then a space should be applied only if where the code is encapsulated is doing anything else more than just assigning values for example:

```C
...
if (!g_GlobalVariable0)
{
	var_a0      = 19;
	var_s0      = 99;
	var_s1      = True;
	var_temp_a1 = 10;
	
	g_StructNumberXXXX.player_0.field_E3        = 0;
	g_StructNumberXXXX.player_0.health_20       = 0;
	g_StructNumberXXXX.playerSave_2024.field_F3 = 1;
	
	if (g_GlobalVariable1 == 30)
	{
		return func_XXXXXXXX;
	}
}
...
```

In case the code encapsulated is just doing value assignation all variables and struct fields should be joined together.

```C
...
if (!g_GlobalVariable0)
{
	var_a0                                      = 19;
	var_s0                                      = 99;
	g_StructNumberXXXX.player_0.field_E3        = 0;
	g_StructNumberXXXX.player_0.health_20       = 0;
	var_s1                                      = True;
	var_temp_a1                                 = 10;
	g_StructNumberXXXX.playerSave_2024.field_F3 = 1;
}
...
```

### Types
Custom primitive type aliases (defined at `include/types.h`) should be used instead of the defaults of the language to ensure type sizes are always clear.

For pointers, `void* name` is preferred over `void *name`.

It is heavily recommended learning a little about PSX's fixed-point in order to apply them properly. Due to the lack of floating point support PSX devs used this "fixed-point" types. We apply this types and some special conversion macros (see `include/bodyprog/math.h`) in order to create a more flexible and comprehensible code.

### Shared defines
Under some instances we use defines in order to define the amount of elements a piece of code uses. The creation and usage of them depends entirely in the interpretation of the member working based on what can be seen in the code.

See for examples:
* `INVENTORY_ITEM_COUNT_MAX` used to define the amount of items the player can hold in the inventory and is normally used in many circumstances related to the code accessing to items data.
* `MEMORY_CARD_SLOT_COUNT` used to define the amount of memory cards the player can connect to the game and it's generally used by array declarations and accessing memory card data.
* `NPC_COUNT_MAX` used to define the max amount of NPCs the game can load and the code uses in the instances where it accesses to all of the currently loaded NPCs.

### Conditionals
We recommend under the possible the reduction of braces to only the needed.

For example:
```
// Don't do this.
if (!(g_Player_Health == FP_HEALTH(30.0f)) && (g_Player_Flag & (1 << 5)))


// Do this.
if (g_playerHealth != FP_HEALTH(30.0f) && g_Player_Flag & (1 << 5))
```

For boolean values don't use comparison operators.

For example:
```
// Don't do this.
if (g_Player_IsAlive == 0)

if (g_Player_IsAlive != 0)


// Do this.
if (g_Player_IsAlive)

if (!g_Player_IsAlive)
```

### Clang-format
The repository includes a `clang-format` configuration to help ensure code consistency. Git also has a command to handle formatting any modified files.

We'd appreciate it if you could follow these steps prior to committing:

1. Stage modified files:</br>
   `git add src/`</br>
   `git add include/`</br>
2. Run clang-format through git:</br>
   `git clang-format`</br>
3. Review the changes with `git diff`, then re-stage and commit them:</br>
   `git add src/`

## Naming Conventions
If a function, enum or struct and most or all of their field's names are known that name should be used.

Excepting the case of PS1's SDK (PSY-Q) it is recommended to put a comment either in the declaration or in the `*.sym.txt` file clarifying the name has been retrieved from another game. 

In case no name has been able to be located then follow the guidelines below:

### General
Names should be written in a limited version of `Pascal_Snake_Case` as only after system names an undercore can be applied as follows:

`[SystemName]_[Noun][Verb]`</br>
`[SystemName]_[SubSystemName]_[Noun][Verb]`

Acronyms and abbreviations should be treated as words. Example:

`GfxFunc` instead of `GFXFunc`, `myId` instead of `myID`.

### Functions
Function parameters should be written in `camelCase`.

Examples:

`Demo_GameGlobalsUpdate()`</br>
`Fs_QueueStartSeek(s32 fileIdx)`</br>
`GameState_KcetLogo_Update()`</br>
`Options_MainOptionsMenu_VolumeBarDraw(bool isSfx, u8 vol)`</br>

This allows functions to be grouped, which can be useful at the moment of comprehend the functionallity of a code.

### Globals
Global variables should be prefixed with `g_` and follow a the previosuly stablished naming format. Under this cases is not obligatory to follow it, but still heavily recommended to specify the system, specially under cases where names could cause confusion with other systems.

Examples:

`g_LastSaveIdx`</br>
`g_Inventory_IsUpClicked`</br>
`g_Player_AttackAnimIdx`

### Structures
Structs should be prefixed with `s_` and named according to their purpose.

However there are many intances where a struct purpose can't be recognized.
* In case the unrecognized struct it is declared in the code name the unrecognized struct using the address where it locates in this way: `s_[HexAddress]`
* In case the unrecognized struct is from a function which uses a pointer struct variable name it the same way the function that is being decompiled is named, for example: `s_func_800625F4`
* In case the unrecognized struct is part from another struct (either being a simple struct or a pointer one) name it the same way the main struct is named and add a underscore at the end of the name with the position where it is defined on the original struct, for example: `s_SysWork_2514`

Struct fields should be written in pure `camelCase` and at the end the offset of the field in hexadecimal. Keeping the offset as part of the name is useful in tracking each field's expected offset and more easily determining when any have moved around due to other changes. Fields known to be accessed but without a known purpose should be named `field_[HexOffset]`, while fields that are completely unknown or which serve as padding should be named as `unk_[HexOffset]`. If the size of a struct is known, the `STATIC_ASSERT_SIZEOF` macro can be used to enforce it.

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

### Enumerators
Enums should be prefixed with `e_` and named according to their purpose. Entries should be written in `PascalCase`, prefixed with the enum's name.

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
Macros should be named according to their purpose. The format they should follow depends on what they produce:
* In case of producing a constant value (for example: Screen position X) `SCREAMING_SNAKE_CASE` should be used.
* In case of producing a set of intructions that get incrusted in the function (similar to inline functions) `Pascal_Snake_Case` should be used.
In any case `camelCase` should be used for the arguments.

For example:
```C
#define SCREEN_POSITION_X(percent) \
    (s32)((SCREEN_WIDTH) * ((percent) / 100.0f))
```

Defines should be named according while using `SCREAMING_SNAKE_CASE` format.

For example:
```C
#define MAP_MESSAGE_DISPLAY_ALL_LENGTH 400
```

## Comments
Use `/** */`-style comments for formal documentation and `//`-style comments for casual development notes. Example:

Struct (applies for enums):
```C
/** @brief Stores my data.
 *
 * This struct store my precious data no one should touch.
 */
typedef struct _MyStruct
{
    VECTOR3 position_0; /** The position of my house.
	                     *
						 * Totally serious description of the data inside the value
						 * and it's usage.
	                     */
    s32     field_C;    // Maybe index?
} s_MyStruct;
```

Function (applies for macros):
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

Documentation comments should be included above declarations in \*.h files to explain the purposes of functions and global variables and in case of being required of enums, structs and macros. Additionally for documentation comments use the tags `@brief` for describing in a simpler way the purpose of the function, global variable, struct or enum and `@param` and `@return` for document the arguments and return value of a function in case it has them. Examples:

Function:
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

Global variable:
```C
/** @brief Current count of ammo the player has. */
extern s32 g_Player_WeaponCurrentAmmo; // 0x800A2345
```

Additionally use the tags  `@note`, `@unused` and `@bug` for additional documentation, document unused pieces of code and unintended game/code behaviour.

```C
/** @unused Some boolean statuses for each save slot.
 *
 * Apparently related to the color of the borders of the save file, but
 * appears nothing more than being constantly redifined to 1 or 0.
 */
extern s16 D_801E7514[2];

/** @brief Main player colision handler.
 *
 * @bug If the player attack with the katana and in middle of the movement
 * get grabbed the colisions will behave incorrectly.
 */
void Player_Colision(); // 0x8000XXXX

/** @brief Struct on charge of the data for enemies.
 *
 * @note Aparently the code uses this same struct for NPCs.
 */
typedef struct _EnemyStruct
{
...
}
```