





void ENVIADATA(){ //--------------------->>>>>>> ENVIA DATA A PROSSESING VIA PUERTO SERIAL
                  //envia paquetes codificados por variable segun la primer PALABRA del PAQUETE
         
       //Serial.print("2-tempActual: ");
          Serial.print("2- ");//       sens nro=  0   palabra1 termina en espacio separador 
             
                Serial.print(T1);   //    sens nro=  1   palabra2
                     Serial.print(F(" "));// separador palabra3
               //-------------------       
                Serial.print(nLectu);//   sens nro=  2 -->sens nro=  2 porque el primero es CERO
                     Serial.print(F(" "));//separador  palabra4
                Serial.print(nModo);//    sens nro=  3 'nModo' 
                       Serial.print(F(" "));// separador palabra5
                Serial.print(ENTROPIA); // sens nro= 4
                Serial.print(F("conPWM="));Serial.print(PwFrio);Serial.print(F("y"));Serial.print(PwHot,1);
                        Serial.print(F(" "));//separador  palabra6
                Serial.print(tempActual);//sens nro=  5 GOAL    
                         Serial.print(F(" "));// separador palabra7
                Serial.print(T2);//        sens nro=  6 META
                          Serial.print(F(" "));//
                Serial.print(Tinstant);//  sens nro=  7 INSTANT   
                         Serial.print(F(" "));//
                Serial.print(freeMemory());//     
                Serial.print(F(" "));//
                //Serial.println(freeMemory()); //  sens nro=  8   Memory 
               
               Serial.println(TempDisip); //  sens nro=  9   idem sens nro= 28 //  
                        Serial.print(F(" "));//
             //-----------------------------------------esto no llega ????------------------------------------  
                Serial.print(TempDisip);//     sens nro=  10   idem sens nro= 28 //
                        Serial.print(F(" "));//
                
                Serial.print("TempDisip");//     sens nro=  11   idem sens nro= 28 //
         Serial.println(" ");//LINE FEED SALTO limitador que indica el fin de un PAQUETE compuesto de PALABRAS.
 // paquet 3 
                     /*                                    Serial.print("3-HoraFecha= ");
                                                          //Una variable  global es aquella que puede ser vista y utilizada por cualquier función, esta se declara al principio. 
                                                          //las variables locales son aquellas que se definen en una función y se usa solo en la función en la que se declaró.
                                                                  //char buf1[20];//First you need a character array to save the output string into.  
                                                           Serial.println(buf1);//aqui pasamos como argumento el búfer de caracteres donde sprintf() almacenó la cadena formateada.   
                                                             
                                                              // sprintf(buf1, "%02d:%02d:%02d %02d/%02d/%02d",  now.hour(), now.minute(), now.second(), now.day(), now.month(), now.year()); 
                                                           3-HoraFecha=          154:  14:  00 -153/ 14 /215D  
                                                                                  22:  08:  nn  02/  06 /2022  
                                                                   código ASCII  154 " Ü "   codigo ascii 153 = Ö 
                     */              
//paquet 4 //temperatura ambiental del RTC  
         if(tempAMBIENT!=tempAMBanterior)
         {               tempAMBanterior=tempAMBIENT;
         
        Serial.print(F("4-rtcTemp= "));//probar teste si acepta la F
        Serial.println(tempAMBIENT); //Enviamos los datos en forma de byte
         Serial.println(" ");//LINE FEED SALTO
             }      
                     
                                                      //paquet 5 //colocarlo en el boton de dataset????
                                                             //Serial.print("5-TEST RESPONDE A DATASET: ");linea  379
                                          
}  //--------------------------------------------------------------------->>>>>>>>> FUNCION  ENVIADATA()



void ENVIAstatus(){ //---------------------------------------------->>>>>>>>>funcion>>>>>>> ENVIAstatus()
              // envia paquetes/frases codificados por vaRiable segun la primer PALABRA de la FRASE/PAQUETE
              // se recibe como un ARRAY[] que contiene STRINGs             
 DateTime now = rtc.now();//toma datos del modulo RTC      

// String mostra4="6-enviaSTATUS";// FRASE enviaSTATUS desde arduino        
   Serial.print("6-enviaSTATUS ");//             sens nro=  0   palabra1 termina en espacio separador
   //delay (100);
                    Serial.print(tempActual);//  sens nro=  1      
                         Serial.print(F(" "));// separador palabra
                    Serial.print(ENTROPIA);//    sens nro=  2 = "HEATING"; //"COOLING"       
                        Serial.print(F(" "));;// separador palabra
                    
                    if(ENTROPIA=="HEATING"){ 
                      Serial.print(PwHot);//sens nro=       3    
                          }
                    else{ 
                    Serial.print(PwFrio);// sens nro=       3   
                    }     
                          Serial.print(F(" "));// separador palabra
                    Serial.print(tempAMBIENT*100);// sens nro=  4//  = -170.1;//rtc       
                          Serial.print(F(" "));// separador palabra
                    Serial.print(nLectu);//      sens nro=  5// contador de LECTURAS DE TEMPERATURA       
                          Serial.print(F(" "));// separador palabra
                    Serial.print(ESTADO_E);//    sens nro=  6//=false;       
                         Serial.print(F(" "));// separador palabra
                    Serial.print(ESTADO_S);//    sens nro=  7//= false;        
                          Serial.print(F(" "));// separador palabra
                    Serial.print(ESTAnt_S);//    sens nro=  8//=false;       
                          Serial.print(F(" "));// separador palabra
                    Serial.print(ESTADO_A);//    sens nro=  9//=false;       
                          Serial.print(F(" "));// separador palabra
                    Serial.print(LLegueT1);//    sens nro= 10//=false;//   Flag DE CONTROL DEL TERMOSTATO se usa en cuerpo pincipal para desconectar el puente H       
                          Serial.print(F(" "));// separador palabra
                    
                    //--------------------------------------ECO VERIFICACION PARA VALIDAR LO RECIBIDO LO REENVIA A PROCESSING 
                    Serial.print(T1);//          sens nro= 11//tempArranque -->  temp de inicio      seteatempMin    --carga inicial para desarrollo       
                    //Serial.print(33.5);// 
                          Serial.print(F(" "));// separador palabra
                    Serial.print(T2);//          sens nro= 12//tempSET -seteatempMax->  temp a llegar en rampa ---carga inicial para desarrollo             
                        Serial.print(F(" "));// separador palabra
                    Serial.print(nModo);//       sens nro= 13// int = 0; 
                        Serial.print(F(" "));// separador palabra
                   
                    //Serial.print(nEvent);//      sens nro= 14// contador de eventos--->> REVISAR no llega, no se usa en ardu
                     Serial.print(321);//      sens nro= 14// contador de eventos--->> REVISAR si llega un numero int, no se usa en ardu
                          Serial.print(F(" "));// separador palabra
                   Serial.print(s3*100);//          sens nro= 15 int s3 = 50; 
                     //Serial.print(375);//          arduino no decodifica float --enviar *100 y dividir  o poner un parse 
                          Serial.print(F(" "));// separador palabra
                   Serial.print(s4);//          sens nro= 16 int s4 = 50;  --->> se recibe como % rango 0 a 100  <<---
                   //Serial.print(425);//          sens nro= 16 envia bien
                          Serial.print(F(" "));// separador palabra
                   //Serial.print(s5/100); //        sens nro= 17  asi llega bien 
                   //s5=0.555;
                   Serial.print(s5*100); //        sens nro= 17 float s5 DECODIFICA DE 0 A 255 
                   //Serial.print(500);
                          Serial.print(F(" "));// separador palabra
                    
                    Serial.print(now.hour(), DEC);//sens nro= 18 // 
                          Serial.print(F(" "));// separador palabra
                    Serial.print(now.minute(), DEC);//sens nro= 19 // de 0 a 59
                          Serial.print(F(" "));// separador palabra
                    Serial.print(now.second());// sens nro= 20 // de 0 a 59
                         Serial.print(F(" "));// separador palabra
                    Serial.print(now.month());//  sens nro= 21 // de 0 a 59
                          Serial.print(F(" "));// separador palabra
                      // char buf1[20];
                   //sprintf(buf1, "%02d:%02d:%02d %02d/%02d/%02d",  now.hour(), now.minute(), now.second(), now.day(), now.month(), now.year()); 
                   //  Serial.print(buf1);//aqui pasamos como argumento el búfer de caracteres donde sprintf() almacenó la cadena formateada.
                         Serial.print(F(" "));// separador palabra                       //sens nro= 22 time 
                         Serial.print(F(" "));// separador palabra                       //sens nro= 23 date  
                       
                   Serial.print(Tinstant);      //sens nro= 24 // temperatura de la funcion del modo seleccionado
                          Serial.print(F(" "));// separador palabra
                   Serial.print(miliAvance);//    sens nro= 25 //  
                          Serial.print(F(" "));// separador palabra
                   Serial.print(sgCorrida);//    sens nro= 26 //
                         Serial.print(F(" "));// separador palabra
                   Serial.print(miliAhora-miliAvance);//    sens nro= 27 // siempre crece    
                         Serial.print(F(" "));// separador palabra
                   Serial.print(TempDisip);//    sens nro= 28 //
                         Serial.print(F(" "));//separador palabra
                               // Voltimetro();VIENE DE LAS RUTINAS PWM_CALOR Y PWM_FRIO
                   Serial.print(tension );//    sens nro= 29 //float tension=0;  

       Serial.println(" ");//LINE FEED SALTO=println limitador que indica el fin de un PAQUETE/FRASE compuesto de PALABRAS/VARIABLES.
// agregar aqui nuevas variables como:
// tiempo maximo
// nro de ciclos
delay (100);
 //grabaMEM();//guarda datos de variables a recuperar luego del reset
 // se reemplaza para version_00 por funcion la parametror()
                                                       
}  //---------------------------------------------------------------------------------->>>>>>>>> FUNCION ENVIAstatus 
   
 
