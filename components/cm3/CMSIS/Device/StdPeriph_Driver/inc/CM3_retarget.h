#ifndef __CM3_retarget_H
#define __CM3_retarget_H

#ifdef __cplusplus
 extern "C" {
#endif

extern unsigned char UartPutc(unsigned char my_ch);
extern unsigned char UartGetc(void);
 #ifdef __cplusplus
}
#endif
  
#endif 
