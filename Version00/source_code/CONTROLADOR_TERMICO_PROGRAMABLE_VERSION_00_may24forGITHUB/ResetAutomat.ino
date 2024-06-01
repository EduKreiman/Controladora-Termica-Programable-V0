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






/*

WDT también tienen problemas propios.  https://www.prometec.net/watch-dog-timer/
cuando tu Arduino se resetea, el WDT sigue en marcha y si el tiempo es corto vuelve a resetear
Por ejemplo, 
si el tiempo de disparo es menor de lo que tu programa tarda en el peor caso en pasar por meta y dar la vuelta al reloj, 
tendrás un Reset aleatorio y no estarás muy seguro de porque razón. 
Será un problema esporádico y muy difícil de detectar.
Peor aún, si te equivocas con el tiempo de disparo del WDT, tu programa puede entrar en un bucle infinito de reinicios, 


//DETECTAR QUE PLACA ESTOY USANDO POR SOFT:
//https://forum.arduino.cc/t/identificar-una-placa-arduino-por-algun-numero-serie/550698/8
//http://blog.elcacharreo.com/2013/10/22/arduino-faq-como-detectar-desde-codigo-que-placa-de-arduino-se-esta-usando/

The NANO and pro mini stock bootloaders ****contain a bug ***** that causes it to get stuck repeatedly resetting in the bootloader after a WDT reset.
SOLUCION----------->Rebootload them as Uno's or as standalone '328p's (using MiniCore board package).
https://github.com/MCUdude/MiniCore/tree/master/avr/libraries/AVR_examples/examples

simplemente vuelva a flashear los NANO con un cargador de arranque para el UNO usando el IDE de arduino 
(a través de otro arduino que ejecuta Arduino como ISP), 
y de ahí en adelante, cuando vaya a programar los NANo, seleccionar UNO en el menú de tableros como el tablero de destino.
https://syxaxis.github.io/post/01_arduino_bootloader/
*/

/*comandos: wdt_enable(timeout)
            wdt_disable()
            wdt_reset()
          */
	void software_Reboot()	{	// esta funcion resetea el arduino y se llama cada 2 horas  para evitar bloqueos.	
        wdt_enable(WDTO_8S );//15 milisegundos y hace el reset 			10-07-2022  WDTO_30MS  WDTO_15MS  WDTO_500MS  WDTO_2S WDTO_8S
              while(1){	}		
		}			





