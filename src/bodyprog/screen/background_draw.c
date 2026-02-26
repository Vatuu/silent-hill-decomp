#include "game.h"

#include "bodyprog/bodyprog.h"
#include "bodyprog/gfx/screen_draw.h"
#include "bodyprog/math/math.h"
#include "main/fsqueue.h"

q0_8 g_BackgroundColor = Q8(0.5f); // Or `g_BackgroundShade`, since it's applied to all components?
u8   D_800A8E59        = 0; // Unused.
s16  D_800A8E5A        = 3; // Unused.

void Gfx_BackgroundSpriteDraw(s_FsImageDesc* image) // 0x800314EC
{
    s32       baseYOffset;
    s32       tileX;
    s32       tileIdxX;
    s32       x;
    s32       y;
    u32       texShift;
    s32       texPageX;
    u32       texOffsetY;
    GsOT*     ot;
    DR_TPAGE* tPage;
    SPRT*     sprt;
    PACKET*   packet;

    ot          = (GsOT*)&g_OtTags1[g_ActiveBufferIdx + 1][0];
    packet      = GsOUT_PACKET_P;
    baseYOffset = -120 << (g_GameWork.gsScreenHeight_58A >> 8);
    texShift    = image->tPage[0];
    texPageX    = image->tPage[1];
    texOffsetY  = image->v;

    for (y = 0; (g_GameWork.gsScreenHeight_58A >> 8) >= y; y++)
    {
        for (x = 0; ((g_GameWork.gsScreenWidth_588 - 1) >> (8 - texShift)) >= x; x++)
        {
            sprt = (SPRT*)packet;

            addPrimFast(ot, sprt, 4);
            setRGBC0(sprt, g_BackgroundColor, g_BackgroundColor, g_BackgroundColor, 100);

            if (y == 0)
            {
                setWH(sprt, 256, 256 - texOffsetY);
                *((u32*)&sprt->u0) = (texOffsetY << 8) + (getClut(image->clutX, image->clutY) << 16);
            }
            else
            {
                setWH(sprt, 256, 256);
                *((u32*)&sprt->u0) = getClut(image->clutX, image->clutY) << 16;
            }

            tileX = x << 8;

            setXY0Fast(sprt,
                       (tileX - (g_GameWork.gsScreenWidth_588 >> 1)) - (image->u << (2 - texShift)),
                       baseYOffset + ((256 - texOffsetY) * y));

            packet += sizeof(SPRT);
            tPage   = (DR_TPAGE*)packet;

            tileIdxX = x << texShift;
            setDrawTPage(tPage, 0, 1, getTPage(texShift, 0, (texPageX + tileIdxX) << 6, ((texPageX << 4) & 0x100) + (y << 8)));

            AddPrim(ot, tPage);
            packet = (PACKET*)tPage + sizeof(DR_TPAGE);
        }
    }

    GsOUT_PACKET_P           = packet;
    g_SysWork.sysFlags_22A0 |= SysFlag_Freeze;
    g_BackgroundColor        = 128;
}

void Gfx_BackgroundSpritesTransition(s_FsImageDesc* image0, s_FsImageDesc* image1, q3_12 alpha) // 0x800317CC
{
    volatile int   pad;
    s32            i;
    s32            j;
    u32            color;
    u8             tPageY;
    s32            offsetX;
    s_FsImageDesc* image;
    POLY_FT4*      poly;

    poly = (POLY_FT4*)GsOUT_PACKET_P;

    for (i = 0; i < 3; i++)
    {
        image = (i > 0) ? image0 : image1;
        color = (i < 2) ? Q12_MULT_PRECISE(alpha, 128) : 128;

        for (j = 0; j < 3; j++)
        {
            setPolyFT4(poly);

            setXY0Fast(poly, -160 + (128 * j), -120);
            setXY1Fast(poly, (128 * j) + ((j != 2) ? -32 : -96), -120);

            offsetX = 128 * j;

            setXY2Fast(poly, -160 + offsetX, 120);
            setXY3Fast(poly, offsetX + ((j != 2) ? -32 : -96), 120);

            *((u32*)&poly->u0) = (image->v << 8) + (getClut(image->clutX, image->clutY) << 16);

            tPageY = image->tPage[1];

            *((u32*)&poly->u1) = (image->v << 8) + ((j != 2) ? 128 : 64) +
                                 (getTPage(image->tPage[0], i + 1, (image->tPage[1] + j) << 6, (tPageY << 4) & 0x100) << 16);

            *((u16*)&poly->u2) = (image->v + 239) << 8;
            *((u16*)&poly->u3) = ((image->v + 239) << 8) + ((j != 2) ? 128 : 64);

            setSemiTrans(poly, i < 2);

            *((u16*)&poly->r0) = color + (color << 8);
            poly->b0           = color;

            addPrim(g_OrderingTable0[g_ActiveBufferIdx].org, poly);
            poly++;
        }
    }

    g_SysWork.sysFlags_22A0 |= SysFlag_Freeze;
    GsOUT_PACKET_P = (PACKET*)poly;
}

void Gfx_BackgroundSpriteDraw_2(s_FsImageDesc* image) // 0x80031AAC
{
    volatile s32 pad; // TODO: Is there a better solution?
    s32          i;
    s32          xOffset;
    u8           tPageY;
    POLY_FT4*    poly;

    poly = (POLY_FT4*)GsOUT_PACKET_P;

    for (i = 0; i < 3; i++)
    {
        setPolyFT4(poly);
        setXY0Fast(poly, -160 + (128 * i), -120);
        setXY1Fast(poly, (128 * i) + ((i == 2) ? -96 : -32), -120);

        xOffset = 128 * i;

        setXY2Fast(poly, -160 + xOffset, 120);
        setXY3Fast(poly, xOffset + (i == 2 ? -96 : -32), 120);

        *((u32*)&poly->u0) = (image->v << 8) + (getClut(image->clutX, image->clutY) << 16);

        tPageY = image->tPage[1];

        *((u32*)&poly->u1) = (image->v << 8) + ((i == 2) ? 64 : 128) +
                             (getTPage(image->tPage[0], 0, (image->tPage[1] + i) << 6, (tPageY << 4) & 0x100) << 16);

        *((u16*)&poly->u2) = (image->v + 239) << 8;
        *((u16*)&poly->u3) = ((image->v + 239) << 8) + ((i == 2) ? 64 : 128);

        setSemiTrans(poly, false);

        *((u16*)&poly->r0) = g_BackgroundColor + (g_BackgroundColor << 8);
        poly->b0           = g_BackgroundColor;

        addPrim(&g_OrderingTable0[g_ActiveBufferIdx].org[2], poly);
        poly++;
    }

    GsOUT_PACKET_P        = (PACKET*)poly;
    g_SysWork.sysFlags_22A0 |= SysFlag_Freeze;
    g_BackgroundColor     = 0x80;
}

bool Gfx_2dBackgroundMotionBlur(s32 vBlanks) // 0x80031CCC
{
    s32       sp10;
    s32       i;
    s32       offsetY;
    s32       texOffsetY;
    s32       tPageOffsetY;
    s32       j;
    GsOT*     ot;
    SPRT*     sprt;
    DR_TPAGE* tPage;

    ot   = (GsOT*)&g_OtTags1[g_ActiveBufferIdx + 1][0];
    sprt = (SPRT*)GsOUT_PACKET_P;
    sp10 = D_800C6E90;

    for (i = 0; (i == 0 || (sp10 != 0 && i == 1)); i++)
    {
        for (j = 0; j < 3; j++)
        {
            if (sp10 != 0)
            {
                texOffsetY   = (-(i == 0)) & 0x20;
                offsetY      = (i == 0) ? -224 : 0;
                tPageOffsetY = i << 8;
            }
            else
            {
                offsetY      = -112;
                texOffsetY   = (g_ActiveBufferIdx == 0) << 5;
                tPageOffsetY = g_ActiveBufferIdx << 8;
            }

            addPrimFast(ot, sprt, 4);

            if ((VSync(SyncMode_Count) % vBlanks) == 0)
            {
                setRGBC0(sprt, 127, 127, 127, PRIM_RECT | RECT_TEXTURE);
            }
            else
            {
                setRGBC0(sprt, 128, 128, 128, PRIM_RECT | RECT_TEXTURE);
            }

            setWH(sprt, 256, 224);
            *((u32*)&sprt->u0) = texOffsetY << 8;

            setXY0Fast(sprt, (-g_GameWork.gsScreenWidth_588 / 2) + (j << 8), offsetY);

            sprt++;
            tPage = (DR_TPAGE*)sprt;

            setDrawTPage(tPage, 0, 1, getTPage(2, 0, (j << 8), tPageOffsetY));
            AddPrim(ot, tPage);

            sprt = (PACKET*)sprt + sizeof(DR_TPAGE);
        }
    }

    GsOUT_PACKET_P = sprt;
    return false;
}
