void sharedFunc_800D2200_0_s01(s_SubCharacter* arg0)
{
    s32 temp_v0;

    temp_v0 = func_800808AC(arg0->position_18.vx, arg0->position_18.vz);
    if (temp_v0 == 7)
    {
        return;
    }
    if (temp_v0 < 8)
    {
        if (temp_v0 != 0)
        {
            arg0->properties_E4.npc.field_124 = func_80080884(arg0->position_18.vx, arg0->position_18.vz);
        }
    } else if (temp_v0 != 12)
    {
        arg0->properties_E4.npc.field_124 = func_80080884(arg0->position_18.vx, arg0->position_18.vz);
    }
}
