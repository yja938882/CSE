#include "serial.h"
#include "vh_cpu_hal.h"
#include "vh_variant_hal.h"
#include "vh_io_hal.h"
#include "dd.h"
#include "printk.h"

void vh_serial_interrupt_handler(void);

char getc(void)
{
	char c;
	unsigned long rxstat;

	while(!vh_SERIAL_CHAR_READY());

	c = vh_SERIAL_READ_CHAR();
	rxstat = vh_SERIAL_READ_STATUS();
/*
	while(pop_idx == push_idx){
	}
	c = serial_buff[pop_idx++];
*/	
	return c;
}

void putc(char c)
{
	vh_SERIAL_PUTC(c);
}

int tstc()
{
	return vh_SERIAL_CHAR_READY();
}

void vh_serial_init(void)
{
	
	int i;

	// UART 1 Setting
	vh_ULCON = 0x03;
	vh_UCON = 0x245;
	vh_UFCON = 0xc7;
	vh_UINTM1 = 0x0E;
	vh_UINTP1 = 0x1f;




	// UART 1 GPIO setting
	vh_GPA0CON = vh_vSERIAL_CON;
	vh_GPA0PUD = vh_vSERIAL_PUD;	




	push_idx = 0;
	pop_idx = 0;
	for(i=0;i<SERIAL_BUFF_SIZE;i++)	serial_buff[i] = '\0';


	
}

void vh_serial_irq_enable(void)
{
	/* enable UART1 Interrupt */
}

void vk_serial_push(void)
{
	char c;
	int i=0;
	c = vh_URXH1;
	if(push_idx == SERIAL_BUFF_SIZE){	// buffer is full
		push_idx = 0;
	}
	serial_buff[push_idx++] = c;
}

void vh_serial_interrupt_handler(void)
{
	vk_serial_push();

}

