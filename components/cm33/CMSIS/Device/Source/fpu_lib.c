//data: 21.11.24
//crate: sdfu
//usage: libary for FPU(fpv5)

#include "fpu_lib.h"
//float multiply accumalate (f0*f1)+*dst
//sdfu at 21.11.24
void FMLA_3(float f0, float f1, float * dst){
	__ASM volatile(
	"VMLA.F32 %[result],%[float0],%[float1]\t"
	:[result] "+t" (*dst)
	:[float1] "t" (f1) ,
	 [float0] "t" (f0) 
	:
	);
}

//float add 
//sdfu at 21.12.4
//return:result of f0+f1
float FADD(float f0, float f1){
	float res =0;
	__ASM volatile(
	"VADD.F32 %[result],%[float1],%[float0]\t"
	:[result] "=t" (res)
	:[float1] "t" (f1) ,
	 [float0] "t" (f0)
	:
	);
	
	return res;
}

//float sub 
//sdfu at 21.12.4
//return:result of f1-f0
float FSUB(float f0, float f1){
	float res =0;
	__ASM volatile(
	"VSUB.F32 %[result],%[float1],%[float0]\t"
	:[result] "=t" (res)
	:[float1] "t" (f1) ,
	 [float0] "t" (f0)
	:
	);
	
	return res;
}

//float sub 
//sdfu at 21.12.4
//return:result of f0*f1
float FMUL(float f0, float f1){
	float res =0;
	__ASM volatile(
	"VMUL.F32 %[result],%[float1],%[float0]\t"
	:[result] "=t" (res)
	:[float1] "t" (f1) ,
	 [float0] "t" (f0)
	:
	);
	
	return res;
}

//float sub 
//sdfu at 21.12.4
//return:result of f0/f1
float FDIV(float f0, float f1){
	float res =0;
	__ASM volatile(
	"VDIV.F32 %[result],%[float1],%[float0]\t"
	:[result] "=t" (res)
	:[float1] "t" (f1) ,
	 [float0] "t" (f0)
	:
	);
	
	return res;
}

//float multiply accumalate 
//sdfu at 21.11.22
//return:result of (f0*f1)+f1
float FMLA_2(float f0, float f1){
	float res =0;
	__ASM volatile(
	"VMLA.F32 %[result],%[float1],%[float0]\t"
	:[result] "=t" (res)
	:[float1] "t" (f1) ,
	 [float0] "t" (f0)
	:
	);
	return res;
}

//get floating point square root
//return: square root of input value
//sdfu at 21.11.22
float FSQRT(float fin){
	float res=0;
	__ASM volatile(
	"VSQRT.F32 %[result],%[input]\t" 
	:[result] "=t"(res) 
	:[input] "t"(fin)
	:
	);
	return res;
}

//get absolute value of float number
//@return: absolute value
//sdfu at 22.3.13
float FABS(float fin){
	float res=0;
	__ASM volatile(
	"VABS.F32 %[result],%[input]\t" 
	:[result] "=t"(res) 
	:[input] "t"(fin)
	:
	);
	return res;
}

//fpu clear fpdzc
void clr_fpdzc(void){
	unsigned int fpscr;
  __asm__ __volatile__("vmrs %[fpscr], fpscr" : [fpscr] "=r"(fpscr)); //get value
	printf("fpscr now is %08x\n",fpscr);
	fpscr &=0xfffffffd;
	__asm__ __volatile__("vmsr fpscr, %[fpscr]" : : [fpscr] "r"(fpscr)); //set value
}

//read fpscr
void read_fpscr(void){
	unsigned int fpscr;
  __asm__ __volatile__("vmrs %[fpscr], fpscr" : [fpscr] "=r"(fpscr)); //get value
	printf("read fpscr : %08x\n",fpscr);
}

//get value of fpscr
uint32_t get_fpscr(void){
	unsigned int fpscr;
  __asm__ __volatile__("vmrs %[fpscr], fpscr" : [fpscr] "=r"(fpscr)); //get value
 return fpscr;
}

//check FPIXC 
uint32_t check_FPIXC(void){
	unsigned int fpscr;
  __asm__ __volatile__("vmrs %[fpscr], fpscr" : [fpscr] "=r"(fpscr)); //get value
	return (fpscr&0x10)>>4;
}
//check FPUFC 
uint32_t check_FPUFC(void){
	unsigned int fpscr;
  __asm__ __volatile__("vmrs %[fpscr], fpscr" : [fpscr] "=r"(fpscr)); //get value
	return (fpscr&0x8)>>3;
}

//check FPOFC 
uint32_t check_FPOFC(void){
	unsigned int fpscr;
  __asm__ __volatile__("vmrs %[fpscr], fpscr" : [fpscr] "=r"(fpscr)); //get value
	return (fpscr&0x4)>>2;
}

//check FPDZC 
uint32_t check_FPDZC(void){
	unsigned int fpscr;
  __asm__ __volatile__("vmrs %[fpscr], fpscr" : [fpscr] "=r"(fpscr)); //get value
	return (fpscr&0x2)>>1;
}

//check FPIDC 
uint32_t check_FPIDC(void){
	unsigned int fpscr;
  __asm__ __volatile__("vmrs %[fpscr], fpscr" : [fpscr] "=r"(fpscr)); //get value
	return (fpscr&0x80)>>7;
}

//check FPIOC
uint32_t check_FPIOC(void){
	unsigned int fpscr;
  __asm__ __volatile__("vmrs %[fpscr], fpscr" : [fpscr] "=r"(fpscr)); //get value
	return (fpscr&0x1);
}

//disable all the excptions of FPU
void disable_fpu_excption(void){
//	SCnSCB_NS->ACTLR |=0x00000400;//0xfffffbff; //disable fpu execption ,invalid,unknow reason
	SCnSCB->ACTLR    |=0x00000400;//0xfffffbff; //disable fpu execption
}


//set FC mode will clear bit[25:24]
void FPU_set_mode(char mode){
	unsigned int fpscr;
	if(mode==FP_FZ){
		__asm__ __volatile__("vmrs %[fpscr], fpscr" : [fpscr] "=r"(fpscr)); //get value
		printf("\n\n config FZ MODE\n");
		printf("fpscr now is %08x\n",fpscr);
		fpscr |=0x01000000; //set bit[24] to 1
		__asm__ __volatile__("vmsr fpscr, %[fpscr]" : : [fpscr] "r"(fpscr)); //set value
		printf("mode cfg:fpscr is %08x\n",fpscr);
	}
	else if(mode==FP_DN){
		__asm__ __volatile__("vmrs %[fpscr], fpscr" : [fpscr] "=r"(fpscr)); //get value
		printf("\n\n config DN MODE\n");
		printf("fpscr now is %08x\n",fpscr);
		fpscr |=0x02000000; //set bit[25] to 1
		__asm__ __volatile__("vmsr fpscr, %[fpscr]" : : [fpscr] "r"(fpscr)); //set value	
		printf("mode cfg:fpscr is %08x\n",fpscr);
	}
	else if(mode==FP_FC){
		__asm__ __volatile__("vmrs %[fpscr], fpscr" : [fpscr] "=r"(fpscr)); //get value
		printf("\n\n config FC MODE\n");
		printf("fpscr now is %08x\n",fpscr);
		fpscr &=0xfcffffff; //set bit[25:24] to 0
		__asm__ __volatile__("vmsr fpscr, %[fpscr]" : : [fpscr] "r"(fpscr)); //set value	
	printf("mode cfg:fpscr is %08x\n",fpscr);
	}
}

//compare option
//if f0>f1 fpscr[31] return 0,else 1 ,if f0=f1 fpscr[30] return 1,else 0
uint32_t FCMP(float f0, float f1){
	unsigned int fpscr;
	__ASM volatile(
	"VCMP.F32 %[float0],%[float1]\t"
	:
	:[float1] "t" (f1) ,
	 [float0] "t" (f0)
	:
	);
  
  __asm__ __volatile__(
	"vmrs %[fpscr], fpscr" 
	: [fpscr] "=r"(fpscr)); //get value
	return fpscr>>30;
}

//sdfu at 21.12.7
void FPU_set_round_mode(uint32_t round_mode){
	uint32_t fpscr;
	__asm__ __volatile__("vmrs %[fpscr], fpscr" : [fpscr] "=r" (fpscr)); //get value
	fpscr&=0xff3fffff;//clear bit[23:22]
	fpscr|=0x00c00000&(round_mode<<22);//set bit[23:22]
	__asm__ __volatile__("vmsr fpscr, %[fpscr]" : : [fpscr] "r"(fpscr)); //set value
}

//show the hex value of the float data, with display
//sdfu at 21.12.8
void hexVflt_disp(float flt){
	uint32_t * fp = &flt;
	printf("HEX value of %f is %8x\n",flt,*fp);
}

//show the hex value of the float data, without display
//sdfu at 21.12.9
uint32_t hexVflt(float flt){
	uint32_t * uint32_p = &flt;
	return *uint32_p;
}

//convert a hex value to float
//sdfu at 21.12.9
float	hex2flt(uint32_t hexV){
	float * flt_p = &hexV;
	return *flt_p;
}

//convert unsigned integer to floating point
//sdfu at 21.12.10
float uint2float(uint32_t uint_num){
	float result;
	__asm__ volatile ("vcvt.f32.u32 %[cvt_result],%[uint32]\t"
	:[cvt_result] "=t" (result)
	:[uint32] "t" (uint_num)
	:
	);
	return result;
}

//convert integer to floating point
//sdfu at 21.12.10
float int2float(int32_t int_num){
	float result;
	__asm__ volatile ("vcvt.f32.s32 %[cvt_result],%[uint32]\t"
	:[cvt_result] "=t" (result)
	:[uint32] "t" (int_num)
	:
	);
	return result;
}

//convert integer to floating point 
//sdfu at 21.12.10
uint32_t float2uint(float flt_num){
	uint32_t result;
	__asm__ volatile ("vcvtr.u32.f32 %[cvt_result],%[flt]\t"
	:[cvt_result] "=t" (result)
	:[flt] "t" (flt_num)
	:
	);
	return result;
}

//convert signed integer to float 
//sdfu at 21.12.10
int32_t float2int(float flt_num){
	int32_t result;
	__asm__ volatile ("vcvtr.s32.f32 %[cvt_result],%[flt]\t"
	:[cvt_result] "=t" (result)
	:[flt] "t" (flt_num)
	:
	);
	return result;
}

//following code can't be compiled by arm compiler v6.16
//////float multiply accumalate
//////sdfu at 21.11.22
////float FMLA(float f1, float f2){
////	float res =0;
////	__ASM volatile(
////	"VMOV S0,R0\t"
////	"VMOV S1,R1\t"
////	"VMLA.F32 S2,S1,S0\t"
////	"VMOV R0,S2\t"
////	);
////	return res;
////}

//////floating point square root
//////sdfu at 21.11.22
////float FSQRT(float f1){
////	float res=0;
////	__ASM volatile(
////	"VMOV S0,R0\t"
////	"VSQRT.F32 S1,S0\t"
////	"VMOV R0,S1\t"
////	);
////	return res;
////}

//////float multiply accumalate
//////sdfu at 21.11.22
////__ASM float FMLA(float f1, float f2){
////	
////	VMOV S0,R0
////	VMOV S1,R1
////	VMLA.F32 S2,S1,S0
////	VMOV R0,S2
////	
////}

//////floating point square root
//////sdfu at 21.11.22
////__ASM float FSQRT(float f1){
////	
////	VMOV S0,R0
////	VSQRT.F32 S1,S0
////	VMOV R0,S1
////	
////}
