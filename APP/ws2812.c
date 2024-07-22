/*
 * ws2812.c
 *
 *  Created on: 2024��7��16��
 *      Author: hp
 */

#include "CH59x_common.h"
#include "ws2812.h"




//������
unsigned char buf[SNUM][3]={
0
};

//������
 unsigned char buf1[SNUM1][3]={
0
};

//������
 unsigned char buf2[SNUM2][3]={
0
};


 int numberone= 0;
 int numbertwo= 0;
 int numberthree= 0;
 int ione = 0;
 int itwo =0;
 int ithree =0;

 char segments[2][4][5];


//��0��
void Set0Code(void) {
    GPIOB_SetBits(GPIO_Pin_7);
    __nop();
    __nop();
    GPIOB_ResetBits(GPIO_Pin_7);
    //       NOP();
}

//��0��
void Set0Code1(void) {
    GPIOB_SetBits(GPIO_Pin_6);
    __nop();
    __nop();
    GPIOB_ResetBits(GPIO_Pin_6);
    //       NOP();
}

//��0��
void Set0Code2(void) {
    GPIOB_SetBits(GPIO_Pin_4);
    __nop();
    __nop();
    GPIOB_ResetBits(GPIO_Pin_4);
    //       NOP();
}
//��1��
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


//��1��
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

//��1��
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

//��һ������
void SendOnePix(unsigned char *ptr) {
    unsigned char i, j;
    unsigned char temp;

    for (j = 0; j < 3; j++) {
        temp = ptr[j];
        for (i = 0; i < 8; i++) {
            if (temp & 0x80)        //�Ӹ�λ��ʼ����
                    {
                Set1Code();
            } else                //���͡�0����
            {
                Set0Code();
            }
            temp = (temp << 1);      //����λ
        }
    }
}


void SendOnePix1(unsigned char *ptr1) {
    unsigned char i1, j1;
    unsigned char temp1;

    for (j1 = 0; j1 < 3; j1++) {
        temp1 = ptr1[j1];
        for (i1 = 0; i1 < 8; i1++) {
            if (temp1 & 0x80)        //�Ӹ�λ��ʼ����
                    {
                Set1Code1();
            } else                //���͡�0����
            {
                Set0Code1();
            }
            temp1 = (temp1 << 1);      //����λ
        }
    }
}

void SendOnePix2(unsigned char *ptr2) {
    unsigned char i2, j2;
    unsigned char temp2;

    for (j2 = 0; j2 < 3; j2++) {
        temp2 = ptr2[j2];
        for (i2 = 0; i2 < 8; i2++) {
            if (temp2 & 0x80)        //�Ӹ�λ��ʼ����
                    {
                Set1Code2();
            } else                //���͡�0����
            {
                Set0Code2();
            }
            temp2 = (temp2 << 1);      //����λ
        }
    }
}
//��һ֡����
void SendOneFrame(unsigned char *ptr) {
    uint16_t k;

    //  PWM_RGB=0;//����֡��λ�ź�
    //  DelayMs(1);

    for (k = 0; k < SNUM; k++)              //����һ֡���ݣ�SNUM�ǰ���LED�ĸ���
            {
        SendOnePix(&ptr[(3 * k)]);
    }

    GPIOB_ResetBits(GPIO_Pin_7);              //����֡��λ�ź�

}


//��һ֡����
void SendOneFrame1(unsigned char *ptr1) {
    uint16_t k1;

    //  PWM_RGB=0;//����֡��λ�ź�
    //  DelayMs(1);

    for (k1 = 0; k1 < SNUM1; k1++)              //����һ֡���ݣ�SNUM�ǰ���LED�ĸ���
            {
        SendOnePix1(&ptr1[(3 * k1)]);
    }

    GPIOB_ResetBits(GPIO_Pin_6);              //����֡��λ�ź�

}


//��һ֡����
void SendOneFrame2(unsigned char *ptr2) {
    uint16_t k2;

    //  PWM_RGB=0;//����֡��λ�ź�
    //  DelayMs(1);

    for (k2 = 0; k2 < SNUM2; k2++)              //����һ֡���ݣ�SNUM�ǰ���LED�ĸ���
            {
        SendOnePix2(&ptr2[(3 * k2)]);
    }

    GPIOB_ResetBits(GPIO_Pin_4);              //����֡��λ�ź�

}





void chuli_proc(char message[])
{
    int length = strlen(message);  // �����ַ�������
    int result = length / 13;   // ���㳤�ȳ���13����
    int b=result+1;

    for(int a=1;a<b;a=a+1)
    {

    strncpy(segments[a-1][0], message+13*(a-1), 4);
    segments[a-1][0][5] = '\0'; // Null-terminate the string

        strncpy( segments[a-1][1], message + 4+13*(a-1), 3);
        segments[a-1][1][4]= '\0';

        strncpy(segments[a-1][2], message + 7+13*(a-1), 3);
        segments[a-1][2][4] = '\0';

        strncpy( segments[a-1][3], message + 10+13*(a-1), 3);
        segments[a-1][3][4] = '\0';

        while (segments[a-1][1][ione] != '\0') {
            // ���ַ�ת��Ϊ��Ӧ�����ֲ��ۼӵ������
            numberone = numberone * 10 + (segments[a-1][1][ione] - '0');
            ione++;
        }

        while (segments[a-1][2][itwo] != '\0') {
            // ���ַ�ת��Ϊ��Ӧ�����ֲ��ۼӵ������
            numbertwo = numbertwo * 10 + (segments[a-1][2][itwo] - '0');
            itwo++;
        }

        while (segments[a-1][3][ithree] != '\0') {
            // ���ַ�ת��Ϊ��Ӧ�����ֲ��ۼӵ������
            numberthree = numberthree * 10 + (segments[a-1][3][ithree] - '0');
            ithree++;
        }


        if(strcmp(segments[a-1][0], "0101") == 0)
               {
                                   buf[0][0]=numberone;
                                   buf[0][1]=numbertwo;
                                   buf[0][2]=numberthree;

                                   SendOneFrame(buf);

               }

        if(strcmp(segments[a-1][0], "0102") == 0)
                       {
                                           buf[1][0]=numberone;
                                           buf[1][1]=numbertwo;
                                           buf[1][2]=numberthree;

                                           SendOneFrame(buf);

                       }

        if(strcmp(segments[a-1][0], "0103") == 0)
                               {
                                                   buf[2][0]=numberone;
                                                   buf[2][1]=numbertwo;
                                                   buf[2][2]=numberthree;

                                                   SendOneFrame(buf);

                               }

        if(strcmp(segments[a-1][0], "0201") == 0)
                       {
                                           buf1[0][0]=numberone;
                                           buf1[0][1]=numbertwo;
                                           buf1[0][2]=numberthree;

                                           SendOneFrame1(buf1);

                       }
        if(strcmp(segments[a-1][0], "0202") == 0)
                              {
                                                  buf1[1][0]=numberone;
                                                  buf1[1][1]=numbertwo;
                                                  buf1[1][2]=numberthree;

                                                  SendOneFrame1(buf1);

                              }
        if(strcmp(segments[a-1][0], "0203") == 0)
                              {
                                                  buf1[2][0]=numberone;
                                                  buf1[2][1]=numbertwo;
                                                  buf1[2][2]=numberthree;

                                                  SendOneFrame1(buf1);

                              }

        if(strcmp(segments[a-1][0], "0301") == 0)
                               {
                                                   buf2[0][0]=numberone;
                                                   buf2[0][1]=numbertwo;
                                                   buf2[0][2]=numberthree;

                                                   SendOneFrame2(buf2);

                               }
        if(strcmp(segments[a-1][0], "0302") == 0)
                                       {
                                                           buf2[1][0]=numberone;
                                                           buf2[1][1]=numbertwo;
                                                           buf2[1][2]=numberthree;

                                                           SendOneFrame2(buf2);

                                       }

        if(strcmp(segments[a-1][0], "0303") == 0)
                                       {
                                                           buf2[2][0]=numberone;
                                                           buf2[2][1]=numbertwo;
                                                           buf2[2][2]=numberthree;

                                                           SendOneFrame2(buf2);

                                       }
    }

                                       numberone=0;
                                       numbertwo=0;
                                       numberthree=0;

}


