#define BIT_MASK(bit) \
    (1 << (bit))

#define BIT_GET(var, val, bit) \
    ((var) = ((u32)(val) >> (bit)), (var) &= 1)

#define BIT_SET(val, bit) \
    (((val) |  BIT_MASK(bit)))

#define BIT_CLEAR(val, bit) \
    (((val) & ~BIT_MASK(bit)))

static inline u32 BitAssign(u32 val, u32 bit, bool cond)
{
    u32 newVal;

    if (cond)
    {
        newVal = BIT_SET(val, bit);
    }
    else
    {
        newVal = BIT_CLEAR(val, bit);
    }

    return newVal;
}

static inline u32 MaskAssign(u32 val, u32 mask, bool cond)
{
    u32 newVal;

    if (cond)
    {
        newVal = val | mask;
    }
    else
    {
        newVal = val & ~mask;
    }

    return newVal;
}

bool sharedFunc_800D2390_0_s01(s_SubCharacter* airScreamer)
{
    s32    bit0;
    s32    bit4;
    s32    bit5;
    s32    bit7;
    s32    sp20;
    s32    sp24;
    s32    sp28;
    bool   cond0;
    s32    bit14;
    s32    sp34;
    s32    bit15;
    s32    bit27;
    s32    cond1;
    s32    bit3;
    q19_12 posX;
    q19_12 posZ;
    s32    temp_s0_2;
    bool   cond2;
    s32    bit22;
    s32    playerFlags;
    s32    bit6;
    s32    bit2;
    s32    bit1;
    s32    temp_s6;
    s32    temp_v0;
    s32    temp_v0_2;
    s32    var_s3;
    s32    var_s4;
    s32    var_s7;
    s32    var_v0;
    s32    var_v0_20;
    s32    var_v1_3;
    s32    bit21;
    s32    var_a0;
    s32    new_var2;
    s32    new_var4;

    sp28 = 0;

    posX        = airScreamer->position_18.vx;
    playerFlags = airScreamer->properties_E4.player.flags_11C;
    posZ        = airScreamer->position_18.vz;

    temp_v0 = sharedData_800CAA98_0_s01.unk_380[39][airScreamer->model_0.anim_4.keyframeIdx_8];

    BIT_GET(bit1, temp_v0, 1);
    BIT_GET(bit2, temp_v0, 2);
    BIT_GET(bit3, temp_v0, 3);
    BIT_GET(bit4, temp_v0, 4);
    BIT_GET(bit5, temp_v0, 5);
    BIT_GET(bit6, temp_v0, 6);
    BIT_GET(bit7, temp_v0, 7);
    BIT_GET(bit0, temp_v0, 0);

    temp_s0_2 = func_800808AC(posX, posZ);

    cond2 = temp_s0_2 == 7;
    if (airScreamer->position_18.vy >= (func_80080884(posX, posZ) - Q12(0.15f)))
    {
        sp28 = !cond2;
    }

    cond0 = false;
    if (temp_s0_2 == 12 || temp_s0_2 == 0)
    {
        cond0 = true;
    }

    BIT_GET(bit27, playerFlags, 27);

    cond1 = false;
    if (playerFlags & PlayerFlag_Unk13 || cond0)
    {
        cond1 = true;
    }

    BIT_GET(bit21, playerFlags, 21);
    BIT_GET(bit22, playerFlags, 22);
    BIT_GET(bit14, playerFlags, 14);
    BIT_GET(bit15, playerFlags, 15);

    temp_v0_2 = playerFlags & (PlayerFlag_Unk6 | PlayerFlag_Unk28);
    sp34      = temp_v0_2;
    sp34      = temp_v0_2 != 0;
    sp20      = 0;

    temp_s6 = (bit0 == 0) & (bit1 == 0);

    if (bit6 == 0)
    {
        sp20 = bit1 & 0x1;
    }

    var_s7 = 0;

    sp24 = bit1 & bit6;

    if (bit2 == 0)
    {
        var_s7 = temp_s6 & 0x1;
    }

    var_s3 = 0;

    if (bit2 != 0)
    {
        var_s3 = temp_s6 & 0x1;
    }

    var_s4 = 0;

    if (airScreamer->position_18.vy < (func_80080884(airScreamer->position_18.vx, airScreamer->position_18.vz) - Q12(0.1f)))
    {
        switch (func_800808AC(airScreamer->position_18.vx, airScreamer->position_18.vz))
        {
            case 7:
            case 0:
            case 12:
                break;

            default:
                if (!bit21)
                {
                    var_v0 = var_s7 & 0x1;
                }
                else
                {
                    var_v0 = 0;
                }

                var_s4 = temp_s6 & var_v0;

                if (!bit22)
                {
                    var_s4 = temp_s6 & (var_v0 | var_s3);
                }
                break;
        }
    }

    // TODO: `e_PlayerFlags` is relevant here.
    playerFlags = BitAssign(playerFlags, 13, bit0 & sp28);
    playerFlags = BitAssign(playerFlags, 17, bit0);
    playerFlags = BitAssign(playerFlags, 18, !bit1);
    playerFlags = BitAssign(playerFlags, 19, sp20);
    playerFlags = BitAssign(playerFlags, 20, sp24);
    playerFlags = BitAssign(playerFlags, 21, var_s7);
    playerFlags = BitAssign(playerFlags, 22, var_s3);
    playerFlags = BitAssign(playerFlags, 23, !bit3 ? (temp_s6 & 1) : 0);
    playerFlags = BitAssign(playerFlags, 24, bit3 == 1 ? (temp_s6 & 1) : 0);
    playerFlags = BitAssign(playerFlags, 25, bit4);
    playerFlags = BitAssign(playerFlags, 26, bit5);
    playerFlags = BitAssign(playerFlags, 27, bit7);
    playerFlags = BIT_CLEAR(BitAssign(playerFlags, 15, bit14), 14);
    var_a0  = BitAssign(playerFlags, 28, sp34);

    new_var4 = BIT_MASK(7);

    if (bit27 == 0)
    {
        var_v1_3 = bit7;
        var_v1_3 = var_v1_3 & sp20;
    }
    else
    {
        var_v1_3 = 0;
    }

    var_v1_3 = MaskAssign(var_a0, new_var4, var_v1_3);

    new_var2 = BIT_MASK(8);
    playerFlags  = MaskAssign(var_v1_3, new_var2, (bit27 == 0) ? ((bit7 & 0x1) & sp24) : 0);
    var_v1_3 = BitAssign(playerFlags, 9, var_s4);

    var_a0 = BIT_MASK(10);
    if (!cond0 && !cond1)
    {
        var_v0_20 = bit0;
        var_v0_20 = var_v0_20 & sp28;
    }
    else
    {
        var_v0_20 = 0;
    }

    playerFlags = BIT_CLEAR(MaskAssign(var_v1_3, var_a0, var_v0_20), 4);
    playerFlags = BIT_CLEAR(playerFlags, 5);
    playerFlags = BIT_CLEAR(playerFlags, 6);
    playerFlags = BIT_CLEAR(BitAssign(playerFlags, 3, !bit15 ? bit14 & 1 : 0), 2);
    playerFlags = BIT_CLEAR(playerFlags, 0);
    playerFlags = BIT_CLEAR(playerFlags, 1);

    airScreamer->properties_E4.player.flags_11C = playerFlags;
    return true;
}
