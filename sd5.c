#include "common.h"
#include "include.h"
#include "feature.h"



/******************************�������************************************/


#define img_upper 35           //ͼ��ȡimg_upper�е�img_dowm��
#define img_down  45
#define p_wandao 2.2           //��� Pֵ
#define p_zhidao 0.5           //ֱ�� p ֵ
#define medium_duty 450        //ռ�ձ���ֵ
#define left_duty 340
#define right_duty 560
#define d_wandao 5
#define d_PID 8
#define d_xiao_S 8 





float p;//����ϵ��
float d;//΢��ϵ��
float error_now=0; 

void SD5_control(void)
{
       int i;  //ѭ����
       int sum=0;
        float error_average; 
        float SD_center =1000-medium_duty ;//����                
	float pwm_SD5;
        float error_last=0;
        
        d=d_PID;
	for(i=img_upper;i<img_down;i++)                  //��Ұ��Χ
	{
		sum=sum+centerline[i];
	}
	error_average=sum/(img_down-img_upper);                            
        error_last=error_now;   //��ǰƫ���Ϊ��һ��ƫ��
	error_now=CAMERA_W/2-error_average;  //���㵱ǰƫ��
        p = p_wandao;
        d = d_PID;
        lianxu_S();
        pwm_SD5 = SD_center + p*error_now+d*(error_now-error_last);      // ʵ�ʴ�������ռ�ձ�Ϊduty_medium-p*error��
        
 
//�޷�        
        if(pwm_SD5<1000-right_duty) pwm_SD5= 1000 - right_duty;                 
        if(pwm_SD5>1000-left_duty) pwm_SD5= 1000 - left_duty;
//�������
        if(error_now>40)
          pwm_SD5 = 1000-left_duty;
        if(error_now<-40)
          pwm_SD5 = 1000-right_duty;
//ת�併��           
        if((uint32)pwm_SD5<(1000-360)||(uint32)pwm_SD5>(1000-540))
        { 
          ftm_pwm_duty(MOTOR_FTM, MOTOR1_PWM,motor_wandao);
          ftm_pwm_duty(MOTOR_FTM, MOTOR2_PWM,motor);
        }
                 
          ftm_pwm_duty(SD5_FTM,SD5_CH,(uint32)pwm_SD5);
        
        
}



 

///****************����ƫ���****************
//* �������ƣ�error
//* ����˵������������ƫ��
//* ��ע��
//********************************************/
//void error(void)
//{
//	int i,sum=0;
//	float err,e1; 
//	for(i=45;i<55;i++)                  //��Ұ��Χ
//	{
//		sum=sum+centerline[i];
//	}
//	err=sum/10;                             //��������ע�� 
//        error_last=error_now;
//	error_now=CAMERA_W/2-err;
//
//	
//}
//
//
///**************PWM���㺯��************
//* �������ƣ�error_to_pwm
//* ����˵����ƫ��ת��ΪPWM
//* ��ע��
//***************************************/
//float error = 0;
//float error_last = 0;
//int16
//
//uint32 error_to_pwm(float error)
//{
//	float SD_center = 1000-medium_duty , p = p_wandao;   //����    //����ϵ��
//	float error��error_last;
//        float pwm;
//        float d=d_wandao;
//        if(error>-20&&error<20) p=P_zhidao;
//        else
//                  
//	pwm = SD_center + p*error_now+15*(error_now-error_last); 
//        pwm = SD_center + p*error + d*
//        
//        if(pwm<1000-right_duty) pwm=1000-right_duty;
//        if(pwm>1000-left_duty) pwm=1000-left_duty;
//        if(error>25)
//          pwm = 1000-left_duty;
//        if(error<-25)
//          pwm = 1000-right_duty;
//         
//	return (uint32)pwm;
//        
//}
