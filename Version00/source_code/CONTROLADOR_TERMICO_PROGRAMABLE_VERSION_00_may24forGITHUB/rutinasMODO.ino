void rutMODO(){//
                                                  /*
                                                  * List l = Arrays.asList("0 SOAK", "1 TERMOSTATO", "2 RAMPA y=mx+b", "3 CIRCADIANO", "4 Temperatura Crítica", "5 por ARCHIVO CVS", "6 Polinomio NN","7 TEMPORIZADO");// CASOS PARA SELECCIONAR MODO
                                                                  13AvisaAZUL
                                                                  10CircaROJO
                                                                  11TCrictYELL
                                                                  12AloneYELL
                                                  0 SOAK
                                                  1 TERMOSTATO es una configuracion de rampa  void R_termos() 12AloneYELL
                                                  SI 2 RAMPA y=mx+b
                                                  SI 3 CIRCADIANO
                                                  SI 4 Temperatura Crítica 
                                                  SI 5 por ARCHIVO CVS
                                                  6 Polinomio NN
                                                  7 TEMPORIZADO 
                                                  * 
                                                  R_soak--> inicio +termostato
                                                                avisa con  LLEGUE=0 estoy corrigiendo,ajustando,llevando la temp del Peltier al seteo
                                                                color background rosado/lila
                                                                avisa con  LLEGUE=1--> color background azul
                                                   */
//APAGA 3 LEDs FRONTAL
      digitalWrite(pinCirca,LOW);
      digitalWrite(pinTCrict,LOW);
      digitalWrite(pinAlone,LOW);//uso este led como indicador TERMOSTATO  void R_termos() ¿es una configuracion de rampa ?

      if (      nModo == 2 ){//sens nro= 13 float nModo =Serial.read();  
                        Lineal ();//llama funcion que   entrega Tinstant
                        //LinealCompleto(); desactivado
                    }
      else if ( nModo == 3 ){//sens nro= 13 float nModo =Serial.read();            
                      R_circadiano();//llama funcion que entrega local float  T_calActual=-4.321; y Tinstant tambien
                      digitalWrite(pinCirca,HIGH);//rojo en el frente de la fuente
                      /*enciende led frontal ROJO 
                          const int pinCirca = 10 ;//pwm desde zocalo SD led frontal ROJO 
                          const int pinTCrict= 11 ;//pwm desde zocalo SD led frontal YELLOW
                          const int pinAlone = 12 ;//    desde zocalo SD led frontal YELLOW
                                    
                          pinMode(pinCirca, OUTPUT);
                          pinMode(pinTCrict, OUTPUT);
                          pinMode(pinAlone, OUTPUT);
                      */
                    }
      else if ( nModo == 4 ){//sens nro= 13 float nModo =Serial.read();            
                      R_TCritica();//llama funcion que   entrega Tinstant global  float Tinstant=-12.34;
                    }                       
      else if ( nModo == 1 ){
        digitalWrite(pinAlone,HIGH);//    desde zocalo SD led frontal YELLOW
                     R_termos();
                      digitalWrite(pinAlone,LOW);//12AloneYELL    desde zocalo SD led frontal YELLOW 
                      /*enciende led frontal ROJO 
                          const int pinCirca = 10 ;//pwm desde zocalo SD led frontal ROJO 
                          const int pinTCrict= 11 ;//pwm desde zocalo SD led frontal YELLOW
                          const int pinAlone = 12 ;//    desde zocalo SD led frontal YELLOW

                          pinMode(pinCirca, OUTPUT);
                          pinMode(pinTCrict, OUTPUT);
                          pinMode(pinAlone, OUTPUT);
                      */

                    }                           
 }//--rutMODO()-fin
           


 
void LinealCompleto (){// void R_y=mx+b()
//               pendiente= 0,25 grados cada 60 segundos
//entrega temperatura deseada ( Tinstant ) en funcion del tiempo transcurrido
//para usar en 
//TERMOSTAT(T1,tempActual,Tmargen);//LLEVA LA PLACA A T1  
// donde cada NNN segundos T1=Tinstant
//si Tinstant == T2  llegue, avisala, mantengo/ciclo/stop/sigue hasta 50 grados?? ?????
// Serial.print(miliAhora-miliAvance);//    sens nro= 27 // siempre crece

  miliAhora=millis();
 // mRecta=0.25/60000;//  pendiente   creciente estandard = 1°C cada 4 minutos = 240.000 milisegundos

  if(T1>=T2){ mRecta=mRecta*-1; }// pendiente DEcreciente 

  if (((ESTADO_A==0)&& (ESTADO_S==1) && (ESTAnt_S==0)))// START + ENCIENDE PUENTE H   idem void EstadosyBotones() ----linea 06--START de la corrida 
     {
        //ESPERA QUE TERMOSTATO EMITA UN -->>>LLEGUE<<<--
        if (LLegueT1==true){
                                  //MANTIENE LA CELDA EN SOAK A T1 DURANTE 4 MINUTOS
                                  if (miliSoak>240000)//4 minutos  = 240.000milisegundos
                                              { miliSoak=miliAhora;  //comienza a actualizar LUEGO DEL SOAK  Y desde el START de la corrida 
                                                miliStart=miliAhora;}//comienza a actualizar desde el START de la corrida y LUEGO DEL SOAK 
                              
                            miliAvance=miliAhora-miliStart;//tiempo transcurrido


                              //Calcula miliAvance cada 4 minutos= 240.000milisegundos  
                              if (miliAvance>10000)//10 segundos =  10.000milisegundos
                                { miliStart=0;// resetea contador de 4 minutos se resetea tambien desde START ?? 


                                    //calculo de  Tinstant
                                    //   y  =        m  *    x        + b        
                                    Tinstant=((  mRecta * miliAvance) + T1);  //temperatura deseada  
                                    //la pendiente mRecta ya tiene el signo evaluado antes

                                  //si Tinstant == T2  // llegue a la temp META, avisala, mantengo o Stop ?????                                      
                                      if((mRecta >=0.01) && ( Tinstant >= T2 )) { //pendiente positiva creciente y supera la temp META
                                     // avisala();          
                                        // llegue, avisala, mantengo o Stop ????? 
                                                                          //   y  =        m  *    x        + b
                                                                          //Tinstant=((  mRecta * miliAvance) + T1);  //temperatura deseada   
                                                                                }
                                      else if((mRecta <=0.01) && ( Tinstant <= T2 )) {  //pendiente negativa  y supera la temp META
                                     // avisala();
                                      // llegue, avisala, mantengo o Stop ????? 
                                                                          //   y  =        m  *    x        + b
                                                                          //Tinstant=((  mRecta * miliAvance) + T1);  //temperatura deseada   
                                                                                    }
                                                  
                                }//-------------------
                        }//-------------------  
        }//-------------------                                            
}//----------------------------------------FIN------------------ void R_y=mx+b()
void Lineal(){// void R_y=mx+b()
//               pendiente= 0,25 grados cada 60 segundos
//entrega temperatura deseada ( Tinstant ) en funcion del tiempo transcurrido
//para usar en 
//TERMOSTAT(T1,tempActual,Tmargen);//LLEVA LA PLACA A T1  
// donde cada NNN segundos T1=Tinstant
//si Tinstant == T2  llegue, avisala, mantengo/ciclo/stop/sigue hasta 50 grados?? ?????
// Serial.print(miliAhora-miliAvance);//    sens nro= 27 // siempre crece

              miliAhora=millis();
             //mRecta=0.25/60000;//  pendiente   creciente estandard = 1°C cada 4 minutos = 240.000 milisegundos
             
              if(T1>=T2){ mRecta=mRecta*-1; 
                        }// pendiente DEcreciente  si no es la pendiente default

              if (((ESTADO_A==0)&&(ESTADO_S==1) && (ESTAnt_S==0)))// START + ENCIENDE PUENTE H   idem void EstadosyBotones() ----linea 06--START de la corrida 
                 {
                            miliAvance=miliAhora-miliStart;//tiempo transcurrido
                              
                        unsigned long avanceTime=240000;//Calcula miliAvance cada 4 minutos= 240.000milisegundos 
                        if (test01==true ){avanceTime=10000;}//PARA DESARROLLO MONITOREADO de Modos

                              if (miliAvance>avanceTime)//10 segundos =  10.000milisegundos
                                { miliStart=0;// resetea contador de 4 minutos se resetea tambien desde START ?? 


                                    //calculo de  Tinstant
                                    //   y  =        m  *    x        + b        
                                    Tinstant=((  mRecta * miliAvance) + T1);  //temperatura deseada  
                                    //la pendiente mRecta ya tiene el signo evaluado antes

                                            //si Tinstant == T2  // llegue a la temp META, avisala, mantengo o Stop ?????                                      
                                                if((mRecta >=0.01) && ( Tinstant >= T2 )) { //pendiente positiva creciente y supera la temp META
                                                //avisala();          
                                                  // llegue, avisala, mantengo o Stop ????? 
                                                                                    //   y  =        m  *    x        + b
                                                                                    Tinstant=((  mRecta * miliAvance) + T1);  //temperatura deseada   
                                                                                          }
                                                else if((mRecta <=0.01) && ( Tinstant <= T2 )) {  //pendiente negativa  y supera la temp META
                                                //avisala();
                                                // llegue, avisala, mantengo o Stop ????? 
                                                                                    //   y  =        m  *    x        + b
                                                                                    Tinstant=((  mRecta * miliAvance) + T1);  //temperatura deseada   
                                                                                              }
                                                  
                                }//--------//Calcula miliAvance cada 4 minutos= 240.000milisegundos -----------
                                  
                }//-------------------          
 Tinstant=30.00 ;
 }//----------------------------------------FIN------------------ void R_y=mx+b()

void R_termos(){
//R_termostato--> y=x  usa PID
  //ESPERA LLEGUE DEL TERMOSTATO
  //SI LLEGUE--> MANTIENE DURANTE 60sg
  //SI LLEGUE Y PASO TIEMPO DE SOAK PROPIO HABILITA Tinstant
  digitalWrite(pinAlone,LOW);// 12AloneYELL   desde zocalo SD led frontal YELLOW
          Tinstant = T2;//seteada desde el slider LLEVA LA PLACA A T1  
          //TERMOSTAT(T1,tempActual,Tmargen);//LLEVA LA PLACA A T1  
  digitalWrite(pinAlone,HIGH);// 12AloneYELL   desde zocalo SD led frontal YELLOW
avisala();

}//----------------------------------------FIN------------------ void R_TCritica()

void R_TCritica(){

  //ESPERA LLEGUE DEL TERMOSTATO
  //SI LLEGUE--> MANTIENE DURANTE 60sg
  //SI LLEGUE Y PASO TIEMPO DE SOAK PROPIO HABILITA Tinstant
          Tinstant = T2;



}//----------------------------------------FIN------------------ void R_TCritica()

               
void R_circadiano(){
                     /* 
                      //ecuaciones del Paper de -->PartonLogan1980<------------------------------------------------
                     ******************************************************************************************  
                                                      PARAMETROS      
                                                                                Latitud del lugar  BsAs  34ª35`35"  
                                                                                fecha  01/01/1900    
                                                                                float incremental=0.10; // hs  centecimal  dato
                                                                                float aManecer=8.00;// hs= Srise  centecimal  dato
                                                                                float aNochecer= 20.00// hs =S set  centecimal  dato     
                                                                                tn = T min  4,00 Cº    dato
                                                                                Tmin=amanecer a las:  8,00 hs= Srise  HORA de Tmin diurna  
                                                                                tx = T Max  16,00 Cº    dato
                                                                                float Hs_Tmax = 15.75;// hora de la remperatura maxima
                                                                                //HORA de tmax  16,50 hs // hora de la temperatura maxima   
                                                                                Tmedia  8,73 Cº    
                                                                                y= deltaT  12,00 Cº    
                                                                                ADY=( AHOU/3.14)* 24.  11,00 hs  long  fotoperiodo DIURNO  
                                                                                ANI=(24.--ADY)  13,00 hs  long  fotoperiodo NOCTURNO  
                                                                                nro de dia(1 a 365)      
                                                                                float b=coef = 0.8;   //ajuste NOCHE      
                                                                                float a=coef=1.5; //ajuste DIA                                                                       
                        */

//tempActual
DateTime now = rtc.now();//toma datos del modulo RTC  
//         now.hour(), now.minute(), now.second(), now.day()
//(now.minute(), DEC);//sens nro= 18 // de 0 a 59
//now.second()  Returns Second (0–59)

//float hs=06.54321;// circadiano hora reloj format centecimal
//hs   formato centecimal dato
hs = now.hour()+ ( float ) now.minute()/60+  ( float )now.second()/6000;   // hora input para el calculo de la temperatura instantanea

                        if ( test01==true) {;//boolean test=true; PARA DESARROLLO MONITOREADO de Modos
                                            //pseudo reloj  mas rapido, 1hora aprox=2.5 segundos
                                                    hs= ( float )now.second()/2.5;// 59 segundos =23.60 horas 1 DIA desarrollado en 1 MINUTO
                                                  
                                                    //pseudo reloj  mas rapido, 1hora aprox=2.5 minutos
                                                    hs= ( float )now.minute()/2.5;// 59 minutos =23.60 horas 1 DIA desarrollado en 1 HORA                          
                                            //pseudo reloj 24 veces mas rapido 
                                          }

                        if  ( test==true) {//boolean test=true; PARA DESARROLLO MONITOREADO
                                              Serial.println (F("------------------------------------------"));
                                              Serial.print (F("modoActivo: "));Serial.println(nModo);
                                              Serial.print (F("HoraModal : "));Serial.println(hs);
                                              Serial.print (F("hora Calc=  "));Serial.print(now.hour());Serial.print (":");Serial.print(now.minute());Serial.print (":");Serial.println(now.second());
                                              Serial.print (F(" T1 : "));Serial.print(T1);
                                              Serial.print (F(" T2 : "));Serial.println(T2);
                                              Serial.println (F("------------------------------------------"));

                                          }               
//incremental=0.10; // hs  centecimal  dato
aManecer=8.00;// hs= Srise  centecimal  dato
aNochecer= 20.00;// hs =S set  centecimal  dato
// float fotoperiodo=aNochecer-aManecer;
//float Hs_Tmax = 15.75;// hora de la temperatura maxima calcularla ????
 //b = 0.8; //=coef ajuste NOCHE    constante definida en raiz   
 //a=1.5; //=coef ajuste DIA        constante definida en raiz 
//calC. algoritmo   ecuaciones del Paper de -->PartonLogan1980<----
//hs=22.10;
tempMin=19.00;//activa Slider s1 // modo tropical VZ
tempMax=33.00;//activa Slider s2 // modo tropical VZ
deltaT=0;
deltaT=tempMax-tempMin;
//float T_instAnterior=tempMin;//  4.000;//  excel t = 4ºC   4.251ºC//4.278084 ºC  8.10hs
//            y=$B$9+((($B$15)*SENO((PI()*(11,9))/($B$15+2*$B$20))+$B$9)   -$B$9)     *EXP(-$B$19*F168/2)
T_aNoche= 0;

//y=              (($B$15) *SENO((PI()*($F9))                    /  ($B$15+2*$B$20))+$B$9)
//T_aNoche=           12   * sin(  (PI*(11.9              ))     / (12    + 2*1.5) )+  4;
  T_aNoche=(deltaT) * sin(  (PI*(aNochecer-aManecer-0.1)) / (deltaT+(2*a)) ) + tempMin; //calc temp  Tdia la ultima hora del dia=aNochecer
                      
                      if ( test==true){   Serial.print   (F("deltaT= "));Serial.println(deltaT,2);
                                          Serial.print(F("  tempMax="));;Serial.println(tempMax);Serial.print("  tempMin=");;Serial.println(tempMin);
                                          Serial.print   (F(" modo 3->     T_aNoche= "));Serial.print(T_aNoche,3);Serial.println(F("  ultima hora del dia= es el aNochecer"));
                                          Serial.println (F("-------------------------------------------------"));
                                         //Serial.println ("20.00 T_aNoche  11,255189378349 Cº   ver si idem excel ----------");
                                         // 20.00 T_aNoche 11,255189378349 Cº   ok excel idem
                                      }
                                              
//float incremento=0;
//boolean dia=false;
if(((float)hs-aManecer)<= (0)){
                  incremento =((float)hs- aManecer+12);//si menor que 0 sumar 12  
                  } 

 else if (((float)hs-aManecer)>= (0)){
                  incremento = ((float)hs- aManecer); // cal del incremento  
                  if(incremento >= 12){//si mayor que 12 restar 12
                          incremento=incremento-12 ;              
                      }  }               //considera el fotoperiodo de 12hs ??? 

if ((hs>=aNochecer) || (hs<=aManecer)){//   (logical OR)   para detectar fotoperiodo DIA/NOCHE
                          //        dia=false;// es de noche
                          //        pow(base, exponent)  
                          //        pow(2.71828,n)              
                          //        exp(n)Returns Euler's number e (2.71828...) raised to the power of the n parameter 
                          //  incremento=suma de incrementos con un maximo de 12    

                           //   =      $B$4+(   H121 - $B$4)  * EXP(-$B$7   *     E122 /2) //hoja LEK   
                  //******* T_calActual************de NOCHE************************** 
                    T_calActual =   tempMin+(T_aNoche-tempMin)*exp((-1*b)   *incremento/2);//calc temp  Tnoche 
                  //*******************************de noche**************************** 
                       Tinstant=T_calActual;
                                                  if ( test==true){
                                                                          //Serial.println ("ES   DE    NOCHE-----------------------------------------------------------------");                   
                                                                          Serial.print(F ("Anochece= "));Serial.print(aNochecer);Serial.print(F("hs    con  "));Serial.print(T_aNoche);
                                                                          Serial.println(F(" ºC")); 

                                                                          // print("T_instAnterior= ",T_instAnterior,"ºC");         
                                                                          // Serial.print ("  coef ajuste NOCHE= ");Serial.println(b);
                                                                         /*             //print (" avance de tiempo= ",a,"  hs ");//   avance de tiempo de calculo en minutos centecimales
                                                                          Serial.println (" incremento = ",incremento,"  hs ");//tiempo acumulado desde el inicio del dia (Amanecer)   incremento=(hs- Amanecer) --en horas centecimales--
                                                                          Serial.println ("TEMPERATURA a las ",hs, "  hs    CALC:", T_calActual,"ºC"); 
                                                                                    //        calc. NOCHE= 8,672606201512 Cº excel,                a las : 21.10  hs 
                                                                          Serial.println ("deltaT =", deltaT,"ºC en un Fotoperiodo( horas de luz)de: ",fotoperiodo,"  hs ");   
                                                                          Serial.println ( "   tempMax=",tempMax,"ºC a las : ",Hs_Tmax,"  hs "); 
                                                                          Serial.println ("Amanece= ",aManecer,"  hs ","con TEMP AMANECER=",tempMin,"ºC (Temp.mínima)"); 
                                                                          */                                                                                         
                                                                }
} // es de noche
  
else  {   //dia=true;// es de DIA                 (B$3-B$4)*SENO((PI()*E122)/(B$6+2*B$8))+B$4)
                 //                          incremento=suma de incrementos con un maximo de 12 
                                                          if ( test==true){
                                                                          Serial.println(F("ES   DE    DIA-----------------------------------------------------------------"));                   
                                                                        //reescribir para arduino
                                                                                          /*Serial.print ("Amanece= ",aManecer,"  hs ","con TEMP AMANECER=",tempMin,"ºC (Temp.mínima)");  
                                                                                           // print("T_instAnterior= ",T_instAnterior,"ºC");         
                                                                                            Serial.print ("coef ajuste DIA= ",a);
                                                                                            /print (" avance de tiempo= ",a,"  hs ");//   avance de tiempo de calculo en minutos centecimales
                                                                                            Serial.println (" incremento = ",incremento,"  hs ");//tiempo acumulado desde el inicio del dia (Amanecer)   incremento=(hs- Amanecer) --en horas centecimales--
                                                                                          */
                                                                  }
//******* T_calActual************de DIA*************
 T_calActual  = (deltaT) * sin( ((PI)*incremento) / (deltaT+(2*a)) ) + tempMin;          //calc temp  Tdia 
//*******************************de DIA***************************************
Tinstant=T_calActual;                                                                                          
        } //es de DIA  
                            //entrega temperatura deseada ( Tinstant ) en funcion del tiempo transcurrido
                            //para usar en 
                            //TERMOSTAT(T1,tempActual,Tmargen);//LLEVA LA PLACA A T1  
                            // donde cada NNN segundos T1=Tinstant
                            //si Tinstant == T2  llegue, avisala, nciclo=nciclo+1;
                            //si nciclo=> ciclo ---avisala /stop
                            //Serial.println ("------------------------------------------");
                            //Serial.print ("Temp calc= ");Serial.println(T_calActual);
}//----------------------------------------FIN------------------ void R_circadiano()
