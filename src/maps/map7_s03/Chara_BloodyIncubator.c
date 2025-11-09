#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/map7/map7_s03.h"

// TODO: Move to src/maps/characters/ once matched.

void Ai_BloodyIncubator_Update(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords) // 0x800D3684
{
    if (chara->model_0.charaId_0 != Chara_BloodyIncubator)
    {
        Ai_BloodyIncubator_Init(chara);
    }

    func_800D38D8(chara, coords);
    func_800D3740(chara, coords);
    Ai_BloodyIncubator_AnimUpdate(chara, anmHdr, coords);
}

void Ai_BloodyIncubator_AnimUpdate(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords) // 0x800D36F8
{
    s_AnimInfo* animInfo;

    // TODO: Wrong properties union.
    if (chara->properties_E4.player.field_F0 == 0)
    {
        animInfo = &BLOODY_INCUBATOR_ANIM_INFOS[chara->model_0.anim_4.status_0];
        animInfo->updateFunc_0(&chara->model_0, anmHdr, coords, animInfo);
    }
}

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/Chara_BloodyIncubator", func_800D3740);

INCLUDE_ASM("asm/maps/map7_s03/nonmatchings/Chara_BloodyIncubator", func_800D38D8);

void Ai_BloodyIncubator_Init(s_SubCharacter* chara) // 0x800D3BA4
{
    sharedFunc_800D923C_0_s00(chara);
}
