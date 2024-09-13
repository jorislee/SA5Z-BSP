//crate by sdfu 
//at 22.3.23
#include "star_dsp.h"


//#define __PKHBT(ARG1,ARG2,ARG3)          ( ((((uint32_t)(ARG1))          ) & 0x0000FFFFUL) |  \
                                           ((((uint32_t)(ARG2)) << (ARG3)) & 0xFFFF0000UL)  )

//#define __PKHTB(ARG1,ARG2,ARG3)          ( ((((uint32_t)(ARG1))          ) & 0xFFFF0000UL) |  \
                                           ((((uint32_t)(ARG2)) >> (ARG3)) & 0x0000FFFFUL)  )
//out =	(in_1&0x0000FFFF)|( (in_2<<imm)&0xFFFF0000	)																 
uint32_t asm_PKHBT(uint32_t in_1, uint32_t in_2){
	uint32_t rlt;
  __asm volatile (
	"PKHBT %[outdata],%[in1],%[in2],LSL #4\t"
	:[outdata] "=r" (rlt)
	:[in1]      "r" (in_1) ,
	 [in2]      "r" (in_2)
	:
	);
	return rlt;
}

//out=(in_1&0xFFFF0000UL)|((in2>>imm)&0x0000FFFFUL)
uint32_t asm_PKHTB(uint32_t in_1, uint32_t in_2){
	uint32_t rlt;
  __asm volatile (
	"PKHTB %[outdata],%[in1],%[in2],ASR #4\t"
	:[outdata] "=r" (rlt)
	:[in1]      "r" (in_1) ,
	 [in2]      "r" (in_2)
	:
	);
	return rlt;
}


//Rd=2*Rn+Rm
int32_t asm_QDADD(int32_t rm, int32_t rn){
	int32_t rd;
	__asm volatile (
	"QDADD %[outdata],%[in1],%[in2]\t"
	:[outdata] "=r" (rd)
	:[in1]      "r" (rm) ,
	 [in2]      "r" (rn)
	:
	);
	return rd;
}

//Rd=Rm-2*Rn
int32_t asm_QDSUB(int32_t rm, int32_t rn){
	int32_t rd;
	__asm volatile (
	"QDSUB %[outdata],%[in1],%[in2]\t"
	:[outdata] "=r" (rd)
	:[in1]      "r" (rm) ,
	 [in2]      "r" (rn)
	:
	);
	return rd;
}

int64_t asm_SMLALBB(int32_t rdlo,int32_t rdhi,int32_t rn, int32_t rm){
  int64_t rlt=0;
	__asm volatile (
	"SMLALBB %[rlo],%[rhi],%[rn],%[rm]\t"
	:[rlo] "+r" (rdlo) ,[rhi] "+r" (rdhi)
	:[rn]   "r" (rm) ,[rm]      "r" (rn)
	:
	);
	rlt=rdhi;
	rlt=(rlt<<32)|rdlo;
	return rlt;
}

int64_t asm_SMLALTT(int32_t rdlo,int32_t rdhi,int32_t rn, int32_t rm){
  int64_t rlt=0;
	__asm volatile (
	"SMLALTT %[rlo],%[rhi],%[rn],%[rm]\t"
	:[rlo] "+r" (rdlo) ,[rhi] "+r" (rdhi)
	:[rn]   "r" (rm) ,[rm]      "r" (rn)
	:
	);
	rlt=rdhi;
	rlt=(rlt<<32)|rdlo;
	return rlt;
}

int64_t asm_SMLALBT(int32_t rdlo,int32_t rdhi,int32_t rn, int32_t rm){
  int64_t rlt=0;
	__asm volatile (
	"SMLALBT %[rlo],%[rhi],%[rn],%[rm]\t"
	:[rlo] "+r" (rdlo) ,[rhi] "+r" (rdhi)
	:[rn]   "r" (rm) ,[rm]      "r" (rn)
	:
	);
	rlt=rdhi;
	rlt=(rlt<<32)|rdlo;
	return rlt;
}

int64_t asm_SMLALTB(int32_t rdlo,int32_t rdhi,int32_t rn, int32_t rm){
  int64_t rlt=0;
	__asm volatile (
	"SMLALTB %[rlo],%[rhi],%[rn],%[rm]\t"
	:[rlo] "+r" (rdlo) ,[rhi] "+r" (rdhi)
	:[rn]   "r" (rm) ,[rm]      "r" (rn)
	:
	);
	rlt=rdhi;
	rlt=(rlt<<32)|rdlo;
	return rlt;
}

int32_t asm__SMMLAR (int32_t op1, int32_t op2, int32_t op3)
{
  int32_t result;
  __asm volatile ("smmlar %0, %1, %2, %3" : "=r" (result): "r"  (op1), "r" (op2), "r" (op3) );
  return(result);
}

int32_t asm__SMMLS (int32_t op1, int32_t op2, int32_t op3)
{
  int32_t result;
  __asm volatile ("smmls %0, %1, %2, %3" : "=r" (result): "r"  (op1), "r" (op2), "r" (op3) );
  return(result);
}

int32_t asm__SMMLSR (int32_t op1, int32_t op2, int32_t op3)
{
  int32_t result;
  __asm volatile ("smmlsr %0, %1, %2, %3" : "=r" (result): "r"  (op1), "r" (op2), "r" (op3) );
  return(result);
}

int32_t asm__SMMUL (int32_t op1, int32_t op2)
{
  int32_t result;
  __asm volatile ("smmul %0, %1, %2" : "=r" (result): "r"  (op1), "r" (op2) );
  return(result);
}

int32_t asm__SMMULR (int32_t op1, int32_t op2)
{
  int32_t result;
  __asm volatile ("smmulr %0, %1, %2" : "=r" (result): "r"  (op1), "r" (op2) );
  return(result);
}

int32_t asm__SXTAB(int32_t op1, int32_t op2){
	int32_t result;
  __asm volatile ("sxtab %0, %1, %2" : "=r" (result): "r"  (op1), "r" (op2) );
  return(result);
}

int32_t asm__SXTAH(int32_t op1, int32_t op2){
	int32_t result;
  __asm volatile ("sxtah %0, %1, %2" : "=r" (result): "r"  (op1), "r" (op2) );
  return(result);
}

uint64_t asm_UMAAL(uint32_t rdlo,uint32_t rdhi,uint32_t rn, uint32_t rm){
  uint64_t rlt=0;
	__asm volatile (
	"UMAAL %[rlo],%[rhi],%[rn],%[rm]\t"
	:[rlo] "+r" (rdlo) ,[rhi] "+r" (rdhi)
	:[rn]   "r" (rm) ,[rm]      "r" (rn)
	:
	);
	rlt=rdhi;
	rlt=(rlt<<32)|rdlo;
	return rlt;
}

uint32_t asm__UXTAB(uint32_t op1, uint32_t op2){
	int32_t result;
  __asm volatile ("uxtab %0, %1, %2" : "=r" (result): "r"  (op1), "r" (op2) );
  return(result);
}
	
uint32_t asm__UXTAH(uint32_t op1, uint32_t op2){
	int32_t result;
  __asm volatile ("uxtah %0, %1, %2" : "=r" (result): "r"  (op1), "r" (op2) );
  return(result);
}
