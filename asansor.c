#include <mega32.h>
#include <delay.h>

#define MAX 4
#define DELAY 100

//start Queue
int req[MAX];
int front = 0;
int rear = -1;
int reqCount = 0;
int data;
int i;

int getFront() {
   return req[front];
}

int getRear() {
   return req[rear];
}

int isEmpty() {
    if(reqCount == 0)
        return 1;
    else
        return 0;
}

int isFull() {
    if(reqCount == MAX)
        return 1;
    else
        return 0;
}

int size() {
   return reqCount;
}       

void insert(int data) {

	if(!isFull()) {
	
		if(rear == MAX-1) {
			rear = -1;            
		}       

		req[++rear] = data;
		reqCount++;
	}
}

int removeData() {
	if(isEmpty())
		return -1;
	data = req[front++];
	
	if(front == MAX) {
		front = 0;
	}
	
   reqCount--;
   return data;  
}

int removeRear() {
	if(isEmpty())
		return -1;
	data = req[rear--];
	
   reqCount--;
   return data;  
}
//end Queue

unsigned char seven_seg[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
unsigned char V,M,LL;   //LL : level to level

interrupt [TIM0_OVF] void timer0_ovf_isr(void){
    TCNT0=220;
    M++;
    if (M==200)
		V++;
}  

    
void main(void)
{
	for(i=0; i<MAX ; i++)
		req[i] = -1;

	PORTA=0x00;
	DDRA=0xFF;

	PORTB=0x00;
	DDRB=0xF0;

	PORTC=0x00;
	DDRC=0xF0;

	PORTD=0x00;
	DDRD=0xFF;

	TCCR0=0x00;
	TCNT0=0x00;
	OCR0=0x00;

	TCCR1A=0x00;
	TCCR1B=0x00;
	TCNT1H=0x00;
	TCNT1L=0x00;
	ICR1H=0x00;
	ICR1L=0x00;
	OCR1AH=0x00;
	OCR1AL=0x00;
	OCR1BH=0x00;
	OCR1BL=0x00;
    
	ASSR=0x00;
	TCCR2=0x00;
	TCNT2=0x00;
	OCR2=0x00;

	MCUCR=0x00;
	MCUCSR=0x00;

	TIMSK=0x00;

	ACSR=0x80;
	SFIOR=0x00;

	DDRA=0x01;
      
    TCCR0=0x03;
    TCNT0=0x06;
    OCR0=0x00;
    
    TIMSK=0x01;
    
    #asm("sei")
        
	LL = 0 ;
	DDRA=0xff;
	PORTA=0x00;
	while (1){      
        if(PINC.0==1) 
			goto level0;
		if(PINC.1==1) 
			goto level1;
		if(PINC.2==1) 
			goto level2;
		if(PINC.3==1) 
			goto level3;
		   
		if(PINC.0==0 &PINC.1==0 &PINC.2==0 &PINC.3==0) {
			goto level0;
		}  
    };                                                                                                                      
       
    level0:
		V=0;
		PORTC.7 = 1;
		PORTA = seven_seg[0];
		while (1){ 
			PORTB.4 = 0;
			PORTB.5 = 0;
			PORTB.6 = 0;
            PORTB.7 = 0;
            delay_ms(DELAY); 
            if(getRear() == 1){
				LL = 01;
				removeRear();
				goto MOTOR;
			}
			if(getRear() == 2){
				LL = 02;
				removeRear();
				goto MOTOR;
			}
			if(getRear() == 3){
				LL = 03;
				removeRear();
				goto MOTOR;
			}
            if (PINB.1 == 0){ 
		        LL = 01;
				goto MOTOR;
            }
            if (PINB.2 == 0){ 
		        LL = 02;
				goto MOTOR;
            }
            if (PINB.3 == 0){ 
		        LL = 03;
				goto MOTOR;
            }
		}
        
	level1:
		V=0;
		PORTC.6 = 1;
		PORTA = seven_seg[1];
		while (1){ 
			PORTB.4 = 0;
			PORTB.5 = 0;
			PORTB.6 = 0;
            PORTB.7 = 0;
            delay_ms(DELAY);
            if(getRear() == 0){
				LL = 10;
				removeRear();
				goto MOTOR;
			}
			if(getRear() == 2){
				LL = 12;
				removeRear();
				goto MOTOR;
			}
			if(getRear() == 3){
				LL = 13;
				removeRear();
				goto MOTOR;
			} 
            if (PINB.0 == 0){ 
		        LL = 10;
				goto MOTOR;
            }
            if (PINB.2 == 0){ 
		        LL = 12;
				goto MOTOR;
            }
            if (PINB.3 == 0){ 
		        LL = 13;
				goto MOTOR;
            }
		} 
      
	level2:
		V = 0;
		PORTC.5 = 1 ;
		PORTA = seven_seg[2];
		while (1){
			PORTB.4 = 0;
			PORTB.5 = 0;
			PORTB.6 = 0;
            PORTB.7 = 0;
            delay_ms(DELAY);  
            if(getRear() == 0){
				LL = 20;
				removeRear();
				goto MOTOR;
			}
			if(getRear() == 1){
				LL = 21;
				removeRear();
				goto MOTOR;
			}
			if(getRear() == 3){
				LL = 23;
				removeRear();
				goto MOTOR;
			}
            if (PINB.0 == 0){ 
		        LL = 20;
				goto MOTOR;
            }
            if (PINB.1 == 0){ 
		        LL = 21;
				goto MOTOR;
            }
            if (PINB.3 == 0){ 
		        LL = 23;
				goto MOTOR;
            }
		}
      
	level3:
		PORTC.4 = 1;
		PORTA = seven_seg[3];
		while (1){
			PORTB.4 = 0;
			PORTB.5 = 0;
			PORTB.6 = 0;
            PORTB.7 = 0;
            delay_ms(DELAY);  
            if(getRear() == 0){
				LL = 30;
				removeRear();
				goto MOTOR;
			}
			if(getRear() == 1){
				LL = 31;
				removeRear();
				goto MOTOR;
			}
			if(getRear() == 2){
				LL = 32;
				removeRear();
				goto MOTOR;
			}
            if (PINB.2 == 0){ 
		        LL = 32;
				goto MOTOR;
            }
            if (PINB.1 == 0){ 
		        LL = 31;
				goto MOTOR;
            }
            if (PINB.0 == 0){ 
		        LL = 30;
				goto MOTOR;
            }
		}
 
	MOTOR:
		while (1){    
            PORTC.4 = 0;
			PORTC.5 = 0;
			PORTC.6 = 0;
			PORTC.7 = 0;
			M=0;
			switch(LL){  
                case 01: //level 0 to level 1
                    PORTB.5 = 1;
					while(1){
						
						PORTD.0=0;
						PORTD.3=1;
						delay_ms(DELAY);
						
						PORTD.3=0;    
						delay_ms(DELAY);
						
						if (PINB.0 == 0) 
							insert(0);
                        if (PINB.2 == 0) 
							insert(2);
						if (PINB.3 == 0)
							insert(3);
						if (PINC.1 == 1)
							goto level1;
					}
                case 02: //level 0 to level 2  
                    PORTB.6 = 1;
					while(1){
						
						PORTD.0=0;
						PORTD.3=1;
						delay_ms(DELAY*2);
						
						PORTD.3=0;    
						delay_ms(DELAY);
						
						if (PINB.0 == 0) 
							insert(0);
                        if (PINB.1 == 0) 
							insert(1);
						if (PINB.3 == 0)
							insert(3);
						if (PINC.2 == 1)
							goto level2;
					}
                case 03: //level 0 to level 3 
                    PORTB.7 = 1;
					while(1){
						
						PORTD.0=0;
						PORTD.3=1;
						delay_ms(DELAY*3);
						
						PORTD.3=0;    
						delay_ms(DELAY);
						
						if (PINB.0 == 0) 
							insert(0);
                        if (PINB.1 == 0) 
							insert(1);
						if (PINB.2 == 0)
							insert(2);
						if (PINC.3 == 1)
							goto level3;
					}
                case 10:
                    PORTB.4 = 1;
					while(1){
						
						PORTD.3=0;
						PORTD.0=1;
						delay_ms(DELAY);
                        
						PORTD.0=0;
						delay_ms(DELAY);
						
                        if (PINB.1 == 0) 
							insert(1);
						if (PINB.2 == 0) 
							insert(2);
						if (PINB.3 == 0)
							insert(3);
						if (PINC.0 == 1)
							goto level0;
					}
				case 12:
					PORTB.6 = 1;
					while(1){
						
						PORTD.0=0;
						PORTD.3=1;
						delay_ms(DELAY);
						
						PORTD.3=0;    
						delay_ms(DELAY);
						
                        if (PINB.0 == 0) 
							insert(0);
						if (PINB.1 == 0) 
							insert(1);
						if (PINB.3 == 0)
							insert(3);
						if (PINC.2 == 1)
							goto level2;
					}
				case 13: 
					PORTB.7 = 1;
					while(1){
						
						PORTD.0=0;
						PORTD.3=1;
						delay_ms(DELAY*2);
						
						PORTD.3=0;
						delay_ms(DELAY);
                        
						if (PINB.0 == 0) 
							insert(0);
						if (PINB.1 == 0) 
							insert(1);
						if (PINB.2 == 0)
							insert(2);
						if (PINC.3 == 1)
							goto level3;
					}
				case 20:          
                    PORTB.4 = 1;
					while(1){
						
						PORTD.3=0;
						PORTD.0=1;
						delay_ms(DELAY*2);
                        
						PORTD.0=0;
						delay_ms(DELAY);
						       
                        if (PINB.1 == 0) 
							insert(1);
						if (PINB.2 == 0) 
							insert(2);
						if (PINB.3 == 0)
							insert(3);
						if (PINC.0 == 1)
							goto level0;
					}
                case 21:
					PORTB.5 = 1;
					while(1){
						
						PORTD.3=0;
						PORTD.0=1;
						delay_ms(DELAY);
                        
						PORTD.0=0;
						delay_ms(DELAY);
						
                        if (PINB.0 == 0) 
							insert(0);
						if (PINB.2 == 0) 
							insert(2);
						if (PINB.3 == 0)
							insert(3);
						if (PINC.1 == 1)
							goto level1;
					}
				case 23:
					PORTB.7 = 1;
					while(1){
						
						PORTD.0=0;
						PORTD.3=1;
						delay_ms(DELAY);
						
						PORTD.3=0;
						delay_ms(DELAY);
						      
                        if (PINB.0 == 0) 
							insert(0);
						if (PINB.1 == 0) 
							insert(1);
						if (PINB.2 == 0)
							insert(2);
						if (PINC.3 == 1)
							goto level3;
					}
				case 30:  
                    PORTB.4 = 1;
					while(1){
						
						PORTD.3=0;
						PORTD.0=1;
						delay_ms(DELAY*3);

						PORTD.0=0;   
						delay_ms(DELAY);
						
						if (PINB.1 == 0) 
							insert(1);
                        if (PINB.2 == 0) 
							insert(2);
						if (PINB.3 == 0)
							insert(3);
						if (PINC.0 == 1)
							goto level0;
					}
                case 31:
					PORTB.5 = 1;
					while(1){
						
						PORTD.3=0;
						PORTD.0=1;
						delay_ms(DELAY*2);

						PORTD.0=0;   
						delay_ms(DELAY);
						         
                        if (PINB.0 == 0) 
							insert(0);
						if (PINB.2 == 0) 
							insert(2);
						if (PINB.3 == 0)
							insert(3);			
						if (PINC.1 == 1)
							goto level1;
					}
				case 32: 
					PORTB.6 = 1;
					while(1){
						
						PORTD.3=0;
						PORTD.0=1;
						delay_ms(DELAY);

						PORTD.0=0;   
						delay_ms(DELAY);
						
                        if (PINB.0 == 0) 
							insert(0);
						if (PINB.1 == 0) 
							insert(1);
						if (PINB.3 == 0)
							insert(3);
						if (PINC.2 == 1)
							goto level2;
					}
			}
		}     
}//end main