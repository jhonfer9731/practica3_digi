
#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */

#define CR   0x0D

// Prototipos de funciones
void SCI_Init(void);
void SCI_PutChar(byte);
void SCI_PutMsg(const byte *);
byte SCI_GetChar(void);

const byte Msg[] = "Bienvenido al curso de ElectrOnica Digital III\n\n\r";
byte response = 0;	

void main(void) {
   	SOPT1 = 0x20;
	SCI_Init();
	
	PTBDD_PTBDD7 = 1;
	PTBD_PTBD7 = 0;
		
	for(;;) {
	
		SCI_PutChar(CR);
		SCI_PutMsg(Msg);
		SCI_PutMsg("InformaciOn: No. estudiantes, Tipo de curso, Nivel. Digite (n/t/s): ");
		response = SCI_GetChar();
		SCI_PutChar(response);
		switch(response) {
		  case 'n': 
			SCI_PutMsg("\n\r\n\rTiene 38 estudiantes!!! \n\r\n\r");
			break;
		  case 't':
			SCI_PutMsg("\n\r\n\rCurso regular obligatorio!!! \n\r\n\r");
			break;
		  case 's':
			SCI_PutMsg("\n\r\n\rCurso de octavo semestre!!! \n\r\n\r");
			break;
          default:
			SCI_PutMsg("\n\r\n\rPregunta incorrecta.Por favor repita pregunta !!\n\r\n\r");
			break;
		}
	}
}
	
void SCI_Init(void) {
	
	// Se procede a hacer las pruebas con el reloj interno de 8 Mhz ya que es el unico disponible en simulación
  SCI2BDL = 52; // SCI Baud rate = BusClock/16*[SBR12:SBR0] ---> 12Mhz/(16*78) = 9600 bps
  SCI2C2 = (SCI2C2_TE_MASK | SCI2C2_RE_MASK); //Masks defined by mcs908jm60.h
  /* By default M=0 inside(SCIxC1) --> Normal -- Start + 8bits (LSB first) + Stop
  PE Parity Enable 0 --> No hardware parity generation or checking
  PT  Parity Type 0 Even parity */
}

void SCI_PutChar(byte Data) {
  while(SCI2S1_TDRE == 0);
  SCI2D = Data;
}

byte SCI_GetChar(void) {
  while(SCI2S1_RDRF == 0);
  return SCI2D;// The RDRF flag is cleared at end of execution. Why?
}

void SCI_PutMsg(const byte * Data) {
  while(*Data != '\0') {
	SCI_PutChar(*Data++);
  }
}



