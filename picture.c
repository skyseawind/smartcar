#include "common.h"
#include "include.h"
uint8 daolu_flag;


void PORTB_IRQHandler()
{
    uint8  n;    //���ź�
    uint32 flag;

    while(!PORTB_ISFR);
    flag = PORTB_ISFR;
    PORTB_ISFR  = ~0;                                   //���жϱ�־λ

    n = 9;                                             //���ж�
    if(flag & (1 << n))                                 //PTA29�����ж�
    {
        camera_vsync();
    }
    
/*���ﲻʹ�����ж�*/
//#if ( CAMERA_USE_HREF == 1 )                            //ʹ�����ж�
//    n = 28;
//    if(flag & (1 << n))                                 //PTA28�����ж�
//    {
//        camera_href();
//    }
//#endif


}

/*!
 *  @brief      DMA0�жϷ�����
 *  @since      v5.0
 */
void DMA0_IRQHandler()
{
    camera_dma();
}