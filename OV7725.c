#include "common.h"
#include "include.h"
#include "define.h"


/*****************OV7725������ʽ*********************

 *\��ʼ----------->  \*
 *\             /    \*
 *\           /      \*
 *\         /        \*
 *\       /          \*
 *\     /            \*
 *\   /              \*
 *\  ----------> ����\*      x->�߶�H   y->���W

 *************************************************/

#define W   CAMERA_W
#define H   CAMERA_H
#define white 255
#define black 0


int centerline[CAMERA_H]={CAMERA_W/2,CAMERA_W/2,CAMERA_W/2,CAMERA_W/2,CAMERA_W/2,CAMERA_W/2,CAMERA_W/2,CAMERA_W/2,CAMERA_W/2,CAMERA_W/2,CAMERA_W/2,CAMERA_W/2,CAMERA_W/2,CAMERA_W/2,CAMERA_W/2,CAMERA_W/2,CAMERA_W/2,CAMERA_W/2,CAMERA_W/2,CAMERA_W/2,CAMERA_W/2,CAMERA_W/2,CAMERA_W/2,CAMERA_W/2,CAMERA_W/2,CAMERA_W/2,CAMERA_W/2,CAMERA_W/2,CAMERA_W/2,CAMERA_W/2,CAMERA_W/2,CAMERA_W/2,CAMERA_W/2,CAMERA_W/2,CAMERA_W/2,CAMERA_W/2,CAMERA_W/2,CAMERA_W/2,CAMERA_W/2,CAMERA_W/2,CAMERA_W/2,CAMERA_W/2,CAMERA_W/2,CAMERA_W/2,CAMERA_W/2,CAMERA_W/2,CAMERA_W/2,CAMERA_W/2,CAMERA_W/2,CAMERA_W/2,CAMERA_W/2,CAMERA_W/2,CAMERA_W/2,CAMERA_W/2,CAMERA_W/2,CAMERA_W/2,CAMERA_W/2,CAMERA_W/2,CAMERA_W/2,CAMERA_W/2};
int left_line[CAMERA_H];
int right_line[CAMERA_H];

/************���� start************/
int left_center_distance[57];
int right_center_distance[57];
/************���� finish************/




/****************���߳���****************
* �������ƣ�Centerline
* ����˵����ȡ����
* ��ע��
********************************************/
void Centerline(void)
{
    int x=0,y=0;
    
        for (x=0;x<H;x++)
       {
          img[W*x]=black;
          img[W*x+W-1]=black;
       
       }
       
    for(x=CAMERA_H-1;x>=CAMERA_H-3;x--)//��59���ѵ�58��
                                             
    {
        for(y=CAMERA_W/2;y<=CAMERA_W;y++)   //�ұ߽��һ��
        {
            /*�ڵ�59�к�58�д��м���������*/
            if(img[W*x+y]==black&&img[W*x+y-1]==white) break;
        }
        /*�õ���������λ��*/
        right_line[x]=y;
        for(y=CAMERA_W/2;y>=0;y--)   //��߽��һ��
        {
            if(img[W*x+y]==black&&img[W*x+y+1]==white) break;
        }
        /*�õ���������λ��*/
        left_line[x]=y;
        
        if(left_line[x]>W) left_line[x]=W;
        else if(left_line[x]<0) left_line[x]=0;
        if(right_line[x]>W) right_line[x]=W;
        else if(right_line[x]<0) right_line[x]=0;
        centerline[x]=(int)((left_line[x]+right_line[x])/2);
    }
    
    //img[160*57]
    for(;x>=0;x--)      //������������
    {
      /*****************�ұ߽�**************************/
        if(img[W*x+right_line[x+1]]==black)         //right
        {
            for(y=right_line[x+1];y>=0;y--)
            {
                if(img[W*x+y]==black&&img[W*x+y-1]==white) break;
            }
            right_line[x]=y;
        }
        else if(img[W*x+right_line[x+1]]==white)
        {
            for(y=right_line[x+1];y<W;y++)
            {
                if(img[W*x+y]==black&&img[W*x+y-1]==white) break;
            }
            right_line[x]=y;
        }
        /*****************��߽�**************************/
        
        if(img[W*x+left_line[x+1]]==white)         //right
        {
            for(y=left_line[x+1];y>=0;y--)
            {
                if(img[W*x+y]==white&&img[W*x+y-1]==black) break;
            }
            left_line[x]=y-1;
        }
        else if(img[W*x+left_line[x+1]]==black)
        {
            for(y=left_line[x+1];y<W;y++)
            {
                if(img[W*x+y]==white&&img[W*x+y-1]==black) break;
            }
            left_line[x]=y;
        }
                
        
        if(left_line[x]>W) left_line[x]=W;         //�޷�
        else if(left_line[x]<0) left_line[x]=0;
        if(right_line[x]>=W) right_line[x]=W;
        else if(right_line[x]<=0) right_line[x]=0;

        
        centerline[x]=(int)((left_line[x]+right_line[x])/2);
    }
}

void show_line(void)
{
    int x=0;
    for(x=0;x<H;x++)
    {
//        img[W*x+left_line[x]]=0;
//        img[W*x+right_line[x]]=0;
        img[W*x+centerline[x]]=0;
    }
}
/*!
 *  @brief      ��ֵ��ͼ���ѹ���ռ� �� ʱ�� ��ѹ��
 *  @param      dst             ͼ���ѹĿ�ĵ�ַ
 *  @param      src             ͼ���ѹԴ��ַ
 *  @param      srclen          ��ֵ��ͼ���ռ�ÿռ��С
 *  @since      v5.0            img_extract(img, imgbuff,CAMERA_SIZE);
 *  Sample usage:
 */
void imgextract(uint8 *dst, uint8 *src, uint32 srclen)
{
    uint8 colour[2] = {255, 0}; //0 �� 1 �ֱ��Ӧ����ɫ
    //ע��ɽ�������ͷ 0 ��ʾ ��ɫ��1��ʾ ��ɫ
    uint8 tmpsrc;
    while(srclen --)
    {
        tmpsrc = *src++;
        *dst++ = colour[ (tmpsrc >> 7 ) & 0x01 ];
        *dst++ = colour[ (tmpsrc >> 6 ) & 0x01 ];
        *dst++ = colour[ (tmpsrc >> 5 ) & 0x01 ];
        *dst++ = colour[ (tmpsrc >> 4 ) & 0x01 ];
        *dst++ = colour[ (tmpsrc >> 3 ) & 0x01 ];
        *dst++ = colour[ (tmpsrc >> 2 ) & 0x01 ];
        *dst++ = colour[ (tmpsrc >> 1 ) & 0x01 ];
        *dst++ = colour[ (tmpsrc >> 0 ) & 0x01 ];
    }
}
void  img_reduce(uint8 *aim,uint8 *get,uint32 length)
{
  while(length>0)
  {
    *get = 0;
    *get += ((*aim++) & 0x80) >> 0;
    *get += ((*aim++) & 0x80) >> 1;
    *get += ((*aim++) & 0x80) >> 2;
    *get += ((*aim++) & 0x80) >> 3;
    *get += ((*aim++) & 0x80) >> 4;
    *get += ((*aim++) & 0x80) >> 5;
    *get += ((*aim++) & 0x80) >> 6;
    *get += ((*aim++) & 0x80) >> 7;
    *get =~ *get;
    get++;
    length -= 8;
  }
  
}