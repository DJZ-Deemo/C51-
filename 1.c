£/*ÒÑÀí½â*/
#include<reg51.h>
unsigned char code table[10]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};		//¹²ÑôÊıÂë¹ÜµÄ±àÂë×é 0123456789£¨P2¿ØÖÆ£©
//unsigned char num[8]={0xfe,0xc0,0xf8,0xf0,0xe0,0xc0,0x80,0x00};						//ÊıÂë¹ÜÉÏµÄ°Ë¸öÎ»1111 1110 µ½0000 0000£¨P0¿ØÖÆ£©

unsigned char ms=0;
unsigned char s=0;
unsigned char	min=0;
unsigned char hour=0;



void inter()interrupt 1		//ÖĞ¶Ï·şÎñ
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


void delay()			//ÑÓ³Ù
{
	unsigned int i,j;
	for(i=0;i<5;i++)
		for(j=0;j<120;j++);
	
}


/*P0=0x00;ÊıÂë¹Ü±àÂë 0000 0000=8 (¹²Ñô£¬µÍµçÆ½ÁÁ)
	P2=0xff;ÊıÂë¹ÜµØÖ·Î» 1111 1111 £¨È«ÁÁ£©

	***×ĞÏ¸¿´ÊıÂë¹ÜÉÏµÄµØÖ·Î»£º12345678 ¶ø¶ÔÓ¦µÄP2½Ó¿ÚÎª£º01234567
	´ÓÓÒÍù×óÀÛ¼ÓÊ±¼ä£¬ËùÒÔP2µÄ0-7¿Ú¶ÔÓ¦Ê±¼äÎª£¨ms£¬s£¬min£¬hour£©
*/
void display(unsigned char num)
{
	P2=0x80;	//ºÁÃëµÍÎ» 1000 0000
	P0=table[ms%10];
	delay();
	P2=0x40;	//ºÁÃë¸ßÎ» 0100 0000
	P0=table[ms/10];
	delay();
	P2=0x20;	//ÃëµÍÎ» 0010 0000
	P0=table[s%10];
	delay();
	P2=0x10;	//Ãë¸ßÎ» 0001 0000
	P0=table[s/10];
	delay();
	P2=0x08;	//·ÖÖÓµÍÎ» 0000 1000
	P0=table[min%10];
	delay();
	P2=0x04;	//·ÖÖÓ¸ßÎ» 0000 0100
	P0=table[min/10];
	delay();
	P2=0x02;//Ğ¡Ê±µÍÎ» 0000 0010
	P0=table[hour%10];
	delay();
	P2=0x01;//Ğ¡Ê±µÍÎ» 0000 0001
	P0=table[hour/10];
	delay();
	
}

void main ()
{
	TH0=(65536-5000)/256;
	TL0=(65536-5000)%256;
	TMOD=0x01;		//	·½Ê½1
	EA=1;						//	ÖĞ¶Ï´ò¿ª
	ET0=1;
	TR0=1;				
	
	while(1)
	{
		display();
	
	}
}