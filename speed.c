/**************yangxiao************/
#include "common.h"
#include "include.h"
//杨逍修改实验git
void PIT0_IRQHandler(void)
{
    if(PIT_TFLG(QEP_pit) == 1)                         //判断是否 PIT0 进入中断
  { 
    Speed_Control();                                //PWM值不变        速度控制
    PIT_Flag_Clear(QEP_pit);                       //清中断标志位     
  }
}

