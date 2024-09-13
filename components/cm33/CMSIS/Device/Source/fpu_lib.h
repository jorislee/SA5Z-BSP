#ifndef __FPU_LIB_H__
#define __FPU_LIB_H__

#include "ARMv8MML_SP.h"                /* ARM v8 Main Line processor and core peripherals       */
#include <stdio.h>

#define FP_FZ 0 //Flush-to-zero
#define FP_DN 1 //Default-NaN
#define FP_FC 2 //full-compliance IEEE754

#define RN 0 //Round to Nearest, default
#define RP 1 //round to plus infinity
#define RM 2 //round to minus infinity
#define RZ 3 //round to zero
//function number:27
void FMLA_3(float f0, float f1, float * dst); //float multiply accumalate
float FMLA_2(float f0, float f1); //float multiply accumalate
float FSQRT(float f1); //floating point square root
void clr_fpdzc(void);  //clear fpdzc
void read_fpscr(void); //with display
uint32_t get_fpscr(void);
void disable_fpu_excption(void); //disable all the excptions of FPU
void FPU_set_mode(char mode);
void FPU_set_round_mode(uint32_t round_mode);
uint32_t FCMP(float f0, float f1);
float FADD(float f0, float f1);
float FSUB(float f0, float f1);
float FMUL(float f0, float f1);
float FDIV(float f0, float f1);
float FABS(float fin);
void hexVflt_disp(float flt);
uint32_t hexVflt(float flt);
float hex2flt(uint32_t hexV);
float uint2float(uint32_t uint_num);
float int2float(int32_t int_num);
uint32_t float2uint(float flt_num);
int32_t float2int(float flt_num);
uint32_t check_FPUFC(void);
uint32_t check_FPIXC(void);
uint32_t check_FPOFC(void);
uint32_t check_FPDZC(void);
uint32_t check_FPIDC(void);
uint32_t check_FPIOC(void);
#endif
