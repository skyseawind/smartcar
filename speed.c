
#include "common.h"
#include "include.h"

void PIT0_IRQHandler(void)
{
    if(PIT_TFLG(QEP_pit) == 1)                         //�ж��Ƿ� PIT0 �����ж�
  { 
    Speed_Control();                                //PWMֵ����        �ٶȿ���
    PIT_Flag_Clear(QEP_pit);                       //���жϱ�־λ     
  }
}
