s32 sharedFunc_800D9188_0_s00(s32 arg0, s_SubCharacter* arg1, s32 arg2, s32 arg3)
{
    // TODO: Should probably be using properties_E4.npc struct instead.
    if (arg1->model_0.anim_4.animIdx_0 == arg0)
    {
        if (arg1->model_0.anim_4.keyframeIdx0_8 >= arg2)
        {
            if (!(arg1->properties_E4.player.flags_11C & (1 << 13)))
            {
                switch (arg3)
                {
#if defined(MAP6_S04)
                    case 0x654:
                        func_8005DC1C(arg3, &arg1->position_18, 0x40, 0);
                        break;
                    case 0x655:
                        func_8005DC1C(arg3, &arg1->position_18, 0x40, 0);
                        break;
                    case 0x656:
                    case 0x666:
                        func_8005DC1C(arg3, &arg1->position_18, 0xC0, 0);
                        break;
                    case 0x65F:
                    case 0x660:
                        func_8005DC1C(arg3, &arg1->position_18, 0x40, 0);
                        break;

#elif defined(MAP3_S00) || defined(MAP5_S02) || defined(MAP5_S03)
                    case 0x5D4:
                        func_8005DC1C(arg3, &arg1->position_18, 0xFF, 2);
                        break;
                    case 0x63A:
                        func_8005DC1C(arg3, &arg1->position_18, 0x80, 0);
                        break;

#elif defined(MAP3_S04) || defined(MAP4_S04) || defined(MAP7_S00)
                    case 0x667:
                        func_8005DC1C(arg3, &arg1->position_18, 0x40, 0);
                        break;

#elif defined(MAP0_S01) || defined(MAP4_S01)
                    case 0x558:
                    case 0x559:
                    case 0x55A:
                        func_8005DC1C(arg3, &arg1->position_18, 0x40, 0);
                        break;

#elif defined(MAP2_S01) || defined(MAP3_S06)
                    case 0x5D0:
                    case 0x5D8:
                        func_8005DC1C(arg3, &arg1->position_18, 0x40, 0);
                        break;

#elif defined(MAP6_S01)
                    // TODO: this is made of two blocks above, maybe can be merged somehow.
                    case 0x5D0:
                    case 0x5D8:
                        func_8005DC1C(arg3, &arg1->position_18, 0x40, 0);
                        break;

                    case 0x558:
                    case 0x559:
                    case 0x55A:
                        func_8005DC1C(arg3, &arg1->position_18, 0x40, 0);
                        break;

#elif defined(MAP7_S03)
                    case 0x603:
                    case 0x68A:
                    case 0x68B:
                        func_8005DC1C(arg3, &arg1->position_18, 0x20, 0);
                        break;

                    case 0x656:
                        func_8005DC1C(arg3, &arg1->position_18, 0xC0, 0);
                        break;

#endif
                    default:
                        func_8005DC1C(arg3, &arg1->position_18, 0x80, 0);
                        break;
                }

                arg1->properties_E4.player.flags_11C |= (1 << 13);
                return 1;
            }
        }
        else
        {
            arg1->properties_E4.player.flags_11C &= ~(1 << 13);
        }
    }
    return 0;
}
