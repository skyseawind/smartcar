#include "common.h"        
#include "include.h"
#include "OV7725.h"
#include "define.h"

/********************赛道识别**********************/

#define MOTOR1_IO   PTC1
#define lianxu_S_front1 3 
#define lianxu_S_back1  8
#define lianxu_S_front2 13
#define lianxu_S_back2  17


//外部定义
extern float p;  
extern float d;


/***************安全模式****************
* 函数名称：away_road_stop
* 功能说明：车冲出赛道处理
* 备注：
********************************************/
void away_road_stop(void)
{
  int stop_flag=0;
  if(img[W*59+centerline[59]]==black&&img[W*58+centerline[58]]==black&&img[W*57+centerline[57]]==black&&img[W*56+centerline[56]]==black&&img[W*55+centerline[55]]==black&&img[W*54+centerline[54]]==black&&img[W*53+centerline[53]]==black)
          {
            stop_flag=1;
          }
          if (stop_flag==1) 
          {
            gpio_init(MOTOR1_IO,GPO,0);   
            
          }
}


/***************连续小S弯处理*******************
* 函数名称：lianxu_S
* 功能说明：识别小S弯
* 备注：
********************************************/
void lianxu_S(void)
{
int i;
float sum = 0 , aver , err;
for(i=lianxu_S_front1;i<lianxu_S_back1;i++)
{
sum = sum + centerline[i];
}
for(i=lianxu_S_front2;i<lianxu_S_back2;i++)
{
sum = sum + centerline[i];
}
aver = sum/((lianxu_S_back1 - lianxu_S_front1)+(lianxu_S_back2 - lianxu_S_front2)); 
err = 80 - aver;
if(err>=70||err<=-70)
//d = d_xiao_S;
p = p_xiao_S;
return;
}