void sharedFunc_800DDA80_2_s00(s_SubCharacter* airScreamer)
{
    q19_12 posX;
    q19_12 posZ;
    q19_12 playerPosZ;
    q19_12 playerPosX;
    q19_12 quadrantAngle;
    s32    var_a0;
    s32    quadrant;
    q19_12 newPosX;
    q19_12 newPosZ;
    s32    var_v1;

    #define airScreamerProps airScreamer->properties_E4.airScreamer

    quadrant = Quadrant_South;

    posX = airScreamer->position_18.vx;
    posZ = airScreamer->position_18.vz;

    playerPosX = g_SysWork.playerWork_4C.player_0.position_18.vx;
    playerPosZ = g_SysWork.playerWork_4C.player_0.position_18.vz;

    newPosX = posX;
    newPosZ = posZ;

    if (playerPosX > Q12(16.0f))
    {
        var_v1 = 2;
    }
    else
    {
        var_v1 = !(playerPosX < Q12(-8.0f));
    }

    if (playerPosZ <= Q12(8.0f))
    {
        var_a0 = !(playerPosZ < Q12(-8.0f));
    }
    else
    {
        var_a0 = 2;
    }

    switch (var_v1 + (var_a0 * 3))
    {
        case 8:
            quadrant = !((playerPosX - Q12(16.0f)) > (playerPosZ - Q12(8.0f))) * 2;
            break;

        case 6:
            if ((Q12(-8.0f) - playerPosX) > (playerPosZ - Q12(8.0f)))
            {
                quadrant = Quadrant_South;
            }
            else
            {
                quadrant = Quadrant_East;
            }
            break;

        case 7:
            quadrant = Quadrant_South;
            break;

        case 5:
            quadrant = Quadrant_West;
            break;

        case 4:
            quadrantAngle = Q12_FRACT(g_SysWork.playerWork_4C.player_0.rotation_24.vy - FP_ANGLE(45.0f));
            switch (quadrantAngle / FP_ANGLE(90.0f))
            {
                case 1:
                    quadrant = Quadrant_East;
                    break;

                case 2:
                    quadrant = Quadrant_South;
                    break;

                case 3:
                    quadrant = Quadrant_West;
                    break;

                default:
                case 0:
                    quadrant = Quadrant_North;
                    break;
            }
            break;

        case 3:
            quadrant = Quadrant_East;
            break;

        case 1:
            quadrant = Quadrant_North;
            break;

        case 2:
            if ((playerPosX - Q12(16.0f)) > (Q12(-8.0f) - playerPosZ))
            {
                quadrant = Quadrant_North;
            }
            else
            {
                quadrant = Quadrant_West;
            }
            break;

        case 0:
            if ((Q12(-8.0f) - playerPosX) > (Q12(-8.0f) - playerPosZ))
            {
                quadrant = Quadrant_North;
            }
            else
            {
                quadrant = Quadrant_East;
            }
            break;
    }

    switch (quadrant)
    {
        case Quadrant_South:
        case Quadrant_North:
            newPosX = (posX + playerPosX) / 2;
            if (newPosX > Q12(16.0f))
            {
                newPosX = Q12(16.0f);
            }
            else if (newPosX < Q12(-8.0f))
            {
                newPosX = Q12(-8.0f);
            }

            newPosZ = Q12(400.0f) - FP_SQUARE_PRECISE(newPosX - playerPosX, Q12_SHIFT);
            if (newPosZ < Q12(0.0f))
            {
                newPosZ = playerPosZ;

                if (newPosX < playerPosX)
                {
                    quadrant = Quadrant_West;
                }
                else
                {
                    quadrant = Quadrant_East;
                }
            }
            else
            {
                newPosZ = SquareRoot12(newPosZ);
                if (quadrant == Quadrant_South)
                {
                    newPosZ = newPosZ + playerPosZ;
                }
                else
                {
                    newPosZ = playerPosZ - newPosZ;
                }
            }
            break;

        case Quadrant_West:
        case Quadrant_East:
            newPosZ = (posZ + playerPosZ) / 2;
            if (newPosZ > Q12(8.0f))
            {
                newPosZ = Q12(8.0f);
            }
            else if (newPosZ < Q12(-8.0f))
            {
                newPosZ = Q12(-8.0f);
            }

            newPosX = Q12(400.0f) - FP_SQUARE_PRECISE(newPosZ - playerPosZ, Q12_SHIFT);

            if (newPosX < 0)
            {
                newPosX = playerPosX;
                quadrant = (newPosZ < playerPosZ) ^ 1;
            }
            else
            {
                newPosX = SquareRoot12(newPosX);
                if (quadrant == Quadrant_West)
                {
                    newPosX = newPosX + playerPosX;
                }
                else
                {
                    newPosX = playerPosX - newPosX;
                }
            }
            break;
    }

    switch (quadrant)
    {
        case Quadrant_South:
            airScreamer->rotation_24.vy = FP_ANGLE(180.0f);
            airScreamer->position_18.vy = Q12(-2.0f);
            break;

        case Quadrant_North:
            airScreamer->rotation_24.vy = FP_ANGLE(0.0f);

        default:
            airScreamer->position_18.vy = Q12(-2.0f);
            break;

        case Quadrant_West:
            airScreamer->rotation_24.vy = FP_ANGLE(270.0f);
            airScreamer->position_18.vy = Q12(-2.0f);
            break;

        case Quadrant_East:
            airScreamer->rotation_24.vy = FP_ANGLE(90.0f);
            airScreamer->position_18.vy = Q12(-2.0f);
            break;
    }

    airScreamer->moveSpeed_38                                 = sharedData_800CAA98_0_s01.unk_380[9][0];
    airScreamer->position_18.vx                               = newPosX;
    airScreamer->position_18.vz                               = newPosZ;
    airScreamerProps.timer_120 = Q12(10.0f);

    sharedFunc_800DEC84_2_s00(airScreamer, Q12(30.0f), airScreamer->rotation_24.vy + ((Rng_RandQ12() - FP_ANGLE(180.0f)) >> 7));
    sharedFunc_800D4E84_0_s01(airScreamer);

    #undef airScreamer
}
