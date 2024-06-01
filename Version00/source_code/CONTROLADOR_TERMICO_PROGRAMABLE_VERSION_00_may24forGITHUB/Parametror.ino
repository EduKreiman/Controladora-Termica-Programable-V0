//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
void Parametror(){ //Parametror()--------//AJUSTESySETEOS();// reemplaza a leeMeM en desarollo o seteo fijo PARA --VERSION 00--

// Setar hora, solo la primera vez, con los valores de la fecha y la hora en que el sketch ha sido compilado.
//ir a  la linea 399 del sketch:  CONTROLADOR_TERMICO_PROGRAMABLE_VERSION_00_may24forGITHUB.ino
//                                    del ----------- Modulo RTC-----------
// Ponemos en hora con los valores de la fecha y la hora en que el sketch ha sido compilado.
// rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));// Fijar a fecha y hora de COMPILACION el sketch
//  luego comentar y volver a cargar.

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
//RUTINA TERMICA ACTIVA//
        nModo=3; // para circadiano REVISAR QUEDA FIJO  
        // nModo = 2;//y=mx+b() nMODO=DOS(2)
                            // nModo = 4; // nModo posicion  rutina rutMODO()
//TEMPERATURAS
        T1 = 33;   // Tim posicion    // tempArranque -GOAL->  temp de inicio 
        T2 = 1.15; // tma posicion    // tempSET ------META->  temp a llegar en rampa -
//FOTOPERIODO                                           
        hcOn  =  (8 + ((float)01/60) );//amanecer   8hs01  rutina fotoperiodo CENTESIMAL
        hcOff =  (20+ ((float)01/60)); //anochecer 20hs01

 s4=85;   //REVISAR QUEDA FIJO PARA CIRCADIANO        
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
/*
//buzzer  con led azul en paralelo usa pasivo con trNPN buffer rutina de tono 450Hz  libreria easyBuzzer
const int BUZZER = A0;  
frequency = 400;
onDuration = 500;
offDuration = 500;
beeps = 5;
pauseDuration = 500;
cycles = 10;
*/

}//Parametror()-------------------------AJUSTESySETEOS()  
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<