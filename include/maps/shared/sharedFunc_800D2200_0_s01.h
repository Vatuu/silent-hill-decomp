void sharedFunc_800D2200_0_s01(s_SubCharacter* chara)
{
    s32 temp_v0;

    temp_v0 = func_800808AC(chara->position_18.vx, chara->position_18.vz);
    if (temp_v0 == 7)
    {
        return;
    }

    if (temp_v0 < 8)
    {
        if (temp_v0 != 0)
        {
            chara->properties_E4.npc.field_124 = func_80080884(chara->position_18.vx, chara->position_18.vz);
        }
    }
    else if (temp_v0 != 12)
    {
        chara->properties_E4.npc.field_124 = func_80080884(chara->position_18.vx, chara->position_18.vz);
    }
}
