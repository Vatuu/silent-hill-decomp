void Ai_HangedScratcher_Control_9(s_SubCharacter* scratcher)
{
    s_Collision coll;

    Chara_MoveSpeedUpdate(scratcher, Q12(4.0f));

    if (ANIM_STATUS_IDX_GET(scratcher->model_0.anim_4.status_0) == 14 && scratcher->moveSpeed_38 == Q12(0.0f))
    {
        Collision_Get(&coll, scratcher->position_18.vx, scratcher->position_18.vz);
        if (scratcher->health_B0 > Q12(100.0f) || coll.field_8 == 7)
        {
            if (scratcher->properties_E4.hangedScratcher.flags_E8 & (1 << 1))
            {
                scratcher->model_0.controlState_2  = 8;
                scratcher->model_0.anim_4.status_0 = ANIM_STATUS(16, false);
            }
            else if (!Rng_GenerateInt(0, 7))
            {
                scratcher->model_0.controlState_2  = 3;
                scratcher->model_0.anim_4.status_0 = ANIM_STATUS(17, false);
            }
        }
        else
        {
            scratcher->model_0.controlState_2  = 11;
            scratcher->model_0.anim_4.status_0 = ANIM_STATUS(10, false);
        }
    }
}
