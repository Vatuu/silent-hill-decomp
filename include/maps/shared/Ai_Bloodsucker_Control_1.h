void Ai_Bloodsucker_Control_1(s_SubCharacter* bloodsucker)
{
    #define bloodsuckerProps bloodsucker->properties_E4.bloodsucker

    bloodsucker->model_0.anim_4.time_4 = Q12(81.0f) + bloodsuckerProps.timer_E8;

    #undef bloodsuckerProps
}
