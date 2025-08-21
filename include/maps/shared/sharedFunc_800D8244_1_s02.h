void sharedFunc_800D8244_1_s02(s_SubCharacter* chara)
{
    switch (chara->model_0.state_2)
    {
        case 1:
            func_800D82F0(chara);
            break;

        case 2:
            func_800D8684(chara);
            break;

        case 3:
            func_800D8F30(chara);
            break;
    
        case 4:
            func_800D9528(chara);
            break;

        case 5:
            func_800D9774(chara);
            break;

        default:
            break;
    }

    chara->properties_E4.player.field_E4 &= ~(1 << 8);
}
