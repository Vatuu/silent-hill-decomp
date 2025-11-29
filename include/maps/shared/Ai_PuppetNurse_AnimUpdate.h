void Ai_PuppetNurse_AnimUpdate(s_SubCharacter* nurse, s_AnmHeader* anmHdr, GsCOORDINATE2* coord)
{
    s_AnimInfo* animInfo;
    s_AnimInfo* animInfoBase;
    s32 sfxIdx0;
    s32 sfxIdx1;
    s32 rot;
    s32 i;
    s32 j;

    animInfoBase = nurse->properties_E4.unk1.field_124->animInfo_24;
    sfxIdx0 = Ai_PuppetNurse_AnimSfxGet(FP_FROM(nurse->model_0.anim_4.time_4, Q12_SHIFT));
    func_8003DD80(nurse->model_0.charaId_0, nurse->properties_E4.unk1.modelVariation_119);
    Math_MatrixTransform(&nurse->position_18, &nurse->rotation_24, coord);
    if (nurse->model_0.anim_4.status_0)
    {
        (&animInfoBase[nurse->model_0.anim_4.status_0])->updateFunc_0(
            &nurse->model_0, anmHdr, coord, &animInfoBase[nurse->model_0.anim_4.status_0]);
    }

    rot = nurse->properties_E4.npc.field_124->field_18;
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            coord->coord.m[i][j] = FP_MULTIPLY_PRECISE(rot, coord->coord.m[i][j], Q12_SHIFT);
        }
    }
    
    sfxIdx1 = Ai_PuppetNurse_AnimSfxGet(FP_FROM(nurse->model_0.anim_4.time_4, Q12_SHIFT));
    if (sfxIdx1 != sfxIdx0 && sfxIdx1 != 9)
    {
        Ai_PuppetNurse_SfxPlay(nurse, sfxIdx1);
    }
}
