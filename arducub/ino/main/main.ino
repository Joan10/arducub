/*
 * EEPROM Read
 *
 * Reads the value of each byte of the EEPROM and prints it 
 * to the computer.
 * This example code is in the public domain.
 */

#include <EEPROM.h>
#include "/home/joan/Escriptori/arducub/arducub/basic3d.h"

#define V_ESTRELLA {{20,0,0},{10,20,0},{30,20,0},{0,10,20},{40,10,20}}
t_aresta a_estrella[5] = {   {0,1} ,
			{0,2} , 
			{1,4} ,
			{3,2} ,
			{3,4}
		    };
t_vertex v_estrella[5] = V_ESTRELLA;
// start reading from the first byte (address 0) of the EEPROM
int address = 0;
byte value;
void setup(){
  // initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
    Objecte3d cub1,cub2,estrella;
    
    	LcdInitialise();
	LcdClear();


	estrella.Objecte3d::Crea(v_estrella, a_estrella, sizeof(v_estrella)/sizeof(t_vertex), sizeof(a_estrella)/sizeof(t_aresta));
	estrella.Objecte3d::Pinta(0);

}

void loop(){
  // read a byte from the current address of the EEPROM
  value = EEPROM.read(address);
  
  Serial.print(address);
  Serial.print("\t");
  Serial.print(value, DEC);
  Serial.println();
  
  // advance to the next address of the EEPROM
  address = address + 1;
  
  // there are only 512 bytes of EEPROM, from 0 to 511, so if we're
  // on address 512, wrap around to address 0
  if (address == 512)
    address = 0;
    
  delay(500);
}
