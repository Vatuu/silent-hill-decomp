bool sharedFunc_800DC0A8_2_s00(s_SubCharacter* chara)
{
    return (Collision_GroundHeightGet(chara->position_18.vx, chara->position_18.vz) - Q12(0.2f)) < chara->position_18.vy;
}
