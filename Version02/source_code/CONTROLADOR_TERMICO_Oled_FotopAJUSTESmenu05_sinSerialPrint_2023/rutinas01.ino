//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>> AQUI SE ESCRIBEN LAS RUTINAS <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
void Parametror(){ //Parametror()-------------------------AJUSTESySETEOS() 
//------------------------------------SE GUARDAN AL SALIR Y SE LEEN AL ENTRAR
//COLOCAR AL FINAL DE   leeMem();                     
/*
                      Serial.println("Leyendo datos guardados...leeMEM()");
        aAT24 = EepromRTC.readFloat(2); //int  //nModo= 2  posicion
        bAT24 = EepromRTC.readFloat(8); //float//T1 
        cAT24 = EepromRTC.readFloat(12);//float//T2 
        dAT24 = EepromRTC.readFloat(16);//float// hcOn //amanecer SUNRISE
        eAT24 = EepromRTC.readFloat(20);//float// hcOff//anochecer SUNSET    
//---------DECLARADAS SIN USAR--------
          //USARLAS PARA GUARDAR POSICIONES INSTANTANEAS DE LOS SETEOS DE T1 T2 HCON ACOFF
        //float fAT24;  T1     hcOn //amanecer SUNRISE
        //float gAT24;  T2     hcOff//anochecer SUNSET
        //char cadenaTiempo;
  */

//                    grabaMEM(); {//guarda datos de variables a recuperar luego del reset
/*
  EepromRTC.writeFloat(2,nModo); // posicion 2:INT ocupa 4 bytes de tamaño  
                   // menuTEMP()
  EepromRTC.writeFloat(8,T1); // posicion 8:FLOAT ocupa 4 bytes de tamaño 
  EepromRTC.writeFloat(12,T2); // posicion 8:FLOAT ocupa 4 bytes de tamaño 
                    // menuFOTO() float dia  float noche 
                        //      hcOn  =  //amanecer   8hs01  
                        //      hcOff =  //anochecer 20hs01   
  EepromRTC.writeFloat(16,hcOn); // posicion 8:FLOAT ocupa 4 bytes de tamaño 
  EepromRTC.writeFloat(20,hcOff); // posicion 8:FLOAT ocupa 4 bytes de tamaño 
          */
//------------------------------------DINAMICAS PARA SRAM
       // nModo = 2;//y=mx+b() nMODO=DOS(2)
                     // nModo = 4; // nModo posicion  rutina rutMODO()

                  //    T1 = 33;   // Tim posicion    // tempArranque -GOAL->  temp de inicio 
                  //    T2 = 1.15;   // tma posicion    // tempSET ------META->  temp a llegar en rampa -
                      //                                          Tinstant
                  //    hcOn  =  (8 + ((float)01/60) );//amanecer   8hs01  rutina fotoperiodo CENTESIMAL
                  //   hcOff =  (20+ ((float)01/60)); //anochecer 20hs01
//------------------------------------DINAMICAS PARA SRAM


//--------------------------------DESAROLLO Y DEBUG
// colocada en el setup 
test01 = false;  //boolean test=true; PARA DESARROLLO MONITOREADO de modos
test=false;// debug de control y desarrollo PARA DESARROLLO MONITOREADO 
                                      //if (test==true ){ serial.print
tomas=5000;// Set min interval in milliseconds between 2 measurements. Default 10000 set in setup() method.
//DS18B20Events::setInterval(tomas); 
rstMin = 7;    // tiempo en minutos para disparar auto reset
//mRecta =15;   //0.000004167;   //0.25 / 60;    unidad second()  pendiente de la recta  m=1 grado cada 4 minutos
//----------------------------------------


// TUNING Y AJUSTES ---------------------------
  s3 = 1.00;      //en °C	DELTA T max	rango de accion		  float s3 = 0.70;//pid   linea 

//----------------------------------------
            //el efecto Peltier es mas eficiente calentando que enfriando 
  s4 = 50;  // % eficacia hot/cool rutina pseudoPID // float s4 = 0.00;//pid 
 if (   ( abs(T2-T1) > 10)   && ( nModo==2)   ){s4=80;} //colocada en leeMEM();

//----------------------------------------

Tmargen=0.100;//en °C	 HISTERESIS variable-->	Tmargen   REVISAR //fijo para entrega    							
//Tmargen = s5;  //en pseudo PID  (Tmargen = s5;) es la HISTERESIS del termostato.//float Tmargen = 0.00;


//---------------------------------------------------------
/* tabla/registro para ajuste sensores medicion en camara 
          bimetalico   ds18b20 azul        ds18b20 negro
          32           32.95  -0.95=30.00                    
          27                                29.30-3.25=27
          const float adjSensor 
--------------------------*/
//                    tempActual = tempActual + adjSensor; // corrector de desvio del sensor de temperatura DS18b20
adjSensor= 0.200;    //COEF DE CALIBRACION DEL SENSOR   tempActual linea 483 -------------------para negro contraible
//                     REFERENCIA USADA DATTALOGGER A 30 ºC

//adjSensor = -0.95; //COEF DE CALIBRACION DEL SENSOR   tempActual linea 483  -0.95 ------------para ds18b20 azul  

/* -------------------------------------------------------------	
    sensor=X	Delta =(T1-tempActual)=x		
              --->>>>    PWM=	y=m x2 + b0   <<<-----
m= 46.3;  //original laboratorio  
b0=68;    //original laboratorio 
-------------------------------------------------------------  */

m= 2000;  //--->>>>    PWM=	y=m x2 + b0   <<<-----
b0=120;// cruce eje X  cero
//---------------------------------------------------------
    /*
    Serial.print(F("parametror--->        T1= "));Serial.println(T1,4); 

    Serial.print(F("parametror--->        T2= ")); Serial.println(T2,4); 
    Serial.print(F("leeMEM-----  >        s4= ")); Serial.println(s4); 

    Serial.print(F("***** parametror--->  mRecta = "));  Serial.println(mRecta);// Configuración de la pendiente de la recta 

    */

}//Parametror()-------------------------AJUSTESySETEOS()  
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
/*
void pseudoTemperature2(){  //--
 DateTime now = rtc.now();  //toma datos del modulo RTC
 hs = now.hour()+ ( float ) now.minute()/60+  ( float )now.second()/6000;   
 // horaAnt = now.hour();     //hora de inicio del setup y control de reset cada N horas
 // minutAnt = now.minute();  //minuto de inicio del setup y control de reset cada N minutos
// if (i % 2 == 0){ // La condición que hemos impuesto
 // if ((now.minute()-minutAnt)%2==0){ tempActual=T1+0.2;} 
   if ( ( ( (now.second()) - minutAnt ) %2)==0)   { tempActual=T1+0.2;}// cada 
} 
*/
float obtenerHoraCentesimal(){//  funcion devuelve  hs -->(hora reloj en formato centecimal)  
      DateTime now = rtc.now();//toma datos del modulo RTC 
      hs = now.hour()+ ( float ) now.minute()/60+  ( float )now.second()/6000;  
      return;
      }//

void pseudoTemperature(){  //simulacion de evolucion termica por bomba de calor peltier
//unsigned long tiempoLectura = 0;   // Tiempo inicial
//unsigned long duracionLectura = 0; // D//
     if (tiempoLectura == 0) { tiempoLectura = millis();}// Si el tiempo ya paso, se guarda el tiempo actual
  duracionLectura = millis() - tiempoLectura;   // Calcula la duración                        
  //Serial.println(duracionLectura); // Imprime la duración de la presión del botón 
if (duracionLectura>=2000){  
             if(pasoSoak==false){ tempActual=(T1+T2)/2; } //en SOAK llegar a T1 desde el promedio de T1yT2
             if(pasoSoak== true){ tempActual=tempActual+(0.75*(abs(mRecta)/mRecta)); } //en RAMPA cambia cada 2 segundos
    tiempoLectura=0;  }// cada 2 segundos
}

void Debug(){ /*
  if (test==true ){ //////////////// debug de control y desarrollo
              Serial.print(ENTROPIA);Serial.print(F(" conPWM= "));Serial.print(PwFrio); Serial.print(F("/"));Serial.print(PwHot);Serial.print(F(" Tensión= "));Serial.print(tension);Serial.print(F("v"));
              Serial.print(F("    TempCamara Ti= "));Serial.print(tempActual);Serial.print(F("        TempCalc  instant= "));Serial.print( Tinstant);
              Serial.print(F("        PENDIENTE= "));Serial.print( mRecta); 
              // Serial.print(F("    miliStart= "));Serial.print(miliStart);
            //  Serial.print(F("   TimeStart= "));Serial.print(TimeStart,6);
              // Serial.print(F("   avance= "));Serial.println(miliAvance);//Serial.println(millis()-miliStart); 
             // Serial.print(F("     avance= "));Serial.println(Avance,6);//Serial.println(millis()-miliStart);
          //pasoSoak==false--> SOAK           pasoSoak==true-->RAMPA  
              if(pasoSoak==false){  Serial.println(F("  SOAK-ing ++++++++ pasoSoak==false")); }//--  soak no concluyo aun -
              if(pasoSoak==true ){  Serial.println(F("  ..**..**..**.. RAMPA-NDO pasoSoak==true ")); } 

              //Serial.print(F(" TIEMPO ENTRE press BotonS= ")); Serial.print(duracionLectura); // Imprime la duración de la presión del botón 
              Serial.print(F("       T1= "));Serial.print(T1);  Serial.print(F("     T2= "));Serial.print(T2);
              Serial.println("");
              Serial.print(F(" TempAire exterior= "));Serial.print(tempAMBIENT);
              Serial.print(F(" SaltoTº Int/Ext= "));Serial.print(tempActual-tempAMBIENT); Serial.print(F(" DELTA Goal/Camara "));Serial.println(tempActual-Tinstant);
              
                              }
               */} // fin debug de control y desarrollo


//auxiliar de lee pulsador------------------------------------
void done() {Serial.print(F("Beep y Boton PASO LA FUNCION"));} 

void numREAL(){  //------------------void numREAL()------ENTEROS + DECIMALES--------aumenta una decima--------
                    Bot=false;
                    contador = 0 ;
                    incrementa=incrementa+incrementador;
                    if (incrementa>=1)  { incrementa=0; } // maximo decimal
                    if (setFoto==true){if (incrementa>=0.982)  { incrementa=0; } }// maximo sexagesimal
                    newPosition = myEnc.read();  //newPosition se actualiza cada vez que se consulta desde la libreria
                        if ((newPosition!= oldPosition)||(Bot==true)){
                                                          Bot=false;
                                oldPosition = (newPosition);
                                                    if (test01==true ) {Serial.print(newPosition); Serial.print("+");Serial.print(incrementa);Serial.print("=  ");Serial.println(incrementa+newPosition);}
                                //delay(10);
                                oled.set2X();
                        } 
                }//fin --------------void numREAL()  ----------aumenta una decima-----------


void numREAL0(){  //------------------void numREAL()---------SOLO ENTEROS-------------
                    Bot=false;
                   // contador = 0 ;
                    //incrementa=incrementa+incrementador;
                   // if (incrementa>=1)  { incrementa=0; } // maximo 0.75
                   // delay(150);
                  
                    newPosition = myEnc.read();  //newPosition se actualiza cada vez que se consulta desde la libreria
                        if ((newPosition!= oldPosition)||(Bot==true)){
                                                          Bot=false;
                                oldPosition = (newPosition);
                                                    if (test01==true ) {Serial.print(incrementa+newPosition);Serial.print(F("=Real= "));Serial.print(newPosition); Serial.print(F("+"));Serial.println(incrementa);}
                                //delay(10);
                                oled.set2X();
                                          // oled.setCursor(140/2, 6);oled.print("           ");
                                           // oled.setCursor(140/2, 6);oled.print( incrementa + newPosition );
                                           // oled.setInvertMode(2 % 2);
                        } 
                }//fin --------------void numREAL()
/*
void HHmm_a_HHcc()  {	//funcion -- HHmm_a_HHcc()

double numero = 21.45;//hora sexagesimal
 //Serial.println(numero);
	int horas = (int) numero;//hora
 // Serial.print(parteEntera);
 // Serial.print(":");
	double minutos = numero - horas;//minutos
//Serial.println(parteDecimal);
//hcON=NN.00+(00.NN*100/60); separa la parte decimal DE() incrementa + newPosition ) para convertir la hora sexa a hora centesimal
//hcON=NN.00+(00.NN*100/60); separa la parte decimal DE() incrementa + newPosition ) para convertir la hora sexa a hora centesimal
Serial.print("hora centesimal XD= ");Serial.println(horas+(minutos*100/60));
} //cierre funcion -- HHmm_a_HHcc()
*/

/*
void hhNN_a_hhSX()  {	//funcion -- hora decimal a hora sexagesimal
double horaNN = 21.75;//horaNN 
	int horas = (int) horaNN;
Serial.println(horas);
 // Serial.print(":");
	double decimal = horaNN - horas;//CENTECIMOS
Serial.println(decimal);
//hcON=NN.00+(00.NN*100/60); separa la parte decimal DE() incrementa + newPosition ) para convertir la hora sexa a hora centesimal
//hcON=NN.00+(00.NN*100/60); separa la parte decimal DE() incrementa + newPosition ) para convertir la hora sexa a hora centesimal
//Serial.print("hora centesimal XD= ");Serial.println(horas+(minutos*100/60));
Serial.print("hora SEXAGESIMAL= ");Serial.println(horas+(decimal*60/100));
} //cierre funcion -- HHmm_a_HHcc()
*/

void hhNN_a_hhSX(double _hhNN)  {	//funcion --convierte hora decimal a hora sexagesimal
	int horas = (int) _hhNN;
  double decimal = _hhNN - horas;//CENTECIMOS
  hhSX=(horas+(decimal*60/100));
                                          //Serial.print("hora SEXAGESIMAL= ");Serial.println(hhSX);
                                          //Serial.println(horas);
                                          // Serial.print(":");
                                          //Serial.println(decimal);
                                          //Serial.print("hora SEXAGESIMAL= ");Serial.println(horas+(decimal*60/100));
} //                               cierre funcion -- hhNN_a_hhSX(double _hhNN)





void  PushBoton(){//Medir el tiempo QUE esta pulsado un boton-----------------------------------------------------------
float Tiempo  = 0;
float Tiempo2 = 0;
bool estadoboton1=false;
                  //estadoboton1 = digitalRead(A2); //Sw2= SwA  pin ardu A2   pull down con resistencia 1K5 y FILTRO 100NF en PCB 
                    estadoboton1 = digitalRead(A1); //Sw1= SwB  pin ardu A2   pull down con resistencia 1K5 y FILTRO 100NF en PCB 
                              delay(59);
                                      if(estadoboton1 == HIGH) { 
                                      Tiempo=millis();
                                                    while(estadoboton1 == HIGH) { 
                                                                            Tiempo2=millis();
                                                                            estadoboton1 = digitalRead(A1);
                                                                            //delay(15);
                                                                            }
                        //if((Tiempo2-Tiempo)<1500 ){Serial.println(F ("PRIMER SETEO <<<<< DECIMALES")); } // incrementa decimales
                        //else 
                        if((Tiempo2-Tiempo)>2500 ){ Serial.print(F ("PASA A SETEO --T1/T2---= ")); miniMenu=!miniMenu;}//cambia de seteo
                        Serial.println(Tiempo2-Tiempo);}
}//cierre             Medir el tiempo QUE esta pulsado un boton-----------------------------------------------------------

void pseudoPID_log(){ // ajuste  PwHot y PwFrio
                     // pseudoPID evalua delta(local) y setea PwHot y PwFrio
                                                /*                                         
                                        s3=2,00 °C	DELTA T max	rango de accion		  float s3 = 0.70;//pid   linea 		
                                        s4=38%	PORCENTAJE DE HOT COOL		eficiencia=( hot/cool)	 // float s4 = 0.2;//pid 		
                                                -------------------------------------------------------------								
                                        s5=	0,335 °C	HISTERESIS variable-->	Tmargen = seteado por s5 es la HISTERESIS del termostato. //float s5 = 1.01;//pid
                                        //                                    Tmargen=s5;//variable-->	Tmargen = seteado por s5 es la HISTERESIS del termostato.  
                                        //                                    Tmargen=0.180;//REVISAR //fijo para entrega                                             
                                         */       



// sensor=X	Delta =(T1-tempActual)=x				
//----------------------------  PWM=	y=m x2 + b0  
//-------------------------------------->delta al cuadrado, logaritmica / parabolica 
          // m= 46.3;  //original laboratorio  
          // b0=68;  //original laboratorio           
delta =(Tinstant-tempActual);//delta =(T1-tempActual);
//------->delta al cuadrado, logaritmica / parabolica
  PwFrio=m*delta*delta+b0;//-------> PWM=	y=m x2 + b0   ---->m=46,3    b0=68
if((PwFrio)>= 255)  {PwFrio=255;} //limite matematico
//----------------------------  ----------------------------------------  

//----------------------  s3= NN°C	DELTA T  rango de accion----> entre s3 y 0.01 °C
if      ((abs(delta))>=   s3)  {PwFrio=255;}
else if ((abs(delta))<= 0.01)  {PwFrio= 5;}

       //DEBERIA APAGAR EL PUENTE EN ALGUN MOMENTO??? SIN CONTAR CON OPTOCOUPLER     

PwHot=s4/100*PwFrio;//    s4 = 0 a 100 PORCENTAJE DE eficiencia=( hot/cool)	    
 }//fin  ajuste PWM pseudoPID_log   reduce el PWM si deltaT  SE ACERCA A LA TEMP SETEADA



void avisala(){//--------------------------avisala()-----------------------------------------------
                                                                /*
                                                              #define PIN_A0 (14)
                                                              #define PIN_A1 (15)
                                                              #define PIN_A2 (16)
                                                              #define PIN_A3 (17)
                                                              #define PIN_A4 (18)
                                                              #define PIN_A5 (19)
                                                              #define PIN_A6 (20)
                                                              #define PIN_A7 (21)
                                                              */
 // En arduino Uno si se quiere utilizar el pin A0 como entrada digital seria:
//  pinMode(14,INPUT); y por supuesto como salida pinMode(14,OUTPUT); 


pinMode(14,OUTPUT);// const int BUZZER = A0;//buzzer  con led azul en paralelo   si usa pasivo generar rutina de tono 450Hz o libreria EasyBuzzer

  for(int i = 1; i<5; i++){
                              digitalWrite(pinFOTOPERIODO,HIGH);//CONECTA led
                              digitalWrite(14, HIGH);//enciende o apaga el led
                              delay(200);
                              digitalWrite(pinFOTOPERIODO,LOW);//apaga 
                              digitalWrite(14,LOW); 
                              delay(400);
                      }
}//--------------------------avisala()-----------------------------------------------


void wdt_delay(unsigned long msec) {// -------------------delay to reset the WDT---------------------
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
                                      }// -------------------delay to reset the WDT---------------------

//para recargar la placa, solo tienes que retrasar > WDT
//otra opción es poner el WDT muy corto, y hacer un delay() corto


void wdt_reload() {
                      delay(8001);
                 }

/*
comandos: wdt_enable(timeout)
          wdt_disable()
          wdt_reset()
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

 void autoReset() { //rutina autoreset duplicarlo dentro del while (dentro no llegaria) 
                          wdt_disable();  //siempre es bueno deshabilitarlo al comienzo
                          DateTime now = rtc.now();  //toma datos del modulo RTC                
                          reinicio = now.minute() - minutAnt;
                                          /*
                                          Serial.print(F(" ahora: "));     Serial.print(now.minute());
                                          Serial.print(F("   anterior: "));Serial.print(minutAnt);//Serial.println(F("  minutos"));
                                          Serial.print(F("   reset en: "));Serial.print(reinicio);Serial.println(F("  minutos"));Serial.print(F("  timeReset: "));Serial.println(rstMin);
                                        */
                          if (reinicio < 0) { reinicio = reinicio + 60; }
                          // Serial.print(F("  resetB en: "));Serial.print(rstMin-reinicio);Serial.println(F("(minutos)"));
                          Mreinicio = minutAnt + rstMin;
                          // Serial.print(F("  Mreinicio: "));Serial.print(Mreinicio);
                          if (Mreinicio > 60) { Mreinicio = Mreinicio - 60; }
                          // Serial.print(F("  minutoReset: "));Serial.println(Mreinicio);
                          //if ((now.hour()-horaAnt) == 1){// reset por wdt cada N horas para prevenir bloqueos y overflow/saturacion
                          wdt_disable();  //siempre es bueno deshabilitarlo al comienzo

                             if (reinicio == rstMin) {  //571 auto reset
                                                              /*  instance-method hour     @return Hour (0--23).  uint8_t  entero sin signo de 8 bits. 
                                                                                                                        // In DateTime
                                                                                                                        public: uint8_t hour() const

                                                                                                                        uint8_t                     int sin signo de 8 bits. 
                                                                                                                        uint_fast8_t    más rápido  int sin signo con al menos 8 bits. 
                                                                                                                        uint_least8_t               int sin signo con al menos 8 bits.
                                                                                                                        */
                                                              //horaAnt=now.hour();	// se define en el setup cada vez que reinicia
                                                              // minutAnt = now.minute();// se define en el setup cada vez que reinicia
                                      //Serial.println(F("nModo INT ;t1  FLOAT;hot_cool  INT ;t2  FLOAT; time stamp"));
                                      grabaMEM();  //  guarda los datos de seteo en la EEPROM del RTC
                                      //alcanza tiempo para grabar antes del reset  ???
                                      // oled.clear();
                                       wdt_enable(WDTO_8S );//15 milisegundos y hace el reset 			10-07-2022  WDTO_30MS  WDTO_15MS  WDTO_500MS  WDTO_2S WDTO_8S
                                     while(1){	}	
                                    //software_Reboot();  // reset por wdt cada N horas para prevenir bloqueos y overflow/saturacion
                                     }
                            }//fin autoReset------------------------	




  void TERMOSTAT(float _T1, float _T2, float _margen){ //------------------- RUTINA TERMOSTAT
//avisala();
LLegueT1=true;  // avisa on  LLEGUE=1
ENTROPIA = "BALANCE";  //por default   establece balance
tempTT=tempActual;//ACTUALIZA cambio DE TEMP sensor  //tempTT;//se usa para evaluar si HAY cambio DE TEMP sensor                                                               
     //->evaluador de FRIO ¿esta por arriba?
                    if( (_T1) < (_T2-(_margen)) ) {//inercia 0.1 grado // A donde voy desde donde estoy ahora                           
                                //motorGo(motor,  1cool 2hot, pwm) pwm =0 a 1023
                                      motorGo(0,         1, PwFrio);
                                      Voltimetro(); 
                                      ENTROPIA = "COOLING"; 
                                    //  Debug(); // debug de control y desarrollo                             
     }//------------------fin evaluador de FRIO
                                                           
    //->evaluador de CALOR ¿esta por abajo?             
                else if( (_T1) > (_T2-(_margen)) ) {//inercia 0.1°C // donde voy desde donde estoy ahora  
                             //motorGo(motor, 1cool 2hot, pwm) pwm =0 a 1023
                                      motorGo(0,         2, PwHot);               
                                      Voltimetro(); 
                                      ENTROPIA = "HEATING";  // 
                                   //   Debug();                       
     } //------------------fin evaluador de  CALOR       
}//-------------------------------------------------------------------------------------FIN RUTINA TERMOSTAT






/*
//---------------------------------------------------------------------------------->>>>>>>>> RUTINA PWM_FRIO SOLO
void PWM_FRIO(int _anchoP) { //_anchoP 0 a 255 del PWM 
  /* analogWrite(pinINVERSOR_A,0);
   analogWrite(pinINVERSOR_B,0);
   delay(1);//PARA PREVENIR RECALENTAMIENTO DEL PUENTE H 
   analogWrite(pinINVERSOR_A, _anchoP);
   //Serial.print("ENFRIANDOconPWM==");Serial.println(_anchoP);
   */
   
  //
  // }      

/*
//-------------------------------------------------------------pin ch# A..--------------->>>>>>>>> RUTINA PWM_CALOR SOLO
void PWM_CALOR(int _anchoP) { //_anchoP 0 a 255 del PWM 
       /* analogWrite(pinINVERSOR_A,0);
        analogWrite(pinINVERSOR_B,0);
         delay(1);//PARA PREVENIR RECALENTAMIENTO DEL PUENTE H 
        analogWrite(pinINVERSOR_B, _anchoP);
                        // analogWrite(Rled, _anchoP);//ROJO valor PWM    
       //Serial.print("CALENTANDOconPWM==");Serial.println(_anchoP);
       */
      //  Voltimetro();
    //  }      
//---------------------------------------------------------------------------------->>>>>>>>> RUTINA PWM_CALOR SOLO
 
//---------------------------------------------------------------------------------->>>>>>>>> RUTINA  Voltimetro()
void Voltimetro(){  //El código lee el voltaje en analogPin y lo muestra.
int sensorValue; // variable que almacena el valor raw (0 a 1023) 
//float tension=0; // variable que almacena el voltaje (0.0 a 25.0) 

   sensorValue = analogRead(pinPOTE); //realizar la lectura    pinPOTE es A3 
  /* 5 voltios / 1024 unidades o , 0,0049 voltios (4,9 mV) por unidad.
COMANDO analogReference(type)   Configura el voltaje de referencia utilizado para la entrada analógica 
(es decir, el valor utilizado como la parte superior del rango de entrada). 
Las opciones son:EXTERNAL: 
the voltage applied to the AREF pin (0 to 5V only) is used as the reference.
Don’t use anything less than 0V or more than 5V for external reference voltage on the AREF pin! 
If you’re using an external reference on the AREF pin, 
you must set the analog reference to EXTERNAL before calling analogRead()
   */ 
       //    map       (value, fromLow, fromHigh,    toLow,  toHigh)    
 //tension = fmap(sensorValue, 0,           1023,      0.0,    16.5254); //llama  funcion para  cambiar escala a 0.0 - 25.0 
 tension = fmap(sensorValue, 0,           1023,      0.0,    10.45); //llama  funcion para  cambiar escala a 0.0 - 25.0 
                                 //Serial.println(value); // mostrar el valor por serial 
                                 //delay(500); 
   } 

   //The map() function uses integer math so will not generate fractions
   //if your project requires precise calculations 
   //(e.g. voltage accurate to 3 decimal places), please consider avoiding map() and 
   //implementing the calculations manually in your code yourself.
   
   // funcion para cambio de escala MAPEO entre floats 
   //    map   (value, fromLow,          fromHigh,         toLow,        toHigh)
   float fmap(float x, float in_min, float in_max, float out_min, float out_max) 
   { return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min; }
//---------------------------------------------------------------------------------->>>>>>>>> RUTINA  Voltimetro()




//---------------------------------------------------------------------------------->>>>>>>>> RUTINA  motorGo()
/* motorGo() will set a motor going in a specific direction
 the motor will continue going in that direction, at that speed
 until told to do otherwise.
 
 motor: this should be either 0 or 1, will selet which of the two
 motors to be controlled
 
 direct: Should be between 0 and 3, with the following result
 0: Brake to VCC
 1: Clockwise           FRIO
 2: CounterClockwise    CALOR
 3: Brake to GND
 
 pwm: should be a value between 0 and 1023, higher the number, the faster
 it'll go
 */
//                   puente,           F/C,      pwm 
void motorGo(uint8_t motor, uint8_t direct, uint8_t pwm)
{
  if (motor <= 1)
  {
    if (direct <=4)
    {
      // Set inA[motor]
      if (direct <=1)
        digitalWrite(inApin[motor], HIGH);
      else
        digitalWrite(inApin[motor], LOW);

      // Set inB[motor]
      if ((direct==0)||(direct==2))
        digitalWrite(inBpin[motor], HIGH);
      else
        digitalWrite(inBpin[motor], LOW);

      analogWrite(pwmpin[motor], pwm);
    }
  } 
}//---------------------------------------------------------------------------------->>>>>>>>> RUTINA  motorGo()

void temperatureChanged(uint8_t index, float tempC) {
  /*
  Serial.print(tempC);
  Serial.print(F(" new tempC at index "));
  Serial.println(index);
  */
}


void DisplayLCD(){
/*lcd.setTextSize(3);
  tempAMBIENT = rtc.getTemperature();          // LEER TEMPERATURA DEL modulo RTC  DEVUELVE   Current temperature (float)
  tempAMBIENT = tempAMBIENT + ajustambiental;  // corretor de desvio del sensor de temperatura
  lcd.setTextColor(BLUE, BLACK);
  lcd.println(tempAMBIENT);
  */
//----------------------------------------------------------------------display ------------------------------------------------------------------------
}





 
