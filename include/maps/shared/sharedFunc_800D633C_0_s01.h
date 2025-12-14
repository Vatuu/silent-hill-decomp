void sharedFunc_800D633C_0_s01(s_SubCharacter* chara)
{
    q19_12 posY;

    func_8006F250(&sharedData_800E2370_0_s01, chara->position_18.vx, chara->position_18.vz, 0, 0);

    posY = sharedData_800E2370_0_s01[1] - chara->field_C8.field_0;
    if (chara->position_18.vy < posY)
    {
        chara->position_18.vy = posY;
    }
}
