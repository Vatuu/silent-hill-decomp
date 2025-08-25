#include "game.h"

#include <strings.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/math.h"
#include "main/fsqueue.h"

/** Known contents:
 * - Map loading funcs
 * - Animation funcs
 */

s8 Sound_StereoBalanceGet(const VECTOR3* soundPos) // 0x80040A64
{
    #define STEREO_BALANCE_RANGE 127

    VECTOR3 camPos;
    VECTOR  vec0;
    VECTOR  vec1;
    MATRIX  mat;
    s32     dot;
    s32     balance;

    // If monoural sound type, default to balance of 0.
    if (g_GameWork.config_0.optSoundType_1E)
    {
        return 0;
    }

    // Compute normal from camera and sound source positions.
    vwGetViewPosition(&camPos);
    vec0.vx = (soundPos->vx - camPos.vx) >> 6;
    vec0.vy = (soundPos->vy - camPos.vy) >> 6;
    vec0.vz = (soundPos->vz - camPos.vz) >> 6;
    VectorNormal(&vec0, &vec1);

    // Compute stereo balance.
    Vw_CoordHierarchyMatrixCompute(vwGetViewCoord(), &mat);
    dot     = Math_MultiplyMatrix(mat, vec1);
    balance = CLAMP(dot, -STEREO_BALANCE_RANGE, STEREO_BALANCE_RANGE);
    return balance;
}

void func_80040B6C() {}

bool func_80040B74(s32 arg0) // 0x80040B74
{
    s32 i;

    for (i = 0; i < ARRAY_SIZE(D_800BCE18.field_0); i++)
    {
        if (D_800BCE18.field_0[i].field_CC.field_0 == arg0)
        {
            return true;
        }
    }

    return false;
}

// Related to the screen.
INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80040BAC); // 0x80040BAC

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80040E7C); // 0x80040E7C

void func_80041074(s32 arg0, void* arg1, SVECTOR* arg2, VECTOR3* arg3) // 0x80041074
{
    VECTOR3 sp18;
    s32     sp28;
    s32     sp2C;

    func_800410D8(&sp18, &sp28, &sp2C, arg2, arg3);
    func_800414E0(arg0, &sp18, arg1, sp28, sp2C);
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_800410D8); // 0x800410D8

void func_8004122C(s32* angle0, s32* angle1, VECTOR* arg2, VECTOR* arg3) // 0x8004122C
{
    VECTOR  vec0;
    VECTOR  vec1;
    VECTOR  vec2;
    SVECTOR svec0;
    SVECTOR svec1;
    VECTOR  vec3;

    VectorNormal(arg2, &vec0);
    VectorNormal(arg3, &vec1);
    OuterProduct12(&vec0, &vec1, &vec2);
    VectorNormal(&vec2, &vec2);

    *angle0 = FP_ANGLE_NORM_U(ratan2(vec2.vy, vec2.vx) - FP_ANGLE(90.0f));

    svec0.vx = FP_FROM((vec0.vx * vec1.vx) + (vec0.vy * vec1.vy) + (vec0.vz * vec1.vz), Q12_SHIFT);
    OuterProduct12(&vec2, &vec0, &vec3);
    svec1.vx = FP_FROM((vec1.vx * vec3.vx) + (vec1.vy * vec3.vy) + (vec1.vz * vec3.vz), Q12_SHIFT);

    *angle1 = FP_ANGLE_NORM_U(ratan2(svec1.vx, svec0.vx));
}

void func_8004137C(VECTOR3* result, VECTOR* vec0, VECTOR* vec1, s32 screenDist)
{
    VECTOR vec;
    s32    offsetX;
    s32    offsetY;
    s32    screenDistHalf;
    s32    z;

    screenDistHalf = screenDist / 2;

    if (screenDistHalf < vec0->vz)
    {
        vec = *vec0;
    }
    else
    {
        z = 1;
        if (vec1->vz != 0)
        {
            z = vec1->vz;
        }

        vec.vz = screenDistHalf;
        vec.vx = (((screenDistHalf - vec0->vz) * vec1->vx) / z) + vec0->vx;
        vec.vy = (((screenDistHalf - vec0->vz) * vec1->vy) / z) + vec0->vy;
    }

    ReadGeomOffset(&offsetX, &offsetY);

    result->vz = vec.vz;
    result->vx = ((vec.vx * screenDist) / vec.vz) + offsetX;
    result->vy = ((vec.vy * screenDist) / vec.vz) + offsetY;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_800414E0); // 0x800414E0

u32 func_80041ADC(s32 queueIdx) // 80041ADC
{
    if (queueIdx == NO_VALUE)
    {
        return 0;
    }
    else if (Fs_QueueIsEntryLoaded(queueIdx) == 0)
    {
        return 1;
    }

    return 2;
}

u32 func_80041B1C(s_800C117C* arg0) // 0x80041B1C
{
    s32 temp_v0;
    s32 newVar;

    temp_v0 = func_80041ADC(arg0->queueIdx_4);
    newVar  = temp_v0;

    if (newVar == 1)
    {
        return 1;
    }
    else if ((newVar == 0) || (temp_v0 != 2))
    {
        return 0;
    }
    else if (arg0->ipdHeader_0->isLoaded_1 && func_80043B70(arg0->ipdHeader_0))
    {
        return 3;
    }

    return 2;
}

s32 func_80041BA0(s_func_80041CB4* arg0) // 0x80041BA0
{
    s32 temp_v0;
    s32 newVar;

    temp_v0 = func_80041ADC(arg0->queueIdx_8);
    newVar  = temp_v0;

    if (newVar == 1)
    {
        return 1;
    }
    else if (newVar == 0 || temp_v0 != 2)
    {
        return 0;
    }
    else if (arg0->plmHeader_0->isLoaded_2 && func_80056888(arg0->plmHeader_0))
    {
        return 3;
    }

    return 2;
}

void func_80041C24(s_PlmHeader* plmHeader, s32 arg1, s32 arg2) // 0x80041C24
{
    bzero(&D_800C1020, 1420);
    func_80041CB4(&D_800C1020.field_138, plmHeader);

    D_800C1020.field_150 = arg1;
    D_800C1020.field_154 = arg2;
    D_800C1020.field_158 = 0;
    D_800C1020.field_588 = 1;

    func_80041D10(D_800C1020.field_15C, 4);
    func_80041D48();
    func_80041E98();
}

// This function is related to map loading.
void func_80041CB4(s_func_80041CB4* arg0, s_PlmHeader* plmHeader) // 0x80041CB4
{
    arg0->plmHeader_0 = plmHeader;
    func_80041CEC(plmHeader);

    arg0->queueIdx_8 = NULL;
    arg0->field_4    = NO_VALUE;
}

void func_80041CEC(s_PlmHeader* plmHeader) // 0x80041CEC
{
    plmHeader->magic_0        = PLM_HEADER_MAGIC;
    plmHeader->version_1      = 6;
    plmHeader->isLoaded_2     = 1;
    plmHeader->textureCount_3 = 0;
    plmHeader->objectCount_8  = 0;
}

void func_80041D10(s_800C117C* arg0, s32 size) // 0x80041D10
{
    s_800C117C* ptr;

    for(ptr = &arg0[0]; ptr < &arg0[size]; ptr++)
    {
        ptr->queueIdx_4 = NO_VALUE;
    }
}

void func_80041D48() // 0x80041D48
{
    s32 i;
    s16 j;
    s16 x;
    s32 y;

    for (i = 0, y = 8, x = 0, j = 0; i < 8; i++, y++, x += 16)
    {
        if (y == 11)
        {
            y = 21;
        }

        func_8005B1A0(&D_800C1450.field_58[i], 0, 0, y, 0, 0, x, j);
    }

    func_8005B46C(&D_800C1450.field_0);
    func_8005B474(&D_800C1450.field_0, D_800C1450.field_58, 8);

    for (i = 0, y = 26, j = 0; i < 2; i++, x += 16)
    {
        func_8005B1A0(&D_800C1450.field_118[i], 0, 0, y, (i & 0x1) * 32, 0, x, j);
        if (i & 0x1)
        {
            y++;
        }
    }

    func_8005B46C(&D_800C1450.field_2C);
    func_8005B474(&D_800C1450.field_2C, D_800C1450.field_118, 2);
}

void func_80041E98() // 0x80041E98
{
    bzero(&D_800C1020, 308);
    D_800C1020.field_1C = 512;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80041ED0); // 0x80041ED0

void func_80041FF0() // 0x80041FF0
{
    func_80042300(&D_800C1020, D_800C1020.field_158);
}

void func_8004201C() // 0x8004201C
{
    s_800C1450_58* ptr;

    ptr = &D_800C1450.field_58[0];
    while (ptr < (&D_800C1450.field_58[8]))
    {
        if (ptr->field_14 == 0)
        {
            func_8005B3A4(ptr);
        }

        ptr++;
    }

    ptr = &D_800C1450.field_118[0];
    while (ptr < (&D_800C1450.field_118[2]))
    {
        if (ptr->field_14 == 0)
        {
            func_8005B3A4(ptr);
        }

        ptr++;
    }
}

void func_800420C0() // 0x800420C0
{
    func_800420FC();
    func_80042300(&D_800C1020, D_800C1020.field_158);
    func_80041D48();
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_800420FC); // 0x800420FC

s_800C1450_58* func_80042178(char* arg0) // 0x80042178
{
    s_800C1450_58* ptr;
    
    ptr = func_8005B4BC(arg0, &D_800C1450.field_0);
    if (ptr != NULL)
    {
        return ptr;
    }

    ptr = func_8005B4BC(arg0, &D_800C1450.field_2C);
    if (ptr != NULL)
    {
        return ptr;
    }

    return NULL;
}

void func_800421D8(char* arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) // 0x800421D8
{
    D_800C1020.field_588 = arg3;
    D_800C1020.field_134 = arg5;

    if (arg1 != NO_VALUE)
    {
        if (arg1 != D_800C1020.field_138.field_4)
        {
            if (func_80041ADC(D_800C1020.field_138.queueIdx_8) >= 2 && D_800C1020.field_138.plmHeader_0->isLoaded_2)
            {
                func_80056BF8(D_800C1020.field_138.plmHeader_0);
            }

            D_800C1020.field_138.field_4 = arg1;
            D_800C1020.field_138.queueIdx_8 = NO_VALUE;
        }
    }

    if (D_800C1020.field_158 != arg2 || strcmp(arg0, D_800C1020.field_144) != 0)
    {
        func_80042300(&D_800C1020, arg2);

        D_800C1020.field_158 = arg2;
        D_800C1020.field_14C = arg4;
        strcpy(D_800C1020.field_144, arg0);

        D_800C1020.field_148 = strlen(arg0);
        func_800423F4(&D_800C1020, arg0, arg4);
    }
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80042300); // 0x80042300

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_800423F4); // 0x800423F4

bool func_8004255C(s32* out, char firstHex, char secondHex) // 0x8004255C
{
    char low;
    char high;
    char letterIdx;
    char hexVal;
    bool isNumber;

    high     = firstHex - '0';
    isNumber = high < 10;

    hexVal   = high;
    hexVal <<= 4;
    if (!isNumber)
    {
        letterIdx = firstHex - 'A';
        if (letterIdx > 5)
        {
            return false;
        }

        hexVal = (firstHex + 201) << 4;
    }

    low      = secondHex - '0';
    isNumber = low < 10;
    if (isNumber)
    {
        hexVal |= low;
    }
    else
    {
        letterIdx = secondHex - 'A';
        if (letterIdx > 5)
        {
            return false;
        }

        hexVal |= secondHex + 201;
    }

    *out = (hexVal << 24) >> 24; // Sign extend.
    return true;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_800425D8); // 0x800425D8

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_800426E4); // 0x800426E4

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_8004287C); // 0x8004287C

s32 func_80042C04(s32 idx) // 0x80042C04
{
    return (func_80041B1C(&D_800C117C[idx]) < 3) ^ 1;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80042C3C); // 0x80042C3C

s32 func_80042DE8(s32 posX, s32 posZ, s32 fileChunkCoordX, s32 fileChunkCoordZ, s32 clip) // 0x80042DE8
{
    #define DIST_THRESHOLD FP_METER(1.0f)

    s32 dist;

    dist = func_80042E2C(FP_FROM(posX, Q4_SHIFT), FP_FROM(posZ, Q4_SHIFT), fileChunkCoordX, fileChunkCoordZ);
    if (clip != 0)
    {
        dist -= DIST_THRESHOLD;
        if (dist < 0)
        {
            dist = 0;
        }
    }

    return dist;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80042E2C); // 0x80042E2C

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80042EBC); // 0x80042EBC

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_800431E4); // 0x800431E4

void func_80043338(s_80043338* arg0, s32 posX0, s32 posZ0, s32 posX1, s32 posZ1, s32 clip) // 0x80043338
{
    arg0->field_C  = func_80042DE8(posX0, posZ0, arg0->fileChunkCoordX_8, arg0->fileChunkCoordZ_A, clip);
    arg0->field_10 = func_80042DE8(posX1, posZ1, arg0->fileChunkCoordX_8, arg0->fileChunkCoordZ_A, clip);
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_800433B8); // 0x800433B8

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80043554); // 0x80043554

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80043578); // 0x80043578

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_800435E4); // 0x800435E4

s32 func_800436D8(s_80043338* arg0, s32 fileIdx, s16 fileChunkCoordX, s16 fileChunkCoordZ, s32 posX0, s32 posZ0, s32 posX1, s32 posZ1, s32 clip) // 0x800436D8
{
    // Return `NO_VALUE` if no file specified.
    if (fileIdx == NO_VALUE)
    {
        return fileIdx;
    }

    // Store file chunk coords and read file.
    arg0->fileChunkCoordX_8 = fileChunkCoordX;
    arg0->fileChunkCoordZ_A = fileChunkCoordZ;
    arg0->queueEntryIdx_4   = Fs_QueueStartRead(fileIdx, arg0->destBuffer_0);

    // Compute and store distance to file chunk edge in `arg0`.
    func_80043338(arg0, posX0, posZ0, posX1, posZ1, clip);

    // Return queue entry index.
    return arg0->queueEntryIdx_4;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80043740); // 0x80043740

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80043830); // 0x80043830

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_8004393C); // 0x8004393C

void func_80043A24(GsOT* ot, s32 arg1) // 0x80043A24
{
    s_800C117C* ptr;
    s32         status;

    status = func_80041ADC(D_800C1020.field_138.queueIdx_8);

    if (status == 1)
    {
        return;
    }

    if (!(status == 0 || (status == 2 && D_800C1020.field_138.plmHeader_0->isLoaded_2)))
    {
        return;
    }

    ptr = &D_800C1020.field_15C[0];
    for (; ptr < &D_800C1020.field_15C[D_800C1020.field_158]; ptr++)
    {
        if (func_80041B1C(ptr) >= 3 && func_80043B34(ptr, &D_800C1020))
        {
            func_80044090(ptr->ipdHeader_0, D_800C1020.field_578, D_800C1020.field_57C, ot, arg1);
        }
    }
}

bool func_80043B34(s_800C117C* arg0, s_800C1020* arg1)
{
    if (arg1->field_580 == arg0->field_8 && arg1->field_584 == arg0->field_A)
    {
        return true;
    }

    return arg1->field_588 != 0;
}

bool func_80043B70(s_IpdHeader* ipdHeader) // 0x80043B70
{
    if (!ipdHeader->isLoaded_1)
    {
        return false;
    }

    return func_80056888(ipdHeader->plmHeader_4);
}

s_IpdCollisionData* IpdHeader_CollisionDataGet(s_IpdHeader* ipdHeader) // 0x80043BA4
{
    if (ipdHeader->isLoaded_1)
    {
        return &ipdHeader->collisionData_54;
    }

    return NULL;
}

void IpdHeader_FixOffsets(s_IpdHeader* ipdHeader, s_PlmHeader** plmHeaders, s32 plmHeaderCount, s32 arg3, s32 arg4, s32 arg5) // 0x80043BC4
{
    if (ipdHeader->isLoaded_1)
    {
        return;
    }
    ipdHeader->isLoaded_1 = true;

    IpdHeader_FixHeaderOffsets(ipdHeader);
    IpdCollData_FixOffsets(&ipdHeader->collisionData_54);
    PlmHeader_FixOffsets(ipdHeader->plmHeader_4);
    func_8008E4EC(ipdHeader->plmHeader_4);
    func_80043C7C(ipdHeader, arg3, arg4, arg5);
    func_80056954(ipdHeader->plmHeader_4);
    IpdHeader_ModelLinkObjectLists(ipdHeader, plmHeaders, plmHeaderCount);
    func_80043F88(ipdHeader, ipdHeader->modelInfo_14);
}

void func_80043C7C(s_IpdHeader* ipdHeader, s32 arg1, s32* arg2, s32 arg3) // 0x80043C7C
{
    if (!ipdHeader->isLoaded_1)
    {
        return;
    }

    if (arg1 != 0)
    {
        func_80056774(ipdHeader->plmHeader_4, arg1, &func_80043D44, arg3, 1);
    }

    if (arg2 != NULL)
    {
        func_80056774(ipdHeader->plmHeader_4, arg2, &func_80043D64, arg3, 1);
    }
}

s32 func_80043D00(s_IpdHeader* ipdHeader) // 0x80043D00
{
    if (!ipdHeader->isLoaded_1)
    {
        return 0;
    }

    return func_80056348(&func_80043D64, ipdHeader->plmHeader_4);
}

bool func_80043D44(s_PlmTexList* texList) // 0x80043D44
{
    return !func_80043D64(texList);
}

bool func_80043D64(s_PlmTexList* texList) // 0x80043D64
{
    char* charCode;

    for (charCode = &texList->texName_0.str[7]; charCode >= &texList->texName_0.str[0]; charCode--)
    {
        if (*charCode == '\0')
        {
            continue;
        }

        return *charCode == 'H';
    }

    return false;
}

void IpdHeader_FixHeaderOffsets(s_IpdHeader* header) // 0x80043DA4
{
    s_IpdModelBuffer* modelBuf;

    header->plmHeader_4       = (u8*)header->plmHeader_4 + (u32)header;
    header->modelInfo_14      = (u8*)header->modelInfo_14 + (u32)header;
    header->modelBuffers_18   = (u8*)header->modelBuffers_18 + (u32)header;
    header->modelOrderList_50 = (u8*)header->modelOrderList_50 + (u32)header;

    for (modelBuf = &header->modelBuffers_18[0];
         modelBuf < &header->modelBuffers_18[header->modelBufferCount_9];
         modelBuf++)
    {
        modelBuf->field_C  = (u8*)modelBuf->field_C + (u32)header;
        modelBuf->field_10 = (u8*)modelBuf->field_10 + (u32)header;
        modelBuf->field_14 = (u8*)modelBuf->field_14 + (u32)header;
    }
}

void IpdHeader_ModelLinkObjectLists(s_IpdHeader* ipdHeader, s_PlmHeader** plmHeaders, s32 plmHeaderCount) // 0x80043E50
{
    s32             i;
    s32             j;
    s_IpdModelInfo* modelInfo;

    for (i = 0; i < ipdHeader->modelCount_8; i++)
    {
        modelInfo = &ipdHeader->modelInfo_14[i];
        if (!modelInfo->isGlobalPlm_0)
        {
            modelInfo->objList_C = PlmHeader_ObjectListSearch(&modelInfo->modelName_4, ipdHeader->plmHeader_4);
        }
        else
        {
            for (j = 0; j < plmHeaderCount; j++)
            {
                modelInfo->objList_C = PlmHeader_ObjectListSearch(&modelInfo->modelName_4, plmHeaders[j]);
                if (modelInfo->objList_C != NULL)
                {
                    break;
                }
            }
        }
    }
}

s_ObjList* PlmHeader_ObjectListSearch(u_Filename* objName, s_PlmHeader* plmHeader) // 0x80043F2C
{
    s32        i;
    s_ObjList* objList;

    objList = plmHeader->objectList_C;

    for (i = 0; i < plmHeader->objectCount_8; i++, objList++)
    {
        if (objName->u32[0] == objList->objName_0.u32[0] &&
            objName->u32[1] == objList->objName_0.u32[1])
        {
            return objList;
        }
    }

    return NULL;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80043F88); // 0x80043F88

void func_80044044(s_80044044* arg0, s32 arg1, s32 arg2) // 0x80044044
{
    s32 var0;
    s32 var1;

    var0 = arg0->field_2;
    var1 = arg0->field_3;

    arg0->field_2 = arg1;
    arg0->field_3 = arg2;
    arg0->field_54 = (arg0->field_54 + ((arg1 - var0) * 0x2800));
    arg0->field_58 = (arg0->field_58 + ((arg2 - var1) * 0x2800));
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80044090); // 0x80044090

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80044420); // 0x80044420

// ========================================
// ANIMATION
// ========================================

// Could be used to load the player model or to execute animations.
// Removing the call from `Game_PlayerInit` causes the player model to not appear.
INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_800445A4); // 0x800445A4

// Anim func.
INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_800446D8); // 0x800446D8

s_AnimInfo* func_80044918(s_ModelAnim* anim) // 0x80044918
{
    // `field_C`/`field_10` usually points to data at `0x800AF228` which contains funcptrs and other stuff.

    s_AnimInfo* animInfo_C;
    s_AnimInfo* animInfo_10;
    u8          animIdx_0;
    s32         animIdx_1;

    animInfo_C  = anim->animInfo_C;
    animInfo_10 = anim->animInfo_10;
    animIdx_0   = anim->animIdx_0;
    animIdx_1   = anim->maybeSomeState_1;

    if (animInfo_10 != NULL && animIdx_0 >= animIdx_1)
    {
        animInfo_C  = animInfo_10;
        animInfo_C -= animIdx_1;
    }

    return &animInfo_C[animIdx_0];
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80044950); // 0x80044950

s32 func_800449AC(s_Model* model, s_AnimInfo* anim) // 0x800449AC
{
    if (anim->hasVariableTimeDelta_5 == 0)
    {
        return anim->timeDelta_8.constTimeDelta;
    }

    return anim->timeDelta_8.variableTimeDeltaFunc(); // The arguments might be passed here.
}

static inline s32 Anim_GetTimeStep(s_Model* model, s_AnimInfo* targetAnim)
{
    s32 timeDelta;

    if (model->anim_4.flags_2 & AnimFlag_Unk1)
    {
        timeDelta = func_800449AC(model, targetAnim);
        return FP_MULTIPLY_PRECISE(timeDelta, (s64)g_DeltaTime0, Q12_SHIFT);
    }

    return 0;
}

void Anim_Update0(s_Model* model, s_Skeleton* skel, GsCOORDINATE2* coord, s_AnimInfo* targetAnim) // 0x800449F0
{
    bool setAnimIdx;
    s32  timeStep;
    s32  newTime;
    s32  newKeyframeIdx0;
    s32  targetTime;
    s32  alpha;

    setAnimIdx = false;

    // Get time step.
    timeStep = Anim_GetTimeStep(model, targetAnim);

    // Compute new time.
    newTime         = model->anim_4.time_4;
    newKeyframeIdx0 = FP_FROM(newTime, Q12_SHIFT);
    if (timeStep != 0)
    {
        // Clamp new time against target time?
        newTime   += timeStep;
        targetTime = FP_TO(targetAnim->keyframeIdx1_E, Q12_SHIFT);
        if (newTime < targetTime)
        {
            targetTime = FP_TO(targetAnim->keyframeIdx0_C, Q12_SHIFT);
            if (newTime <= targetTime)
            {
                newTime    = targetTime;
                setAnimIdx = true;
            }
        }
        else
        {
            newTime    = targetTime;
            setAnimIdx = true;
        }

        newKeyframeIdx0 = FP_FROM(newTime, Q12_SHIFT);
    }

    // Update skeleton.
    alpha = FP_ALPHA_NORM(newTime);
    if ((model->anim_4.flags_2 & AnimFlag_Unk1) || (model->anim_4.flags_2 & AnimFlag_Visible))
    {
        func_800446D8(skel, coord, newKeyframeIdx0, newKeyframeIdx0 + 1, alpha);
    }

    // Update frame data.
    model->anim_4.time_4         = newTime;
    model->anim_4.keyframeIdx0_8 = newKeyframeIdx0;
    model->anim_4.keyframeIdx1_A = 0;

    // Update anim.
    if (setAnimIdx)
    {
        model->anim_4.animIdx_0 = targetAnim->animIdx_6;
    }
}

void Anim_Update1(s_Model* model, s_Skeleton* skel, GsCOORDINATE2* coord, s_AnimInfo* targetAnim) // 0x80044B38
{
    s32 keyframeIdx0;
    s32 keyframeIdx1;
    s32 nextKeyframeIdx;
    s32 keyframeDelta;
    s32 currentKeyframeTime;
    s32 nextKeyframeTime;
    s32 keyframeTimeDelta;
    s32 timeStep;
    s32 newTime;
    s32 newKeyframeIdx0;
    s32 newKeyframeIdx1;
    s32 alpha;

    keyframeIdx0    = targetAnim->keyframeIdx0_C;
    keyframeIdx1    = targetAnim->keyframeIdx1_E;
    nextKeyframeIdx = keyframeIdx1 + 1;
    keyframeDelta   = nextKeyframeIdx - keyframeIdx0;

    currentKeyframeTime = FP_TO(keyframeIdx0, Q12_SHIFT);
    nextKeyframeTime    = FP_TO(nextKeyframeIdx, Q12_SHIFT);
    keyframeTimeDelta   = FP_TO(keyframeDelta, Q12_SHIFT);

    // Get time step.
    timeStep = Anim_GetTimeStep(model, targetAnim);

    // Wrap new time to valid range?
    newTime = model->anim_4.time_4 + timeStep;
    while (newTime < currentKeyframeTime)
    {
        newTime += keyframeTimeDelta;
    }
    while (newTime >= nextKeyframeTime)
    {
        newTime -= keyframeTimeDelta;
    }

    // Compute new keyframe 1.
    newKeyframeIdx0 = FP_FROM(newTime, Q12_SHIFT);
    newKeyframeIdx1 = newKeyframeIdx0 + 1;
    if (newKeyframeIdx1 == nextKeyframeIdx)
    {
        newKeyframeIdx1 = keyframeIdx0;
    }

    // Update skeleton.
    alpha = FP_ALPHA_NORM(newTime);
    if ((model->anim_4.flags_2 & AnimFlag_Unk1) || (model->anim_4.flags_2 & AnimFlag_Visible))
    {
        func_800446D8(skel, coord, newKeyframeIdx0, newKeyframeIdx1, alpha);
    }

    // Update frame data.
    model->anim_4.time_4         = newTime;
    model->anim_4.keyframeIdx0_8 = newKeyframeIdx0;
    model->anim_4.keyframeIdx1_A = 0;
}

void Anim_Update2(s_Model* model, s_Skeleton* skel, GsCOORDINATE2* coord, s_AnimInfo* targetAnim) // 0x80044CA4
{
    bool setAnimIdx;
    s32  newKeyframeIdx0;
    s32  newKeyframeIdx1;
    s32  timeStep;
    s32  alpha;
    
    setAnimIdx      = false;
    newKeyframeIdx0 = targetAnim->keyframeIdx0_C;
    newKeyframeIdx1 = targetAnim->keyframeIdx1_E;

    // If no target frame 0 set, default to current frame index 0.
    if (newKeyframeIdx0 == NO_VALUE)
    {
        newKeyframeIdx0 = model->anim_4.keyframeIdx0_8;
    }

    // Get time step.
    timeStep = Anim_GetTimeStep(model, targetAnim);

    // Set time.
    alpha  = model->anim_4.keyframeIdx1_A;
    alpha += timeStep;
    if (alpha >= FP_ALPHA(0.5f))
    {
        model->anim_4.time_4 = FP_TO(newKeyframeIdx1, 12);
    }
    else
    {
        model->anim_4.time_4 = FP_TO(newKeyframeIdx0, Q12_SHIFT);
    }

    // Progress keyframes.
    if (alpha >= FP_ALPHA(1.0f))
    {
        newKeyframeIdx0              = newKeyframeIdx1;
        model->anim_4.keyframeIdx0_8 = newKeyframeIdx1;
        
        alpha      = FP_ALPHA(0.0f);
        setAnimIdx = true;
    }

    // Update skeleton.
    if ((model->anim_4.flags_2 & AnimFlag_Unk1) || (model->anim_4.flags_2 & AnimFlag_Visible))
    {
        func_800446D8(skel, coord, newKeyframeIdx0, newKeyframeIdx1, alpha);
    }

    // Update frame 1.
    model->anim_4.keyframeIdx1_A = alpha;

    // Update anim.
    if (setAnimIdx)
    {
        model->anim_4.animIdx_0 = targetAnim->animIdx_6;
    }
}

void Anim_Update3(s_Model* model, s_Skeleton* skel, GsCOORDINATE2* coord, s_AnimInfo* targetAnim) // 0x80044DF0
{
    s32 keyframeIdx0;
    s32 keyframeIdx1;
    s32 timeDelta;
    register s32 timeStep asm("v0"); // HACK: Manually set register to match.
    s32 newKeyframeIdx1;
    s32 sinVal;
    s32 newTime;
    s32 alpha;

    keyframeIdx0 = targetAnim->keyframeIdx0_C;
    keyframeIdx1 = targetAnim->keyframeIdx1_E;

    // Compute time step. NOTE: Can't call `Anim_GetTimeStep` inline due to register constraints.
    if (model->anim_4.flags_2 & AnimFlag_Unk1)
    {
        timeDelta = func_800449AC(model, targetAnim);
        timeStep  = FP_MULTIPLY_PRECISE(timeDelta, (s64)g_DeltaTime0, Q12_SHIFT);
    }
    else
    {
        timeStep = 0;
    }

    // Update keyframe 1.
    newKeyframeIdx1              = model->anim_4.keyframeIdx1_A + timeStep;
    model->anim_4.keyframeIdx1_A = newKeyframeIdx1;

    // Sine-based easing?
    sinVal = Math_Sin((newKeyframeIdx1 / 2) - FP_ALPHA(0.25f));
    alpha  = (sinVal / 2) + FP_ALPHA(0.5f);

    // Clamp new time to keyframe 0 or 1.
    if (alpha >= FP_ALPHA(0.5f))
    {
        newTime = FP_TO(keyframeIdx0, Q12_SHIFT);
    }
    else
    {
        newTime = FP_TO(keyframeIdx1, Q12_SHIFT);
    }

    // Update time.
    model->anim_4.time_4 = newTime;

    // Update skeleton.
    if ((model->anim_4.flags_2 & AnimFlag_Unk1) || (model->anim_4.flags_2 & AnimFlag_Visible))
    {
        func_800446D8(skel, coord, keyframeIdx0, keyframeIdx1, alpha);
    }

    // Update keyframe 0.
    model->anim_4.keyframeIdx0_8 = FP_FROM(newTime, Q12_SHIFT);
}

void func_80044F14(GsCOORDINATE2* coord, s16 z, s16 x, s16 y) // 0x80044F14
{
    *(s16*)0x1F800004 = z;
    *(s16*)0x1F800002 = y;
    *(s16*)0x1F800000 = x;
    
    func_80096E78((SVECTOR*)0x1F800000, (MATRIX*)0x1F800008);
    MulMatrix(&coord->coord, (MATRIX*)0x1F800008);
}

s8 func_80044F6C(s8* ptr, bool arg1) // 0x80044F6C
{
    s8 temp;

    if (arg1)
    {
        D_800C15B0 = ptr;
    }

    if (D_800C15B0[0] != -3)
    {
        D_800C15B4 = D_800C15B0[0];
        D_800C15B0++;
    }
    else if (++D_800C15B4 >= (D_800C15B0[1] - 1))
    {
        D_800C15B0++;
    }

    return D_800C15B4;
}

void func_80044FE0(s_Skeleton* skel, s_Bone* bones, u8 boneCount) // 0x80044FE0
{
    skel->bones_8 = bones;
    skel->boneCount_0 = boneCount;
    skel->boneIdx_1 = 0;
    skel->field_2 = 1;
    skel->field_4 = 0;

    func_80045014(skel);
}

void func_80045014(s_Skeleton* skel) // 0x80045014
{
    s_Bone* bone;

    // Traverse bone hierarchy and clear flags.
    for (bone = &skel->bones_8[0]; bone < &skel->bones_8[skel->boneCount_0]; bone++)
    {
        bone->flags_0 = 0;
    }
}

void func_8004506C(s_Skeleton* skel, s_PlmHeader* plmHeader) // 0x8004506C
{
    u8  sp10[3]; // Size unsure, this could be larger.
    s32 switchVar;

    switchVar = PlmHeader_ObjectCountGet(plmHeader);
    sp10[0]   = 0;

    switch (switchVar)
    {
        case 0:
            sp10[0] = 0xFE;
            break;

        case 1:
            sp10[0] = 0;
            sp10[1] = 254;
            break;

        default:
            sp10[1] = 253;
            sp10[2] = PlmHeader_ObjectCountGet(plmHeader) - 1;
            sp10[3] = 254;
            break;
    }

    func_80045108(skel, plmHeader, sp10, 0);
}

// Anim func.
void func_80045108(s_Skeleton* skel, s_PlmHeader* plmHeader, u8* arg2, s32 arg3) // 0x80045108
{
    s_Skeleton*  skel0; // Guessed the type. They both access `field_14` so maybe it's also `s_Skeleton`.
    s_Skeleton** skel1;
    s32          boneIdx;

    if (arg3 == 0)
    {
        skel->boneIdx_1 = 0;
        skel->field_4   = 0;
    }

    boneIdx = skel->boneIdx_1;
    func_800451B0(skel, plmHeader, arg2);

    skel1 = &skel->field_4;
    while (*skel1 != 0)
    {
        skel0 = *skel1;
        skel1 = &skel0->skeleton_14;
    }

    func_80045258(skel1, &skel->bones_8[boneIdx], skel->boneIdx_1 - boneIdx, plmHeader); // Very wierd third argument.
    func_800453E8(skel, false);
}

void func_800451B0(s_Skeleton* skel, s_PlmHeader* plmHeader, s32* arg2) // 0x800451B0
{
    s32 var;
    
    var = func_80044F6C(arg2, true);

    while (var != -2)
    {
        func_80056C8C(&skel->bones_8[skel->boneIdx_1], plmHeader, var);

        skel->boneIdx_1++;
        var = func_80044F6C(arg2, false);
    }
}

// Anim func.
INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80045258); // 0x80045258

// Anim func.
INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_800452EC); // 0x800452EC

// Anim func. Traverses skeleton bones for something.
INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80045360); // 0x80045360

// `cond` may actually be another `s_Skeleton` pointer.
void func_800453E8(s_Skeleton* skel, bool cond) // 0x800453E8
{
    s_Bone* bone;

    // Traverse bone hierarchy and set flags according to cond.
    for (bone = &skel->bones_8[0]; bone < &skel->bones_8[skel->boneCount_0]; bone++)
    {
        if (cond)
        {
            bone->flags_0 &= ~(1 << 31);
        }
        else
        {
            bone->flags_0 |= 1 << 31;
        }
    }
}

void func_80045468(s_Skeleton* skel, s32* arg1, bool cond) // 0x80045468
{
    s_Bone* bone;
    s32     status;

    bone = skel->bones_8;

    // Get skeleton status?
    status = func_80044F6C(arg1, true);
    if (status == -2)
    {
        return;
    }

    // Traverse bone hierarchy and set flags according to some condition.
    do
    {
        if (cond)
        {
            bone[status].flags_0 &= ~(1 << 31);
        }
        else
        {
            bone[status].flags_0 |= 1 << 31;
        }
        
        status = func_80044F6C(arg1, false);
    }
    while (status != -2);
}

// Maybe larger anim func.
INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80040A64", func_80045534); // 0x80045534
