/*
1.
gpio_init(MOTOR1_IO,GPO,1); ʹ�����
ftm_pwm_duty(MOTOR_FTM, MOTOR1_PWM,30); 
ftm_pwm_duty(MOTOR_FTM, MOTOR2_PWM,60);
MOTOR_HZ  Ƶ��
Ҫ��ϵ��������ֹͣ���Ӽ������޸�

2.�󲿷�ȫ�ֱ������ⲿ��������������define.h�ļ���

*/
/**************************������*******************************
* �������ƣ�main
* ����˵����
* ��ע��
***************************************************************/


//����ͷ��غ궨����VCAN_OV7725_Eagle.h/.c�����


#include "common.h"        //����ͷ��ͷ�ļ�&���ͷ�ļ�&���ͷ�ļ�
#include "include.h"
#include "VCAN_camera.h"       
#include "OV7725.h"
#include "picture.h"                             
#include "feature.h"




/*************************/   
uint8 imgbuff[CAMERA_SIZE];                             //����洢����ͼ������飨��ѹǰ��
uint8 img[CAMERA_W*CAMERA_H];                           //img ��ѹ������ֵ����ĵ�ַ
uint16 i;
uint8 duty;
float error2;
uint32 pwm_sd_5;




void  main(void)
{
 
  
  
  
   /************��ʼ��***********************/
  //��ʼ������(UART3 �ǹ���������Ϊprintf��������˿ڣ����Ѿ����г�ʼ��
   //UART0_RX_PIN    PTB16
  // UART0_TX_PIN    PTB17
  
     uart_init(UART0,115200);     
                                
                               
    //��ʼ������ͷ��ص�����
    camera_init(imgbuff);         
    
    
   //��ʼ�� ��� PWM
    ftm_pwm_init(SD5_FTM, SD5_CH,SD5_HZ,1000-450);       // 0~1000��ʾ0%~100%      ռ�ձȣ�ռ���������ڡ�duty=������Ҫ��ʱ��*Ƶ��*����
    
    //��ʼ�� ��� PWM
    ftm_pwm_init(MOTOR_FTM, MOTOR1_PWM,MOTOR_HZ,motor_zhidao);      //��ʼ�� ��� PWM      ��С�´�ת
    ftm_pwm_init(MOTOR_FTM, MOTOR2_PWM,MOTOR_HZ,motor);      //��ʼ�� ��� PWM        0~1000��ʾ0%~100%
//                                                        // FTM0��FTM1������1000u
//    
//    
    gpio_init(MOTOR1_IO,GPO,1);            //ʹ�����ã�PTC1���ߵ�ƽʹ�ܿ�,�������
    
    
    
    
   // ftm_pwm_duty(MOTOR_FTM, MOTOR1_PWM,30);
        
   // ftm_pwm_duty(MOTOR_FTM, MOTOR2_PWM,60);

    
     
    /**************�����жϷ�����***************/
    set_vector_handler(PORTB_VECTORn , PORTB_IRQHandler);   //���� PORTB ���жϷ�����Ϊ PORTB_IRQHandler
    set_vector_handler(DMA0_VECTORn , DMA0_IRQHandler);     //���� DMA0 ���жϷ�����Ϊ DNA0_IRQHandler
   
    DELAY_MS(1000);
    

    while(1)
    {
        camera_get_img();                                   //����ͷ��ȡͼ��
        imgextract(img, imgbuff, CAMERA_SIZE);//��ѹͼ��
        Centerline();  //��ȡ����
        
        
        show_line();   //��λ����ʾ����                
       img_reduce(img,imgbuff,CAMERA_W*CAMERA_H);
       vcan_sendimg(imgbuff,CAMERA_SIZE);   //�������ܣ���ͼ�����ݷ��͵���λ��
//        
                                                 //img ��ѹ������ֵ����ĵ�ַ
 

       
        away_road_stop();    //ͣ��

        
         
          
          SD5_control();
          
        }
        
      
        
      
    }                                         

