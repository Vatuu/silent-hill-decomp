# These functions aren't added to undefined_funcs_auto for some reason, but other overlays still need to know the location of them
_spu_t                = 0x80012990;
_spu_Fw               = 0x80012C10;
_spu_FsetRXX          = 0x80012CF8;
_spu_FsetRXXa         = 0x80012D3C;
printf                = 0x80012F3C;
_SpuDataCallback      = 0x80012F4C;
ChangeClearPAD        = 0x8001331C;
ChangeClearRCnt       = 0x8001332C;
ResetCallback         = 0x8001335C;
DMACallback           = 0x800133BC;
GetVideoMode          = 0x80013E50;
CdReady               = 0x80014120;
CdReadyCallback       = 0x80014154;
CdDataCallback        = 0x80014584;
CdPosToInt            = 0x800146CC;
ResetGraph            = 0x800180FC;
SetDispMask           = 0x800183E0;
ClearOTagR            = 0x80018964;
PutDrawEnv            = 0x80018ADC;
PutDispEnv            = 0x80018CA8;
_spu_EVdma            = 0x80021354;
_spu_keystat          = 0x80021358;
_spu_trans_mode       = 0x8002135C;
_spu_rev_flag         = 0x80021360;
_spu_rev_reserve_wa   = 0x80021364;
_spu_rev_offsetaddr   = 0x80021368;
_spu_rev_attr         = 0x8002136C;
_spu_RQvoice          = 0x80021380;
_spu_RQmask           = 0x80021384;
_spu_voice_centerNote = 0x80021388;
_spu_env              = 0x800213B8;
_spu_isCalled         = 0x800213BC;
_spu_RXX              = 0x800213CC;
_spu_tsa              = 0x800213E4;
_spu_transMode        = 0x800213E8;
_spu_mem_mode_plus    = 0x800213F4;
_spu_inTransfer       = 0x80021400;
_spu_transferCallback = 0x80021404;
_spu_IRQCallback      = 0x80021408;
_spu_rev_startaddr    = 0x8002142C;
_spu_AllocBlockNum    = 0x8002145C;
_spu_AllocLastNum     = 0x80021460;
_spu_memList          = 0x80021464;
CD_debug              = 0x800226C0;
CD_nopen              = 0x800226CC;
DS_active             = 0x800226D8;
_spu_RQ               = 0x800231A0;
StMode                = 0x800231E8;
DsReadyCallback       = 0x801E34E0;
DsDataCallback        = 0x801E3508;

# @hack Fix for splat/spimdisasm not recognizing `MAP_INFOS` as referenced in certain maps, which only make use of later elements in the array.
MAP_INFOS    = 0x8002500C;

# @hack map1_s04 `func_800CCA2C` treats `D_800CD768` as both a `s32` and a `u16[]`
# Can only get code match if the `u16[]` is treated as a different symbol under the same address.
D_800CD768_tbl = 0x800CD768;

# @hack Referenced in some HARRY_MXSXX_ANIM_INFOS tables.
func_800706E4 = 0x800706E4;
