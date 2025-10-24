
#define F_CPU 16000000UL
#define BAUD 9600

#include <inttypes.h>
#include <avr/io.h>
#include <util/delay.h>  
#include <stdio.h>
#include <stdlib.h>
#include <avr/interrupt.h>


int main(void){
    TCCR1A = _BV(COM1A1) | !_BV(COM1A0)                 //  Both PWM outputs set at TOP,
                | _BV(COM1B1) | !_BV(COM1B0)            //    clear on compare match
                | !_BV(FOC1A) | !_BV(FOC1B)             //  PWM mode, can't force output
                | _BV(WGM11) | !_BV(WGM10);             //  Fast PWM, TOP = ICR1
    
    TCCR1B = !_BV(ICNC1) | !_BV(ICES1)                  //  Disable input capture noise canceler,
                                                        //    edge select to negative.
                | _BV(WGM13) | _BV(WGM12)               //  Fast PWM, TOP = ICR1
                | !_BV(CS12) | _BV(CS11) | !_BV(CS10);   //  clk(i/o) / 8


    ICR1 = 4000; //  PWM period ( 50 Hz)

    OCR1A = 2000; 

    PORTD = _BV (PD4) | _BV (PD5); // direction
    
    while (1){
	//  PWM duty cycle 2000 = 1 ms, 4000 = 2 ms 
		
		for(int i=2000;i<4000;i=i+10){
			OCR1A = i;
			
			_delay_ms(1);
		}
    }
    
    return 0;
}

