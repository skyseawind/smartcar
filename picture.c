#include "common.h"
#include "include.h"
uint8 daolu_flag;


void PORTB_IRQHandler()
{
    uint8  n;    //引脚号
    uint32 flag;

    while(!PORTB_ISFR);
    flag = PORTB_ISFR;
    PORTB_ISFR  = ~0;                                   //清中断标志位

    n = 9;                                             //场中断
    if(flag & (1 << n))                                 //PTA29触发中断
    {
        camera_vsync();
    }
    
/*这里不使用行中断*/
//#if ( CAMERA_USE_HREF == 1 )                            //使用行中断
//    n = 28;
//    if(flag & (1 << n))                                 //PTA28触发中断
//    {
//        camera_href();
//    }
//#endif


}

/*!
 *  @brief      DMA0中断服务函数
 *  @since      v5.0
 */
void DMA0_IRQHandler()
{
    camera_dma();
}