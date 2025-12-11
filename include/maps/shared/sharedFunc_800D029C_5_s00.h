void sharedFunc_800D029C_5_s00(s_SubCharacter* scratcher)
{
    s32 animStatus;

    animStatus = scratcher->model_0.anim_4.status_0;
    if ((animStatus != ANIM_STATUS(4, true)) && (animStatus != ANIM_STATUS(5, true)))
    {
        scratcher->field_44.field_0 = 0;
    }

    switch (scratcher->model_0.state_2)
    {
        case 0:
            break;
        case 1:
            sharedFunc_800D041C_5_s00(scratcher);
            break;
        case 2:
            sharedFunc_800D0514_5_s00(scratcher);
            break;
        case 3:
            sharedFunc_800D063C_5_s00(scratcher);
            break;
        case 4:
            sharedFunc_800D0C44_5_s00(scratcher);
            break;
        case 5:
            sharedFunc_800D0F04_5_s00(scratcher);
            break;
        case 6:
            sharedFunc_800D10B8_5_s00(scratcher);
            break;
        case 7:
            sharedFunc_800D1274_5_s00(scratcher);
            break;
        case 8:
            sharedFunc_800D19AC_5_s00(scratcher);
            break;
        case 9:
            sharedFunc_800D1AD0_5_s00(scratcher);
            break;
        case 10:
            sharedFunc_800D1C0C_5_s00(scratcher);
            break;
        case 11:
            sharedFunc_800D1CE4_5_s00(scratcher);
            break;
        case 12:
            sharedFunc_800D1E84_5_s00(scratcher);
            break;
        case 13:
            sharedFunc_800D2040_5_s00(scratcher);
            break;
        case 14:
            sharedFunc_800D2180_5_s00(scratcher);
            break;
        case 15:
            sharedFunc_800D23E0_5_s00(scratcher);
            break;
        case 16:
            sharedFunc_800D03F8_5_s00(scratcher);
            break;
    }
}
