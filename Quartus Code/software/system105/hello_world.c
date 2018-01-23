#define RS232_Control (*(volatile unsigned char *)(0x84000200))
#define RS232_Status (*(volatile unsigned char *)(0x84000200))
#define RS232_TxData (*(volatile unsigned char *)(0x84000202))
#define RS232_RxData (*(volatile unsigned char *)(0x84000202))
#define RS232_Baud (*(volatile unsigned char *)(0x84000204))

// RS232_Control = 0x55;
// RS232_Baud = 0x01;

/* Subroutine to initialise the RS232 Port by writing some data
** to the internal registers.
** Call this function at the start of the program before you attempt
** to read or write to data via the RS232 port
**
** Refer to 6850 data sheet for details of registers and
***************************************************************************/
void Init_RS232(void)
{
 // set up 6850 Control Register to utilise a divide by 16 clock,
 // set RTS low, use 8 bits of data, no parity, 1 stop bit,
 // transmitter interrupt disabled
 // program baud rate generator to use 115k baud

 //Clock (0 - 1) : 1
 //Mode (2 - 4) : 6
 //Transmit interrupt and RTS (5-6) : 0
	RS232_Control = 0x15;
	RS232_Baud = 0x01;
}









int putcharRS232(int c)
{
// poll Tx bit in 6850 status register. Wait for it to become '1'

	while(RS232_TxData & 0x02 != 0x02){

	}

// write 'c' to the 6850 TxData register to output the character
	RS232_TxData = c;
    return c ; // return c
}
int getcharRS232( void )
{
 // poll Rx bit in 6850 status register. Wait for it to become '1'
 // read received character from 6850 RxData register.

	while( !((RS232_Status & 0x1) == 0x1) ){

	}
	return RS232_RxData;
}
// the following function polls the 6850 to determine if any character
// has been received. It doesn't wait for one, or read it, it simply tests
// to see if one is available to read
int RS232TestForReceivedData(void)
{
 // Test Rx bit in 6850 serial comms chip status register
 // if RX bit is set, return TRUE, otherwise return FALSE
	if (RS232_Status & 0x1)
		return 1;
	else
		return 0;
}

int main (void){
	Init_RS232();
	printf("Initializing...\n");

	putcharRS232(1);
	printf("Input into Nios II...\n");

	int status = RS232TestForReceivedData();
	printf("Status is %d\n", status);

	int receive = getcharRS232();
	printf("Receiving...\n");

	while(1){
		receive = getcharRS232();
		printf("%c\n", (char)receive);
	}
}
