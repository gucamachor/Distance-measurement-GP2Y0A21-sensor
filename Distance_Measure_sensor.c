///////////////////////////////////////////////////////////////////////////////
// TÍTULO:  Práctica 7 - Sensor de medición de distancia óptico.             //
//                                                                           //
// PROYECTO: Instrumentar un sistema de medición de distancia óptico,        // 
//           utilizando un diodo IR y un fototransistor (fotodiodo).         //
//                                                                           //
// AUTOR: Camacho Rodríguez, Gerardo U                                       //
// COMPILADOR:  CCS C COMPILER                                               //
// MICROCONTROLADOR: PIC16F887                                               //
// OSCILADOR: 4 MHz                                                          //
//////////////////////////////////  DIRECTIVAS  ///////////////////////////////

//Generales.
#INCLUDE <16F887.H>                                // Incluye fichero del MCU PIC16F887
#DEVICE ADC = 10
#USE DELAY(CLOCK = 4000000)                        // Define la Frecuencia del oscilador de PIC(4MHz)
#define LCD_DATA_PORT getenv("SFR:PORTD")
#INCLUDE <LCD.C>                                   // Incluye librería LCD
#include <math.h>                                  // Incluye librería LCD
#FUSES XT,NOPROTECT,NOWDT,NOBROWNOUT,PUT           // Define las palabras de configuración del PIC

// LCD pinmap
// RD0 = E
// RD1 = RS
// RD2 = RW
// RD4 = d4
// RD5 = D5
// RD6 = D6
// RD7 = D7

// Registros.
//#use standard_io(a)
//#use standard_io(b)
#byte porta = 0x05                                 // Puerto A
#byte trisa = 0x85                                 // Dirección (E/S) del puerto A
//#byte portb = 0x06                               // Puerto B
//#byte trisb = 0x86                               // Dirección (E/S) del puerto B

// Variable globales.
float AD1;
float Vo1;
float d;
float val_adc;

/////////////////////  PROTOTIPOS DE FUNCIONES Y TAREAS ///////////////////////

/////////////////////////////  FUNCIÓN PRINCIPAL   ////////////////////////////

void MAIN() {                                      // Inicia el programa principal
   
   LCD_INIT();  // Inicia la libRería LCD 16x2
   LCD_GOTOXY(1,1);
   printf(LCD_PUTC, "\fReady...");
   delay_ms(1000);
   LCD_GOTOXY(6,1);
   printf(LCD_PUTC, "\fMedicion.");
   delay_ms(1000);
   
   // Configura los Puertos del PIC
   //set_tris_a(0b111111111);                      // Fija PIN A0 y PIN A1 como entradas 
   
   // Configura la Entrada Analoga
   setup_adc(ADC_CLOCK_INTERNAL);                  // Configura el ADC en modo Oscilador interno
   setup_adc_ports(sAN0);                          // Configura los puertos de lecturas analógicas
   set_adc_channel(0);                             // Configura el PIN A0 como canal de entrada
   delay_us(20);
   
   LCD_PUTC("\f");                                 // Borra el contenido del LCD
   while(TRUE) {                                   // Inicia el bucle do ... While infinito
       set_adc_channel(0);                         // Configura el PIN A0 como canal de entrada
       AD1 = read_adc();                           // Lee el valor digital del canal 0 y almacena en la variable "AD1"
       //Vo1 = AD1 * 0.0050803;                    // Conversión de bits
       d = -0.000002*pow(AD1,3)+0.0019*pow(AD1,2)-0.62*AD1+83.703; // Ecuación de 3er grado
       //d = 11800.1*pow(AD1,-1.27);               // Ecuación exponencial
        
       LCD_GOTOXY(1,1);                            // Ubica en la columna 1 fila 1
       printf(LCD_PUTC,"Vo: %0.2f V ", AD1);       // Muestra el valor de la lectura de ADC
       LCD_GOTOXY(1,2);                            // Ubica en la columna 3 fila 2
       printf(LCD_PUTC,"d: %0.2f cm ", d);         // Muestra el valor de la distancia
       delay_ms(600);                              // Retraso 0.6 s para mostrar el texto         
      }//Cierra while true
   }    
