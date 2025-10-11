s32 sharedFunc_800D6A60_0_s01(VECTOR3* vec0, VECTOR3* vec1, s_SubCharacter* chara, s32 arg3, VECTOR3* vec2)
{
    s32      vec0X;
    s32      vec0Z;
    s32      vec0Y;
    s32      vec1X;
    s32      vec1Y;
    s32      vec1Z;
    s32      vec2X;
    s32      vec2Z;
    q19_12   posY;
    s32      calcY;
    s32      newVec1Y;
    s32      newVec2Y;
    s32      time;
    s32      ret;
    s32      retCode1;
    s32      flags;
    VECTOR3* vec0Cpy;

    flags = chara->properties_E4.player.flags_11C;
    vec0Cpy = vec0;

    vec0X = vec0Cpy->vx;
    vec0Z = vec0Cpy->vz;

    ret = arg3;

    chara->position_18.vx += vec0X;
    chara->position_18.vz += vec0Z;

    if (ret == 0)
    {
        flags &= ~PlayerFlag_Unk31;
        vec1X = 0;
        vec2->vx = vec1->vx;
        vec1Z = 0;
        vec2->vz = vec1->vz;
    }
    else
    {
        flags |= PlayerFlag_Unk31;
        time = 0x01000000 / g_DeltaTime0;

        if (!(vec0X | vec0Z))
        {
            vec2X = 0;
            vec2Z = 0;
            vec2->vx = 0;
            vec2->vz = 0;
        }
        else
        {
            vec2X = FP_MULTIPLY_PRECISE(vec0X, time, Q12_SHIFT);
            vec2->vx = vec2X;
            vec2Z = FP_MULTIPLY_PRECISE(vec0Z, time, Q12_SHIFT);
            vec2->vz = vec2Z;
        }

        vec1X = vec2X - vec1->vx;
        vec1Z = vec2Z - vec1->vz;
    }

    vec1->vx = vec1X;
    vec1->vz = vec1Z;
    posY = chara->position_18.vy;
    vec1Y = vec1->vy;
    vec0Y = vec0Cpy->vy;

    calcY = func_80080884(chara->position_18.vx, chara->position_18.vz);
    sharedData_800E21D0_0_s01.field_114 = calcY;
    retCode1 = 1;

    if (!(chara->field_E1_0))
    {
        newVec2Y = 0;
        newVec1Y = 0;
    } 
    else if (posY >= calcY && vec0Y >= 0)
    {
        flags &= ~PlayerFlag_Unk30;
        posY = calcY;
        newVec2Y = 0;
        newVec1Y = 0;
    } 
    else 
    {
        posY += vec0Y;
        if (posY >= calcY)
        {
            flags |= PlayerFlag_Unk30;
            ret = retCode1;
            newVec2Y = 0;
            newVec1Y = -vec1Y;
            posY = calcY;
        } 
        else 
        {
            flags &= ~PlayerFlag_Unk30;
            newVec2Y = vec1Y;
            newVec1Y = 0;
        }
    }

    chara->position_18.vy = posY;
    vec2->vy = newVec2Y;
    vec1->vy = newVec1Y;
    chara->properties_E4.player.flags_11C = flags;
    return ret;
}
