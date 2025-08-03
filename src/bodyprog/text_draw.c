#include "game.h"

#include "bodyprog/bodyprog.h"
#include "bodyprog/math.h"

#define DIALOG_CODE_NEWLINE         'N'
#define DIALOG_CODE_JUMP_DELAY      'J'
#define DIALOG_CODE_LINE_POSITION   'L'
#define DIALOG_CODE_MIDDLE_ALIGN    'M'
#define DIALOG_CODE_TAB             'T' // Unused.
#define DIALOG_CODE_COLOR           'C'
#define DIALOG_CODE_DISPLAY_ALL     'D'
#define DIALOG_CODE_END             'E'
#define DIALOG_CODE_SELECT          'S'
#define DIALOG_CODE_HIGH_RESOLUTION 'H'

void Gfx_StringSetPosition(s32 x, s32 y) // 0x8004A87C
{
    #define OFFSET_X SCREEN_POSITION_X(50.0f)
    #define OFFSET_Y SCREEN_POSITION_Y(47.0f)

    if (x != NO_VALUE)
    {
        g_StringPosition.vx = x - OFFSET_X;
        g_StringPositionX1  = (s16)(x - OFFSET_X);
    }

    if (y != NO_VALUE)
    {
        g_StringPosition.vy = y - OFFSET_Y;
    }

    D_800AD49C = 6;
}

void func_8004A8C0(s32 arg0) // 0x8004A8C0
{
    D_800AD49C = arg0;
}

void func_8004A8CC() // 0x8004A8CC
{
    D_800AD49C = 6;
}

void Gfx_StringSetColor(s16 colorId) // 0x8004A8DC
{
    g_StringColorId = colorId;
}

// TODO: Requires `s_SysWork::HighResolutionTextRender` to be `s32`, causing mismatch elsewhere.
#ifdef NON_MATCHING
bool Gfx_StringDraw(char* str, s32 size) // 0x8004A8E8
{
    #define GLYPH_SIZE_X       12
    #define GLYPH_SIZE_Y       16
    #define SPACE_SIZE         6
    #define WIDE_SPACE_SIZE    10
    #define ATLAS_BASE_Y       240
    #define ATLAS_COLUMN_COUNT 21

    // TODO: This only works for one case. There may originally have been some other generic macro.
    #define setSprtUvClut(glyphSprt, idx, clut)                                                                           \
    *((u32*)&(glyphSprt)->u0) = (((idx) % ATLAS_COLUMN_COUNT) * GLYPH_SIZE_X) + /* `u0`:   Column in atlas. */            \
                                (ATLAS_BASE_Y << 8)                           + /* `v0`:   Row 0 in atlas with offset. */ \
                                ((clut) << 16)                                  /* `clut`: Packed magic value. */

    s32       posX;
    s32       posY;
    s32       u0;
    s32       sizeCpy;
    s32       glyphIdx;
    u32       glyphColor;
    u32       charCode;
    u8*       strCpy;
    bool      result;
    s32       glyphWidth;
    s32       posXCpy;
    GsOT*     ot;
    PACKET*   packet;
    DR_TPAGE* tPage;
    POLY_FT4* glyphPoly;
    SPRT*     glyphSprt;

    // Create local argument copies.
    strCpy  = str;
    sizeCpy = size;

    packet = NULL;
    result = false;

    // Set base screen position.
    posX = g_StringPosition.vx;
    posY = g_StringPosition.vy;

    glyphColor = D_80025DC0[g_StringColorId];
    ot         = &D_800B5C40[g_ObjectTableIdx].field_0[D_800AD49C];

    if (!(g_SysWork.HighResolutionTextRender & 0xF))
    {
        packet = GsOUT_PACKET_P;
    }

    // Parse string.
    while (sizeCpy > 0) 
    {
        charCode = *strCpy;

        // TODO: Try refactoring into switch.

        // Convert literal `!` and `&` into `char`s mappable to representative atlas glyphs.
        if (charCode == '!') 
        {
            charCode = '\\';
        }
        else if (charCode == '&')
        {
            charCode = '^';
        }

        // Space.
        if (charCode == '_')
        {
            posX += SPACE_SIZE;
        }
        // Wide space.
        else if (charCode == '\v')
        {
            posX += WIDE_SPACE_SIZE;
        }
        // Start of header.
        else if (charCode == '\x01')
        {
            posX--;
        }
        // Regular character.
        else if (charCode >= '\'' && charCode <= 'z')
        {
            sizeCpy--;

            // Draw glyph sprite.
            if (g_SysWork.HighResolutionTextRender & 0xF)
            {
                glyphPoly = (POLY_FT4*)GsOUT_PACKET_P;

                glyphIdx   = charCode - '\'';
                glyphWidth = D_80025D6C[glyphIdx];

                setPolyFT4(glyphPoly);
                setRGB0(glyphPoly, glyphColor, glyphColor >> 8, glyphColor >> 16);
                setXY4(glyphPoly,
                       posX,                posY * 2,
                       posX,                (posY * 2) + 30,
                       posX + GLYPH_SIZE_X, posY * 2,
                       posX + GLYPH_SIZE_X, (posY * 2) + 30);

                posX += glyphWidth;

                u0 = (glyphIdx % ATLAS_COLUMN_COUNT) * GLYPH_SIZE_X;

                *((u32*)&glyphPoly->u0) = u0 + (0xF000 + (0x7FD3 << 16));                                         // `u0`, `v0`, `clut`.
                *((u32*)&glyphPoly->u1) = u0 + (((((glyphIdx / ATLAS_COLUMN_COUNT) & 0xF) | 16) << 16) | 0xFF00); // `u1`, `v1`, `page`.
                *((u16*)&glyphPoly->u2) = u0 - 0xFF4;                                                             // `u2`, `v2`.
                *((u16*)&glyphPoly->u3) = u0 - 0xF4;                                                              // `u3`, `v3`.

                addPrim(ot, glyphPoly);
                GsOUT_PACKET_P = (u8*)glyphPoly + sizeof(POLY_FT4);
            }
            else
            {
                posXCpy = (u16)posX;

                glyphSprt              = (SPRT*)packet;
                *((u32*)&glyphSprt->w) = 0x10000C;
                
                glyphIdx = charCode - '\'';
                posX    += D_80025D6C[glyphIdx];

                addPrimFast(ot, glyphSprt, 4);
                *((u32*)&glyphSprt->r0)   = glyphColor;
                *((u32*)(&glyphSprt->x0)) = posXCpy + (posY << 16);

                setSprtUvClut(glyphSprt, glyphIdx, 0x7FD3); // TODO: Demagic CLUT arg.
                //*((u32*)&glyphSprt->u0) = ((glyphIdx % ATLAS_COLUMN_COUNT) * GLYPH_SIZE_X) + 0xF000 + (0x7FD3 << 16); // `u0`, `v0`, `clut`.

                packet += sizeof(SPRT);

                tPage = (DR_TPAGE*)packet;
                setDrawTPage(tPage, 0, 1, ((glyphIdx / ATLAS_COLUMN_COUNT) & 0xF) | 16);
                addPrim(ot, tPage);

                packet += sizeof(DR_TPAGE);
            }
        }
        // Newline.
        else if (charCode == '\n')
        {
            posX  = g_StringPositionX1;
            posY += GLYPH_SIZE_Y;
        }
        // New color.
        else if (charCode >= '\x01' && charCode < '\b')
        {
            glyphColor      = D_80025DC0[charCode];
            g_StringColorId = charCode;
        }
        // Terminator.
        else if (charCode == '\0')
        {
            result = true;
            break;
        }

        strCpy++;
    }

    if (!(g_SysWork.HighResolutionTextRender & 0xF))
    {
        GsOUT_PACKET_P = packet;
    }

    // Reset base string position?
    *((u32*)&g_StringPosition) = (posX & 0xFFFF) + (posY << 16);

    return result;
}
#else
INCLUDE_ASM("asm/bodyprog/nonmatchings/text_draw", Gfx_StringDraw); // 0x8004A8E8
#endif

void MapMsgCalculateWidthTable(s32 mapMsgIdx) // 0x8004ACF4
{
    #define GLYPH_SPACE_SIZE 6
    #define LINE_MAX_COUNT 9
    s32 i;
    s32 j;
    s8 tagCode;
    s8 tagArg;
    u8* mapMsg;
    s32 charCode;
    u8 msgCode;
    s32 msgArg;

    D_800C38B4.lineCount_0 = 1;
    g_MapMsgAudioLoadBlock       = 0;
    
    for (i = LINE_MAX_COUNT-1; i >= 0; i--)
    {
        g_MapMsgWidthTable[i] = 0;
    }

    mapMsg = g_MapOverlayHeader.mapMessageStrings_30[mapMsgIdx];
    
    for (j = 0; j < LINE_MAX_COUNT; )
    {
        charCode = *mapMsg;
        
        switch (charCode)
        {
            case '\t':
            case '\n':
            case ' ':
                mapMsg++;
                break;
            
            case '_':
                ++mapMsg;
                g_MapMsgWidthTable[D_800C38B4.lineCount_0 - 1] += GLYPH_SPACE_SIZE;
                break;
                
            case MAP_MSG_CODE_MARKER:
                msgCode = *++mapMsg;
                msgArg = *++mapMsg - '0';
                
                switch (msgCode) 
                {
                    case MAP_MSG_CODE_COLOR:
                    case MAP_MSG_CODE_SELECT:
                    case MAP_MSG_CODE_TAB:
                        break;

                    case MAP_MSG_CODE_NEWLINE:
                        j = j + 1;
                        D_800C38B4.lineCount_0++;
                        break;

                    case MAP_MSG_CODE_END:
                        j = LINE_MAX_COUNT;
                        break;

                    case MAP_MSG_CODE_LINE_POSITION:
                        D_800C38B0.positionIdx_1 = msgArg;
                        break;

                    case MAP_MSG_CODE_JUMP:
                        if (msgArg == 2)
                        {
                            g_MapMsgAudioLoadBlock = 3;
                        }

                        while (msgArg != ' ' && msgArg != '\t')
                        {
                            msgArg = *++mapMsg;
                        }

                        break;

                    case MAP_MSG_CODE_HIGH_RES:
                        g_SysWork.HighResolutionTextRender = 1;
                        break;
                }
                
                mapMsg++;
                break;
            
            case 0:
                j = LINE_MAX_COUNT;
                break;
            
            default:
                if (charCode == '!')
                {
                    charCode = '\\';
                } 
                else if (charCode == '&')
                {
                    charCode = '^';
                }
                
                g_MapMsgWidthTable[D_800C38B4.lineCount_0 - 1] += D_80025D6C[charCode - '\''];
                mapMsg++;
            break;
        }
    }
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/text_draw", func_8004AF18); // 0x8004AF18

void func_8004B658() // 0x8004B658
{
    D_800C38F8.attribute = 64;
    D_800C38F8.cx        = 304;
    D_800C38F8.v         = 240;
    D_800C38F8.h         = 16;
}

void func_8004B684() // 0x8004B684
{
    D_800C38B4.lineCount_0   = 1;
    D_800C38B0.field_0       = 0;
    D_800C38B0.positionIdx_1 = 1;
    g_StringPositionX1       = SCREEN_POSITION_X(-37.5f);
    g_StringColorId          = ColorId_White;
    g_SysWork.HighResolutionTextRender   = 0;
}

void func_8004B6D4(s16 arg0, s16 arg1) // 0x8004B6D4
{
    if (arg0 != NO_VALUE)
    {
        D_800C38FC = arg0 + (-g_GameWork.gsScreenWidth_588 / 2);
        D_800C391C = D_800C38FC;
    }

    if (arg1 != NO_VALUE)
    {
        D_800C38FE = arg1 + (-g_GameWork.gsScreenHeight_58A / 2);
    }
}

void func_8004B74C(s16 arg0) // 0x8004B74C
{
    if (arg0 < 0 || arg0 >= 5)
    {
        D_800C391E = 0;
        return;
    }

    D_800C391E = arg0;
}

void func_8004B76C(char* str, s32 useFixedWidth) // 0x8004B76C
{
    #define GLYPH_SIZE_X       11
    #define GLYPH_SIZE_Y       12
    #define SPACE_SIZE         12
    #define LINE_SPACE_SIZE    16
    #define ATLAS_COLUMN_COUNT 21

    s32       tileRow;
    s32       glyphIdx;
    GsOT*     ot;
    GsSPRITE* glyphSprt;

    glyphSprt  = (GsSPRITE*)PSX_SCRATCH_ADDR(0x30);
    *glyphSprt = D_800C38F8;
    ot         = &g_ObjectTable1[g_ObjectTableIdx];

    // Parse string.
    while (*str != '\0')
    {
        switch (*str) 
        {
            // Draw glyph sprite.
            default:
                glyphIdx     = *str - '\'';
                tileRow      = glyphIdx / ATLAS_COLUMN_COUNT;
                glyphSprt->u = (glyphIdx % ATLAS_COLUMN_COUNT) * GLYPH_SIZE_Y;

                if (useFixedWidth)
                {
                    glyphSprt->w = GLYPH_SIZE_X;
                } 
                else 
                {
                    glyphSprt->w = D_80025D6C[glyphIdx];
                }

                glyphSprt->tpage = (tileRow & 0xF) | 0x10;
                glyphSprt->cx    = 304;
                glyphSprt->cy    = D_800C391E + 506;

                GsSortFastSprite(glyphSprt, ot, 4);

                glyphSprt->x += glyphSprt->w;
                break;

            // Space.
            case ' ':
            case '\t':
                glyphSprt->x += SPACE_SIZE;
                break;

            // Backspace.
            case '~':
            case '\b':
                glyphSprt->x -= SPACE_SIZE;
                break;
            
            // Newline.
            case '\n':
                glyphSprt->x  = D_800C391C;
                glyphSprt->y += LINE_SPACE_SIZE;
                break;

            // Carriage return.
            case '\r':
                glyphSprt->x  = D_800C391C;
                glyphSprt->y -= LINE_SPACE_SIZE;
                break;
        }

        str++; 
    }

    D_800C38F8 = *glyphSprt;
}

void Gfx_StringDrawInt(s32 widthMin, s32 val) // 0x8004B9F8
{
    #define GLYPH_SIZE_X       11
    #define ATLAS_COLUMN_COUNT 10

    s32   quotient;
    s32   isNegative;
    s32   i;
    char* str;

    if (widthMin > 0) 
    {
        for (i = 0; i < (widthMin - 1); i++) 
        {
            D_800C38F8.x += GLYPH_SIZE_X;
        }
    }

    str  = (char*)PSX_SCRATCH_ADDR(0x2F);
    *str = 0;

    if (val < 0) 
    {
        isNegative = true;
        val        = -val;
    } 
    else 
    {
        isNegative = false;
    }

    // Wrap atlas row?
    while (val >= ATLAS_COLUMN_COUNT)
    {
        str--;
        quotient = (val / ATLAS_COLUMN_COUNT) >> 32;
        *str     = (val - (quotient * ATLAS_COLUMN_COUNT)) + '0';
            
        if (widthMin > 0) 
        {
            D_800C38F8.x -= GLYPH_SIZE_X;
        }
        
        val = quotient;
    }

    str--;
    *str = val + '0';

    if (isNegative)
    {
        str--;
        *str          = '-';
        D_800C38F8.x -= GLYPH_SIZE_X;
    }

    // Draw numeric string.
    Gfx_StringDraw(str, 5);
    return;
}

void func_8004BB10() // 0x8004BB10
{
    GsFCALL4.g3[GsDivMODE_NDIV][GsLMODE_FOG]  = GsTMDfastG3LFG;
    GsFCALL4.tg3[GsDivMODE_NDIV][GsLMODE_FOG] = GsTMDfastTG3LFG;
    GsFCALL4.g4[GsDivMODE_NDIV][GsLMODE_FOG]  = GsTMDfastG4LFG;
    GsFCALL4.tg4[GsDivMODE_NDIV][GsLMODE_FOG] = GsTMDfastTG4LFG;
}
