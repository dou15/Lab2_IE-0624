#include <avr/io.h>
#include <util/delay.h>

#define INTERRUPT_BOTTON1 PD2 //INT0, PIN PD2 
#define INTERRUPT_BOTTON2 PD3 //INT1, PIN PD3

//LEDs semaforos
#define LDPV  PB1 //paso vehiculos
#define LDVD  PB0 //vehiculos detenidos
#define LDPP1 PB3 //paso peatones 1
#define LDPD1 PB2 //peatones detenidos 1
#define LDPP2 PB5 //paso peatones 2
#define LDPD2 PB4 //peatones detenidos 2

int estado                      = 0; // Estado por defecto
int PasoVehiculos               = 0;
int TransicionVehiculosPeatones = 1;
int PasoPeatones                = 2;
int TransicionPeatonesVehiculos = 3;

int toggle = 0;

/******************** Estados posibles ********************/
void estados(){
    if(estado==PasoVehiculos){
        PORTB |=  (1 << LDPV);
        PORTB &= ~(1 << LDVD);
        PORTB &= ~(1 << LDPP1);
        PORTB |=  (1 << LDPD1);
        PORTB &= ~(1 << LDPP2);
        PORTB |=  (1 << LDPD2);
    }
    if(estado==TransicionVehiculosPeatones){        
        if(toggle==0){
        PORTB |=  (1 << LDPV);
        PORTB &= ~(1 << LDVD);
        PORTB &= ~(1 << LDPP1);
        PORTB |=  (1 << LDPD1);
        PORTB &= ~(1 << LDPP2);
        PORTB |=  (1 << LDPD2);
        toggle =   1;
        }
        else{
        PORTB &= ~(1 << LDPV);
        PORTB |=  (1 << LDVD);
        PORTB &= ~(1 << LDPP1);
        PORTB |=  (1 << LDPD1);
        PORTB &= ~(1 << LDPP2);
        PORTB |=  (1 << LDPD2);
        toggle =   0;
        }
    }
    if(estado==PasoPeatones){
        PORTB &= ~(1 << LDPV);
        PORTB |=  (1 << LDVD);
        PORTB |=  (1 << LDPP1);
        PORTB &= ~(1 << LDPD1);
        PORTB |=  (1 << LDPP2);
        PORTB &= ~(1 << LDPD2);
    }
    if(estado==TransicionPeatonesVehiculos){
        if(toggle==0){
        PORTB &= ~(1 << LDPV);
        PORTB |=  (1 << LDVD);
        PORTB |=  (1 << LDPP1);
        PORTB &= ~(1 << LDPD1);
        PORTB |=  (1 << LDPP2);
        PORTB &= ~(1 << LDPD2);
        toggle =   1;
        }
        else{
        PORTB &= ~(1 << LDPV);
        PORTB |=  (1 << LDVD);
        PORTB &= ~(1 << LDPP1);
        PORTB |=  (1 << LDPD1);
        PORTB &= ~(1 << LDPP2);
        PORTB |=  (1 << LDPD2);
        toggle =   0;
        }
    }
}

int main(void)
{
   DDRB = 0x3f; //PB0 a PB5 como salidas
   DDRD = 0xc;  //PD2 y PD3 como entradas

  //Algo
  while (1) {
      
      estados();
      if (PIND & (1 << INTERRUPT_BOTTON1) || PIND & (1 << INTERRUPT_BOTTON2)){
          if(estado == PasoVehiculos){
              estado = PasoVehiculos;
          }
          if(estado == TransicionVehiculosPeatones){
              estado = PasoPeatones;
          }
          if(estado == PasoPeatones){
              estado = TransicionPeatonesVehiculos;
          }
          if(estado == TransicionPeatonesVehiculos){
              estado = PasoVehiculos;
          }
      }
      else{
          if(estado == PasoVehiculos){
              estado = TransicionVehiculosPeatones;
      }
     
     }
  }
}
