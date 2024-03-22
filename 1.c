�/*�����*/
#include<reg51.h>
unsigned char code table[10]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};		//��������ܵı����� 0123456789��P2���ƣ�
//unsigned char num[8]={0xfe,0xc0,0xf8,0xf0,0xe0,0xc0,0x80,0x00};						//������ϵİ˸�λ1111 1110 ��0000 0000��P0���ƣ�

unsigned char ms=0;
unsigned char s=0;
unsigned char	min=0;
unsigned char hour=0;



void inter()interrupt 1		//�жϷ���
{
	TH0=(65536-5000)/256;
	TL0=(65536-5000)%256;
	
	ms++;
	if(ms==100){
		ms=0;
		s++;
		if(s==60){
			s=0;
			min++;
			if(min==60){
				min=0;
				hour++;
				if(hour==24){
					hour=0;
				}
			}
		}
	}
	
	
}


void delay()			//�ӳ�
{
	unsigned int i,j;
	for(i=0;i<5;i++)
		for(j=0;j<120;j++);
	
}


/*P0=0x00;����ܱ��� 0000 0000=8 (�������͵�ƽ��)
	P2=0xff;����ܵ�ַλ 1111 1111 ��ȫ����

	***��ϸ��������ϵĵ�ַλ��12345678 ����Ӧ��P2�ӿ�Ϊ��01234567
	���������ۼ�ʱ�䣬����P2��0-7�ڶ�Ӧʱ��Ϊ��ms��s��min��hour��
*/
void display(unsigned char num)
{
	P2=0x80;	//�����λ 1000 0000
	P0=table[ms%10];
	delay();
	P2=0x40;	//�����λ 0100 0000
	P0=table[ms/10];
	delay();
	P2=0x20;	//���λ 0010 0000
	P0=table[s%10];
	delay();
	P2=0x10;	//���λ 0001 0000
	P0=table[s/10];
	delay();
	P2=0x08;	//���ӵ�λ 0000 1000
	P0=table[min%10];
	delay();
	P2=0x04;	//���Ӹ�λ 0000 0100
	P0=table[min/10];
	delay();
	P2=0x02;//Сʱ��λ 0000 0010
	P0=table[hour%10];
	delay();
	P2=0x01;//Сʱ��λ 0000 0001
	P0=table[hour/10];
	delay();
	
}

void main ()
{
	TH0=(65536-5000)/256;
	TL0=(65536-5000)%256;
	TMOD=0x01;		//	��ʽ1
	EA=1;						//	�жϴ�
	ET0=1;
	TR0=1;				
	
	while(1)
	{
		display();
	
	}
}