void grabaMEM(){//guarda datos de variables a recuperar luego del reset
 /*
 Serial.println(" Guardando y mostrando  datos en la EEPROM...");
  /*
  Serial.print("Dato byte: ");Serial.println(variable_byte);
  Serial.print("Dato int: ");Serial.println( variable_int);
  Serial.print("Dato long: ");Serial.println( variable_long);
  Serial.print("Dato float: ");Serial.println( variable_float);
  Serial.print("Dato Cadena : "); Serial.println(cadena);
  Serial.println();
 
Serial.println();
Serial.println(F("nModo INT ;t1  FLOAT;hot_cool  INT ;t2  FLOAT; time stamp"));  
Serial.println(F("verifica contenido memoria"));
Serial.print(F(" nModo INT=")); Serial.println(nModo); 
Serial.print(F(" int/100 t1="));Serial.println(T1); 
Serial.print(F(" float t2=")); Serial.println(T2);
Serial.print(F(" rango="));Serial.println(s3);                                 
Serial.print(F(" hot_cool="));Serial.println(s4);
Serial.print(F(" histeresis="));Serial.println(s5);
Serial.print(F(" etiqTime=")); Serial.println(hs);
Serial.print(F(" etiqTime=")); Serial.println(cadena2);



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
  /*
DateTime now = rtc.now(); 
hs = now.hour()+ ( float ) now.minute()/60+  ( float )now.second()/6000;   // hora input para el calculo de la temperatura instantanea
//      float, porcion entera, cant decimales, variabl destino
dtostrf ( hs ,             5 ,             6 ,         cadena );
 
 
  //void      write(unsigned int address, byte *data, int n);
  //EepromRTC.write(1,variable_byte); // posiscion 1:ocupa 1 byte de tamaño
  EepromRTC.writeInt(2,nModo); // posiscion 2:ocupa 2 bytes de tamaño 
  EepromRTC.writeFloat(8,T1); // posiscion 8:ocupa 4 bytes de tamaño 
  EepromRTC.writeFloat(12,T2); // posiscion 8:ocupa 4 bytes de tamaño 
  EepromRTC.writeFloat(16,s3); // posiscion 8:ocupa 4 bytes de tamaño 
  EepromRTC.writeFloat(20,s4); // posiscion 8:ocupa 4 bytes de tamaño 
  EepromRTC.writeFloat(24,s5); // posiscion 8:ocupa 4 bytes de tamaño 
  EepromRTC.writeFloat(28,hs); // posiscion 8:ocupa 4 bytes de tamaño 
  EepromRTC.writeChars(32, cadena, 30);// posicion 16 y 20 bytes de tamaño 
   */
    }//cierre    grabaMEM()


void leeMEM(){// lectura y presentacion y recupera datos en variables
//nModo = 3;// 3= circadiano para test autonomo
// se reemplaza para version_00 por funcion la parametror()
Parametror();

/*
Serial.println("Leyendo datos guardados...");
 aAT24 = EepromRTC.read(1);//posicion
  bAT24 = EepromRTC.readInt(8);
  cAT24 = EepromRTC.readFloat(12);
  dAT24 = EepromRTC.readFloat(16);
  eAT24= EepromRTC.readFloat(16);
  fAT24= EepromRTC.readFloat(16);
  char cadena2[30];
  cadena2[30];EepromRTC.readChars(28,cadena2,30);

//nModo=aAT24; if (nModo >=7   ){nModo=3;}
//T1= bAT24;
//T2= cAT24;
//s3= dAT24;
//s4= eAT24;
//s5= fAT24;//revisar
//etiqTime=cadena2; uso directo cadena2 como control

Serial.println();
Serial.println(F("nModo INT ;t1  FLOAT;hot_cool  INT ;t2  FLOAT; time stamp"));  
Serial.println(F("verifica contenido memoria"));
/*
Serial.print(F(" nModo INT=")); Serial.println(nModo); 
Serial.print(F(" int/100 t1="));Serial.println(T1/100); 
Serial.print(F(" float t2=")); Serial.println(T2);
Serial.print(F(" rango="));Serial.println(s3);                                 
Serial.print(F(" hot_cool="));Serial.println(s4);
Serial.print(F(" histeresis="));Serial.println(s5);
Serial.print(F(" etiqTime=")); Serial.println(cadena2);
*/
/*
Serial.print(F(" nModo INT=")); Serial.println(aAT24); 
Serial.print(F(" int/100 t1="));Serial.println(bAT24); 
Serial.print(F(" float t2=")); Serial.println(cAT24);
Serial.print(F(" rango="));Serial.println(dAT24);                                 
Serial.print(F(" hot_cool="));Serial.println(eAT24);
Serial.print(F(" histeresis="));Serial.println(fAT24);
Serial.print(F(" etiqTime=")); Serial.println(cadena2);
*/


 }//cierre leeMEM()


