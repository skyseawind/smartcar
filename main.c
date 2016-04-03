/*
1.
gpio_init(MOTOR1_IO,GPO,1); 使能与否
ftm_pwm_duty(MOTOR_FTM, MOTOR1_PWM,30); 
ftm_pwm_duty(MOTOR_FTM, MOTOR2_PWM,60);
MOTOR_HZ  频率
要结合电机的启动停止，加减速做修改

2.大部分全局变量，外部函数的声明都在define.h文件里

*/
/**************************主函数*******************************
* 函数名称：main
* 功能说明：
* 备注：
***************************************************************/


//摄像头相关宏定义在VCAN_OV7725_Eagle.h/.c中完成


#include "common.h"        //摄像头总头文件&舵机头文件&电机头文件
#include "include.h"
#include "VCAN_camera.h"       
#include "OV7725.h"
#include "picture.h"                             
#include "feature.h"




/*************************/   
uint8 imgbuff[CAMERA_SIZE];                             //定义存储接收图像的数组（解压前）
uint8 img[CAMERA_W*CAMERA_H];                           //img 解压后像素值数组的地址
uint16 i;
uint8 duty;
float error2;
uint32 pwm_sd_5;




void  main(void)
{
 
  
  
  
   /************初始化***********************/
  //初始化串口(UART3 是工程里配置为printf函数输出端口，故已经进行初始化
   //UART0_RX_PIN    PTB16
  // UART0_TX_PIN    PTB17
  
     uart_init(UART0,115200);     
                                
                               
    //初始化摄像头相关的引脚
    camera_init(imgbuff);         
    
    
   //初始化 舵机 PWM
    ftm_pwm_init(SD5_FTM, SD5_CH,SD5_HZ,1000-450);       // 0~1000表示0%~100%      占空比，占：整个周期。duty=我们需要的时间*频率*精度
    
    //初始化 电机 PWM
    ftm_pwm_init(MOTOR_FTM, MOTOR1_PWM,MOTOR_HZ,motor_zhidao);      //初始化 电机 PWM      上小下大反转
    ftm_pwm_init(MOTOR_FTM, MOTOR2_PWM,MOTOR_HZ,motor);      //初始化 电机 PWM        0~1000表示0%~100%
//                                                        // FTM0，FTM1精度是1000u
//    
//    
    gpio_init(MOTOR1_IO,GPO,1);            //使能作用，PTC1给高电平使能开,电机启动
    
    
    
    
   // ftm_pwm_duty(MOTOR_FTM, MOTOR1_PWM,30);
        
   // ftm_pwm_duty(MOTOR_FTM, MOTOR2_PWM,60);

    
     
    /**************配置中断服务函数***************/
    set_vector_handler(PORTB_VECTORn , PORTB_IRQHandler);   //设置 PORTB 的中断服务函数为 PORTB_IRQHandler
    set_vector_handler(DMA0_VECTORn , DMA0_IRQHandler);     //设置 DMA0 的中断服务函数为 DNA0_IRQHandler
   
    DELAY_MS(1000);
    

    while(1)
    {
        camera_get_img();                                   //摄像头获取图像
        imgextract(img, imgbuff, CAMERA_SIZE);//解压图像
        Centerline();  //提取中线
        
        
        show_line();   //上位机显示中线                
       img_reduce(img,imgbuff,CAMERA_W*CAMERA_H);
       vcan_sendimg(imgbuff,CAMERA_SIZE);   //函数功能：把图像数据发送到上位机
//        
                                                 //img 解压后像素值数组的地址
 

       
        away_road_stop();    //停车

        
         
          
          SD5_control();
          
        }
        
      
        
      
    }                                         

