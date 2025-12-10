void sharedFunc_800CEFF4_0_s00(s_Particle* part, s32 arg1)
{
#if defined(MAP0_S00) || defined(MAP4_S02) || defined(MAP4_S03)
    VECTOR3 sp10;
#endif
    SVECTOR     sp20;
    SVECTOR     sp28;
    SVECTOR     sp30;
    SVECTOR     sp38;
    s32         depth;
    s32         colorComp;
    s32         test;
    u8          color;
    u32         step;
    u8          r;
    u8          g;
    u8          b;
    s32         rScaled;
    s32         gScaled;
    s32         bScaled;
    POLY_FT4*   poly;
    s_Particle* localPart;

    localPart = part;
    poly      = (POLY_FT4*)GsOUT_PACKET_P;

#if defined(MAP4_S02)
    g = 0;
    b = 0;
#endif

#if defined(MAP0_S00) || defined(MAP4_S02) || defined(MAP4_S03)
    if (localPart->stateStep_1E != 0 && sharedData_800DD591_0_s00 != 0)
    {
        sp10    = localPart->position0_0;
        sp10.vy = -1;

        sharedFunc_800D0700_0_s00(&sp10, sharedData_800E326C_0_s00.corners_0, &sharedData_800E326C_0_s00.corners_0[1], 0);

        localPart->position0_0.vx = sp10.vx;
        localPart->position0_0.vz = sp10.vz;

        if (sp10.vy == 0)
        {
            localPart->stateStep_1E = 0;
            return;
        }
    }
#endif

    switch (localPart->stateStep_1E)
    {
        case 0:
            return;

        case 1:
            sp20.vx = localPart->position1_C.vx >> 4;
            sp20.vy = localPart->position1_C.vy >> 4;
            sp20.vz = localPart->position1_C.vz >> 4;

            gte_ldv0(&sp20);
            gte_rtps();

            sp28.vx = localPart->position0_0.vx >> 4;
            sp28.vy = localPart->position0_0.vy >> 4;
            sp28.vz = localPart->position0_0.vz >> 4;

            gte_stsxy(&poly->x0);
            gte_stszotz(&depth);
            gte_ldv0(&sp28);
            gte_rtps();

            if (D_800C39A0 == 1 || D_800C39A0 == 4)
            {
                color = sharedData_800E325C_0_s00.r - (func_80055A50(depth) >> 5);
                r     = color;
                b     = color;
                g     = color;
            }
            else
            {
#if defined(MAP5_S00) || defined(MAP6_S03)
                r = (sharedData_800E325C_0_s00.r * 3) >> 1;
                g = (sharedData_800E325C_0_s00.g * 3) >> 1;
                b = (sharedData_800E325C_0_s00.b * 3) >> 1;
#else
                r = sharedData_800E325C_0_s00.r;
                g = sharedData_800E325C_0_s00.g;
                b = sharedData_800E325C_0_s00.b;
#endif
            }

            depth = depth >> 1;

            gte_stsxy(&poly->x1);

            if (depth > 32 && depth < 0x7FF)
            {
                setPolyFT4(poly);
                setSemiTrans(poly, 1);

#if !defined(MAP4_S02)
                poly->tpage = 44;
#endif

#if defined(MAP0_S00)
                if (g_SysWork.field_2358 != 0)
                {
                    setRGB0(poly, 0x12, 8, 8);
                }
                else
                {
                    setRGB0(poly, r, g, b);
                }
#elif defined(MAP4_S02)
                if (localPart->movement_18.vx == 5)
                {
                    poly->tpage = 0x4C;
                    setRGB0(poly, (r * 2) / 3, (g * 2) / 3, b);
                }
                else
                {
                    poly->tpage = 44;
                    setRGB0(poly, r, g, b);
                }
#else
                setRGB0(poly, r, g, b);
#endif

                setUV4(poly, 10, 112, 10, 128, 13, 112, 13, 128);

                if (!(depth > 63 && depth < 256))
                {
                    poly->clut = 0x1A30;
                }
                else
                {
                    poly->clut = (((depth >> 5) + 0x68) << 6) | 0x30;
                }

                poly->x2 = poly->x0 + 1;
                poly->y2 = poly->y0;

                poly->x3 = poly->x1 + 1;
                poly->y3 = poly->y1;

                addPrim(&g_OrderingTable0[g_ActiveBufferIdx].org[depth], poly);
                GsOUT_PACKET_P = (PACKET*)(poly + 1);
            }

            return;
    }

    switch (localPart->type_1F)
    {
        case 2:
        case 242:
#if defined(MAP4_S02)
            if (localPart->movement_18.vx == 5)
            {
                if (localPart->stateStep_1E < 25)
                {
                    colorComp = 0xA3;
                }
                else
                {
                    localPart->stateStep_1E = 0;
                    return;
                }
            }
            else
#endif
            {
                if (localPart->stateStep_1E < 17)
                {
                    colorComp = localPart->stateStep_1E;
                    colorComp = colorComp << arg1;

                    if (localPart->position0_0.vy == INT_MAX)
                    {
                        return;
                    }
                }
                else
                {
                    localPart->stateStep_1E = 0;
                    return;
                }
            }

            sp20.vx = (localPart->position0_0.vx - colorComp) >> 4;
            sp20.vy = localPart->position0_0.vy >> 4;
            sp20.vz = (localPart->position0_0.vz - colorComp) >> 4;

            gte_ldv0(&sp20);
            gte_rtps();

            sp28.vx = sp20.vx;
            sp28.vy = sp20.vy;
            sp28.vz = (localPart->position0_0.vz + colorComp) >> 4;

            gte_stsxy(&poly->x0);
            gte_stszotz(&depth);

            sp30.vx = (localPart->position0_0.vx + colorComp) >> 4;
            sp30.vy = sp20.vy;
            sp30.vz = sp20.vz;

            sp38.vx = sp30.vx;
            sp38.vy = sp20.vy;
            sp38.vz = sp28.vz;

            gte_ldv3(&sp28, &sp30, &sp38);
            gte_rtpt();

            depth = depth >> 1;

#if defined(MAP4_S02)
            if (localPart->movement_18.vx == 5)
            {
                color = localPart->stateStep_1E;

                if (color >= 9U)
                {
                    r = 0x40 - ((color - 8) * 4);
                }
                else
                {
                    r = 0x40;
                }

                setUV4(poly, 0x20, 0x70, 0x20, 0x7F, 0x2F, 0x70, 0x2F, 0x7F);
                poly->tpage = 0x4C;
            }
            else
#endif
            {
                colorComp >>= (arg1 - 3);
                colorComp   = 0x80 - colorComp;

                if ((D_800C39A0 == 2 || D_800C39A0 == 6))
                {
                    if (Game_FlashlightIsOn())
                    {
                        r = colorComp * 2;
                    }
                    else
                    {
                        r = colorComp;
                    }

                    g = b = colorComp;
                }
                else
                {
                    r = g = b = colorComp;
                }

                step = localPart->stateStep_1E;

                setUV4(poly, 16, 112, 16, 127, 31, 112, 31, 127);

                poly->tpage = 44;

                rScaled = r * step;
                r      -= rScaled >> 4;

                gScaled = g * step;
                g      -= gScaled >> 4;

                bScaled = b * step;
                b      -= bScaled >> 4;
            }

            gte_stsxy3(&poly->x1, &poly->x2, &poly->x3);

            if (depth > 0x20 && depth < 0x7FF)
            {
                setPolyFT4(poly);
                setSemiTrans(poly, 1);

#if !defined(MAP4_S02)
                if (!(depth > 0x3F && depth < 0x100))
                {
                    poly->clut = 0x1A30;
                }
                else
                {
                    poly->clut = (((depth >> 5) + 0x68) << 6) | 0x30;
                }
#endif

#if defined(MAP0_S00)
                if (g_SysWork.field_2358 != 0)
                {
                    setRGB0(poly, r + 0xA, g, b);
                }
                else
                {
                    setRGB0(poly, r, g, b);
                }

#elif defined(MAP4_S02)
                if (localPart->movement_18.vx == 5)
                {
                    poly->clut = (((depth >> 5) + 0x68) << 6) | 0x30;
                    setRGB0(poly, r, r, r);
                }
                else
                {
                    if (!(depth > 0x3F && depth < 0x100))
                    {
                        poly->clut = 0x1A30;
                    }
                    else
                    {
                        poly->clut = (((depth >> 5) + 0x68) << 6) | 0x30;
                    }

                    setRGB0(poly, r, g, b);
                }
#else
                setRGB0(poly, r, g, b);
#endif

                addPrim(&g_OrderingTable0[g_ActiveBufferIdx].org[depth], poly);
                GsOUT_PACKET_P = (PACKET*)(poly + 1);
            }

            return;
    }

    if (localPart->stateStep_1E < 31)
    {
        colorComp = localPart->stateStep_1E;
    }
    else
    {
        colorComp = 0x20;
    }

    if (localPart->stateStep_1E >= 49)
    {
        localPart->stateStep_1E = 0;
        return;
    }

    sp20.vx = Q12_TO_Q8(localPart->position1_C.vx);
    sp20.vy = Q12_TO_Q8(localPart->position1_C.vy);
    sp20.vz = Q12_TO_Q8(localPart->position1_C.vz);

    gte_ldv0(&sp20);
    gte_rtps();

    sp28.vx = Q12_TO_Q8(localPart->position0_0.vx);
    sp28.vy = Q12_TO_Q8(localPart->position0_0.vy);
    sp28.vz = Q12_TO_Q8(localPart->position0_0.vz);

    gte_stsxy(&poly->x0);
    gte_stszotz(&depth);
    gte_ldv0(&sp28);
    gte_rtps();

    depth = depth >> 1;

    gte_stsxy(&poly->x1);

    if (depth > 0x20 && depth < 0x7FF)
    {
        setPolyFT4(poly);
        setSemiTrans(poly, 1);
        setUV4(poly, 10, 112, 10, 128, 13, 112, 13, 128);
        setRGB0(poly, colorComp, colorComp, colorComp + 0x18);

        poly->tpage = 44;

        if (!(depth > 0x3F && depth < 0x100))
        {
            poly->clut = 0x1A30;
        }
        else
        {
            poly->clut = (((depth >> 5) + 0x68) << 6) | 0x30;
        }

        poly->x2 = poly->x0 + 1;
        poly->y2 = poly->y0;
        poly->x3 = poly->x1 + 1;
        poly->y1++;
        poly->y3 = poly->y1;

        addPrim(&g_OrderingTable0[g_ActiveBufferIdx].org[depth], poly);
        GsOUT_PACKET_P = (PACKET*)(poly + 1);
    }
}
