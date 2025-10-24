#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/map7/map7_s03.h"

void Ai_BloodyIncubator_Update(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords) // 0x800D3684
{
    if (chara->model_0.charaId_0 != Chara_BloodyIncubator)
    {
        Ai_BloodyIncubator_Init(chara);
    }

    func_800D38D8(chara, coords);
    func_800D3740(chara, coords);
    func_800D36F8(chara, anmHdr, coords);
}

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/Chara_BloodyIncubator", func_800D36F8);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/Chara_BloodyIncubator", func_800D3740);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/Chara_BloodyIncubator", func_800D38D8);

void Ai_BloodyIncubator_Init(s_SubCharacter* chara) // 0x800D3BA4
{
    sharedFunc_800D923C_0_s00(chara);
}