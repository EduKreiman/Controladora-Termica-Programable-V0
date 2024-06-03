void envia_BT(){ //--------------------->>>>>>>>> FUNCION envia_BT                        
             //Serial.print("2-tempActual: ");
      BT1.print(tempActual); //  sNN.NN  max=6 min=4
      BT1.println("°C ");//8

      //probar println
      DateTime now = rtc.now();//toma datos del modulo RTC 
      hs = now.hour()+ ( float ) now.minute()/60+  ( float )now.second()/6000;   // hora input para el calculo de la temperatura instantanea
      BT1.print(hs); //  sNN.NN  max=6 min=4
      BT1.println("=HCalc ");//8
      BT1.print(Tinstant-tempActual); //  sNN.NN  max=6 min=4
      BT1.println("=DeltaT     ");//8
      //BT1.print("  L ");
      //BT1.println(nLectu);
                                     //paquet 3 2
                                              //BT1.print("3-HoraFecha= ");
                                            //   BT1.print("Time= ");
                                              //char buf1[20];//First you need a character array to save the output string into.  
                                              // sprintf(buf1, "%02d:%02d:%02d %02d/%02d/%02d",  now.hour(), now.minute(), now.second(), now.day(), now.month(), now.year()); 
                                           //   BT1.println(buf1);//argumento el búfer de caracteres donde sprintf() almacenó la cadena formateada.
                              
                              
                              /*With Arduino Uno, you can assign any of the pins D0 to D13, 
                              originally used for digital output, as digital input.

                              Library: manipulate general-purpose I/O (GPIO) pins on your Arduino 
                                https://www.arduino.cc/reference/en/libraries/fastgpio/
                              The pin states can be checked by switching to the digital input mode programmatically.  
                              https://github.com/pololu/fastgpio-arduino
                              https://github.com/pololu/fastgpio-arduino/blob/master/examples/Test/Test.ino

                                  */                                 
                           

    }  //------------------------------->>>>>>>>> FUNCION envia_BT 
