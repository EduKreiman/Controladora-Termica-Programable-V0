void rutMODO(){//
                                                  /*
                                                  * List l = Arrays.asList("0 SOAK", "1 TERMOSTATO", "2 RAMPA y=mx+b", "3 CIRCADIANO", "4 Temperatura Crítica", "5 por ARCHIVO CVS", "6 Polinomio NN","7 TEMPORIZADO");// CASOS PARA SELECCIONAR MODO
                                                                  13AvisaAZUL
                                                                  10CircaROJO
                                                                  11TCrictYELL
                                                                  12AloneYELL
                                                 NO 0 SOAK
                                                 NO 1 TERMOSTATO es una configuracion de rampa  void R_termos() 12AloneYELL
                                                  SI 2 RAMPA y=mx+b
                                                  SI 3 CIRCADIANO
                                                 NO 4 Temperatura Crítica 
                                                  SI 5 por ARCHIVO CVS
                                                 NO 6 Polinomio NN
                                                 NO 7 TEMPORIZADO 
                                                  * 
                                                  R_soak--> inicio +termostato
                                                                avisa con  LLEGUE=0 estoy corrigiendo,ajustando,llevando la temp del Peltier al seteo
                                                                color background rosado/lila
                                                                avisa con  LLEGUE=1--> color background azul
                                                   */


                              
      if (      nModo == 2 ){//  2RAMPA y=mx+b
                        DateTime now = rtc.now();//toma datos del modulo RTC 
                        leeMEM();
                        //TimeStart=   now.hour()+ ( float ) now.minute()/60+  ( float )now.second()/6000; //revisar para que no quede en cero
                        //miliStart=   now.hour()+ ( float ) now.minute()/60+  ( float )now.second()/6000; 
                       // miliStart=millis();
                        pasoSoak=false; 
                        //grabaMEM();
                        Lineal ();//llama funcion que   entrega Tinstant  
                       // setRampa==true;                     
                    }
      else if ( nModo == 3 ){//sens nro= 13 float nModo =Serial.read();            
                      R_circadiano();//llama funcion que entrega local float  T_calActual=-4.321; y Tinstant tambien
                      
                    } 
      else if ( nModo == 4 ){//T1=T2  nMODO=(4)   ----          
                     LinealCTE();//llama funcion que entrega local float  T_calActual=-4.321; y Tinstant tambien                                                                                                                                
                    }                         
 }//--rutMODO()-fin


void R_circadiano(){// nMODO=TRES(3)
                     /* 
                      //ecuaciones del Paper de -->PartonLogan1980<------------------------------------------------
                     *********************************************PARAMETROS *************************  
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

//hs = now.hour()+ ( float ) now.minute()/60+  ( float )now.second()/6000;   // hora input para el calculo de la temperatura instantanea
obtenerHoraCentesimal();
                                               //elimino test y test01         
//incremental=0.10; // hs  centecimal  dato
aManecer=8.00;// hs= Srise  centecimal  dato
aNochecer= 20.00;// hs =S set  centecimal  dato
// float fotoperiodo=aNochecer-aManecer;
//float Hs_Tmax = 15.75;// hora de la temperatura maxima calcularla ????
 //b = 0.8; //=coef ajuste NOCHE    constante definida en raiz   
 //a=1.5; //=coef ajuste DIA        constante definida en raiz 
//calC. algoritmo   ecuaciones del Paper de -->PartonLogan1980<----
//hs=22.10;
//tempMin=16.00;//activa Slider s1 // modo tropical VZ
//tempMax=32.00;//activa Slider s2 // modo tropical VZ
tempMin=T1;//DESDE SrAM
tempMax=T2;//DESDE SrAM
deltaT=0;
deltaT=tempMax-tempMin;
//float T_instAnterior=tempMin;//  4.000;//  excel t = 4ºC   4.251ºC//4.278084 ºC  8.10hs
//            y=$B$9+((($B$15)*SENO((PI()*(11,9))/($B$15+2*$B$20))+$B$9)   -$B$9)     *EXP(-$B$19*F168/2)
T_aNoche= 0;
//y=              (($B$15) *SENO((PI()*($F9))                    /  ($B$15+2*$B$20))+$B$9)
//T_aNoche=           12   * sin(  (PI*(11.9              ))     / (12    + 2*1.5) )+  4;
  T_aNoche=(deltaT) * sin(  (PI*(aNochecer-aManecer-0.1)) / (deltaT+(2*a)) ) + tempMin; //calc temp  Tdia la ultima hora del dia=aNochecer
                                                //elimino test y test01                                                                                        
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
                                                                      //elimino test y test01                                                 
} // es de noche
  
else  {   //dia=true;// es de DIA                 (B$3-B$4)*SENO((PI()*E122)/(B$6+2*B$8))+B$4)
                 //                          incremento=suma de incrementos con un maximo de 12 
                                                                //elimino test y test01  
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


void LinealCTE(){//T1=T2  nMODO=(4)   ----LinealCTE() 
 Tinstant=T1; 
 T2=T1;
}//----------------------------------------FIN------------------LinealCTE() nMODO=(4)









void Lineal(){// -----------------------------------------------  y=mx+b() nMODO=DOS(2)
   /*-Descripcion de la funcion 
            Esta funcion es llamada desde la rutina rutModo()
            y controla la temperatura de una camara termica Peltier, alimentada con un puente H.
            la funcion Termostat() recibe  la variable Tinstant  generada por la rutina Lineal().

            Comienza llevando la camara a la temperatura T1 funcion llamada en los comentarios  SOAK.
            cuando la alcanza T1 comienza una RAMPA termica ascendente o descendente segun las relaciones de magnitud de T1 y T2 
            Esta RAMPA responde a la ecuacion y=mx+b donde m= 1 grado centigrado cada 4 minutos.(variable mRecta)

            hay un watchDog que resetea el arduino cada 15 minutos, pero antes guarda las variables volatiles en una memoria (con la  funcion guardaMEM()   )

            para recuperarlas luego del reinicio ( con la funcion leeMEM() ) 

            variable TimeStart SE guarda y  Se usa para calcular el valor instantaneo de la recta,
            esta variable debe generarse antes del reset y ser guardada para ser usada solamente luego de finalizada la funcion SOAK 
            a partir de ese momento se calculara el avance de tiempo para usar en la ecuacion de la recta  

                    Avance=(hs-TimeStart);//tiempo transcurrido en milisegundos     //unsigned long miliStart = 0;
                                              //la pendiente mRecta ya tiene el signo evaluado antes//unsigned long miliAvance = 0;
                                  //calculo de  Tinstant
                                      //   y  =  b + (      m  *    x )                     
                                          Tinstant=(T1+ (  mRecta * Avance)        );

                                          //= 1°C cada 4 minutos 
            */

        //en rutModo() al llamar a la funcion con nModo==2 se cargan:
        //                                                      pasoSoak=false;
        //                                                      miliStart= hs centesimal

        //               pendiente= 0,25 grados cada 60 segundos
        //                          1 grado cada 4 minutos
        //entrega temperatura deseada ( Tinstant ) en funcion del tiempo transcurrido
        //para usar en 
        //TERMOSTAT(T1,tempActual,Tmargen);//LLEVA LA PLACA A T1  
        // donde cada NNN segundos T1=Tinstant

        // rutina SOAK con AVISO Y arraque automatico luego de alcanzar la temp de inicio CON HISTERSIS DE +-1.25 ºC
        //SI LLEGUE Y PASO TIEMPO DE SOAK PROPIO HABILITA Tinstant
                                              //   Tinstant = T2;

        //sigue CONTINUA LA PENDIENTE HASTA LA SATURACION OPERATIVA DEL EQUIPO TERMICO    hasta -8ºC  /  hasta 50ºC
        //si Tinstant == T2 ---> LLEGUE, avisala, mantengo/ciclo/stop/sigue hasta 50 grados?? ?????
        // Serial.print(miliAhora-miliAvance);//    sens nro= 27 // siempre crece

         

//REORDENAMIENTO--------1-05-2023------------------
//pasoSoak==false--> SOAK         pasoSoak==true-->RAMPA       
  //pasoSoak= false; //FUERZA A ENTRAR EN SOAK  ANTES DE ENTRAR EN WHILE

//Dado que la prueba de rampa tiene una duracion maxima de 90 /120 minutos se deshabilita para esta funcion el autoreset /o se lo setea en 120 minutos

//0  // comienza WHILE PARA PERMANECER EN RUTINA LINEAL LLAMADA DESDE MENU_SETEADOR
  while (nModo == 2 )  {//  2RAMPA y=mx+b

 //1 EVALUA PENDIENTE RAMPA 
  mRecta =15.00;   //0.000004167;   //0.25 / 60;    unidad second()  pendiente de la recta  m=1 grado cada 4 minutos
  //AQUI ES EL UNICO LUGAR DONDE SE DEFINE Y SE EVALUA  LA VARIABLE mRecta

  if (T1 >= T2) { mRecta = -mRecta; Serial.print(F("*********  mRecta = "));  Serial.println(mRecta); }// Configuración de la pendiente de la recta 
 // Serial.print(F("****WHILE RAMPA*****  mRecta = "));  Serial.println(mRecta);
  thermometer.loop();  // Mandatory to measure temperature and fire an event if needed
  tempActual = thermometer.getTempC();  // Get last measured tempC if needed.
  tempActual = tempActual + adjSensor; // corrector de desvio del sensor de temperatura DS18b20  

 //2 ESTOY EN CONDICION DE SOAK?   //pasoSoak==false--> SOAK           pasoSoak==true-->RAMPA   

                  if(pasoSoak==false ) {  //pasoSoak==false--> SOAK   
//                    SI--->  ENTRA EN SOAK Y ACTUALIZA Y GUARDA TimeStart PARA USAR EN RAMPA
                               Tinstant = T1; // para llevar la camara a T1 inicial   
                               obtenerHoraCentesimal();
                               TimeStart = hs;  // mientras este en  SOAK 
                               grabaMEM(); // para recuperarlo luego de un reset
                          
//                                   3 SOAK TERMINO?                                                
                                             // Variable de Evaluacion  de SOAK:  bool temperaturaObjetivoAlcanzada 
                                                                              //   TEMP CAMARA     TemARRANQUE RAMPA   AND       ASCENDENTE         OR                              DECRECIENTE
                                              bool temperaturaObjetivoAlcanzada = (tempActual >=  T1 - 0.25            &&        mRecta >= 0)       ||     (tempActual >=  T1 + 0.25   &&  mRecta <= 0);
                                              //bool (T1=Tinst)  es true      si esta en SOaK y si Tinstant == T1  INDICA FIN DE SOAK
                                              if ( temperaturaObjetivoAlcanzada ==true) { 
 //                                           SI--->    //--termine Soak -habilita inicio de Rampa Asc ó Desc  ,  pasoSoak true, llegue a T1, 
                                            // pasoSoak==true-->RAMPA
                                               pasoSoak = true; //--termine Soak -habilita inicio de Rampa Asc ó Desc  ,  pasoSoak true, llegue a T1,  
                                               grabaMEM();                                                          
 //                                           NO----> sige en soak
                                                 }//                                                   
//                   NO---->si no es soak es RAMPA  //pasoSoak==false--> SOAK    pasoSoak==true-->RAMPA 
                     }//
//            4 ENTRA EN RAMPA que calcula tinstant por avance de tiempo     //pasoSoak==false--> SOAKpasoSoak==true-->RAMPA            
              obtenerHoraCentesimal();//funcion:   float obtenerHoraCentesimal(){//  funcion devuelve  hs -->(hora reloj en formato centecimal)   
                  Avance=(hs-TimeStart);//tiempo transcurrido en milisegundos     //unsigned long miliStart = 0;
                        //calculo de  Tinstant
                        //   y  =  b + (      m  *    x )                     
                         Tinstant=(T1+ (  mRecta * Avance)        );  //calcula temperatura deseada GOAL                      
 
//            5 RAMPA TERMINO ?? si SI--> AVISA Y FIN
                                             //  pasoSoak==false--> SOAK      pasoSoak==true-->RAMPA 
              // consulta tempActual          y  NO estoy en SOAK       pasoSoak==true-->RAMPA
             // (si tempActual >= T2 y pasoSoak==false  y mRecta>0)  ó  (si tempActual >= T2 y pasoSoak==false  y mRecta<0) serial.print ("TERMINO CICLO RAMPA");
            //      pasoSoak==true-->RAMPA    
              if ( (pasoSoak==true) &&  (( mRecta<0) &&  (tempActual <= T2) || ( mRecta>0) &&  (tempActual >= T2) ) ){ //TERMINO CICLO RAMPA

                                                                                                      pasoSoak=false;//pasoSoak==false--> SOAK       pasoSoak==true-->RAMPA 
                                                                                                      grabaMEM(); //fuerza entrar en Soak para el proximo ciclo despues de un final
                                                                                                        Debug();
                                                                                                      Serial.print(F("*********TERMINO CICLO RAMPA******Con mRecta = "));  Serial.println(mRecta);
                                                                                                      Serial.print(F("*********TERMINO CICLO RAMPA******Con mRecta = "));  Serial.println(mRecta);
                                                                                                      Serial.print(F("*********TERMINO CICLO RAMPA******Con mRecta = "));  Serial.println(mRecta);
                                                                                                        Debug();
                                                                                                    motorGo(0, 2, 0);//quita energia en puente H 
                                                                                                    for (int i = 0; i <= 10; i++) {blinkFOTOPERIODO(); delay(2000);} 
                                                                                                    // -----------------stop
                                                                                                    while (1==1) {} // stop
                                                                                                    // -----------------stop
                                                                              }// sale  de la funcion rampa                         //TERMINO CICLO RAMPA
 
//            6   PARA PODER SALIR DEL WIHLE RUTINA LINEAL  SE REPITE DENTRO DEL WHILE     
              if(digitalRead(boton)==LOW){avisala();}// PARA SALIR DE LA RUTINA nModo 2
                    //if(digitalRead(Sw2) == HIGH){ blinkFOTOPERIODO();break;}// sale  de la funcion soak rampa      swA pin analogico A2 
                   // if(digitalRead(Sw2) == HIGH){setRampa=false;oled.clear();}// con lo mismo que entro circular SwA   pin analogico A2 

                                                    //  SwA=Sw2  llama a menuSeteador que entra en un while y se CONTROLA con la variable Seteador--> si seteador = true entra en un while 
                                                    // menuSeteador llamará : 1progs/modos  2temp  3foto  NNno opcion    
                                                    if (digitalRead(Sw2) == HIGH) {  Seteador = !Seteador; avisala(); }// ---------->>>> entra y sale del seteador  ><<<<<<<<<<<---------   
                                                    // ooooooooooooooooooooooooo ooooooooooo  while de seteador
                                                    paso = false;// evita parpadeo de sobreimpresion del display
                                                   
                                                   
                                                    while (Seteador == true)  
                                                      {   motorGo(0, 2, 0);//quita energia en puente H mientras setea
                                                      //Después de pulsar el botón de reset  los valores almacenados en la función millis() se reinician a cero.

                                                                        // atencion aqui  autoReset();//actualizado dentro del while 
                                                                                                              // if (test==true){Serial.println(F("Seteador true"));}    
                                                                        if (digitalRead(Sw2) == HIGH) { Seteador = !Seteador; }// ---------->>>> entra y sale del seteador  con SwA><<<<<<<<<<<---------
                                                                  leeMEM();
                                                                  Aceptor();//lee el pulsador del rotor (swC=OK) , cambia la variable  Bot (togle)  y acepta=true;   
                                                                  menuSeteador(); //----- void menuSeteador(){// 1-                      
                                                      }  // oooooooooooooooooooooooooooooooooo cierra while de seteador

//7 CIERRA WHILE RUTINA LINEAL
          fotoperiodo();
          pseudoPID_log();
          TERMOSTAT(Tinstant,tempActual,Tmargen);//LLEVA LA PLACA A T1 ó Tinstant
          // atencion aqui  autoReset();	//void software_Reboot()	{	// esta funcion resetea el arduino y se llama cada XXX para evitar bloqueos.	
          displayOLED();
          Debug();
      }//------fin WHILE para rutina soak rampa
}  // WHILE RUTINA LINEAL //----------------------------------------FIN------------------ void Lineal()----------------------y=mx+b() nMODO=DOS(2)








/*
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

}//----------------------------------------FIN------------------void R_termos() 
 */
                                         
                                         
/*
void R_TCritica(){

                                        //ESPERA LLEGUE DEL TERMOSTATO
                                        //SI LLEGUE--> MANTIENE DURANTE 60sg
                                        //SI LLEGUE Y PASO TIEMPO DE SOAK PROPIO HABILITA Tinstant
                                          Tinstant = T2;
}//----------------------------------------FIN------------------ void R_TCritica()
*/