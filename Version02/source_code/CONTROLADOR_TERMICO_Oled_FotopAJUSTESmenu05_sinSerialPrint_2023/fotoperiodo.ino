void fotoperiodo(){   // controla ILUMINACION DENTRO DE LA CAMARA                                                                                     
DateTime now = rtc.now();//toma datos del modulo RTC  
HcRTC = now.hour()+ ( float ) now.minute()/60+  ( float )now.second()/6000;   // hora input para el calculo de la temperatura instantanea      
     // pasan a parametror y luego a MemRTC             
     //   hcOn  =  (8 + ((float)01/60) );//amanecer   8hs01
     //   hcOff =  (20+ ((float)01/60)); //anochecer 20hs01
                                                                                   
        if (( HcRTC >= hcOn) and (HcRTC <= hcOff)            ){                       
                                XhcOn = 0; 
                                XhcOn = hcOn;                       
                                digitalWrite(pinFOTOPERIODO,HIGH);//CONECTA mosfet
                                       /* if (test==true ){ 
                                                        //Serial.println(F("conectado= "));  
                                                        Serial.print(F("               HoraCentesimal: "));Serial.print(HcRTC);Serial.print(F(" voidfotoperiodo-> DIA=Conectado  "));                 
                                                        Serial.print(F("Sunrise: "));Serial.print(hcOn);Serial.print(F("  Sunset : "));Serial.println(hcOff);
                                                       }*/
                               }
             else {digitalWrite(pinFOTOPERIODO,LOW);//DESCONECTA mosfet
                                      /*  if (test==true ){ 
                                                        Serial.print(F("               HoraCentesimal: "));Serial.print(HcRTC);Serial.print(F(" voidfotoperiodo-> NOCHE=Desconectado "));
                                                        Serial.print(F("Sunset "));Serial.print(hcOff);Serial.print(F("  Sunrise: "));Serial.println(hcOn); 
                                                        }*/
            }                                                                                   
} //fin rutina************* fotoperiodo