/*-------------------------------------------------------------------
menues display 
---------------------------------------------------
oled 128*64	SSD1306	
1+ 10 +1   ancho caracter x2 =12
4 12 4   borde caracteres borde =128
-------------------------
1+ 5 +1   ancho caracter x1 = 7
1 18 1   borde caracteres borde =128




-------------------------------------------------

cararcteristicas funcionales:
Menues ciclicos  e intuitivos con solo 5 operadores para todos los parametros.
un reloj de tiempo real con bateria de 10 años de vida y una memoria Sram (no volatil),
Permiten el funcionamiento continuo aun con cortes de energia, dado que al reiniciar toma los parametros  seteados y 
los aplica a la hora de actualizada para continuar la funcion establecida en la memoria.




--Manual de uso --------------------------------------------------------------------------------
Operadores:
            A boton:  ciclico para entrar y salir del menu en curso
            B boton   pulso corto avanza decimas de grado o 5 minutos de hora
            B boton   pulso mayor de 10 Sg ciclico para pasar de T1 a T2 o de Dia a Noche
            C pulsad  rotativo  Amarillo  -OK/ACEPTA-acepta la opcion o el campo mostrado en el display 
            
             
             Entra y Sale     ->A
             Cambia Numeros   ->Rotor 
             Acepta           ->C=OK
             Cambia decimales ->B pulso 1 Sg 
             Cambia Campos    ->B mayor de 10 Sg ciclico
            
                
--------
Menues o pantallas:
0-  inicial y constante: 
       pulsando A se pasa al siguiente menu y siempre se vuelve a esta pantalla/Menu.

      muestra  las temperaturas Min=T1 y Max=T2 y el Modo o Programa termico.
      muestra la temperatura instantanea del sensor del interior de la Camara.
      muestra la temperatura Goal a lograr en ese instante.
      muestra la diferencia en Grados entre ambas.
      la hora actual, el minuto de disparo del autoreset.

1-  menu Seteador  : selecciona el ingreso a los siguientes menues:

2-  menu Modo/Progs: selecciona Programas de comportamiento termico:
                                            temp costante (Termostato) 
                                            temp Lineal   (y=mx+b)
                                            circadiano    (modelo Parton/Logan)

3-  menu Temp      : parametriza T1 y T2 ( Temperaturas Minima y Maxima a desarrollar en el tiempo)

4-  menu Foto      : simula el fotoperiod regulando  la iluminacion del interior de la camara
                                parametriza amanecer y anochecer (fotoperiodo)  ( Dia y Noche)
--------------------------------------------------------------------------------------

  tiempo pulso  
            corto  
            largo  pasa de hora a minuto toggle circular

 A  B  pulso corto
 -  -
 +  -  corto      aumenta hora/min/temp 
 -  +  corto      decrece hora/min/temp
 +  -  largo      llama menu circular
 +  +  
 C pulsad  OK/ACEPTA

tiempo sin oper


1-  menu SETEador
2-  menu Foto  menuFOTO();
3-  menu MOdo  menuModo();
4-  menu Temp  menuTEMP();

----------------------------------------------------------------
const int Sw3 = A1;  
const int Sw2 = A2;  
void Aceptor();

void menuModo();   
void menuTEMP();
void menuFOTO();

void blinkFOTOPERIODO();

--------------------------------------------------------------------------------------------------
if swA and swB
paso =1

        while W1= true   while (Seteador == true) 
        if (tiempo sin oper){sale W1, W1=W2=W3=W4=FALSE}
            menu1
                  while(W2){// 
                          //dia
                            corto          swA largo pasa de HH a MM circular
                              swA +        //   HH  MM
                              swB -
                            aceptor   pasa de dia a noche circular
                          //noche
                            corto          swA largo pasa de HH a MM circular   
                              swA +       //   HH  MM   
                              swB -
                            aceptor   pasa de dia a noche circular
                     
                     sale del w2 con swB largo para volver a Menu 1(W1) 
                  	}	

                  while(W3){
                    swA +
                        swB -
                       aceptor  
                        swA +
                        swB -B
                  	}

                  while(W4){
                    swA +
                        swB -
                       aceptor  
                        swA +
                        swB -B
                   	}     

        }/end wihle W1
------------------------------------------------------------------------------------------------------------------*/


void displayOLED(){ //displayOLED*************lo muestra siempre // RAIZ*****************************************         
        // if (nModo>9 || nModo<0) {nModo=1;}
          oled.setCursor(0, 0);oled.set1X();oled.print(F("Tmi :"));oled.print(T1);oled.print(F(" Tma :"));oled.print(T2);
          oled.setCursor(0, 1);oled.print(F(" Prg= "));//oled.print(nModo);
          oled.setCursor(40, 1);                       //oled.println("01234567890");
                    if (nModo == 2) {oled.print(nModo);oled.print(F(" RAMPA"));//oled.print(F("+SOAK"));

                    if(pasoSoak==false){  oled.print(F("+SOAK")); }//--  soak no concluyo AUN -
                    if(pasoSoak==true){   oled.print(Avance,4); }
                    
                      }
                    if (nModo == 3) {oled.print(nModo);oled.println(F(" CIRCADIANO"));}   

                    if (nModo == 4) {oled.print(nModo);oled.println(F(" Temp CTE  "));}

          oled.set2X();
          oled.setCursor(0, 2);oled.print(F("Ti=  "));   oled.setInvertMode(1%2);//1 es true
          oled.setCursor(61, 2);oled.println(tempActual);oled.setInvertMode(0%2);//0 es false 
          oled.setCursor(0, 4);oled.print(F("Tcal="));oled.setCursor(61,4);oled.print(Tinstant);
            
          DateTime now = rtc.now(); 
          oled.setCursor(0,6);  oled.set1X();
          oled.print(now.hour());oled.print(F(":"));oled.print(now.minute());oled.print(F(":"));oled.print(now.second());
          oled.print(F(" DLTa= "));oled.print((tempActual-Tinstant),2); 
                oled.setInvertMode(1%2);//1 es true
          oled.setCursor(16,7);oled.print(Mreinicio);oled.print(F("=Reset  "));
          oled.print((tempActual-tempAMBIENT),2); oled.print(F("=SLTo"));
                oled.setInvertMode(0%2);//0 es false 
          
          //                     Columna,  Fila   ,S     ,I
          //                     0 a 239, 0 a 7   ,1 ó 2 ,0 ó  1
          //void leeStepper(int _Columna,int _Fila,int _S,bool _I){//-----------------------------
          //leeStepper(196/2, 6,2,0);//entrega newPosition 

          // si se pulsa el boton su valor va a LOW                                                                                                                                                             
}//fin displayOLED ******************************************************





 void menuSeteador()// 1---------------TIENE EL WHILE AFUERA en void loop()-----------------------------------------
 /*
                                                      entra                                       con swA Sw2
                                                      sale sin grabar con lo mismo que entro circular swA
                                                      graba Sram con Acepta                        swC=OK

                                                                  Cambia       Sale         Acepta		
                                                                  Rotor	       swA	        swC=OK
                                                                               sale sin grabar con togle circular swA
                                                                                           graba Sram con Acepta swC=OK, 
                                                                        //va pasando con el rotor
                                                                        //         1 MODO
                                                                        //         2 TEMP
                                                                        //         3 FOTO
                                                                        //         4 ACEPTA s/n graba Sram con Acepta con   swC=OK
*/


{// 1-----------menuSeteador()---------------------------------------------
if( paso == false) {oled.clear(); } //evita parpadeo 
    paso= true;
          oled.setInvertMode(0%2);//0 es false
          oled.set2X();//tamaño GRANDE
    
    //                   X, Y
          oled.setCursor(0, 0);oled.print(newPosition,0);
          
          oled.set1X();//tamaño chico
          oled.setCursor(0, 3); oled.print(F("Cambia Sale Acepta"));
          oled.setCursor(0, 4); oled.print(F("Rotor  swA  swC=OK"));

    //             X,Y,Tx,Inverso
        leeStepper(0,6,2 ,0);// coloca el stepper en el campo indicado 
        oled.setCursor(12, 6);oled.set2X();//tamaño GRANDE
        //oled.println("0123456789");=10	caract x2
        oled.println(F("  ACEPTA?"));
    if( (newPosition >= 4) || ( newPosition <= 0) ) { myEnc.write(2);} //newPosition=1;}      
   Aceptor();// Lee el pulsador del rotatorio y cambia la variable bool Bot (togle)       
      if(Bot == false){ acepta = true; newPosition=LASTposition; }// Entrega variable = acepta --> la opcion mostrada                       
      if( (newPosition >= 4) || ( newPosition <= 0) ) { myEnc.write(2);} //newPosition=1;}   
                    if (newPosition == 1) {LASTposition=newPosition; //oled.println("01234567890");
                                                oled.setCursor(10, 0);oled.println(F(" Set.Programs"));// menuModo
                                                              // swC=OK (pulsador Rotor amarillo) 
                                                              if (acepta== true){avisala();oled.clear();setMODO=true; 
                                                                                //obtenerHoraCentesimal();
                                                                              // DateTime now = rtc.now();//toma datos del modulo RTC 
                                                                              //hs   formato centecimal dato  hora reloj format centecimal
                                                                              // TimeStart = now.hour()+ ( float ) now.minute()/60+  ( float )now.second()/6000;   // hora centecimal input para el calculo de la temperatura instantanea   
                                                             
                                                              menuModo(); }//1modos PROGS                      
                        }
              else if (newPosition == 2) {LASTposition=newPosition;//oled.println("01234567890");
                                             oled.setCursor(10, 0);oled.println(F(" TEMP      "));
                                                                // swC=OK (pulsador Rotor amarillo) 
                                                              if (acepta== true){avisala();oled.clear();setTEMP=true;

                                                                      // DateTime now = rtc.now();//toma datos del modulo RTC 
                                                                      //hs   formato centecimal dato  hora reloj format centecimal
                                                                      // TimeStart = now.hour()+ ( float ) now.minute()/60+  ( float )now.second()/6000;   // hora centecimal input para el calculo de la temperatura instantanea   
                                                             menuTEMP(); }//2                   
                        }
              else if (newPosition == 3) {LASTposition=newPosition;//oled.println("01234567890");
                                             oled.setCursor(10, 0);oled.println(F(" FOTOPER.  "));
                                             // swC=OK (pulsador Rotor amarillo) 
                                                              if (acepta== true){avisala();oled.clear();setFoto=true; menuFOTO();  }//3                                                       
                       }
              else {  myEnc.write(1);oled.setCursor(0, 0);oled.set2X();oled.println(F(" NO opc.    ")); }//blinkFOTOPERIODO(); 
    
}//cierre --------------- menuSeteador()-------------


       

    
void menuModo(){//2    //   MODO/PROGRAMS:       lineal  cte  circad   rampa
 
while (setMODO==true) //----------------------------------------------abre while (setMODO==true) 																	
 {	
 
  if( paso == false) {oled.clear(); } //evita parpadeo de sobreimpresion del menu
      paso=true;

  oled.setInvertMode(1%2);oled.set1X();//tamaño chico
            oled.setCursor(0, 0);oled.print(F("    2 Set MODOS/PROGS    "));oled.setInvertMode(0%2);//0 es false
              leeStepper    (0, 6,2,0);// coloca el stepper en el campo indicado
                //           X, Y              
              oled.setCursor(0, 1);oled.print(F("M="));//oled.print(nModo);
          if (newPosition == 2) {//                oled.println("01234567890");
              nModo=newPosition;oled.setCursor(32, 1);oled.print(nModo);  oled.print(F(" RAMPA.")); }//Lineal ();  RAMPA y=mx+b
          if (newPosition == 3) {//                oled.println("01234567890");
              nModo=newPosition;oled.setCursor(32, 1);oled.print(nModo);oled.println(F(" CIRCAD")); }//R_circadiano();
          if (newPosition == 4) {//                oled.println("01234567890");
              nModo=newPosition;oled.setCursor(32, 1);oled.print(nModo);oled.println(F(" TEMP C")); } 
              
              oled.set1X();//LinealCTE();
              oled.setCursor( 0, 4); oled.print(F("Cambia  Sale  Acepta"));
              oled.setCursor( 0, 5); oled.print(F("Rotor    swA  swC=OK")); oled.set2X();
              oled.setCursor(50, 6);//oled.println("01234567890");
                                    oled.println(F("OK?"));
         Aceptor();//lee el pulsador del rotatorio y cambia la variable bool Bot (togle)                     
         if(Bot == false){ acepta = true; newPosition=LASTposition; }
    
    if(digitalRead(Sw2) ==HIGH){setMODO=false;oled.clear();}// sale sin grabar con lo mismo que entro circular SwA   pin analogico A2 
                                                            // pin ardu A2 = SwA   pull down con resistencia 1K5 y FILTRO 100NF en PCB 
    if(digitalRead(boton)==LOW){setMODO=false;pasoSoak=true;grabaMEM();
     oled.set1X();oled.clear();oled.setCursor(0, 2);oled.print(F("OPCION ACEPTADA"));oled.set2X();
    }//graba Sram con Acepta swC=OK,  pin analogico A1 
                                                                  // pin ardu A1   pull down con resistencia 1K5 y FILTRO 100NF en PCB
 }//cierre -----------while (setMODO==true) ------------    
}//cierre ------//2    //   MODO/PROGRAMS: 


void menuTEMP(){//3 -----------------------------setea T1 y T2 
                                        //float fAT24;  T1     
                                        //float gAT24;  T2    
                                        bool pasoT1=false;bool pasoT2=false;
                                        // myEnc.write(0);// pone el encoder en 0
    while (setTEMP==true) //----------------------------------------------abre while (setTEmp==true) 																	
    {		float tempT1; //= 0; // variable temporal para retener el valor de fAT24
        float tempT2; //= 0; // variable temporal para retener el valor de gAT24																				        
            if( paso == false) { oled.clear(); } //evita parpadeo de sobreimpresion del menu
            paso=true;  oled.setInvertMode(1%2);//0 es false
            oled.set1X();//tamaño chico
            oled.setCursor(0, 0); oled.print(F("    3  "));oled.print(F("    Set TEMP           "));   oled.setInvertMode(0%2);//0 es false
                      oled.setCursor(0, 6); oled.print(F("Cambia    Salir    OK"));                    oled.setInvertMode(1%2);//0 es false
                      oled.setCursor(0, 7); oled.print(F(" ^ Rotor  ^ A   B:DEC")); //CAMBIA=rotor SALE=SwA  ACEPTA=OK    ENTEROS/DECIMALES=Swb CORTO/LARGO                                                            
                                                                                                       oled.setInvertMode(0%2);//0 es false
            oled.set2X();//grande 
            oled.setCursor(0, 1);oled.print(F("T1=  "));
            oled.setCursor(0, 4);oled.print(F("T2=  "));         
         
         //bool miniMenu=true;//circular entre T1 y T2
        

            if (miniMenu==true){// setea   T1------------------------ 
                 if (pasoT1==false){ //pasa solo 1 vez para reservar el valor de la otra       
                            pasoT1=true; pasoT2=false;  
                            gAT24 = tempT2; // restaurar el valor anterior de gAT24 desde tempT2 -------- la otra  
                            //myEnc.write(int(gAT24));// pone el encoder en 0  
                                int j=int(fAT24); //Serial.print(j);//int miInt = int(miFloat); 
                                myEnc.write(j);// pone el encoder en 0      
                                                                                  // Serial.print(j);Serial.println("  Setea   T1   111111------------------------------ ");
                                                                                  //Serial.print("  T2   gAT24= ");  Serial.print(gAT24);Serial.print(" t2= ");  Serial.println(tempT2); 
                                    
                                      } 
                            numREAL0();// setea -SOLO ENTEROS---      entrega  newPosition 
                            if (digitalRead(Sw3)==true){numREAL();}// ENTREGA  incrementa  //  aumenta una decima // oled.print( newPosition + incrementa );//un pulso de Sw3 (= SwB) aumenta una decima de grado                         
                                                              fAT24=incrementa+newPosition; //  actualiza variable CON DECIMALES   T1
                                                     tempT1 = fAT24; // guardar el valor actual de fAT24 en tempT1 
                           // Serial.print("T1   fAT24= ");  Serial.println(fAT24);//Serial.print(" t1= ");  Serial.println(T1);      
                                      //pasa de ciclicamente el display de T1 a T2  
                                            PushBoton();//Medir el tiempo QUE esta pulsado boton sw3=SwB  .                                         
                                      // cambia ciclicamente la booleana miniMenu
                  oled.setCursor(64, 1);oled.print( fAT24 );// T1 
                  oled.set1X();oled.setCursor(45, 2);oled.print("T1");oled.setCursor(45, 5);oled.print(F( "  " )); //dotBlink
                  oled.set2X(); 
          T1=tempT1; 
                 }// setea   T1------------------------

                else if (miniMenu==false){// setea   T2------------------------ 
                          if (pasoT2==false){         
                       pasoT2=true; pasoT1=false;     
                       fAT24 = tempT1; // restaurar el valor anterior de fAT24 desde tempT1 -------- la otra 
                      int j=int(gAT24);
                      myEnc.write(j);// pone el encoder en 0 
                                                                              //    Serial.print(j); Serial.println("  Setea   T2    2222----------------------------------- "); 
                                                                               //  Serial.print(" T1    fAT24= ");  Serial.print(fAT24);Serial.print(" t1= ");  Serial.println(tempT1); 
                                       
                                      }                                     
                                       if (digitalRead(Sw3)==true){numREAL();}// oled.print( newPosition + incrementa ); //un pulso de Sw3 (= SwB) aumenta una decima de grado 
                                       numREAL0();//  // setea enteros   oled.print( newPosition );  
                                       gAT24 = incrementa+newPosition;//  actualiza variable
                                       tempT2 = gAT24; // guardar el valor actual de gAT24 en tempT2

                                       //Serial.print("T2   gAT24= ");  Serial.print(gAT24);Serial.print(" t1= ");  Serial.println(T1);
                                                  //pasa de ciclicamente el display de T1 a T2  
                                                        PushBoton();//Medir el tiempo QUE esta pulsado boton sw3=SwB  .                                         
                                                  // cambia ciclicamente la booleana miniMenu
                  oled.setCursor(64, 4);oled.print( gAT24 ); // T2 
                  oled.set1X();oled.setCursor(45, 5);oled.print(F( "T2" )); oled.setCursor(45, 2);oled.print(F( "  " )); //dotBlink
                  oled.set2X();    
        T2=tempT2;                       
                }// setea   T2------------------------ 
                 //bool miniMenu=true;//circular entre T1 y T2

    if(digitalRead(Sw2) ==HIGH){setTEMP=false;oled.clear();}// sale sin grabar con lo mismo que entro circular SwA   pin analogico A2 
                                                            // pin ardu A2 = SwA   pull down con resistencia 1K5 y FILTRO 100NF en PCB 

    if(digitalRead(boton)==LOW){setTEMP=false;oled.clear(); pasoSoak=true; grabaMEM();}//graba Sram con Acepta swC=OK,  pin analogico A1 
                                                                  // pin ardu A1   pull down con resistencia 1K5 y FILTRO 100NF en PCB
}//cierre -----------while (setTEmp==true) ------------                                                             

if(digitalRead(Sw2) ==HIGH){setTEMP=false;oled.clear();}// sale sin grabar con lo mismo que entro circular swA   pin analogico A2 
                                                        // pin ardu A2   pull down con resistencia 1K5 y FILTRO 100NF en PCB 

if(digitalRead(boton)==LOW){setTEMP=false;oled.clear();pasoSoak=true;grabaMEM();}//graba Sram con Acepta swC=OK,  pin analogico A1 
                                                                  // pin ardu A1   pull down con resistencia 1K5 y FILTRO 100NF en PCB                                                                                                    
                                                  numREAL0();// oled.print( newPosition );  //----------------esto es para test de rotor  
                      if (digitalRead(Sw3)==true){numREAL();}// oled.print( newPosition + incrementa ); 
                                                  //oled.set2X();//grande
                                                  //oled.setCursor(140/2, 6);oled.print( incrementa + newPosition );
                                                  //oled.setInvertMode(2 % 2); //-----------------------------esto es para test de rotor                                                                                               
}//cierre ---------------menuTEMP 3-------------


void menuFOTO(){// 4---------------------setea hh.mm para Dia y para Noche ------------------------
                                        // ON   HH:MM
                                        // OFF  HH:MM 

                                        //float fAT24;    hcOn //amanecer SUNRISE
                                        //float gAT24;    hcOff//anochecer SUNSET
                                bool pasoT1=false; bool pasoT2=false;
                                // myEnc.write(0);// pone el encoder en 0
       while (setFoto==true) //----------------------------------------------abre while (setFoto==true) 																	
          {		
        float tempT1; //= 0; // variable temporal para retener el valor de fAT24--> hcOn //amanecer SUNRISE
        float tempT2; //= 0; // variable temporal para retener el valor de gAT24-->hcOff//anochecer SUNSET																																		            

if( paso == false) {oled.clear(); } //evita parpadeo de sobeimpresion del menu
paso=true;  Parametror(); incrementador=0.0833;//pasos de 5 minutos para display oled
              oled.set1X();oled.setInvertMode(1%2);//1 es true
              //                      oled.println("012345678901234567890");
              oled.setCursor(0, 0); oled.print(F  ("  SET FOTOPERIODO    "));oled.setInvertMode(0%2);//0 es false

              oled.set1X();//tamaño chico
              oled.setCursor(0, 4); oled.print(F("Cambia    Salir    OK"));
              oled.setCursor(0, 5); oled.print(F(" ^ Rotor  ^ A   B:DEC")); //CAMBIA=rotor SALE=SwA  ACEPTA=OK    ENTEROS/DECIMALES=Swb CORTO/LARGO                                                                         

                                        oled.setInvertMode(0%2);//0 es false
            oled.set2X();                                                        
            oled.setCursor(0, 2); oled.print(F("DIA  "));//oled.print(hcOn);           
            oled.setCursor(0, 6); oled.print(F("Nche"));//oled.print(hcOff);
      
      //bool miniMenu=true;//circular entre dia y noche 
                if (miniMenu==true){// setea-Dia-----------------------  
                  if (pasoT1==false){ //pasa solo 1 vez para reservar el valor de la otra     
                         pasoT1=true; pasoT2=false;  
                          gAT24 = tempT2; // restaurar el valor anterior de gAT24 desde tempT2 -------- la otra  
                            //myEnc.write(int(gAT24));// pone el encoder en 0  
                                int j=int(fAT24); Serial.print(j);//int miInt = int(miFloat); 
                                myEnc.write(j);// pone el encoder en j=  
                                      } 

                                                 numREAL0();// setea -SOLO ENTEROS---      entrega  newPosition 
                     if (digitalRead(Sw3)==true){numREAL();}// aumenta 5 minutos // oled.print( newPosition + incrementa );    
                                                          //un pulso de Sw3 (= SwB)  aumenta 5 minutos  

                                          fAT24=incrementa+newPosition; //  actualiza variable CON DECIMALES   T1
                                                     tempT1 = fAT24; // guardar el valor actual de fAT24 en tempT1 
                           // Serial.print("T1   fAT24= ");  Serial.println(fAT24);//Serial.print(" t1= ");  Serial.println(T1);      
                                      oled.setCursor(67, 2);//DIA 
                                                float hora=(incrementa+newPosition);//actualiza variable CON DECIMALES   T1
                                                //if( hora>24){ hora=0;} if( hora<0){ hora=0;}  
                                                if(( hora>24)||(hora<0)){ hora=0;myEnc.write(0);}
                                                
                                                   fAT24= hora; 
                                                   tempT1 = fAT24; // guardar el valor actual de fAT24 en tempT1                                  
                                       // HHmm_a_HHcc()  {	//funcion -- HHmm_a_HHcc()
                                       hhNN_a_hhSX(hora);//hora SEXAGESIMAL para display oled
                                       //Serial.print("hora SEXAGESIMAL= ");Serial.println(hhSX);
                                       //pasa de ciclicamente el display de T1 a T2  
                          PushBoton();//Medir el tiempo QUE esta pulsado un boton sw3=SwB 
                          // cambia ciclicamente la booleana miniMenu     
                                       oled.print( hhSX,2 );  //dia //oled.print( hora,2 );  //dia 
                                      oled.set1X();oled.setCursor(48, 3);oled.print(F( "D" )); oled.setCursor(48, 7); oled.print(F( " " )); oled.set2X(); 
                  hcOn=tempT1; //amanecer SUNRISE
                                  }// setea-Dia------------------------



                else if (miniMenu==false){// setea---Noche--------------------- 
                  //bool miniMenu=true;//circular entre dia y noche   
                  if (pasoT2==false){         
                                      pasoT2=true; pasoT1=false;     
                                      fAT24 = tempT1; // restaurar el valor anterior de fAT24 desde tempT1 -------- la otra 
                                      int j=int(gAT24);
                                      myEnc.write(j);// pone el encoder en j=gAT24  
                                                                                      //    Serial.print(j); Serial.println("  Setea   T2    2222----------------------------------- "); 
                                                                                      //  Serial.print(" T1    fAT24= ");  Serial.print(fAT24);Serial.print(" t1= ");  Serial.println(tempT1); 
                                    } 
                     if (digitalRead(Sw3)==true){numREAL();}// aumenta 5 minutos // oled.print( newPosition + incrementa );    
                                                          //un pulso de Sw3 (= SwB)  aumenta 5 minutos  
                                    numREAL0();//  // setea enteros   oled.print( newPosition );  
                                    gAT24 = incrementa+newPosition;//  actualiza variable
                                    tempT2 = gAT24; // guardar el valor actual de gAT24 en tempT2
                                    //pasa de ciclicamente el display de T1 a T2  
                                              PushBoton();//Medir el tiempo QUE esta pulsado boton sw3=SwB  .                                         
                                   // cambia ciclicamente la booleana miniMenu
                                       oled.setCursor(67, 6); //noche
                                              float hora=(incrementa+newPosition);
                                               if(( hora>24)||(hora<0)){ hora=0;myEnc.write(0);}
                                         // HHmm_a_HHcc()  {	//funcion -- HHmm_a_HHcc()
                                       hhNN_a_hhSX(hora);//hora SEXAGESIMAL para display oled
                                       Serial.print("hora SEXAGESIMAL= ");Serial.println(hhSX);
                                      oled.print( hhSX,2 );  //noche                  
                                      oled.set1X();oled.setCursor(48, 7);oled.print(F( "N" )); 
                                      oled.setCursor(48, 3);             oled.print(F( " " )); oled.set2X();  
                   hcOff=tempT2;//anochecer SUNSET                           
                                         }// setea---Noche---------------------  
                 //bool miniMenu=true;//circular entre T1 y T2

              if(digitalRead(Sw2) ==HIGH){setFoto=false;oled.clear();}// sale sin grabar con lo mismo que entro circular swA pin analogico A2 
                                                                      // pin ardu A2   pull down con resistencia 1K5 y FILTRO 100NF en PCB 
              if(digitalRead(boton)==LOW){setFoto=false;oled.clear();grabaMEM();}//graba Sram con Acepta swC=OK,  pin analogico A1   
                                                  numREAL0();// oled.print( newPosition );             //esto es para test de rotor 
                      if (digitalRead(Sw3)==true){numREAL();}// oled.print( newPosition + incrementa ); //esto es para test de rotor                  
      }//-----------------------------------------cierre while (setFoto==true) 
incrementador=0.1;
}//cierre funcion --------------menuFOTO(){// 4-------------




//---------------------

void Aceptor(){//lee el pulsador del rotor (swC=OK) , cambia la variable  Bot (togle)  y acepta=true; 
      acepta=false;
          Bot = digitalRead(boton);
                      if (!Bot)  // si se pulsa el boton su valor va a BAJO == false
                        {acepta=true;
                         // Serial.println(F("Boton ON Cont=0"));
                          //oled.clear();
                          oled.set2X();oled.setCursor(0, 7);  //Column is expressed in pixels, but Row in rows of 8 pixels.
                          //oled.print("012345678901234567890");                       "ACEPTADO "
                          oled.print(F("ACEPTADO "));oled.setCursor(0, 7);oled.print(F("         "));

                          //              Frequency in hertz(HZ).Duration of the beep in milliseconds(ms).[Optional] Function to call when done.
                        for(int i = 1; i<8; i++){
                         // EasyBuzzer.singleBeep(850, 500, done);delay(150);
                          EasyBuzzer.singleBeep(1300, 500, done);  delay(150);
                          EasyBuzzer.stopBeep();  // Use this function to stop the beeping. You may call this function at all time, everywhere in the code.
                          }
                        
                        
                         // EasyBuzzer.stopBeep();

                          //acepta valor, finaliza funcion, guarda variable......................
                        }
      EasyBuzzer.stopBeep();
}//----------------------------------------------------------------------------fin Aceptor()


void blinkFOTOPERIODO(){ //-----------------------------------------           
               for(int i = 1; i<11; i++){
                              digitalWrite(pinFOTOPERIODO,HIGH);//CONECTA led
                              delay(50);
                              digitalWrite(pinFOTOPERIODO,LOW);//apaga  
                              delay(100);
                      }
}//----------------------blinkFOTOPERIODO()
