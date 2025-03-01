## Code Conventions
Code should use the Allman indentation style, placing braces on separate lines, with an indentation of 4 spaces - for pointers, `void* name` is preferred over `void *name`.

Comments should also be included to give the function address, and ideally explain the purpose of functions or code blocks, eg:

```C
// 0x81234567 - debug function that makes harry fly (not actually part of the game)
void Chara_HarrySetFly(bool is_flying, int* char_z)
{
    if (is_flying)
    {
        *char_z = 100; // set harry to 100 units above the map
    }
}
```

## Naming Conventions
If the name of a function/structure/field is already known (from some kind of SDK library/header, or symbols of another title) that name should be used as-is, but guesses for names should try to follow the formats below.

### Functions
Function names should be written in CamelCase, and try to follow the format:

`[SystemName]_[Noun][Verb]`

For example:

`Demo_GameGlobalsUpdate`  
`FS_FileRead`

This allows us to easily sort functions alphabetically and have related functions kept grouped together, which can be useful when looking into the game using a disassembler.

Function parameters should try to be written in `snake_case`, similar to structure fields below, but without any offset/register needing to be appended (though this is more of a suggestion than a requirement)

### Globals
Global variables should begin with `g_` and try to use the same form as functions, for example:

`g_SysWork`  
`g_Demo_RandSeedPrevious`

### Structures
Structure names should begin with `s_`, named according to their usage, though if the usage isn't completely understood (or seems to be used for multiple things), naming as `s_[HexAddress]` can be used when the structure is only ever held at a static address.

Fields inside structures should be written in `snake_case`, with the field offset appended to it - keeping the offset as part of the name allows us to track the expected offset for each field, and more easily notice if any have moved around due to other changes.

For example:

```C
int frame_counter_1C;
s_CharaInfo characters_20[6];
int ammo_amount_320;
```

Fields that are known to be accessed but without a known purpose should just be named `field_XYZ`, while fields that are completely unknown/padding bytes should be named as `unk_XYZ`.
