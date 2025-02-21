/*
 * $PSLibId: Run-time Library Release 4.3$ 
 */

#ifndef _LIBGTE_H_
#define _LIBGTE_H_

/*
 *  (C) Copyright 1993/1994/1995 Sony Computer Entertainment ,Tokyo,Japan.
 *				All Rights Reserved
 *
 * 		libgte.h: Geometry Basic Structures Database
 *
 *$Id: libgte.h,v 1.35 1998/03/10 03:52:35 noda Exp $
 */



/*
 * Geometry Structures:
 */
#define	ONE		4096	/* GTE regards 4096 as 1.0 */
#define TMPVTXNUM	16	/* Clip Function Header */
#define OUTVTXNUM	10

#ifdef ASSEMBLER
/*
* GTE read macros
*/
#define	read_sz_fifo3(r1,r2,r3)		mfc2	r1,$17; \
					mfc2	r2,$18; \
					mfc2	r3,$19; \
					nop

#define	read_sz_fifo4(r1,r2,r3,r4) 	mfc2	r1,$16; \
					mfc2	r2,$17; \
					mfc2	r3,$18; \
					mfc2	r4,$19;	\
					nop

#define	read_szx(r1) 			mfc2	r1,$16;	\
					nop
			
#define	read_sz0(r1)			mfc2	r1,$17;	\
					nop
			
#define	read_sz1(r1)			mfc2	r1,$18;	\
					nop
			
#define	read_sz2(r1)			mfc2	r1,$19;	\
					nop
			
#define	read_sxsy_fifo3(r1,r2,r3) 	mfc2	r1,$12; \
					mfc2	r2,$13; \
					mfc2	r3,$14;	\
					nop

#define	read_sxsy0(r1)			mfc2	r1,$12;	\
					nop

#define	read_sxsy1(r1)			mfc2	r1,$13;	\
					nop

#define	read_sxsy2(r1)			mfc2	r1,$14;	\
					nop

#define	read_rgb_fifo(r1,r2,r3)		mfc2	r1,$20; \
					mfc2	r2,$21; \
					mfc2	r3,$22;	\
					nop

#define	read_rgb0(r1)			mfc2	r1,$20; \
					nop

#define	read_rgb1(r1)			mfc2	r1,$21; \
					nop

#define	read_rgb2(r1)			mfc2	r1,$22; \
					nop

#define	read_flag(r1)			cfc2	r1,$31;	\
					nop

#define	read_p(r1)			mfc2	r1,$8;	\
					nop

#define	read_otz(r1)			mfc2	r1,$7;	\
					nop

#define	read_opz(r1)			mfc2	r1,$24;	\
					nop

#define read_mt(r1,r2,r3)		mfc2	r1,$25; \
					mfc2	r2,$26; \
					mfc2	r3,$27; \
					nop
/*
* GTE store macros
*/
#define store_sxsy_fifo3(r1,r2,r3)	swc2	$12,(r1); \
					swc2	$13,(r2); \
					swc2	$14,(r3); \
					nop

#define store_sxsy0(r1)			swc2	$12,(r1); \
					nop

#define store_sxsy1(r1)			swc2	$13,(r1); \
					nop

#define store_sxsy2(r1)			swc2	$14,(r1); \
					nop

#define	store_rgb_fifo(r1,r2,r3)	swc2	$20,(r1); \
					swc2	$21,(r2); \
					swc2	$22,(r3); \
					nop

#define store_rgb0(r1)			swc2	$20,(r1); \
					nop

#define store_rgb1(r1)			swc2	$21,(r1); \
					nop

#define store_rgb2(r1)			swc2	$22,(r1); \
					nop

/*
* GTE set macros
*/
#define set_trans_matrix(r1,r2,r3)	ctc2	r1,$5;	\
					ctc2	r2,$6;	\
					ctc2	r3,$7;	\
					nop
#endif

#ifndef ASSEMBLER
typedef struct  {
	short	m[3][3];	/* 3x3 rotation matrix */
        long    t[3];		/* transfer vector */
} MATRIX;

typedef struct {		/* long word type 3D vector */
	long	vx, vy;
	long	vz, pad;
} VECTOR;
	
typedef struct {		/* short word type 3D vector */	
	short	vx, vy;
	short	vz, pad;
} SVECTOR;
	       
typedef struct {		/* color type vector */	
	u_char	r, g, b, cd;
} CVECTOR;
	       
typedef struct {		/* 2D short vector */
	short vx, vy;
} DVECTOR;


typedef struct {		
	SVECTOR v;		/* Object(Local) 3D Vertex 	*/
	VECTOR sxyz;		/* Screen 3D Vertex		*/
	DVECTOR sxy;		/* Screen 2D Vertex		*/
	CVECTOR rgb;		/* Vertex Color Data	 	*/
	short txuv,pad;		/* Texture Mapping Data 	*/
	long chx,chy;		/* Clip Window Data 		*/
} EVECTOR;

typedef struct {
	SVECTOR v;
	u_char uv[2]; u_short pad;	/*  */  
	CVECTOR c;
	DVECTOR sxy;		
	u_long  sz;		/* clip z-data */		
} RVECTOR;			/* division vertex data vector */


typedef struct {
	RVECTOR r01,r12,r20;
	RVECTOR	*r0,*r1,*r2;
	u_long *rtn;
} CRVECTOR3;			/* recursive vector for triangles */

typedef struct {
	u_long 	ndiv;		/* number of divisions */
	u_long 	pih,piv;	/* clipping area */
	u_short clut,tpage;
	CVECTOR	rgbc;
	u_long	*ot;
	RVECTOR r0,r1,r2;
	CRVECTOR3 cr[5];	
} DIVPOLYGON3;			/* division buffer for triangles */

typedef struct {
	RVECTOR r01,r02,r31,r32,rc;
	RVECTOR	*r0,*r1,*r2,*r3;
	u_long *rtn;
} CRVECTOR4;			/* recursive vector for four-sided polygons */

typedef struct {
	u_long 	ndiv;		/* number of divisions */
	u_long 	pih,piv;	/* clipping area */
	u_short clut,tpage;
	CVECTOR	rgbc;
	u_long	*ot;
	RVECTOR r0,r1,r2,r3;
	CRVECTOR4 cr[5];	
} DIVPOLYGON4;			/* division buffer for four-sided polygons */

typedef struct {
        short   xy[3];
        short   uv[2];
        short   rgb[3];
} SPOL;

                                        /*polygon: 41 bytes/1 polygon*/
typedef struct {
        short   sxy[4][2];              /*0..7*/
        short   sz[4][2];               /*8..15sz[][1] is dummy*/
        short   uv[4][2];               /*16..23*/
        short   rgb[4][3];              /*23..34*/
        short   code;                   /*35...  F4:5,TF4:6,G4:7,TG4:8*/
} POL4;

typedef struct {
        short   sxy[3][2];
        short   sz[3][2];               /*sz[][1] is dummy*/
        short   uv[3][2];
        short   rgb[3][3];
        short   code;                   /*F3:1,TF3:2,G3:3,TG3:4*/
} POL3;

typedef struct {
        SVECTOR         *v;                     /*shared vertices*/
        SVECTOR         *n;                     /*shared normals*/
        SVECTOR         *u;                     /*shared texture addresses*/
        CVECTOR         *c;                     /*shared colors*/
        u_long          len;                    /*mesh length(=#vertex)*/
} TMESH;

typedef struct {
        SVECTOR         *v;                     /*shared vertices*/
        SVECTOR         *n;                     /*shared normals*/
        SVECTOR         *u;                     /*shared texture addresses*/
        CVECTOR         *c;                     /*shared colors*/
        u_long          lenv;                   /*mesh length_V(=#vertex_V)*/
        u_long          lenh;                   /*mesh length_H(=#vertex_H)*/
} QMESH;


/*
 *      ProtoTypes
 */
#ifndef NO_PROTOTYPE

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern "C" {
#endif

extern void InitGeom();

extern void EigenMatrix(MATRIX *m, MATRIX *t);
extern int  IsIdMatrix(MATRIX *m);
extern MATRIX *MulMatrix0(MATRIX *m0,MATRIX *m1,MATRIX *m2);
extern MATRIX *MulRotMatrix0(MATRIX *m0,MATRIX *m1);
extern MATRIX *MulMatrix(MATRIX *m0,MATRIX *m1);
extern MATRIX *MulMatrix2(MATRIX *m0,MATRIX *m1);
extern MATRIX *MulRotMatrix(MATRIX *m0);
extern MATRIX *SetMulMatrix(MATRIX *m0,MATRIX *m1);
extern MATRIX *SetMulRotMatrix(MATRIX *m0);
extern VECTOR *ApplyMatrix(MATRIX *m,SVECTOR *v0,VECTOR *v1);
extern VECTOR *ApplyRotMatrix(SVECTOR *v0,VECTOR *v1);
extern VECTOR *ApplyRotMatrixLV(VECTOR *v0,VECTOR *v1);
extern VECTOR *ApplyMatrixLV(MATRIX *m,VECTOR *v0,VECTOR *v1);
extern SVECTOR *ApplyMatrixSV(MATRIX *m,SVECTOR *v0,SVECTOR *v1);
extern VECTOR *ApplyTransposeMatrixLV(MATRIX *m,VECTOR *v0,VECTOR *v1);
extern MATRIX *RotMatrix(SVECTOR *r,MATRIX *m);
extern MATRIX *RotMatrixXZY(SVECTOR *r,MATRIX *m);
extern MATRIX *RotMatrixYXZ(SVECTOR *r,MATRIX *m);
extern MATRIX *RotMatrixYZX(SVECTOR *r,MATRIX *m);
extern MATRIX *RotMatrixZXY(SVECTOR *r,MATRIX *m);
extern MATRIX *RotMatrixZYX(SVECTOR *r,MATRIX *m);
extern MATRIX *RotMatrix_gte(SVECTOR *r,MATRIX *m);
extern MATRIX *RotMatrixYXZ_gte(SVECTOR *r,MATRIX *m);
extern MATRIX *RotMatrixZYX_gte(SVECTOR *r,MATRIX *m);
extern MATRIX *RotMatrixX(long r,MATRIX *m);
extern MATRIX *RotMatrixY(long r,MATRIX *m);
extern MATRIX *RotMatrixZ(long r,MATRIX *m);
extern MATRIX *RotMatrixC(SVECTOR *r,MATRIX *m);
extern MATRIX *TransMatrix(MATRIX *m,VECTOR *v);
extern MATRIX *ScaleMatrix(MATRIX *m,VECTOR *v);
extern MATRIX *ScaleMatrixL(MATRIX *m,VECTOR *v);
extern MATRIX *TransposeMatrix(MATRIX *m0,MATRIX *m1);
extern MATRIX *CompMatrix(MATRIX *m0,MATRIX *m1,MATRIX *m2);
extern MATRIX *CompMatrixLV(MATRIX *m0,MATRIX *m1,MATRIX *m2);

extern void MatrixNormal(MATRIX *m, MATRIX *n); 
extern void MatrixNormal_0(MATRIX *m, MATRIX *n);
extern void MatrixNormal_1(MATRIX *m, MATRIX *n);
extern void MatrixNormal_2(MATRIX *m, MATRIX *n);

extern void SetRotMatrix(MATRIX *m); 
extern void SetLightMatrix(MATRIX *m);
extern void SetColorMatrix(MATRIX *m);
extern void SetTransMatrix(MATRIX *m);
extern void PushMatrix();
extern void PopMatrix();
extern void ReadRotMatrix(MATRIX *m);
extern void ReadLightMatrix(MATRIX *m);
extern void ReadColorMatrix(MATRIX *m);
extern void SetRGBcd(CVECTOR *v);
extern void SetBackColor(long rbk,long gbk,long bbk);
extern void SetFarColor(long rfc,long gfc,long bfc);
extern void SetGeomOffset(long ofx,long ofy);
extern void SetGeomScreen(long h);
extern void ReadSZfifo3(long *sz0,long *sz1,long *sz2);
extern void ReadSZfifo4(long *szx,long *sz0,long *sz1,long *sz2);
extern void ReadSXSYfifo(long *sxy0,long *sxy1,long *sxy2);
extern void ReadRGBfifo(CVECTOR *v0,CVECTOR *v1,CVECTOR *v2);
extern void ReadGeomOffset(long *ofx,long *ofy);
extern long ReadGeomScreen();

extern void TransRot_32(VECTOR *v0, VECTOR *v1, long *flag);
extern long TransRotPers(SVECTOR *v0, long *sxy, long *p, long *flag);
extern long TransRotPers3(SVECTOR *v0, SVECTOR *v1, SVECTOR *v2, long *sxy0, 
		long *sxy1, long *sxy2, long *p, long *flag);

extern void pers_map(int abuf, SVECTOR **vertex, int tex[4][2], u_short *dtext);
extern void PhongLine(int istart_x, int iend_x, int p, int q, u_short **pixx,
		int fs, int ft, int i4, int det);

extern long RotTransPers(SVECTOR *v0,long *sxy,long *p,long *flag);
extern long RotTransPers3(SVECTOR *v0,SVECTOR *v1,SVECTOR *v2,
			long *sxy0,long *sxy1,long *sxy2,long *p,long *flag);
extern void RotTrans(SVECTOR *v0,VECTOR *v1,long *flag);
extern void RotTransSV(SVECTOR *v0,SVECTOR *v1,long *flag);
extern void LocalLight(SVECTOR *v0,VECTOR *v1);
extern void LightColor(VECTOR *v0,VECTOR *v1);
extern void DpqColorLight(VECTOR *v0,CVECTOR *v1,long p,CVECTOR *v2);
extern void DpqColor(CVECTOR *v0,long p,CVECTOR *v1);
extern void DpqColor3(CVECTOR *v0,CVECTOR *v1,CVECTOR *v2,
			long p,CVECTOR *v3,CVECTOR *v4,CVECTOR *v5);
extern void Intpl(VECTOR *v0,long p,CVECTOR *v1);
extern VECTOR *Square12(VECTOR *v0,VECTOR *v1);
extern VECTOR *Square0(VECTOR *v0,VECTOR *v1);
extern VECTOR *SquareSL12(SVECTOR *v0,VECTOR *v1);
extern VECTOR *SquareSL0(SVECTOR *v0,VECTOR *v1);
extern SVECTOR *SquareSS12(SVECTOR *v0,SVECTOR *v1);
extern SVECTOR *SquareSS0(SVECTOR *v0,SVECTOR *v1);
extern void NormalColor(SVECTOR *v0,CVECTOR *v1);
extern void NormalColor3(SVECTOR *v0,SVECTOR *v1,SVECTOR *v2,
			CVECTOR *v3,CVECTOR *v4,CVECTOR *v5);
extern void NormalColorDpq(SVECTOR *v0,CVECTOR *v1,long p,CVECTOR *v2);
extern void NormalColorDpq3(SVECTOR *v0,SVECTOR *v1,SVECTOR *v2,CVECTOR *v3,
			long p,CVECTOR *v4,CVECTOR *v5,CVECTOR *v6);
extern void NormalColorCol(SVECTOR *v0,CVECTOR *v1,CVECTOR *v2);
extern void NormalColorCol3(SVECTOR *v0,SVECTOR *v1,SVECTOR *v2,CVECTOR *v3,
			CVECTOR *v4,CVECTOR *v5,CVECTOR *v6);
extern void ColorDpq(VECTOR *v0,CVECTOR *v1,long p,CVECTOR *v2);
extern void ColorCol(VECTOR *v0,CVECTOR *v1,CVECTOR *v2);
extern long NormalClip(long sxy0,long sxy1,long sxy2);
extern long AverageZ3(long sz0,long sz1,long sz2);
extern long AverageZ4(long sz0,long sz1,long sz2,long sz3);
extern void OuterProduct12(VECTOR *v0,VECTOR *v1,VECTOR *v2);
extern void OuterProduct0(VECTOR *v0,VECTOR *v1,VECTOR *v2);
extern long Lzc(long data);


extern long RotTransPers4(SVECTOR *v0,SVECTOR *v1,SVECTOR *v2,SVECTOR *v3,
			long *sxy0,long *sxy1,long *sxy2,long *sxy3,
			long *p,long *flag);
extern void RotTransPersN(SVECTOR *v0,DVECTOR *v1,u_short *sz,u_short *p,
			u_short *flag,long n);
extern void RotTransPers3N(SVECTOR *v0,DVECTOR *v1,u_short *sz,u_short *flag,
			long n);
extern void RotMeshH(short *Yheight,DVECTOR *Vo,u_short *sz,u_short *flag,
			short Xoffset,short Zoffset,short m,short n,
			DVECTOR *base);
extern long RotAverage3(SVECTOR *v0,SVECTOR *v1,SVECTOR *v2,
			long *sxy0,long *sxy1,long *sxy2,long *p,long *flag);
extern long RotAverage4(SVECTOR *v0,SVECTOR *v1,SVECTOR *v2,SVECTOR *v3,
			long *sxy0,long *sxy1,long *sxy2,long *sxy3,
			long *p,long *flag);
extern long RotNclip3(SVECTOR *v0,SVECTOR *v1,SVECTOR *v2,
			long *sxy0,long *sxy1,long *sxy2,long *p,long *otz,
			long *flag);
extern long RotNclip4(SVECTOR *v0,SVECTOR *v1,SVECTOR *v2,SVECTOR *v3,
			long *sxy0,long *sxy1,long *sxy2,long *sxy3,
			long *p,long *otz,long *flag);
extern long RotAverageNclip3(SVECTOR *v0,SVECTOR *v1,SVECTOR *v2,
			long *sxy0,long *sxy1,long *sxy2,
			long *p,long *otz,long *flag);
extern long RotAverageNclip4(SVECTOR *v0,SVECTOR *v1,SVECTOR *v2,SVECTOR *v3,
			long *sxy0,long *sxy1,long *sxy2,long *sxy3,
			long *p,long *otz,long *flag);
extern long RotColorDpq(SVECTOR *v0,SVECTOR *v1,CVECTOR *v2,
			long *sxy,CVECTOR *v3,long *flag);
extern long RotColorDpq3(SVECTOR *v0,SVECTOR *v1,SVECTOR *v2,
			SVECTOR *v3,SVECTOR *v4,SVECTOR *v5,CVECTOR *v6,
			long *sxy0,long *sxy1,long *sxy2,
			CVECTOR *v7,CVECTOR *v8,CVECTOR *v9,long *flag);
extern long RotAverageNclipColorDpq3(SVECTOR *v0,SVECTOR *v1,SVECTOR *v2,
			SVECTOR *v3,SVECTOR *v4,SVECTOR *v5,CVECTOR *v6,
			long *sxy0,long *sxy1,long *sxy2,
			CVECTOR *v7,CVECTOR *v8,CVECTOR *v9,
			long *otz,long *flag);	 		   	      
extern long RotAverageNclipColorCol3(SVECTOR *v0,SVECTOR *v1,SVECTOR *v2,
			SVECTOR *v3,SVECTOR *v4,SVECTOR *v5,CVECTOR *v6,
			long *sxy0,long *sxy1,long *sxy2,
			CVECTOR *v7,CVECTOR *v8,CVECTOR *v9,
			long *otz,long *flag);	 		   	      
extern long RotColorMatDpq(SVECTOR *v0,SVECTOR *v1,CVECTOR *v2,long *sxy,
			CVECTOR *v3,long matc,long flag);
extern void ColorMatDpq(SVECTOR *v0,CVECTOR *v1,long p,CVECTOR *v2,long matc);
extern void ColorMatCol(SVECTOR *v0,CVECTOR *v1,CVECTOR *v2,long matc);
extern void LoadAverage12(VECTOR *v0,VECTOR *v1,long p0,long p1,VECTOR *v2);
extern void LoadAverageShort12(SVECTOR *v0,SVECTOR *v1,long p0,long p1,
			SVECTOR *v2);
extern void LoadAverage0(VECTOR *v0,VECTOR *v1,long p0,long p1,VECTOR *v2);
extern void LoadAverageShort0(SVECTOR *v0,SVECTOR *v1,long p0,long p1,
			SVECTOR *v2);
extern void LoadAverageByte(u_char *v0,u_char *v1,long p0,long p1,u_char *v2);
extern void LoadAverageCol(u_char *v0,u_char *v1,long p0,long p1,u_char *v2);
extern long VectorNormal(VECTOR *v0, VECTOR *v1);
extern long VectorNormalS(VECTOR *v0, SVECTOR *v1);
extern long VectorNormalSS(SVECTOR *v0, SVECTOR *v1);
extern long SquareRoot0(long a);
extern long SquareRoot12(long a);
extern void InvSquareRoot(long a, long *b, long *c);
extern void gteMIMefunc(SVECTOR *otp, SVECTOR *dfp, long n, long p);
extern void SetFogFar(long a,long h);
extern void SetFogNear(long a,long h);
extern void SetFogNearFar(long a,long b,long h);
extern void SubPol4(POL4 *p, SPOL *sp, int ndiv);
extern void SubPol3(POL3 *p, SPOL *sp, int ndiv);

extern int rcos(int a);
extern int rsin(int a);
extern int ccos(int a);
extern int csin(int a);
extern int cln(int a);
extern int csqrt(int a);
extern int catan(int a);
extern long ratan2(long y, long x);


extern void RotPMD_F3(long *pa,u_long *ot,int otlen,int id,int backc);
extern void RotPMD_G3(long *pa,u_long *ot,int otlen,int id,int backc);
extern void RotPMD_FT3(long *pa,u_long *ot,int otlen,int id,int backc);
extern void RotPMD_GT3(long *pa,u_long *ot,int otlen,int id,int backc);
extern void RotPMD_F4(long *pa,u_long *ot,int otlen,int id,int backc);
extern void RotPMD_G4(long *pa,u_long *ot,int otlen,int id,int backc);
extern void RotPMD_FT4(long *pa,u_long *ot,int otlen,int id,int backc);
extern void RotPMD_GT4(long *pa,u_long *ot,int otlen,int id,int backc);

extern void RotPMD_SV_F3(long *pa,long *va,u_long *ot,int otlen,int id,
			int backc);
extern void RotPMD_SV_G3(long *pa,long *va,u_long *ot,int otlen,int id,
			int backc);
extern void RotPMD_SV_FT3(long *pa,long *va,u_long *ot,int otlen,int id,
			int backc);
extern void RotPMD_SV_GT3(long *pa,long *va,u_long *ot,int otlen,int id,
			int backc);
extern void RotPMD_SV_F4(long *pa,long *va,u_long *ot,int otlen,int id,
			int backc);
extern void RotPMD_SV_G4(long *pa,long *va,u_long *ot,int otlen,int id,
			int backc);
extern void RotPMD_SV_FT4(long *pa,long *va,u_long *ot,int otlen,int id,
			int backc);
extern void RotPMD_SV_GT4(long *pa,long *va,u_long *ot,int otlen,int id,
			int backc);


extern void InitClip(EVECTOR *evbfad,long hw,long vw,long h,long near,long far);
extern long Clip3F(SVECTOR *v0,SVECTOR *v1,SVECTOR *v2,EVECTOR **evmx);
extern long Clip3FP(SVECTOR *v0,SVECTOR *v1,SVECTOR *v2,EVECTOR **evmx);
extern long Clip4F(SVECTOR *v0,SVECTOR *v1,SVECTOR *v2,SVECTOR *v3,
			EVECTOR **evmx);
extern long Clip4FP(SVECTOR *v0,SVECTOR *v1,SVECTOR *v2,SVECTOR *v3,
			EVECTOR **evmx);
extern long Clip3FT(SVECTOR *v0,SVECTOR *v1,SVECTOR *v2,
		short *uv0,short *uv1,short *uv2,EVECTOR **evmx);
extern long Clip3FTP(SVECTOR *v0,SVECTOR *v1,SVECTOR *v2,
		short *uv0,short *uv1,short *uv2,EVECTOR **evmx);
extern long Clip4FT(SVECTOR *v0,SVECTOR *v1,SVECTOR *v2,SVECTOR *v3,
		short *uv0,short *uv1,short *uv2,short *uv3,EVECTOR **evmx);
extern long Clip4FTP(SVECTOR *v0,SVECTOR *v1,SVECTOR *v2,SVECTOR *v3,
		short *uv0,short *uv1,short *uv2,short *uv3,EVECTOR **evmx);
extern long Clip3G(SVECTOR *v0,SVECTOR *v1,SVECTOR *v2,
		CVECTOR *rgb0,CVECTOR *rgb1,CVECTOR *rgb2,EVECTOR **evmx);
extern long Clip3GP(SVECTOR *v0,SVECTOR *v1,SVECTOR *v2,
		CVECTOR *rgb0,CVECTOR *rgb1,CVECTOR *rgb2,EVECTOR **evmx);
extern long Clip4G(SVECTOR *v0,SVECTOR *v1,SVECTOR *v2,SVECTOR *v3,
		CVECTOR *rgb0,CVECTOR *rgb1,CVECTOR *rgb2,CVECTOR *rgb3,
		EVECTOR **evmx);
extern long Clip4GP(SVECTOR *v0,SVECTOR *v1,SVECTOR *v2,SVECTOR *v3,
		CVECTOR *rgb0,CVECTOR *rgb1,CVECTOR *rgb2,CVECTOR *rgb3,
		EVECTOR **evmx);
extern long Clip3GT(SVECTOR *v0,SVECTOR *v1,SVECTOR *v2,
		short *uv0,short *uv1,short *uv2,
		CVECTOR *rgb0,CVECTOR *rgb1,CVECTOR *rgb2,
		EVECTOR **evmx);
extern long Clip3GTP(SVECTOR *v0,SVECTOR *v1,SVECTOR *v2,
		short *uv0,short *uv1,short *uv2,
		CVECTOR *rgb0,CVECTOR *rgb1,CVECTOR *rgb2,
		EVECTOR **evmx);
extern long Clip4GT(SVECTOR *v0,SVECTOR *v1,SVECTOR *v2,SVECTOR *v3,
		short *uv0,short *uv1,short *uv2,short *uv3,
		CVECTOR *rgb0,CVECTOR *rgb1,CVECTOR *rgb2,CVECTOR *rgb3,
		EVECTOR **evmx);
extern long Clip4GTP(SVECTOR *v0,SVECTOR *v1,SVECTOR *v2,SVECTOR *v3,
		short *uv0,short *uv1,short *uv2,short *uv3,
		CVECTOR *rgb0,CVECTOR *rgb1,CVECTOR *rgb2,CVECTOR *rgb3,
		EVECTOR **evmx);

extern void RotTransPers_nom(SVECTOR *v0);
extern void RotTransPers3_nom(SVECTOR *v0,SVECTOR *v1,SVECTOR *v2);
extern void RotTransPers4_nom(SVECTOR *v0,SVECTOR *v1,SVECTOR *v2,SVECTOR *v3);
extern void RotTrans_nom(SVECTOR *v0);
extern void RotAverage3_nom(SVECTOR *v0,SVECTOR *v1,SVECTOR *v2);
extern void RotNclip3_nom(SVECTOR *v0,SVECTOR *v1,SVECTOR *v2);
extern void RotAverageNclip3_nom(SVECTOR *v0,SVECTOR *v1,SVECTOR *v2);
extern void RotAverageNclipColorDpq3_nom(SVECTOR *v0,SVECTOR *v1,SVECTOR *v2,
			SVECTOR *v3,SVECTOR *v4,SVECTOR *v5,CVECTOR *v6);
extern void RotAverageNclipColorCol3_nom(SVECTOR *v0,SVECTOR *v1,SVECTOR *v2,
			SVECTOR *v3,SVECTOR *v4,SVECTOR *v5,CVECTOR *v6);
extern void RotColorDpq_nom(SVECTOR *v0,SVECTOR *v1,CVECTOR *v2);
extern long RotColorDpq3_nom(SVECTOR *v0,SVECTOR *v1,SVECTOR *v2,
			SVECTOR *v3,SVECTOR *v4,SVECTOR *v5,CVECTOR *v6);
extern void NormalColor_nom(SVECTOR *v0);
extern void NormalColor3_nom(SVECTOR *v0,SVECTOR *v1,SVECTOR *v2);
extern void NormalColorDpq_nom(SVECTOR *v0,CVECTOR *v1,long p);
extern void NormalColorDpq3_nom(SVECTOR *v0,SVECTOR *v1,SVECTOR *v2,
			CVECTOR *v3,long p);
extern void NormalColorCol_nom(SVECTOR *v0,CVECTOR *v1);
extern void NormalColorCol3_nom(SVECTOR *v0,SVECTOR *v1,SVECTOR *v2,
			CVECTOR *v3);

/*

extern u_long *DivideF3(SVECTOR *v0,SVECTOR *v1,SVECTOR *v2,CVECTOR *rgbc,
		POLY *otp);
extern u_long *GsPrng n,u_long shift,GsOT *otp);

extern u_long *GsTMDfastTG3LB(TMD_P_TG3 *primtop,SVECTOR *vertop,SVECTOR *nortop,
		POLY_GT3 *s,u_long n,u_long shift,GsOT *otp);
extern u_long *GsTMDfastTG3LFGB(TMD_P_TG3 *primtop,SVECTOR *vertop,
		SVECTOR *nortop,POLY_GT3 *s,u_long n,u_long shift,GsOT *otp);
extern u_long *GsTMDfastTG3NLB(TMD_P_TG3 *primtop,SVECTOR *vertop,
		SVECTOR *nortop,POLY_GT3 *s,u_long n,u_long shift,GsOT *otp);
extern u_long *GsTMDfastTNG3B(TMD_P_TNG3 *primtop,SVECTOR *vertop,
		POLY_GT3 *s,u_long n,u_long shift,GsOT *otp);

extern u_long *GsTMDfastTG4LB(TMD_P_TG4 *primtop,SVECTOR *vertop,SVECTOR *nortop,
		POLY_GT4 *s,u_long n,u_long shift,GsOT *otp);
extern u_long *GsTMDfastTG4LFGB(TMD_P_TG4 *primtop,SVECTOR *vertop,
		SVECTOR *nortop,POLY_GT4 *s,u_long n,u_long shift,GsOT *otp);
extern u_long *GsTMDfastTG4NLB(TMD_P_TG4 *primtop,SVECTOR *vertop,
		SVECTOR *nortop,POLY_GT4 *s,u_long n,u_long shift,GsOT *otp);
extern u_long *GsTMDfastTNG4B(TMD_P_TNG4 *primtop,SVECTOR *vertop,
		POLY_GT4 *s,u_long n,u_long shift,GsOT *otp);

extern u_long *GsTMDdivF3LB(TMD_P_F3 *primtop,SVECTOR *vertop,SVECTOR *nortop,
		POLY_F3 *s,u_long n,u_long shift,GsOT *otp,DIVPOLYGON3 *divp);
extern u_long *GsTMDdivF3LFGB(TMD_P_F3 *primtop,SVECTOR *vertop,SVECTOR *nortop,
		POLY_F3 *s,u_long n,u_long shift,GsOT *otp,DIVPOLYGON3 *divp);
extern u_long *GsTMDdivF3NLB(TMD_P_F3 *primtop,SVECTOR *vertop,SVECTOR *nortop,
		POLY_F3 *s,u_long n,u_long shift,GsOT *otp,DIVPOLYGON3 *divp);
extern u_long *GsTMDdivNF3B(TMD_P_NF3 *primtop,SVECTOR *vertop,
		POLY_F3 *s,u_long n,u_long shift,GsOT *otp,DIVPOLYGON3 *divp);

extern u_long *GsTMDdivF4LB(TMD_P_F4 *primtop,SVECTOR *vertop,SVECTOR *nortop,
		POLY_F4 *s,u_long n,u_long shift,GsOT *otp,DIVPOLYGON4 *divp);
extern u_long *GsTMDdivF4LFGB(TMD_P_F4 *primtop,SVECTOR *vertop,SVECTOR *nortop,
		POLY_F4 *s,u_long n,u_long shift,GsOT *otp,DIVPOLYGON4 *divp);
extern u_long *GsTMDdivF4NLB(TMD_P_F4 *primtop,SVECTOR *vertop,SVECTOR *nortop,
		POLY_F4 *s,u_long n,u_long shift,GsOT *otp,DIVPOLYGON4 *divp);
extern u_long *GsTMDdivNF4B(TMD_P_NF4 *primtop,SVECTOR *vertop,
		POLY_F4 *s,u_long n,u_long shift,GsOT *otp,DIVPOLYGON4 *divp);

extern u_long *GsTMDdivTF3LB(TMD_P_TF3 *primtop,SVECTOR *vertop,SVECTOR *nortop,
		POLY_FT3 *s,u_long n,u_long shift,GsOT *otp,DIVPOLYGON3 *divp);
extern u_long *GsTMDdivTF3LFGB(TMD_P_TF3 *primtop,SVECTOR *vertop,
		SVECTOR *nortop,POLY_FT3 *s,u_long n,u_long shift,
		GsOT *otp,DIVPOLYGON3 *divp);
extern u_long *GsTMDdivTF3NLB(TMD_P_TF3 *primtop,SVECTOR *vertop,SVECTOR *nortop,
		POLY_FT3 *s,u_long n,u_long shift,GsOT *otp,DIVPOLYGON3 *divp);
extern u_long *GsTMDdivTNF3B(TMD_P_TNF3 *primtop,SVECTOR *vertop,
		POLY_FT3 *s,u_long n,u_long shift,GsOT *otp,DIVPOLYGON3 *divp);

extern u_long *GsTMDdivTF4LB(TMD_P_TF4 *primtop,SVECTOR *vertop,SVECTOR *nortop,
		POLY_FT4 *s,u_long n,u_long shift,GsOT *otp,DIVPOLYGON4 *divp);
extern u_long *GsTMDdivTF4LFGB(TMD_P_TF4 *primtop,SVECTOR *vertop,
		SVECTOR *nortop,POLY_FT4 *s,u_long n,u_long shift,
		GsOT *otp,DIVPOLYGON4 *divp);
extern u_long *GsTMDdivTF4NLB(TMD_P_TF4 *primtop,SVECTOR *vertop,SVECTOR *nortop,
		POLY_FT4 *s,u_long n,u_long shift,GsOT *otp,DIVPOLYGON4 *divp);
extern u_long *GsTMDdivTNF4B(TMD_P_TNF4 *primtop,SVECTOR *vertop,
		POLY_FT4 *s,u_long n,u_long shift,GsOT *otp,DIVPOLYGON4 *divp);

extern u_long *GsTMDdivG3LB(TMD_P_G3 *primtop,SVECTOR *vertop,SVECTOR *nortop,
		POLY_G3 *s,u_long n,u_long shift,GsOT *otp,DIVPOLYGON3 *divp);
extern u_long *GsTMDdivG3LFGB(TMD_P_G3 *primtop,SVECTOR *vertop,SVECTOR *nortop,
		POLY_G3 *s,u_long n,u_long shift,GsOT *otp,DIVPOLYGON3 *divp);
extern u_long *GsTMDdivG3NLB(TMD_P_G3 *primtop,SVECTOR *vertop,SVECTOR *nortop,
		POLY_G3 *s,u_long n,u_long shift,GsOT *otp,DIVPOLYGON3 *divp);
extern u_long *GsTMDdivNG3B(TMD_P_NG3 *primtop,SVECTOR *vertop,
		POLY_G3 *s,u_long n,u_long shift,GsOT *otp,DIVPOLYGON3 *divp);

extern u_long *GsTMDdivG4LB(TMD_P_G4 *primtop,SVECTOR *vertop,SVECTOR *nortop,
		POLY_G4 *s,u_long n,u_long shift,GsOT *otp,DIVPOLYGON4 *divp);
extern u_long *GsTMDdivG4LFGB(TMD_P_G4 *primtop,SVECTOR *vertop,SVECTOR *nortop,
		POLY_G4 *s,u_long n,u_long shift,GsOT *otp,DIVPOLYGON4 *divp);
extern u_long *GsTMDdivG4NLB(TMD_P_G4 *primtop,SVECTOR *vertop,SVECTOR *nortop,
		POLY_G4 *s,u_long n,u_long shift,GsOT *otp,DIVPOLYGON4 *divp);
extern u_long *GsTMDdivNG4B(TMD_P_NG4 *primtop,SVECTOR *vertop,
		POLY_G4 *s,u_long n,u_long shift,GsOT *otp,DIVPOLYGON4 *divp);

extern u_long *GsTMDdivTG3LB(TMD_P_TG3 *primtop,SVECTOR *vertop,SVECTOR *nortop,
		POLY_GT3 *s,u_long n,u_long shift,GsOT *otp,DIVPOLYGON3 *divp);
extern u_long *GsTMDdivTG3LFGB(TMD_P_TG3 *primtop,SVECTOR *vertop,
		SVECTOR *nortop,POLY_GT3 *s,u_long n,u_long shift,
		GsOT *otp,DIVPOLYGON3 *divp);
extern u_long *GsTMDdivTG3NLB(TMD_P_TG3 *primtop,SVECTOR *vertop,SVECTOR *nortop,
		POLY_GT3 *s,u_long n,u_long shift,GsOT *otp,DIVPOLYGON3 *divp);
extern u_long *GsTMDdivTNG3B(TMD_P_TNG3 *primtop,SVECTOR *vertop,
		POLY_GT3 *s,u_long n,u_long shift,GsOT *otp,DIVPOLYGON3 *divp);

extern u_long *GsTMDdivTG4LB(TMD_P_TG4 *primtop,SVECTOR *vertop,SVECTOR *nortop,
		POLY_GT4 *s,u_long n,u_long shift,GsOT *otp,DIVPOLYGON4 *divp);
extern u_long *GsTMDdivTG4LFGB(TMD_P_TG4 *primtop,SVECTOR *vertop,
		SVECTOR *nortop,POLY_GT4 *s,u_long n,u_long shift,
		GsOT *otp,DIVPOLYGON4 *divp);
extern u_long *GsTMDdivTG4NLB(TMD_P_TG4 *primtop,SVECTOR *vertop,SVECTOR *nortop,
		POLY_GT4 *s,u_long n,u_long shift,GsOT *otp,DIVPOLYGON4 *divp);
extern u_long *GsTMDdivTNG4B(TMD_P_TNG4 *primtop,SVECTOR *vertop,
		POLY_GT4 *s,u_long n,u_long shift,GsOT *otp,DIVPOLYGON4 *divp);

*/

extern void RotSMD_F3(long *pa,u_long *ot,int otlen,int id,
			int sclip, int hclip, int vclip, int nclipmode);		
extern void RotSMD_G3(long *pa,u_long *ot,int otlen,int id,
			int sclip, int hclip, int vclip, int nclipmode);		
extern void RotSMD_FT3(long *pa,u_long *ot,int otlen,int id,
			int sclip, int hclip, int vclip, int nclipmode);		
extern void RotSMD_GT3(long *pa,u_long *ot,int otlen,int id,
			int sclip, int hclip, int vclip, int nclipmode);		
extern void RotSMD_F4(long *pa,u_long *ot,int otlen,int id,
			int sclip, int hclip, int vclip, int nclipmode);		
extern void RotSMD_G4(long *pa,u_long *ot,int otlen,int id,
			int sclip, int hclip, int vclip, int nclipmode);		
extern void RotSMD_FT4(long *pa,u_long *ot,int otlen,int id,
			int sclip, int hclip, int vclip, int nclipmode);		
extern void RotSMD_GT4(long *pa,u_long *ot,int otlen,int id,
			int sclip, int hclip, int vclip, int nclipmode);		

extern void RotSMD_SV_F3(long *pa,long *va,u_long *ot,int otlen,int id,
			int sclip, int hclip, int vclip, int nclipmode);		
extern void RotSMD_SV_G3(long *pa,long *va,u_long *ot,int otlen,int id,
			int sclip, int hclip, int vclip, int nclipmode);		
extern void RotSMD_SV_FT3(long *pa,long *va,u_long *ot,int otlen,int id,
			int sclip, int hclip, int vclip, int nclipmode);		
extern void RotSMD_SV_GT3(long *pa,long *va,u_long *ot,int otlen,int id,
			int sclip, int hclip, int vclip, int nclipmode);		
extern void RotSMD_SV_F4(long *pa,long *va,u_long *ot,int otlen,int id,
			int sclip, int hclip, int vclip, int nclipmode);		
extern void RotSMD_SV_G4(long *pa,long *va,u_long *ot,int otlen,int id,
			int sclip, int hclip, int vclip, int nclipmode);		
extern void RotSMD_SV_FT4(long *pa,long *va,u_long *ot,int otlen,int id,
			int sclip, int hclip, int vclip, int nclipmode);		
extern void RotSMD_SV_GT4(long *pa,long *va,u_long *ot,int otlen,int id,
			int sclip, int hclip, int vclip, int nclipmode);		



extern void RotRMD_F3(long *pa,u_long *ot,int otlen,int id,		
			int sclip, int hclip, int vclip, int nclipmode);		
extern void RotRMD_G3(long *pa,u_long *ot,int otlen,int id,
			int sclip, int hclip, int vclip, int nclipmode);		
extern void RotRMD_FT3(long *pa,u_long *ot,int otlen,int id,
			int sclip, int hclip, int vclip, int nclipmode);		
extern void RotRMD_GT3(long *pa,u_long *ot,int otlen,int id,
			int sclip, int hclip, int vclip, int nclipmode);		
extern void RotRMD_F4(long *pa,u_long *ot,int otlen,int id,
			int sclip, int hclip, int vclip, int nclipmode);		
extern void RotRMD_G4(long *pa,u_long *ot,int otlen,int id,
			int sclip, int hclip, int vclip, int nclipmode);		
extern void RotRMD_FT4(long *pa,u_long *ot,int otlen,int id,
			int sclip, int hclip, int vclip, int nclipmode);		
extern void RotRMD_GT4(long *pa,u_long *ot,int otlen,int id,
			int sclip, int hclip, int vclip, int nclipmode);		

extern void RotRMD_SV_F3(long *pa,long *va,u_long *ot,int otlen,int id,	
			int sclip, int hclip, int vclip, int nclipmode);		
extern void RotRMD_SV_G3(long *pa,long *va,u_long *ot,int otlen,int id,
			int sclip, int hclip, int vclip, int nclipmode);		
extern void RotRMD_SV_FT3(long *pa,long *va,u_long *ot,int otlen,int id,
			int sclip, int hclip, int vclip, int nclipmode);		
extern void RotRMD_SV_GT3(long *pa,long *va,u_long *ot,int otlen,int id,
			int sclip, int hclip, int vclip, int nclipmode);		
extern void RotRMD_SV_F4(long *pa,long *va,u_long *ot,int otlen,int id,
			int sclip, int hclip, int vclip, int nclipmode);		
extern void RotRMD_SV_G4(long *pa,long *va,u_long *ot,int otlen,int id,
			int sclip, int hclip, int vclip, int nclipmode);		
extern void RotRMD_SV_FT4(long *pa,long *va,u_long *ot,int otlen,int id,
			int sclip, int hclip, int vclip, int nclipmode);		
extern void RotRMD_SV_GT4(long *pa,long *va,u_long *ot,int otlen,int id,
			int sclip, int hclip, int vclip, int nclipmode);		

extern long p2otz(long p, long projection);
extern long otz2p(long otz, long projection);

/*
extern void RotMeshPrimS_F3(TMESH *msh,POLY_F3 *prim,u_long *ot,
			u_long otlen,long dpq,u_long backc);
extern void RotMeshPrimS_G3(TMESH *msh,POLY_G3 *prim,u_long *ot,
			u_long otlen,long dpq,u_long backc);
extern void RotMeshPrimS_FC3(TMESH *msh,POLY_F3 *prim,u_long *ot,
			u_long otlen,long dpq,u_long backc);
extern void RotMeshPrimS_GC3(TMESH *msh,POLY_G3 *prim,u_long *ot,
			u_long otlen,long dpq,u_long backc);
extern void RotMeshPrimS_FT3(TMESH *msh,POLY_FT3 *prim,u_long *ot,
			u_long otlen,long dpq,u_long backc);
extern void RotMeshPrimS_GT3(TMESH *msh,POLY_GT3 *prim,u_long *ot,
			u_long otlen,long dpq,u_long backc);
extern void RotMeshPrimS_FCT3(TMESH *msh,POLY_FT3 *prim,u_long *ot,
			u_long otlen,long dpq,u_long backc);
extern void RotMeshPrimS_GCT3(TMESH *msh,POLY_GT3 *prim,u_long *ot,
			u_long otlen,long dpq,u_long backc);
extern void RotMeshPrimS_T3(TMESH *msh,POLY_FT3 *prim,u_long *ot,
			u_long otlen,long dpq,u_long backc);

extern void RotMeshPrimR_F3(TMESH *msh,POLY_F3 *prim,u_long *ot,
			u_long otlen,long dpq,u _long backc);
extern void RotMeshPrimR_G3(TMESH *msh,POLY_G3 *prim,u_long *ot,
			u_long otlen,long dpq,u_long backc);
extern void RotMeshPrimR_FC3(TMESH *msh,POLY_F3 *prim,u_long *ot,
			u_long otlen,long dpq,u_long backc);
extern void RotMeshPrimR_GC3(TMESH *msh,POLY_G3 *prim,u_long *ot,
			u_long otlen,long dpq,u_long backc);
extern void RotMeshPrimR_FT3(TMESH *msh,POLY_FT3 *prim,u_long *ot,
			u_long otlen,long dpq,u_long backc);
extern void RotMeshPrimR_GT3(TMESH *msh,POLY_GT3 *prim,u_long *ot,
			u_long otlen,long dpq,u_long backc);
extern void RotMeshPrimR_FCT3(TMESH *msh,POLY_FT3 *prim,u_long *ot,
			u_long otlen,long dpq,u_long backc);
extern void RotMeshPrimR_GCT3(TMESH *msh,POLY_GT3 *prim,u_long *ot,
			u_long otlen,long dpq,u_long backc);
extern void RotMeshPrimR_T3(TMESH *msh,POLY_FT3 *prim,u_long *ot,
			u_long otlen,long dpq,u_long backc);

extern void RotMeshPrimQ_T(QMESH *msh,POLY_FT4 *prim,u_long *ot,
			u_long otlen,long dpq,long backc);                            
*/

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif

#endif
#endif

#endif /* _LIBGTE_H_ */
