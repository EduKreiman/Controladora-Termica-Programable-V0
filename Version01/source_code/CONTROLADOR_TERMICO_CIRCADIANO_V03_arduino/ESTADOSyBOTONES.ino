void DETENCION(){ // FIN DE CICLO  Ó ABORT MISION-------------BOTON/PIN A2-----------------ROJO                             
                    //APAGA TODO                             
                    ESTADO_E=0;//EVENTO
                    ESTADO_A=0;
                    //ESTADO_S=0; //modo autonomo
                    ESTAnt_S=0;
                digitalWrite (pinOPTOCUPLER, LOW);
               }           // FIN DE CICLO  Ó ABORT MISION------------BOTON/PIN A2-----------------ROJO    
                                    

void EstadosyBotones() 
{//---------------------------------------------------------------------------                        
  //LOGICA DEL SWITCH PULL DOWN PARA EVITAR PULSO falso POR CAIDA DE TENSION
  // read the input pin devuelve   HIGH or LOW reposo es LOW presionado es HIGH
                      /*
                      const int pinEVENTO= A0;   // BOTON EVENTO       
                      const int pinSTART = A1;   // BOTON START/INICIO 
                      const int pinABORT = A2;   // BOTON  ABORT/Stop  */
//ESTADO_S=false;  
//ESTADO_A=false;
  S=digitalRead(pinSTART);   // read the input pin devuelve   HIGH or LOW reposo es LOW presionado es HIGH
  if (S==HIGH || dataIN == '2') {
                                ESTADO_S=1;  
                                ESTADO_A=0;
                                        /*  avisala();
                                        avisala();
                                          delay(500);
                                          avisala();//2  */
                                digitalWrite (pinOPTOCUPLER, HIGH);
                                Serial.print("1- "); //PALABRA del PAQUETE
                                Serial.print("Estoy_recibiendo_un_START_2="); 
                                Serial.println(dataIN); //Enviamos los datos en forma de byte     
                              }

  A=digitalRead(pinABORT);   // read the input pin devuelve   HIGH or LOW reposo es LOW presionado es HIGH
  if (A==HIGH || dataIN == '3') {
                                ESTADO_S=0;  
                                ESTADO_A=1;// FIN DE CICLO  Ó ABORT MISION------------BOTON/PIN A2-----------------ROJO   
                                           for (int avi=0; avi<=3;avi=avi+1) {avisala();}avisala();        
                                digitalWrite (pinOPTOCUPLER,  LOW); 
                                Serial.print("3- "); //PALABRA del PAQUETE
                                Serial.print("Estoy_recibiendo_un_ABORT="); 
                                Serial.println(dataIN); //Enviamos los datos en forma de byte      
                              }

  E= digitalRead(pinEVENTO); // A0
  if (E==HIGH) { // EVENTO SOLO desde PROCESSING PARA GUARDAR EN FILE 
                       digitalWrite (BUZZER,1);
                        delay(75);
                       digitalWrite (BUZZER,0);
                                 
                      //Usare el PuLSADOR  para desarrollo toggle de variables test=false 
                      //luego se habilitara el selector rotativo y leds 
                      test=!test;
                      //test=1;//habia un error de coneccion en el pcb frontal 4-7-22
                                           for (int avi=0; avi<=5;avi=avi+1) {avisala();}
                                              delay(150);
                                          
                                  if (test)    { 
                                              delay(150);
                                         for (int avi=0; avi<=2;avi=avi+1) {avisala();}
                                       Serial.println(" ESTA ACTIVO test==true por pulsador E hard PARA DESARROLLO");
                                              }
                  }
                  
  //Serial.print(F("SWITCHs= a1=S   a2=A   a0=E      ")); Serial.print(S);  Serial.print(A); Serial.println(E);  
 // Serial.print(F("Estados= S   A   AS      ")); Serial.print(ESTADO_S);  Serial.print(ESTADO_A); Serial.println(ESTAnt_S);  

} // CIERRE ------------------------------------------------------------------------EstadosyBotones11




/* //carga tiempo inicial para de calculo  de las funciones temp f tiempo  usar WD-TIMER
  //y=mx+b
                                      digitalWrite(pinOPTOCUPLER, HIGH);// Led OPTOCUPLER cable verde de fuente HIGH CONECTA 
                                     
                                      miliStart=0;
                                        if (ESTAnt_S==0){//solo 1 vez si no hay cabio en ESTADO_S==1 
                                          ESTAnt_S= 1; 
                                          miliStart=0;
                                                  digitalWrite(pinOPTOCUPLER, HIGH);// Led OPTOCUPLER cable verde de fuente HIGH CONECTA 
                                                        //carga tiempo inicial para de calculo  de las funciones temp f tiempo
                                                        //y=mx+b
                                                        delay(150);//evita pico de consumo en fuente ????                                                                                                
                        */
