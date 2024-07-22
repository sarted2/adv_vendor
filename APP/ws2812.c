/*
 * ws2812.c
 *
 *  Created on: 2024年7月16日
 *      Author: hp
 */

#include "CH59x_common.h"
#include "ws2812.h"




//缓存区
unsigned char buf[SNUM][3]={
0
};

//缓存区
 unsigned char buf1[SNUM1][3]={
0
};

//缓存区
 unsigned char buf2[SNUM2][3]={
0
};




       char part1[5];
       char part2[4];
       char part3[4];
       char part4[4];


//发0码
void Set0Code(void) {
    GPIOB_SetBits(GPIO_Pin_7);
    __nop();
    __nop();
    GPIOB_ResetBits(GPIO_Pin_7);
    //       NOP();
}

//发0码
void Set0Code1(void) {
    GPIOB_SetBits(GPIO_Pin_6);
    __nop();
    __nop();
    GPIOB_ResetBits(GPIO_Pin_6);
    //       NOP();
}

//发0码
void Set0Code2(void) {
    GPIOB_SetBits(GPIO_Pin_4);
    __nop();
    __nop();
    GPIOB_ResetBits(GPIO_Pin_4);
    //       NOP();
}
//发1码
void Set1Code(void) {
    GPIOB_SetBits(GPIO_Pin_7);
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    GPIOB_ResetBits(GPIO_Pin_7);
}


//发1码
void Set1Code1(void) {
    GPIOB_SetBits(GPIO_Pin_6);
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    GPIOB_ResetBits(GPIO_Pin_6);
}

//发1码
void Set1Code2(void) {
    GPIOB_SetBits(GPIO_Pin_4);
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    __nop();
    GPIOB_ResetBits(GPIO_Pin_4);
}

//发一个像素
void SendOnePix(unsigned char *ptr) {
    unsigned char i, j;
    unsigned char temp;

    for (j = 0; j < 3; j++) {
        temp = ptr[j];
        for (i = 0; i < 8; i++) {
            if (temp & 0x80)        //从高位开始发送
                    {
                Set1Code();
            } else                //发送“0”码
            {
                Set0Code();
            }
            temp = (temp << 1);      //左移位
        }
    }
}


void SendOnePix1(unsigned char *ptr1) {
    unsigned char i1, j1;
    unsigned char temp1;

    for (j1 = 0; j1 < 3; j1++) {
        temp1 = ptr1[j1];
        for (i1 = 0; i1 < 8; i1++) {
            if (temp1 & 0x80)        //从高位开始发送
                    {
                Set1Code1();
            } else                //发送“0”码
            {
                Set0Code1();
            }
            temp1 = (temp1 << 1);      //左移位
        }
    }
}

void SendOnePix2(unsigned char *ptr2) {
    unsigned char i2, j2;
    unsigned char temp2;

    for (j2 = 0; j2 < 3; j2++) {
        temp2 = ptr2[j2];
        for (i2 = 0; i2 < 8; i2++) {
            if (temp2 & 0x80)        //从高位开始发送
                    {
                Set1Code2();
            } else                //发送“0”码
            {
                Set0Code2();
            }
            temp2 = (temp2 << 1);      //左移位
        }
    }
}
//发一帧数据
void SendOneFrame(unsigned char *ptr) {
    uint16_t k;

    //  PWM_RGB=0;//发送帧复位信号
    //  DelayMs(1);

    for (k = 0; k < SNUM; k++)              //发送一帧数据，SNUM是板子LED的个数
            {
        SendOnePix(&ptr[(3 * k)]);
    }

    GPIOB_ResetBits(GPIO_Pin_7);              //发送帧复位信号

}


//发一帧数据
void SendOneFrame1(unsigned char *ptr1) {
    uint16_t k1;

    //  PWM_RGB=0;//发送帧复位信号
    //  DelayMs(1);

    for (k1 = 0; k1 < SNUM1; k1++)              //发送一帧数据，SNUM是板子LED的个数
            {
        SendOnePix1(&ptr1[(3 * k1)]);
    }

    GPIOB_ResetBits(GPIO_Pin_6);              //发送帧复位信号

}


//发一帧数据
void SendOneFrame2(unsigned char *ptr2) {
    uint16_t k2;

    //  PWM_RGB=0;//发送帧复位信号
    //  DelayMs(1);

    for (k2 = 0; k2 < SNUM2; k2++)              //发送一帧数据，SNUM是板子LED的个数
            {
        SendOnePix2(&ptr2[(3 * k2)]);
    }

    GPIOB_ResetBits(GPIO_Pin_4);              //发送帧复位信号

}





void chuli_proc(char message[])
{

    int numberone= 0;
    int numbertwo= 0;
    int numberthree= 0;
    int ione = 0;
    int itwo =0;
    int ithree =0;




        strncpy(part1, message, 4);
        part1[4] = '\0';

        strncpy( part2, message + 4, 3);
        part2[3]= '\0';

        strncpy(part3, message + 7, 3);
        part3[3] = '\0';

        strncpy( part4, message + 10, 3);
        part4[3] = '\0';

        while (part2[ione] != '\0') {
                                // 将字符转换为对应的数字并累加到结果中
                                numberone = numberone * 10 + (part2[ione] - '0');
                                ione++;
                            }

                            while (part3[itwo] != '\0') {
                                // 将字符转换为对应的数字并累加到结果中
                                numbertwo = numbertwo * 10 + (part3[itwo] - '0');
                                itwo++;
                            }

                            while (part4[ithree] != '\0') {
                                // 将字符转换为对应的数字并累加到结果中
                                numberthree = numberthree * 10 + (part4[ithree] - '0');
                                ithree++;
                            }

        if(strcmp(part1, "0101") == 0)
               {


                                   buf[0][0]=numberone;
                                   buf[0][1]=numbertwo;
                                   buf[0][2]=numberthree;

                                   SendOneFrame((unsigned char *)buf);


               }
        else if(strcmp(part1, "0102") == 0)
                       {



                                           buf[1][0]=numberone;
                                           buf[1][1]=numbertwo;
                                           buf[1][2]=numberthree;

                                           SendOneFrame((unsigned char *)buf);

                       }
        else if(strcmp(part1, "0103") == 0)
                               {



                                                   buf[2][0]=numberone;
                                                   buf[2][1]=numbertwo;
                                                   buf[2][2]=numberthree;

                                                   SendOneFrame((unsigned char *)buf);

                               }
        else if(strcmp(part1, "0201") == 0)
                                       {



                                                           buf1[0][0]=numberone;
                                                           buf1[0][1]=numbertwo;
                                                           buf1[0][2]=numberthree;

                                                           SendOneFrame1((unsigned char *)buf1);

                                       }
        else if(strcmp(part1, "0202") == 0)
                                              {



                                                                  buf1[1][0]=numberone;
                                                                  buf1[1][1]=numbertwo;
                                                                  buf1[1][2]=numberthree;

                                                                  SendOneFrame1((unsigned char *)buf1);

                                              }
        else if(strcmp(part1, "0203") == 0)
                                              {



                                                                  buf1[2][0]=numberone;
                                                                  buf1[2][1]=numbertwo;
                                                                  buf1[2][2]=numberthree;

                                                                  SendOneFrame1((unsigned char *)buf1);

                                              }
        else if(strcmp(part1, "0301") == 0)
                                              {



                                                                  buf2[0][0]=numberone;
                                                                  buf2[0][1]=numbertwo;
                                                                  buf2[0][2]=numberthree;

                                                                  SendOneFrame2((unsigned char *)buf2);

                                              }
        else if(strcmp(part1, "0302") == 0)
                                                      {



                                                                          buf2[1][0]=numberone;
                                                                          buf2[1][1]=numbertwo;
                                                                          buf2[1][2]=numberthree;

                                                                          SendOneFrame2((unsigned char *)buf2);

                                                      }
        else if(strcmp(part1, "0303") == 0)
                                                      {



                                                                          buf2[2][0]=numberone;
                                                                          buf2[2][1]=numbertwo;
                                                                          buf2[2][2]=numberthree;

                                                                          SendOneFrame2((unsigned char *)buf2);

                                                      }
        else if(strcmp(part1, "0000") == 0)
                                                              {



                                                                                buf[0][0]=000;
                                                                                buf[0][1]=000;
                                                                                buf[0][2]=000;
                                                                                buf[1][0]=000;
                                                                                buf[1][1]=000;
                                                                                buf[1][2]=000;
                                                                                buf[2][0]=000;
                                                                                buf[2][1]=000;
                                                                                buf[2][2]=000;
                                                                                buf1[0][0]=000;
                                                                                buf1[0][1]=000;
                                                                                buf1[0][2]=000;
                                                                                buf1[1][0]=000;
                                                                                buf1[1][1]=000;
                                                                                buf1[1][2]=000;
                                                                                buf1[2][0]=000;
                                                                                buf1[2][1]=000;
                                                                                buf1[2][2]=000;
                                                                                buf2[0][0]=000;
                                                                                buf2[0][1]=000;
                                                                                buf2[0][2]=000;
                                                                                buf2[1][0]=000;
                                                                                buf2[1][1]=000;
                                                                                buf2[1][2]=000;
                                                                                buf2[2][0]=000;
                                                                                buf2[2][1]=000;
                                                                                buf2[2][2]=000;
                                                                                SendOneFrame((unsigned char *)buf);
                                                                                SendOneFrame1((unsigned char *)buf1);
                                                                                SendOneFrame2((unsigned char *)buf2);

                                                              }

}

void paoma_proc()
{
    for(int count=0;count<3;count++)
    {
        for(int i = 0; i < 3; i++)
                {
                    buf[i][0] = 150-50*i;
                    buf[i][1] = 60*i;
                    buf[i][2] = 100+50*i;
                    buf1[i][0] = 150-50*i;
                    buf1[i][1] = 60*i;
                    buf1[i][2] = 100+50*i;
                    buf2[i][0] = 150-50*i;
                    buf2[i][1] = 60*i;
                    buf2[i][2] = 100+50*i;
                    SendOneFrame((unsigned char *)buf);
                    SendOneFrame1((unsigned char *)buf1);
                    SendOneFrame2((unsigned char *)buf2);
                    DelayMs(125);
                    buf[i][0] = 0;
                    buf[i][1] = 0;
                    buf[i][2] = 0;
                    buf1[i][0] = 0;
                    buf1[i][1] = 0;
                    buf1[i][2] = 0;
                    buf2[i][0] = 0;
                    buf2[i][1] = 0;
                    buf2[i][2] = 0;
                }

                // 从第三个灯珠到第一个灯珠
                for(int i = 2; i >= 0; i--)
                {
                    buf[i][0] = 100+50*i;
                    buf[i][1] = 60*i;
                    buf[i][2] = 150-50*i;
                    buf1[i][0] = 100+50*i;
                    buf1[i][1] = 60*i;
                    buf1[i][2] = 150-50*i;
                    buf2[i][0] = 100+50*i;
                    buf2[i][1] = 60*i;
                    buf2[i][2] = 150-50*i;
                    SendOneFrame((unsigned char *)buf);
                    SendOneFrame1((unsigned char *)buf1);
                    SendOneFrame2((unsigned char *)buf2);
                    DelayMs(125);
                    buf[i][0] = 0;
                    buf[i][1] = 0;
                    buf[i][2] = 0;
                    buf1[i][0] = 0;
                    buf1[i][1] = 0;
                    buf1[i][2] = 0;
                    buf2[i][0] = 0;
                    buf2[i][1] = 0;
                    buf2[i][2] = 0;
                }

    }
    SendOneFrame((unsigned char *)buf);
    SendOneFrame1((unsigned char *)buf1);
    SendOneFrame2((unsigned char *)buf2);

}


