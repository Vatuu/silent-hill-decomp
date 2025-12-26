void Ai_AirScreamer_GroundWarp(s_SubCharacter* airScreamer)
{
    airScreamer->position_18.vy = Collision_GroundHeightGet(airScreamer->position_18.vx, airScreamer->position_18.vz);
}
