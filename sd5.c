#include "common.h"
#include "include.h"
#include "feature.h"



/******************************舵机控制************************************/


#define img_upper 35           //图像取img_upper行到img_dowm行
#define img_down  45
#define p_wandao 2.2           //弯道 P值
#define p_zhidao 0.5           //直道 p 值
#define medium_duty 450        //占空比中值
#define left_duty 340
#define right_duty 560
#define d_wandao 5
#define d_PID 8
#define d_xiao_S 8 





float p;//比例系数
float d;//微分系数
float error_now=0; 

void SD5_control(void)
{
       int i;  //循环用
       int sum=0;
        float error_average; 
        float SD_center =1000-medium_duty ;//居中                
	float pwm_SD5;
        float error_last=0;
        
        d=d_PID;
	for(i=img_upper;i<img_down;i++)                  //视野范围
	{
		sum=sum+centerline[i];
	}
	error_average=sum/(img_down-img_upper);                            
        error_last=error_now;   //当前偏差变为上一次偏差
	error_now=CAMERA_W/2-error_average;  //计算当前偏差
        p = p_wandao;
        d = d_PID;
        lianxu_S();
        pwm_SD5 = SD_center + p*error_now+d*(error_now-error_last);      // 实际传入舵机的占空比为duty_medium-p*error；
        
 
//限幅        
        if(pwm_SD5<1000-right_duty) pwm_SD5= 1000 - right_duty;                 
        if(pwm_SD5>1000-left_duty) pwm_SD5= 1000 - left_duty;
//过弯打死
        if(error_now>40)
          pwm_SD5 = 1000-left_duty;
        if(error_now<-40)
          pwm_SD5 = 1000-right_duty;
//转弯降速           
        if((uint32)pwm_SD5<(1000-360)||(uint32)pwm_SD5>(1000-540))
        { 
          ftm_pwm_duty(MOTOR_FTM, MOTOR1_PWM,motor_wandao);
          ftm_pwm_duty(MOTOR_FTM, MOTOR2_PWM,motor);
        }
                 
          ftm_pwm_duty(SD5_FTM,SD5_CH,(uint32)pwm_SD5);
        
        
}



 

///****************计算偏差函数****************
//* 函数名称：error
//* 功能说明：计算中线偏差
//* 备注：
//********************************************/
//void error(void)
//{
//	int i,sum=0;
//	float err,e1; 
//	for(i=45;i<55;i++)                  //视野范围
//	{
//		sum=sum+centerline[i];
//	}
//	err=sum/10;                             //总数、、注意 
//        error_last=error_now;
//	error_now=CAMERA_W/2-err;
//
//	
//}
//
//
///**************PWM计算函数************
//* 函数名称：error_to_pwm
//* 功能说明：偏差转化为PWM
//* 备注：
//***************************************/
//float error = 0;
//float error_last = 0;
//int16
//
//uint32 error_to_pwm(float error)
//{
//	float SD_center = 1000-medium_duty , p = p_wandao;   //居中    //比例系数
//	float error，error_last;
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
