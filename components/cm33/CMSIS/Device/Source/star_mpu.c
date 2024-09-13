//crate at 22.3.1 by sdfu
//for arm core STAR
#include "star_mpu.h"

void set_region_base(uint32_t base,uint8_t share_att,uint8_t ap_att, uint8_t xn){
		MPU->RBAR = (base&MPU_CTRL_RBAR_BASE_MASK) |  //from addr 0
							  ((share_att << MPU_CTRL_RBAR_SH_SHIFT) & MPU_CTRL_RBAR_SH_MASK) |
                ((ap_att << MPU_CTRL_RBAR_AP_SHIFT) & MPU_CTRL_RBAR_AP_MASK) | //r&w
                (xn & MPU_CTRL_RBAR_XN_MASK);  //executable
}

void set_region_limit(uint32_t limit, uint32_t att_num ,uint32_t en){
		MPU->RLAR = (limit&MPU_CTRL_RLAR_LIMIT_MASK) | //end at addr 0x1ffff
							  ((att_num << MPU_CTRL_RLAR_ATTRIDX_SHIFT) & MPU_CTRL_RLAR_ATTRIDX_MASK) | //use att0
                (en & MPU_CTRL_RLAR_EN_MASK); //region enable
}

void set_mair(uint8_t idx,uint8_t att){
	if(idx<=3){
		MPU->MAIR0 &= ~(0xFF << (idx * 8)); //crate mask of index 0
		MPU->MAIR0 |=  (att << (idx * 8));  //set value of index 0.device-ngnrne
	}
	else if(idx>3&&idx<=7){
		MPU->MAIR1 &= ~(0xFF << ((idx - 4) * 8)); //crate mask
  	MPU->MAIR1 |=  (att << ((idx - 4) * 8));  //set value
	}	
}

void mpu_enable(){
		MPU->CTRL=0x7; //enable PRIVDEFENA HFNMIENA MPU 
		__DSB();
		__ISB();
}








