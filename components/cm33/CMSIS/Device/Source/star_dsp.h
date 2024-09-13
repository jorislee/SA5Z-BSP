//crate by sdfu 
//at 22.3.23
#ifndef STAR_DSP_H
#define STAR_DSP_H

#include <inttypes.h>
uint32_t asm_PKHBT(uint32_t in_1, uint32_t in_2);
uint32_t asm_PKHTB(uint32_t in_1, uint32_t in_2);
int32_t asm_QDADD(int32_t rn, int32_t rm);
int32_t asm_QDSUB(int32_t rn, int32_t rm);
int64_t asm_SMLALBB(int32_t rdlo,int32_t rdhi,int32_t rn, int32_t rm);
int64_t asm_SMLALBT(int32_t rdlo,int32_t rdhi,int32_t rn, int32_t rm);
int64_t asm_SMLALTB(int32_t rdlo,int32_t rdhi,int32_t rn, int32_t rm);
int64_t asm_SMLALTT(int32_t rdlo,int32_t rdhi,int32_t rn, int32_t rm);
int32_t asm__SMMLAR (int32_t op1, int32_t op2, int32_t op3);
int32_t asm__SMMLSR (int32_t op1, int32_t op2, int32_t op3);
int32_t asm__SMMLS (int32_t op1, int32_t op2, int32_t op3);
int32_t asm__SMMUL (int32_t op1, int32_t op2);
int32_t asm__SMMULR (int32_t op1, int32_t op2);
int32_t asm__SXTAB(int32_t op1, int32_t op2);
int32_t asm__SXTAH(int32_t op1, int32_t op2);
uint64_t asm_UMAAL(uint32_t rdlo,uint32_t rdhi,uint32_t rn, uint32_t rm);
uint32_t asm__UXTAB(uint32_t op1, uint32_t op2);
uint32_t asm__UXTAH(uint32_t op1, uint32_t op2);
#endif