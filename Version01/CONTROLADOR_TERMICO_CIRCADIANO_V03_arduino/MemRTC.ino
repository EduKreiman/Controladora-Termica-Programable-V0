void grabaMEM(){ //guarda datos de variables a recuperar luego del reset
                                
                  Clock.formatEEPROM();// Erase the contents of the EEPROM
                  MyLogDataStructure loggedData; //define estructura de datos 

                            //set 1  assemble our data into a variable               
                                          loggedData.nModo  = nModo;      //int
                                          loggedData.te1  = T1*100;   //int   T1=loggedData.te1/100;
                                                                //tempMin
                                                                /* para circadiano Vz la rutina tiene fija 
                                                                  tempMin=16.00;//activa Slider s1 // modo tropical VZ
                                                                  tempMax=32.00;//activa Slider s2 // modo tropical VZ
                                                                  deltaT=0;
                                                                  deltaT=tempMax-tempMin;
                                                                  */
                            //ES PREFERIBLE GUARDAR s3  s5
                            
                                        Clock.writeLog(loggedData);// ESCRIBE set 1
                                                                  Serial.print('.');

                            //set 2  assemble our data into a variable    
                                          loggedData.nModo  = s4; //int s4=loggedData.nModo/100; REVISAR esto
                                          loggedData.te1  = T2*100;  //int // T2=loggedData.te1/100;
                                        Clock.writeLog(loggedData);  //ESCRIBE set 2
                                                                  Serial.print('>');

                }


void leeMEM(){// lectura y presentacion y recupera datos en variables
//nModo = 3;// 3= circadiano para test autonomo

                MyLogDataStructure loggedData;//define estructura de datos 
                DateSTime     loggedTime;
                
                // Note that reading a log entry also deletes the log entry
                // so you only get one-shot at reading it, if you want to do
                // something with it, do it before you discard it!
               // unsigned int x = 0;
                // while(Clock.readLog(    loggedTime,loggedData))//
                //Passed by reference as timestamp, as data
  
   Serial.println(F("nModo INT ;t1  FLOAT;hot_cool  INT ;t2  FLOAT; time stamp"));     
                Clock.readLog(    loggedTime,loggedData);  //leo set 1                   
                                  nModo=loggedData.nModo;
                                  if (nModo >=7   ){nModo=3;}
                                  Serial.print(" nModo INT="); Serial.println(nModo);                                 
                                  T1=loggedData.te1/100;
                                  Serial.print(" int/100 t1=");Serial.println(T1);

                Clock.readLog(    loggedTime,loggedData);   //leo set 2                                     
                                  s4=loggedData.nModo/100;
                                  Serial.print(" int hot_cool=");Serial.println(s4);
                                  T2=loggedData.te1/100;
                                  Serial.print(" float t2="); Serial.println(T2);
 
                Clock.printTo(Serial,loggedTime);
nModo=3; //REVISAR QUEDA FIJO PARA VZ CIRCADIANO 

                      Serial.println(' ');   
  // Erase the contents of the EEPROM
      Clock.formatEEPROM();
              }//cierre funcion  leeMEM