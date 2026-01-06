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
    q19_12   groundHeight;
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
            vec2X = Q12_MULT_PRECISE(vec0X, time);
            vec2->vx = vec2X;
            vec2Z = Q12_MULT_PRECISE(vec0Z, time);
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

    groundHeight = Collision_GroundHeightGet(chara->position_18.vx, chara->position_18.vz);
    sharedData_800E21D0_0_s01.field_114 = groundHeight;
    retCode1 = 1;

    if (!(chara->field_E1_0))
    {
        newVec2Y = 0;
        newVec1Y = 0;
    } 
    else if (posY >= groundHeight && vec0Y >= Q12(0.0f))
    {
        flags &= ~PlayerFlag_Unk30;
        posY = groundHeight;
        newVec2Y = 0;
        newVec1Y = 0;
    } 
    else 
    {
        posY += vec0Y;
        if (posY >= groundHeight)
        {
            flags |= PlayerFlag_Unk30;
            ret = retCode1;
            newVec2Y = 0;
            newVec1Y = -vec1Y;
            posY = groundHeight;
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
