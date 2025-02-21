/*
 * $PSLibId: Run-time Library Release 4.3$
 */

#ifndef _LIBMATH_H_
#define _LIBMATH_H_

/* 
  libmath.h
*/
#define _ABS(x)		((x) < 0 ? -(x) : (x))
#define fabs(x)		_ABS(x)

extern int math_errno;
extern int math_err_point;


#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern "C" {
#endif

double pow(double, double),exp(double);
double log(double), log10(double);
double floor(double), ceil(double);
double fmod(double,double),modf(double,double *);
double sin(double), cos(double), tan(double);
double asin(double), acos(double);
double atan(double), atan2(double, double);
double sinh(double), cosh(double), tanh(double);
double sqrt(double);
double hypot(double, double);
double ldexp(double, int), frexp(double, int *);

double atof(char *);
double strtod(char *, char **);
int printf2(char *, ...);
int sprintf2(char *, char *, ...);

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif

#endif /* _LIBMATH_H_ */

