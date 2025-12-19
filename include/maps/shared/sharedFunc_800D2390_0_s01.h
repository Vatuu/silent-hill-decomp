#define BIT_MASK(bit)          (1 << bit)
#define BIT_GET(var, val, bit) (var = ((u32)val >> bit), var &= 1)
#define BIT_SET(val, bit)      ((val | BIT_MASK(bit)))
#define BIT_CLEAR(val, bit)    ((val & ~BIT_MASK(bit)))

static inline u32 BitAssign(u32 value, u32 bit, bool cond)
{
    u32 val;
    if (cond)
    {
        val = BIT_SET(value, bit);
    }
    else
    {
        val = BIT_CLEAR(value, bit);
    }
    return val;
}

static inline u32 MaskAssign(u32 value, u32 mask, bool cond)
{
    u32 val;
    if (cond)
    {
        val = value | mask;
    }
    else
    {
        val = value & ~mask;
    }
    return val;
}

bool sharedFunc_800D2390_0_s01(s_SubCharacter* airScreamer)
{
    s32 bit0;
    s32 bit4;
    s32 bit5;
    s32 bit7;
    s32 sp20;
    s32 sp24;
    s32 sp28;
    s32 sp2C;
    s32 bit14;
    s32 sp34;
    s32 bit15;
    s32 bit27;
    s32 sp40;
    s32 bit3;
    s32 temp_s0;
    s32 temp_s0_2;
    s32 temp_s1;
    s32 temp_s1_2;
    s32 bit22;
    s32 temp_s2;
    s32 bit6;
    s32 bit2;
    s32 bit1;
    s32 temp_s6;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 var_s3;
    s32 var_s4;
    s32 var_s7;
    s32 var_v0;
    s32 var_v0_20;
    s32 var_v1_3;
    s32 bit21;
    s32 var_a0;
    s32 new_var2;
    s32 new_var4;

    sp28 = 0;

    temp_s1 = airScreamer->position_18.vx;
    temp_s2 = airScreamer->properties_E4.player.flags_11C;
    temp_s0 = airScreamer->position_18.vz;

    temp_v0 = sharedData_800CAA98_0_s01.unk_380[39][airScreamer->model_0.anim_4.keyframeIdx_8];

    BIT_GET(bit1, temp_v0, 1);
    BIT_GET(bit2, temp_v0, 2);
    BIT_GET(bit3, temp_v0, 3);
    BIT_GET(bit4, temp_v0, 4);
    BIT_GET(bit5, temp_v0, 5);
    BIT_GET(bit6, temp_v0, 6);
    BIT_GET(bit7, temp_v0, 7);
    BIT_GET(bit0, temp_v0, 0);

    temp_s0_2 = func_800808AC(temp_s1, temp_s0);

    temp_s1_2 = temp_s0_2 == 7;

    if (airScreamer->position_18.vy >= func_80080884(temp_s1, temp_s0) - 0x266)
    {
        sp28 = temp_s1_2 == 0;
    }

    sp2C = 0;

    if (temp_s0_2 == 0xC || temp_s0_2 == 0)
    {
        sp2C = 1;
    }

    BIT_GET(bit27, temp_s2, 27);

    sp40 = 0;

    if (temp_s2 & 0x2000 || sp2C)
    {
        sp40 = 1;
    }

    BIT_GET(bit21, temp_s2, 21);
    BIT_GET(bit22, temp_s2, 22);
    BIT_GET(bit14, temp_s2, 14);
    BIT_GET(bit15, temp_s2, 15);

    temp_v0_2 = temp_s2 & 0x10000040;
    sp34      = temp_v0_2;
    sp34      = temp_v0_2 != 0;
    sp20      = 0;

    temp_s6 = (bit0 == 0) & (bit1 == 0);

    if (bit6 == 0)
    {
        sp20 = bit1 & 1;
    }

    var_s7 = 0;

    sp24 = bit1 & bit6;

    if (bit2 == 0)
    {
        var_s7 = temp_s6 & 1;
    }

    var_s3 = 0;

    if (bit2 != 0)
    {
        var_s3 = temp_s6 & 1;
    }

    var_s4 = 0;

    if (airScreamer->position_18.vy < func_80080884(airScreamer->position_18.vx, airScreamer->position_18.vz) - 0x199)
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
                    var_v0 = var_s7 & 1;
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

    temp_s2 = BitAssign(temp_s2, 13, bit0 & sp28);
    temp_s2 = BitAssign(temp_s2, 17, bit0);
    temp_s2 = BitAssign(temp_s2, 18, !bit1);
    temp_s2 = BitAssign(temp_s2, 19, sp20);
    temp_s2 = BitAssign(temp_s2, 20, sp24);
    temp_s2 = BitAssign(temp_s2, 21, var_s7);
    temp_s2 = BitAssign(temp_s2, 22, var_s3);
    temp_s2 = BitAssign(temp_s2, 23, !bit3 ? (temp_s6 & 1) : 0);
    temp_s2 = BitAssign(temp_s2, 24, bit3 == 1 ? (temp_s6 & 1) : 0);
    temp_s2 = BitAssign(temp_s2, 25, bit4);
    temp_s2 = BitAssign(temp_s2, 26, bit5);
    temp_s2 = BitAssign(temp_s2, 27, bit7);
    temp_s2 = BIT_CLEAR(BitAssign(temp_s2, 15, bit14), 14);
    var_a0  = BitAssign(temp_s2, 28, sp34);

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
    temp_s2  = MaskAssign(var_v1_3, new_var2, !bit27 ? (bit7 & 1) & sp24 : 0);
    var_v1_3 = BitAssign(temp_s2, 9, var_s4);

    var_a0 = BIT_MASK(10);
    if (sp2C == 0 && sp40 == 0)
    {
        var_v0_20 = bit0;
        var_v0_20 = var_v0_20 & sp28;
    }
    else
    {
        var_v0_20 = 0;
    }

    temp_s2 = BIT_CLEAR(MaskAssign(var_v1_3, var_a0, var_v0_20), 4);
    temp_s2 = BIT_CLEAR(temp_s2, 5);
    temp_s2 = BIT_CLEAR(temp_s2, 6);
    temp_s2 = BIT_CLEAR(BitAssign(temp_s2, 3, !bit15 ? bit14 & 1 : 0), 2);
    temp_s2 = BIT_CLEAR(temp_s2, 0);
    temp_s2 = BIT_CLEAR(temp_s2, 1);

    airScreamer->properties_E4.player.flags_11C = temp_s2;
    return true;
}