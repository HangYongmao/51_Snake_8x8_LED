//proteus������̳:proteus.5d6d.com
#include <reg51.h>
#define uchar unsigned char
#define SNAKE 20                 //��󳤶�
#define TIME 50                 //��ʾ��ʱʱ��
#define SPEED 71               //�ٶȿ���
//#define  keyenable 1
sbit keyenable=P3^6;			//����ʹ��
/*sbit keyx=P0^1;					//����
sbit keyy=P0^2;					//����	*/
//sbit up=P0^0;
sbit up=P3^3;       //down
sbit down=P3^1;
sbit right=P3^2;
sbit left=P3^4;
uchar x[SNAKE+1];
uchar y[SNAKE+1];          
uchar time,n,i,e;              //��ʱʱ�䣬��ǰ�߳���ͨ��ѭ����������ǰ�ٶ�		
char addx,addy;                //λ��ƫ����
/********************
��ʱ����
*********************/
void delay(char MS)
{
char us,usn;
while(MS!=0)
{
usn = 0;
while(usn!=0)
{
us=0xff;
while (us!=0){us--;};
usn--;
}
MS--;
}
}
/*******************************************
�ж���ײ
*******************************************/
bit knock()
{bit k;
k=0;
if(x[1]>7||y[1]>7)k=1;                             //ײǽ
for(i=2;i<n;i++)if((x[1]==x[i])&(y[1]==y[i]))k=1;  //ײ�Լ�
return k;
}
/*****************
�������Ҽ�λ����
*****************/
void turnkey()// interrupt 0 using 2  
{//up=1;
if(keyenable)
{
if(left){addy=0;if(addx!=1)addx=-1; else addx=1;}
if(right){addy=0;if(addx!=-1)addx=1; else addx=-1;}
if(up){addx=0;if(addy!=-1)addy=1; else addy=-1;}
if(down){addx=0;if(addy!=1)addy=-1; else addy=1;}
/*if(keyy)
{addy=0;                                   //����
if(keyx)if(addx==-1)addx=-1; else addx=1;  //��
else
if(addx==1)addx=1; else addx=-1;           //��
}
else
{addx=0;                                   //����
if(keyx)if(addy==1)addy=1; else addy=-1;   //��
else
if(addy==-1)addy=-1; else addy=1;          //��	  
} */
}
}
/*****************
�˷�����
*****************/
uchar mux(uchar temp) 
{
if(temp==7)return 128;
if(temp==6)return 64;
if(temp==5)return 32;
if(temp==4)return 16;
if(temp==3)return 8;
if(temp==2)return 4;
if(temp==1)return 2;
if(temp==0)return 1;
return 0;
}
/*****************
��ʾʱ�� ��ʾ����
*****************/
void timer0(uchar k)
{while(k--)
{for(i=0;i<SNAKE+1;i++)
{P2=mux(x[i]);P1=255-mux(y[i]);
turnkey();                     //�������Ҽ�λ����
delay(TIME);                   //��ʾ�ӳ�
P2=0x00;P1=0xff;
}}
} 
/*****************
������
*****************/	
void main(void)
{e=SPEED;
 P0=0x00;
 P1=0xff;
 P2=0x00;
 P3=0x00;
while(1)       
 {//if(keyenable==1){P1=0x00;P2=0xff;}else{P1=0xff;P2=0x00;}
 for(i=3;i<SNAKE+1;i++)x[i]=100;for(i=3;i<SNAKE+1;i++)y[i]=100;//��ʼ��
 x[0]=4;y[0]=4;                                                //����                            
 n=3;                                                          //�߳� n=-1
 x[1]=1;y[1]=0;                                                //��ͷ
 x[2]=0;y[2]=0;                                                //��β1
 addx=0;addy=0;                                                //λ��ƫ��
 //k=1;
 while(1){if(keyenable)break;timer0(1);}
 while(1)         
  {timer0(e);
   if(knock()){e=SPEED;break;}                          //�ж���ײ
        if((x[0]==x[1]+addx)&(y[0]==y[1]+addy))         //�Ƿ�Զ���
           {n++;
		   if(n==SNAKE+1)
		   {n=3;e=e-10;
		   for(i=3;i<SNAKE+1;i++)x[i]=100;
           for(i=3;i<SNAKE+1;i++)y[i]=100;
		   }
           x[0]=x[n-2];
           y[0]=y[n-2];
           }
    for(i=n-1;i>1;i--){x[i]=x[i-1];y[i]=y[i-1];}        
    //x[n-1]=x[2];y[n-1]=y[2];
    x[1]=x[2]+addx;y[1]=y[2]+addy;                     //�ƶ�
  }						
 }			
}