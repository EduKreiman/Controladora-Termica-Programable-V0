//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>> AQUI SE ESCRIBEN LAS RUTINAS <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


void avisala(){
  digitalWrite(LedPin, HIGH);//enciende o apaga el led
  //digitalWrite(BUZZER,HIGH); 
  delay(200);
  //digitalWrite(BUZZER,LOW);
  digitalWrite(LedPin, LOW);//enciende o apaga el led
  delay(200);
  }


//-------------------------------------------------------------pin ch# B..-------------->>>>>>>>> RUTINA PWM_FRIO SOLO
void PWM_FRIO(int _anchoP) { //_anchoP 0 a 255 del PWM 
   analogWrite(pinINVERSOR_A,0);
   analogWrite(pinINVERSOR_B,0);
   delay(10);//PARA PREVENIR RECALENTAMIENTO DEL PUENTE H 
   analogWrite(pinINVERSOR_A, _anchoP);
   //Serial.print("ENFRIANDOconPWM==");Serial.println(_anchoP);
    Voltimetro();
   }      
//---------------------------------------------------------------------------------->>>>>>>>> RUTINA PWM_FRIO SOLO

//-------------------------------------------------------------pin ch# A..--------------->>>>>>>>> RUTINA PWM_CALOR SOLO
void PWM_CALOR(int _anchoP) { //_anchoP 0 a 255 del PWM 
        analogWrite(pinINVERSOR_A,0);
        analogWrite(pinINVERSOR_B,0);
         delay(10);//PARA PREVENIR RECALENTAMIENTO DEL PUENTE H 
         //e14142
        analogWrite(pinINVERSOR_B, _anchoP);
          // analogWrite(pinINVERSOR_B, 10);
                        // analogWrite(Rled, _anchoP);//ROJO valor PWM    
       //Serial.print("CALENTANDOconPWM==");Serial.println(_anchoP);
        Voltimetro();
      }      
//---------------------------------------------------------------------------------->>>>>>>>> RUTINA PWM_CALOR SOLO
 
 
 void flashAzul(){//FLASH AZUL
                    LEDState = 1; 
                          digitalWrite(LedPin,  LEDState);//enciende o apaga el led AZUL y el de onboard(13)
                          delay(50);//FLASH AZUL
                    LEDState = !LEDState;
                          digitalWrite(LedPin,  LEDState);//enciende o apaga el led   
       }//FLASH AZUL

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
                             if (reinicio == rstMin) {  
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



void TERMOSTAT(float _T1, float _T2, float _margen){ 
 flashAzul(); 
 LLegueT1=0;
//tempTT;//se usa para evaluar si HAY cambio DE TEMP sensor
analogWrite(pinINVERSOR_A,0);
analogWrite(pinINVERSOR_B,0); 
LLegueT1=true;  // avisa on  LLEGUE=1
ENTROPIA = "BALANCE";  //por default   establece balance
    
//if (tempActual!=tempTT){ //---ACTUA-solo si HAY DESVIO DE TEMP -----T2(TemFINAL / SET / GOAL) Y avisa on  LLEGUE=1
    tempTT=tempActual;//ACTUALIZA cambio DE TEMP sensor                                                         
              //->evaluador de FRIO ¿esta por arriba?
                    if( (_T1) < (_T2-(_margen)) ) {//inercia 0.1 grado // A donde voy desde donde estoy ahora                           
                                     PWM_FRIO(PwFrio);//   PWM_FRIO(int _anchoP); int _anchoP determinado por el PID  
                                      ENTROPIA = "COOLING";                  
                     }//------------------fin evaluador de FRIO
                                                            /*
                                                                  // ->evaluador de equilibrio/Balance //Logical AND &&  results in true only if both operands are true.
                                                                  //&& Called Logical AND operator. If both the operands are non-zero then then condition becomes true. (A && B) is true.
                                                                  else if ( (_T1) >=(_T2-(_margen)) && (_T1) <=(_T2+(_margen)) ) { //----LLEGUE dentro del MARGEN ----------
                                                                                    analogWrite(pinINVERSOR_A,0);
                                                                                    analogWrite(pinINVERSOR_B,0); 
                                                                                    LLegueT1=true;  // avisa on  LLEGUE=1
                                                                                      ENTROPIA = "BALANCE";  
                                                                                      LEDState = 1;                      
                                                                                            digitalWrite(LedPin,  LEDState);//enciende o apaga el led AZUL y el de onboard
                                                                                            delay(80);//FLASH AZUL
                                                                                      LEDState = !LEDState;
                                                                                            digitalWrite(LedPin,  LEDState);//enciende o apaga el led                             
                                                                    } //------------------------------------------------------------LLEGUE dentro deL MARGEN
                                                            */
                //->evaluador de CALOR ¿esta por abajo?             
                else if( (_T1) > (_T2-(_margen)) ) {//inercia 0.1°C // donde voy desde donde estoy ahora  
                             PWM_CALOR(PwHot);//        PWM_CALOR(int _anchoP) int _anchoP determinado por el PID 
                              ENTROPIA = "HEATING";                        
                } //------------------fin evaluador de  CALOR        
   //}//fin cambio  habilita solo si la Temp cambio       
}//-------------------------------------------------------------------------------------FIN RUTINA TERMOSTAT


void pseudoPID_log(){ // ajuste  PWM pseudoPID evalua delta(local) y setea PwHot y PwFrio
                          /*                                         
                  s3=2,00 °C	DELTA T max	rango de accion		  float s3 = 0.70;//pid   linea 		
                  s4=38%	PORCENTAJE DE HOT COOL		eficiencia=( hot/cool)	 // float s4 = 0.2;//pid 		
                          -------------------------------------------------------------								
                  s5=	0,335 °C	HISTERESIS variable-->	Tmargen = seteado por s5 es la HISTERESIS del termostato. //float s5 = 1.01;//pid
                          sensor=X	Delta =(T1-tempActual)=x				
                          PWM=	y=m x2 + b0   ---->m=46,3    b0=68
                          */
    m= 46.3;    
    b0=68;
     Tmargen=s5;//variable-->	Tmargen = seteado por s5 es la HISTERESIS del termostato.  
      Tmargen=0.180;//REVISAR //fijo para entrega 
                 
      delta =(Tinstant-tempActual);//delta =(T1-tempActual);
      
       PwFrio=m*delta*delta+b0;//-------> PWM=	y=m x2 + b0   ---->m=46,3    b0=68
                                //s3= NN°C	DELTA T max	rango de accion	
              if((abs(delta))>=   s3)  {PwFrio=255;}

        else if ((abs(delta))<= 0.01)  {PwFrio= 68;}
       //DEBERIA APAGAR EL PUENTE EN ALGUN MOMENTO??? SIN CONTAR CON OPTOCOUPLER
   PwHot=s4/100*PwFrio;//s4=0.036	rango se s4 = 0 a 100 PORCENTAJE DE HOT COOL		eficiencia=( hot/cool)	    
  }//fin  ajuste PWM pseudoPID_log   reduce el PWM si deltaT  SE ACERCA A LA TEMP SETEADA




void monitoreo(){//boolean test=true; PARA DESARROLLO MONITOREADO
if ( test==true) {
            digitalWrite(LedPin , HIGH);//INDICA QUE ESTA ACTIVO  IMPRESIONES POR CONSOLA PARA DESARROLLO
            Serial.println("3 ESTA ACTIVO test==true IMPRESIONES POR CONSOLA PARA DESARROLLO");
            Serial.println(F("   "));  
                      //Serial.println("   ");  
                                Serial.print (F("tempActual Camara = ")); Serial.print (tempActual);//sens nro=  5 
                                Serial.print(F("   nLectu      = "));  Serial.println(nLectu);//  sens nro=  2
                                                            //Serial.print ("D4 AutoPIDoutputVal= "); Serial.println (outputVal); 
                                                            //Serial.print ("A1 INtempPID= ");        Serial.println(temperature);
                                                            //Serial.print ("B2  SetPoint= ");        Serial.println(setPoint);
                                                            
                                                      /*      Serial.print(now.hour(), DEC);//sens nro= 18 // 
                                                                  Serial.print("hs");// separador palabra
                                                            Serial.print(now.minute(), DEC);//sens nro= 19 // de 0 a 59
                                                                  Serial.print("min");// separador palabra
                                                            Serial.print(now.second());// sens nro= 20 // de 0 a 59
                                                                  Serial.println("sg");// 
                                                            */
                                                            //Serial.print ("buffer con cadena formateada "); Serial.println(buf1);// 
                             
                                Serial.print(F("tempAMBIENT= "));    Serial.print (tempAMBIENT); Serial.print(F("  Dist Camara-AireExterior= ")); Serial.println (tempActual-tempAMBIENT);
                                Serial.print(F("BbaTermica  = "));   Serial.print (TempDisip); Serial.println (" ºC");
                                Serial.print(F("Dif Camara-BbaTermica= ")); Serial.print (tempActual-TempDisip);Serial.println (" ºC");
                                
                                Serial.print(F("TEMPERATURA Calc a las "));Serial.print (hs); Serial.print  (F(" hsCENT "));Serial.print  (F( "T_calActual= "));Serial.print ( T_calActual);Serial.println  (F(" ºC")); 
                                Serial.print(F("  Dif T Calc/Camara   = "));  Serial.print (abs(Tinstant-tempActual)); Serial.println (" ºC");   
                                Serial.print(F("incremento amAnecer/anOchecer cada12hs =  "));Serial.print (incremento);Serial.println  (F(" hs   "));
                    Serial.print  (F("   ")); 
                              
                                Serial.print (F("ENTROPIA= "));Serial.print(ENTROPIA); // sens nro= 4
                                Serial.print (F("   conPWM-Frio = "));  Serial.print(PwFrio);
                                Serial.print (F("   conPWM-HOT  = "));Serial.println(PwHot);
                           Serial.println(F("control ---------RTC--------------- "));
                                Serial.print(F("HORA cent RTC "));
                                DateTime now = rtc.now();//toma datos del modulo RTC 
                                Serial.print  (now.hour()+ ( float ) now.minute()/60+  ( float )now.second()/6000);               
                                Serial.print("---->");
                                Serial.print (now.hour());
                                Serial.print(":");
                                Serial.print (  now.minute());
                                Serial.print(":");
                                Serial.println (now.second()); 
                            Serial.println(F("control lectura mem RTC------------------------ "));
                                Serial.print (F(" s4: EFICIENCIA ( hot/cool) = "));      Serial.println(s4);
                                Serial.print (F(" s3:	DELTA T max	rango de accion= "));  Serial.println(s3);
                                Serial.print (F(" s5: HISTERESIS= "));                   Serial.println(s5);
                                Serial.print (F(" T1Goal instant  = "));        Serial.print (Tinstant); 
                                Serial.print (F(" T2-Meta  = "));             Serial.println(T2);//     sens nro=  6   
                                Serial.print (F(" nModo= "));              Serial.println(nModo);//   sens nro=  3 'nModo' 
                            Serial.println (F("   "));    
                                             
                                Voltimetro();       
                                Serial.print(F(" TENSION volts     = "));   Serial.println (tension); 
                        
                                Serial.println  (F("///////////////////////////////////////////"));  
                            }
}//cierre rutina  monitoreo
