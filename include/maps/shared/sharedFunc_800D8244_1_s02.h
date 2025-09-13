void sharedFunc_800D8244_1_s02(s_SubCharacter* chara)
{
    switch (chara->model_0.state_2)
    {
        case 1:
            sharedFunc_800D82F0_1_s02(chara);
            break;

        case 2:
            sharedFunc_800D8684_1_s02(chara);
            break;

        case 3:
            sharedFunc_800D8F30_1_s02(chara);
            break;
    
        case 4:
            sharedFunc_800D9528_1_s02(chara);
            break;

        case 5:
            sharedFunc_800D9774_1_s02(chara);
            break;

        default:
            break;
    }

    chara->properties_E4.larvalStalker.properties_E8[0].val16[0] &= ~(1 << 8);
}
