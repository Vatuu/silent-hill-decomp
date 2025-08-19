void sharedFunc_800CEFD0_1_s02(s32 arg0, s_sharedFunc_800CEFD0_1_s02* arg1, u16* arg2, s32* deltaTime)
#ifdef SHARED_FUNC_IMPL
{
    s_func_800699F8              sp10;
    s32                          temp_v1;
    s32                          var_v0;
    s32                          var_t0;
    s32                          var_t1;
    s_sharedFunc_800CEFD0_1_s02* var_s0;

    var_s0 = arg1;

    if (arg0 == 0)
    {
        return;
    }

    if (arg0 == 1)
    {
        var_t0 = sharedData_800E3178_1_s02.field_C.vx - sharedData_800E3148_1_s02.field_C.vx;
        var_t1 = sharedData_800E3178_1_s02.field_C.vz - sharedData_800E3148_1_s02.field_C.vz;

        var_s0->field_C.vx = var_s0->field_0.vx;
        var_s0->field_C.vz = var_s0->field_0.vz;
        var_s0->field_C.vy = var_s0->field_0.vy - var_s0->field_1A;

        var_s0->field_0.vx += ((sharedData_800DFB64_0_s00 + var_t0) * *deltaTime) / 136;
        var_s0->field_1A   += sharedData_800E5768_1_s02;
        var_s0->field_0.vy += ((var_s0->field_1A << 2) * *deltaTime) / 136;
        var_s0->field_0.vz += ((sharedData_800DFB68_0_s00 + var_t1) * *deltaTime) / 136;

        if (sharedData_800DF158_1_s02 != 0)
        {
            var_s0->field_C.vx = var_s0->field_0.vx;
            var_s0->field_C.vz = var_s0->field_0.vz;
        }

        var_v0  = abs(var_s0->field_0.vx);
        temp_v1 = var_s0->field_0.vz;

        if ((temp_v1 >= 0 && (var_v0 + temp_v1) > FP_METER(6.0f)) ||
            (temp_v1 <  0 && (var_v0 - temp_v1) > FP_METER(6.0f)))
        {
            if (sharedData_800DF158_1_s02 != 0)
            {
                sharedFunc_800D01BC_0_s00(arg2, &arg1->field_0, 6);

                var_s0->field_C.vx = var_s0->field_0.vx;
                var_s0->field_C.vz = var_s0->field_0.vz;
            }
            else
            {
                var_s0->field_C.vx -= var_s0->field_0.vx;
                var_s0->field_C.vz -= var_s0->field_0.vz;

                var_s0->field_0.vx = -var_s0->field_0.vx;
                var_s0->field_0.vz = -var_s0->field_0.vz;

                var_s0->field_C.vx += var_s0->field_0.vx;
                var_s0->field_C.vz += var_s0->field_0.vz;
            }
        }

        if (var_s0->field_0.vy >= 0)
        {
            PushMatrix();
            func_800699F8(&sp10, var_s0->field_0.vx + sharedData_800E323C_0_s00.vx, var_s0->field_0.vz + sharedData_800E323C_0_s00.vz);
            PopMatrix();

            var_s0->field_0.vy = sp10.groundHeight_0;
            var_s0->field_18   = sp10.field_8;

            if (sp10.field_8 == 11)
            {
                var_s0->field_1F   = 3;
                var_s0->field_C.vx = var_s0->field_0.vx;
                var_s0->field_C.vz = var_s0->field_0.vz;
                var_s0->field_C.vy = var_s0->field_0.vy - 96;
            }

            var_s0->field_1C = 0;
            var_s0->field_1A = 0;
            var_s0->field_1E++;
        }
    }
}
#else
;
#endif
