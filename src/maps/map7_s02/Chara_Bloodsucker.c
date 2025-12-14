#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/map7/map7_s02.h"

#include "inline_no_dmpsx.h"
#include <psyq/gtemac.h>

// TODO: Move to src/maps/characters/ once other map usages are split.

#include "maps/shared/Ai_Bloodsucker_Update.h" // 0x800D6874

#include "maps/shared/Ai_Bloodsucker_Init.h" // 0x800D6B8C

#include "maps/shared/sharedFunc_800D0E20_3_s03.h" // 0x800D6C20

#include "maps/shared/sharedSymbol_800D0E38_3_s03.h" // 0x800D6C38

#include "maps/shared/sharedFunc_800D0E80_3_s03.h" // 0x800D6C40

#include "maps/shared/sharedSymbol_800D0ECC_3_s03.h" // 0x800D6C8C

#include "maps/shared/sharedFunc_800D0F28_3_s03.h" // 0x800D6C94
