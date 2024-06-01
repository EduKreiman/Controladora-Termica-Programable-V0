void wdt_delay(unsigned long msec) {// delay to reset the WDT
                                                  wdt_reset();
                                            while(msec > 1000) {// es posible también ajustar el '1000' if you WDT is shorter
                                                  wdt_reset();
                                                  delay(1000);// es posible también ajustar el '1000' if you WDT is shorter
                                                  msec -= 1000;
                            //Serial.print("en wdt delayFree=");Serial.println(freeMemory()); // 
                                                  Serial.print("milisegundos=");Serial.println(msec); // msec
                                                }
                                          delay(msec);
                                          wdt_reset();
                                      }

//para recargar la placa, solo tienes que retrasar > WDT
//otra opción es poner el WDT muy corto, y hacer un delay() corto
void wdt_reload() {
                      delay(8001);
                 }


	void software_Reboot()	{	// esta funcion resetea el arduino y se llama cada 2 horas  para evitar bloqueos.	
        wdt_enable(WDTO_15MS);//15 milisegundos y hace el reset 			10-07-2022
              while(1){	}		
		}			





