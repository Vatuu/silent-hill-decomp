void sharedFunc_800DD13C_2_s00(s_SubCharacter* airScreamer, s32 npcSlot, q19_12 spawnChance)
{
    u32 flags;
    s32 i;
    s32 counter;
    s32 bitsSet;

    bitsSet = 0;
    flags   = g_SysWork.npcFlags_2290;
    counter = 0;

    if (spawnChance < Rng_RandQ12())
    {
        return;
    }

    if (g_VBlanks >= 4)
    {
        return;
    }

    // @bug This loops 32 times, but `npcs_1A0` only has 6 entries. Only accesses `npcs_1A0` when bit is set inside `flags_2290` first.
    for (i = 0; i < 32; i++)
    {
        if (flags & (1 << i))
        {
            bitsSet++;

            if (g_SysWork.npcs_1A0[i].model_0.charaId_0 == airScreamer->model_0.charaId_0)
            {
                switch (g_SysWork.npcs_1A0[i].model_0.controlState_2)
                {
                    case 2:
                    case 17:
                    case 30:
                    case 32:
                    case 45:
                        counter += 2;
                        break;

                    default:
                        counter += 3;
                        break;
                }
            }
        }
    }

    // If free slot in `npcs_1A0` exists and some counter is not over 5 (idle, aggro? currently animating?)
    if (bitsSet < 32)
    {
        counter = (counter + 2) / 3;
        if (counter < 5)
        {
            s32 selectNpcSlot = npcSlot & 0x1F;
            CLEAR_FLAG(g_SysWork.field_228C, selectNpcSlot);

            Chara_Spawn(airScreamer->model_0.charaId_0,
                        selectNpcSlot,
                        g_SysWork.playerWork_4C.player_0.position_18.vx + Q12(20.0f),
                        g_SysWork.playerWork_4C.player_0.position_18.vz, FP_ANGLE(0.0f),
                        10);
        }
    }
}
