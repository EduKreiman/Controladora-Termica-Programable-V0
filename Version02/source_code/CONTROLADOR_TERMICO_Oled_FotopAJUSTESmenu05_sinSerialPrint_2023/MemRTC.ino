





void grabaMEM() {//guarda datos de variables a recuperar luego del reset
                                                                                          //incluye para verificacion un leeMEM(); al final

                                                                                            // Serial.println(" Guardando y mostrando  datos en la EEPROM..grabaMEM().");
                                                                                                  /*Serial.print("Dato bool: ");Serial.println(variable_bool); // verificar existencia en docu libreria

                                                                                                    Serial.print("Dato byte: ");Serial.println(variable_byte); 
                                                                                                    Serial.print("Dato int: ");Serial.println( variable_int);
                                                                                                    Serial.print("Dato long: ");Serial.println( variable_long);
                                                                                                    Serial.print("Dato float: ");Serial.println( variable_float);
                                                                                                    Serial.print("Dato Cadena : "); Serial.println(cadena);
                                                                                                    Serial.println();
                                                                                                  */
                                                                                                  //Serial.println();
 /*      Serial.println(F("Contenido LOCAL a grabar-->---grabaMEM()"));
// menuModo()
        Serial.print(F("  nModo=  ")); Serial.println(nModo);
// menuTEMP()
        Serial.print(F("  T1=  ")); Serial.println(T1,4); 
        Serial.print(F("  T2=  ")); Serial.println(T2,4);  
        Serial.print(F(" mRecta=  "));Serial.println(mRecta);// Configuración de la pendiente de la recta 
// menuFOTO() float dia  float noche
        Serial.print(F(" float dia=    "));Serial.println(hcOn);                               
        Serial.print(F(" float noche=  "));Serial.println(hcOff);

        Serial.print(F(" TimeStart =  "));Serial.println(TimeStart);   
        Serial.print(F(" pasoSoak =   "));Serial.println(pasoSoak);   // posicion 28:FLOAT ocupa 4 bytes de tamaño

       // Serial.print(F(" histeresis=  "));Serial.println(s5); 
      //  Serial.print(F("         hs=  ")); Serial.println(hs);
        //Serial.print(F("   etiqTime=  ")); Serial.println(cadena2);
      //  Serial.print(F("TEMP CAMARA=  ")); Serial.println(tempActual);

                                                                                            /*
                                                                                            para float:
                                                                                            dtostrf ( float_value ,  min_width ,  num_digits_after_decimal ,  where_to_store_string )

                                                                                            hs = now.hour()+ ( float ) now.minute()/60+  ( float )now.second()/6000;   // hora input para el calculo de la temperatura instantanea
                                                                                            dtostrf ( hs ,  2 ,  6 ,  cadena );

                                                                                            para enteros:
                                                                                            sprintf() significa  “string print formateado”. 

                                                                                                                      sprintf(buffer, "The %d burritos are %s degrees F", numBurritos, tempStr); 
                                                                                                                      sprintf(); //takes a minimum of 2 arguments. 
                                                                                                              The first argument is where you plan to store the string that sprintf() will be making for you.
                                                                                                              
                                                                                              //Serial.println( buf1);
                                                                                              //println( buf1);//        FUNCION 
                                                                                              */
                                                                                          
   //     Serial.println(F("Grabando datos grabaMEM()"));         
          //void      write(unsigned int address, byte *data, int n);
          //               (             puntero, referencia, int)
          //EepromRTC.write(1,variable_byte); // posiscion 1:ocupa 1 byte de tamaño
     // menuModo()
          EepromRTC.writeFloat(2,nModo); // posicion 2:INT ocupa 4 bytes de tamaño  
     // menuTEMP()
          EepromRTC.writeFloat(8,T1); // posicion 8:FLOAT ocupa 4 bytes de tamaño 
          EepromRTC.writeFloat(12,T2); // posicion 12:FLOAT ocupa 4 bytes de tamaño 
     // menuFOTO() float dia  float noche 
                      //      hcOn  =  //amanecer   8hs01  
                      //      hcOff =  //anochecer 20hs01   
          EepromRTC.writeFloat(16,hcOn); // posicion 16:FLOAT ocupa 4 bytes de tamaño 
          EepromRTC.writeFloat(20,hcOff); // posicion 20:FLOAT ocupa 4 bytes de tamaño 
      // menu   void  Lineal()
         EepromRTC.writeFloat(24,TimeStart); // posicion 24:FLOAT ocupa 4 bytes de tamaño 
         EepromRTC.writeFloat(28,pasoSoak); // posicion 28:FLOAT ocupa 4 bytes de tamaño  atencion----------> pasoSoak es bool

        // EepromRTC.writeFloat(24,s5); // posicion 8:FLOAT ocupa 4 bytes de tamaño ocupa 4 bytes de tamaño 
         //         DateTime now = rtc.now(); 
         //         hs = now.hour()+ ( float ) now.minute()/60+  ( float )now.second()/6000;   // hora input para el calculo de la temperatura instantanea
        //  EepromRTC.writeFloat(28,hs); // posicion 8:ocupa 4 bytes de tamaño 
        //      float, porcion entera, cant decimales, variabl destino
        //dtostrf ( hs ,             5 ,             6 ,         cadena );
       //EepromRTC.writeChars(32, cadena, 30);// posicion 16 y 20 bytes de tamaño 
   leeMEM();//esta rutina pasa los datos guardados a las variables del programa
} //cierre    grabaMEM()------------------------------------------------------------------------------------------------------




void leeMEM(){ // lectura y presentacion //esta rutina pasa los datos guardados a las variables del programa---------------------------------
//                 al leer carga el valor de las variable locales y las pasa a las variables globales del programa
            
//Serial.println(F("leeMEM().........Leyendo Memoria... y  "));
  aAT24 = EepromRTC.readFloat(2); //nModo= 2  posicion
  bAT24 = EepromRTC.readFloat(8); //T1 
  cAT24 = EepromRTC.readFloat(12);//T2 
  dAT24 = EepromRTC.readFloat(16);// hcOn //amanecer SUNRISE
  eAT24 = EepromRTC.readFloat(20);// hcOff//anochecer SUNSET
  MTimeStart=EepromRTC.readFloat(24);//timeStar
  MpasoSoak=EepromRTC.readFloat(28);//pasoSoak
                                          //fAT24 = EepromRTC.readFloat(24);// histeresis= 0.15
                                          //gAT24 = EepromRTC.readFloat(28);// CENTetiqTim
                                          //char cadena2[30];
                                          //cadena2[30];EepromRTC.readChars(28,cadena2,30);

                                        // Serial.println(F("nModo INT ;t1  FLOAT;hot_cool  INT ;t2  FLOAT; time stamp"));  
//Serial.println(F("MUESTRA contenido ----leeMEM()---"));
                                  /*
                                  Serial.print(F(" nModo INT=")); Serial.println(nModo); 
                                  Serial.print(F(" int/100 T1="));Serial.println(T1/100); 
                                  Serial.print(F(" float T2=")); Serial.println(T2);
                                  Serial.print(F(" rango="));Serial.println(s3);                                 
                                  Serial.print(F(" hot_cool="));Serial.println(s4);
                                  Serial.print(F(" histeresis="));Serial.println(s5);
                                  Serial.print(F(" etiqTime=")); Serial.println(cadena2);
                                  */
nModo=aAT24;//Serial.print(F(" nModo    = "));Serial.println(aAT24);
   T1=bAT24;//Serial.print(F("        T1= "));Serial.println(bAT24);// Serial.println(T1); 
   T2=cAT24;//Serial.print(F("        T2= "));Serial.println(cAT24); // Serial.println(T2); 
                                                //if (T1 >= T2) { mRecta = -mRecta; 
                                                //Serial.print(F("*********  mRecta = ")); Serial.println(mRecta);// Configuración de la pendiente de la recta

     //hcOn  =  (8 + ((float)01/60) );//amanecer   8hs01
hcOn=dAT24;//Serial.print(F("   SUNRISE= "));Serial.println(dAT24); // SUNRISE  
     //hcOff =  (20+ ((float)01/60)); //anochecer 20hs01                          
hcOff=eAT24;//Serial.print(F("    SUNSET= "));Serial.println(eAT24);/ SUNSET

TimeStart=MTimeStart;//Serial.print(F("  TimeStart= "));Serial.println(MTimeStart);//TimeStart   FLOAT
pasoSoak=MpasoSoak; //Serial.print(F("  pasoSoak= "));Serial.println(MpasoSoak);   //pasoSoak    BOOL

//Serial.print(F(" histeresis= "));Serial.println(fAT24);//s5 =0.14;//fijo para entrega
// Serial.print(F(" CENTetiqTime= ")); Serial.println(gAT24);//HS CENTECIMAL
//Serial.print(F(" etiqTime= ")); Serial.println(cadena);

 if (   ( abs(T2-T1) > 10)   && ( nModo==2)   ){s4=80;}
 }//cierre leeMEM()----------------------------------------------------------------------------------------------

