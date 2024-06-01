
/*
 USAR COMM ESTRUCTURADA CON
 LADO ARDUINO:
 AsyncSerial  ---> UseWithParser.ino  https://www.arduino.cc/reference/en/libraries/asyncserial/
                //implementa funciones para recibir y enviar un Stream de forma no bloqueant
 ArduinoParser--->  https://www.luisllamas.es/libreria-arduino-parser/
//            interpretar de forma sencilla la información contenida en un char Array o en un String
//            para trabajar con un array recibido por un medio de comunicación

INCORPORO: temperatura_arduino_LADOprocessing006 
UseWithParser.ino  https://www.arduino.cc/reference/en/libraries/asyncserial/
             ArduinoParser--->  https://www.luisllamas.es/libreria-arduino-parser/
 INTEGRIDAD DE DATOS EN ARDUINO CON CHECKSUM CRC32 libreria: https://github.com/arduino-libraries/Arduino_CRC32
 ------------------------------------
 prueba correr este sketch y deberías 
 ver un hola mundo en tu consola y 
 al hacer clic en la ventana de Processing deberías ver el LED, conectado al pin 13, encenderse y apagarse.            
 */


/*programar función serialEvent(). 
 
 Cada vez que recibamos un retorno de carro esta función (función serialEvent()) será llamada.
 
 para que ejecute una serie de acciones:
 Leer los datos que llegan.
 Verifique la existencia de datos después de una lectura (por ejemplo que no sea vacío o null).
 Reducir los espacios en blanco y otras cosas.
 
 
 Si es la primera vez que recibimos un dato o carácter que buscamos, 
 cambia nuestro boolean firstContact y 
 avisa a Arduino que estamos listos para recibir más datos.
 
 Si no es la primera vez que ejecutamos esto, entonces debemos 
 mostrar por consola los datos y 
 enviar de vuelta cualquiera sea la cantidad de clics (en forma de números 1) que hagamos en la ventana.
 
 Finalmente debemos decirle a nuestro Arduino que estamos listos para recibir más datos.
 Processing tiene funciones que hacen la mayoría de estas tareas y de una manera bastante fácil. 
 &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*/
 
 
 
 
 
void HANDS_SHAKE(){//--------------------FUNCION HANDS_SHAKE   establece comunicacion bidireccional
                  if(test==false){// flag para desarrollo habilita impresion en consola de variables y estados
                            if (firstContact == true) {//SI es primer contacto
                                                   if (dataIN.equals("A")) {//Busca nuestro string A para iniciar el handshake. 
                                                      myPort.clear();//Si el carácter existe limpiar el buffer de datos y 
                                                      firstContact = false;//NO es primer contacto
                                                      myPort.write("B");//envia una solicitud de datos
                                                      println("comunicacion01  bidireccionalOK-> funcion HANDS_SHAKE");//----------------------->>>>>>>establece comunicacion bidireccional
                                                                }
                                   }//fin SI es primer contacto
                         }
}// --------cierre //--------------------FUNCION HANDS_SHAKE   establece comunicacion bidireccional



//  RECIBE DATOS DE ARUINO                                se activa              when data is available         
void serialEvent(Serial myPort) {//Called when data is available -----------------------------------------------------------funcion serialEvent 
// identifica PAQUETE compuesto de PALABRAS RECIBIDO-------COMPARANDO CON CONSTANTES   -> mostraN <-- --------------------------
        dataIN =  myPort.readStringUntil('\n'); 
        //  '\n' (salto de línea) o '\r' (retorno de carro) el limitador que indica el fin de un PAQUETE compuesto de PALABRAS.
        //   PAQUETE'\n' compuesto de PALABRA1" "PALABRA2" "PALABRA3" "PALABRAnn" "
// imprime_en_consola();//desmarcar SOLO para debug esta en pestaña FUNCIONES
if (dataIN != null) { //se asegura que LOS datos RECIBIDOS no son espacios en blanco
                              dataIN  = trim(dataIN);
                          //esto se repite en cada PAQUETE de datos RECIBIDOS
                             //imprime_en_consola();//desmarcar SOLO para debug esta en pestaña FUNCIONES        
                                //            The split() function  CORTA  un PAQUETE en PALABRAS 
                                //                split(val, separa)
                                //            entrega un String[] array que contiene cada PALABRA
                               
                                //The split() function          breaks a String into pieces using  
                                //a character or string as the delimiter. 
                                //The delim parameter specifies the character or characters that 
                                //mark the boundaries between each piece. 
                                //A String[] array is returned that contains each of the pieces.
                                //EN ARDUDROID #define CARACTER_DIV_CMD '|'
                           // String                        separa= ("|");//espacio entre palabras del string 
                             
                              String                        separa= (" ");//espacio entre palabras del string  EN arduino COLOCAR un espacio al final como SEPARADOR
                              String sensors[] = split(dataIN, separa);//SEPARA en palabras y las coloca en el String Array sensors[]
              //declara una matriz/Array    String sensors[] local de long variable ??
              //Una matriz=array es una lista de datos. 
                         
         //String  mostra=   "2-tempActual:";// paquete temperatura sensor recibido desde arduino 
          if (sensors[0].equals(mostra)) {//   palabra(0) temperatura sensor recibido desde arduino  
          println("--abre------2---------(sensors[0].equals(mostra)--------------------- ");  
                              for (int i = 0; i < sensors.length; i = i+1) {
                                    println("long array= ",sensors.length," sens nro= ",i,"CON:" ,sensors[i]);  }
                                       
                            //println("--abre------2---------(sensors[0].equals(mostra)--------------------- ");
                                                              /*
                                                              -abre------2---------(sensors[0].equals(mostra)--------------------- 
                                                              long array=  9  sens nro=  0 CON: 2-                     cabezal mostra
                                                              long array=  9  sens nro=  1 CON: 16.00                  Temp1-goal= 
                                                              long array=  9  sens nro=  2 CON: 1                      Lectun
                                                              long array=  9  sens nro=  3 CON: 0.00                   nModo
                                                              long array=  9  sens nro=  4 CON: BALANCEconPWM=255y96   status
                                                              long array=  9  sens nro=  5 CON: -127.00                tempActual
                                                              long array=  9  sens nro=  6 CON: 32.00                  Temp2-Met
                                                              long array=  9  sens nro=  7 CON: 31.57                  TempInsFuncion  calculo teInsta
                                                              long array=  9  sens nro=  8 CON: 368                    memory free
                                                              long array=  10 sens nro=  9 CON: -127.00                TempDisip  idem sens nro= 28 //
                                                              -> Mostra recibido= 2-   LecturaN= 1
                                                              Temp1-goal= 16.00 ºC Temp2-Meta= 32.00 ºC TempInsFuncion=  31.57 ºC
                                                              status:  BALANCEconPWM=255y96  TempPeltier=  -127.0 ºC
                                                              -------------------------------------------------------------- 
                                                              -> datos2locales=                             
                                                              pid (se 15)DELTA= 2.0   pid(se 16) EFICACIA= 38.0  pid(se 17) HISTERESIS= 0.33
                                                              -> datos locales= tempMin= 16.0   tempMax= 32.0   EVENTO= 0  nModo= 0
                                                              ---cierra-----2---------(sensors[0].equals(mostra)--------------------- 
                            */
                            print("-> Mostra recibido= ");print( sensors[0]," ");//1er palabra(0)es el contenido de la constante de identidad
                                println( " LecturaN=",sensors[2]);//palabra3 
                                Lectun=Integer.parseInt(sensors[2]);
                                print("Temp1-goal= "); print( sensors[1],"ºC ");// palabra2 palabra(1)es el contenido variable  
                                print("Temp2-Meta= "); print( sensors[6],"ºC ");//
                                if (sensors.length>7){ 
                                println("TempInsFuncion= ",sensors[7],"ºC");//dato recibido de  funcion mat arduino
                               }
                                print("status: ",sensors[4]);//COOLING o HEATING
                                Status =sensors[4];
                                int x=0;
                                float  Suma=0;
                                for (x = 0; x < 7; x++) { //toma 7 mediciones
                               
                                      Suma= float(sensors[5])+Suma; 
                                   }  
                               println("  TempPeltier= ", (Suma/x),"ºC");//dato recibido sensor Peltier
                            //carga datos recibidos a variables locales  
                            if (sensors.length>7){ 
                                teInsta  = float(sensors[7]);  //   data[j]=float(inString);
                                 }
                              if (sensors.length>9){ 
                                 TempDisip=float(sensors[9]);//     sens nro=  9   idem sens nro= 28 //
                                 }    
                                inByteRaw=float(sensors[5]);//dato recibido sensor temp
                                tempsensor=inByteRaw;
                                inByte=float(sensors[5]);
                                inByte=map(inByte, 20, 41, 0, height);//Mapea rango dato temperatura del sensor  temp min,  temp max
                                freeMemory=float(sensors[8]); //  sens nro=  8   Memory   sensors[5]              
                                
                           println("-------------------------------------------------------------- ");
            //para desarrollo  
            println("-> datos2locales=                             "); print ("pid (se 15)DELTA= "+ s3); print ("   pid(se 16) EFICACIA= "+ s4);println ("  pid(se 17) HISTERESIS= "+ s5);//dataset
            print("-> datos locales= "); print ("tempMin= "+seteatempMin); print ("   tempMax= "+ seteatempMax);print ("   EVENTO= "+ nEvento);println ("  nModo= "+seteanModo);//dataset
                               println("---cierra-----2---------(sensors[0].equals(mostra)--------------------- ");
                               }//---------------------------------- palabra(0)  temperatura sensor recibido desde arduino               
                            
                              
       // String   mostra0="1-desdeArduinoEnvioDATOS-->hola_mundo";// paquete STRING del HOLAmundo
                          //    mostra0---> se puede usar para control de trafico de data
          else if (sensors[0].equals(mostra0)) {//   palabra(0) temperatura sensor recibido desde arduino
            println("---abre-----1---------(sensors[0].equals(mostra0)--------------------- ");                                                         
                                print("-> sensor de CONTROL= ");
                                print( sensors[0]," ");//1er palabra(0)es el contenido de la constante de identidad                  
                              println( sensors[1]);//la segunda palabra(1)es el contenido variable
                             // println("$_holi_$_");//la segunda palabra(1)es el contenido variable
            println("---cierre-----1---------(sensors[0].equals(mostra0)--------------------- ");
                                  }//------------------------------------------------ 
                          
                          
                          
                          
        //String mostra1="3-HoraFecha=";// paquete STRING del RTC desde arduino 
             else if (sensors[0].equals(mostra1)) {//       palabra(0) // paquete STRING del RTC desde arduino
                 println("---abre-----3---------(sensors[0].equals(mostra1)--------------------- ");                   
                                print("-> Reloj RTC recibido=   ");
                                print( sensors[0]," ");//1er palabra(0)es el contenido de la constante de identidad
                                print( sensors[1],"- ");//la segunda palabra(1)es el contenido variable HORA  
                                RTChoraActual=sensors[1];
                                println(sensors[2]);//la 3er palabra(2)es el contenido variable         FECHA
                                RTCfecha= sensors[2];
                                //horaActual//cargar la variable  
               println("---cierre-----3---------(sensors[0].equals(mostra1)--------------------- ");
                               }//---------------------------------- 
     
                              
                              
          //String mostra2="4-rtcTemp= ;// paquete STRING del RTC desde arduino 
                  else if (sensors[0].equals(mostra2)) {//       palabra(0) // temperatura ambiental del RTC 
                  println("---abre-----4---------(sensors[0].equals(mostra2)--------------------- ");                   
                                print("-> Temp  RTC recibido=   ");
                                println( sensors[1],"ºC");//la segunda palabra(1)es el contenido variable TEMP AMBIENTAL
                                tamb=float(sensors[1]);
                println("---cierre-----4---------(sensors[0].equals(mostra2)--------------------- ");
                               }//---------------------------------- 
                               
                          
       
         
         
         // String mostra3="5-"; // respuesta desde arduino con un espacio al final como SEPARADOR
                           // Serial.print("5-RESPONDE_DATASET: ");
               else if (sensors[0].equals(mostra3)) {//       palabra(0) 
               println("---abre-----5---------(sensors[0].equals(mostra3)--------------------- ");          
                              //  for (int i = 0; i < sensors.length; i = i+1) {
                              //         println("long array= ",sensors.length," sens nro= ",i,"con:" ,sensors[i]);  }
                                       
                                print( sensors[0]);print("con_5_ARDUINO CONFIRMA");//la segunda palabra(1)es el contenido variable 
                                print("  Tmeta=",sensors[1]); 
                                println("  nModo=",sensors[1]); 
                                //xxxxx=float(sensors[1]);
               println("---cierre-----5---------(sensors[0].equals(mostra3)--------------------- ");
                               }//---------------------------------- 
                                                   /*
                                                                       //String mostra4=     "6-DTHambiental";// paquete STRING del DTH desde arduino     Serial.print("6-DTHambiental ");//ENCABEZADO
                                                                                             else if (sensors[0].equals(mostra4)) {//       palabra(0) //  
                                                                                              //String                 mostra3="5-RESPONDE_DATASET: "         
                                                                                                print("-> Temp  DTH recibido=   ");
                                                                                             h =float(sensors[1]);//      dht.readHumidity();//----------- para sensor Ambiental DTH022
                                                                                               print( sensors[1]," ");//la segunda palabra(1)es el contenido variable TEMP AMBIENTAL
                                                                                                t= float(sensors[2]);  
                                                                                                println( sensors[2]);//la tercer palabra(1)es el contenido variable TEMP AMBIENTALprintln( sensors[1],"ºC");//la segunda palabra(1)es el contenido variable TEMP AMBIENTAL
                                                                                               // println( sensors[3],"nose aun");//la segunda palabra(1)es el contenido variable TEMP AMBIENTAL
                                                                                               }//---------------------------------- 
                                                    */                                           
            
            //String mostra4=     ("6-enviaSTATUS ")
                               else if (sensors[0].equals(mostra4)) {//       palabra(0) //  
                   println("---abre--------------(sensors[0].equals(mostra4)--------------------- ");             
                              // lista en consola ARRAY recibido completo  desde DATAset() o  ENVIAstatus() en arduino
                                for (int i = 0; i < sensors.length; i = i+1) {
                                       println("long array= ",sensors.length," sens nro= ",i,"CON:" ,sensors[i]);  }
                                       teInsta  = float(sensors[24]);  //   data[j]=float(inString);
                                       TempDisip= float(sensors[28]);  //Serial.print(TempDisip);//    sens nro= 28 //
                                       tension= float(sensors[29]);  //    sens nro= 29 //float tension=0;
                              // lista en consola ARRAY recibido completo
                   println("-------------------------------------------------------------- ");
                   println("---cierre--------------(sensors[0].equals(mostra4)--------------------- ");
                             //carga datos recibidos a variables locales 
                             
                             
                             
                             
                             //carga datos recibidos a variables locales 
                                }//---------------------------------- 
                                
                                
                                
           }//se asegura que LOS datos RECIBIDOS no son espacios en blanco  
         
}// -----------------------------fin Funcion serialEvent  //--------------------------- COMUNICACION     

 
    
   



/*   //-----------------ESTRUCTURA LADO ARDUINO
           //para ------------  ---------   ArduDroid
#define CARACTER_INICIO_CMD '*'
#define CARACTER_FINAL_CMD '#'
#define CARACTER_DIV_CMD '|'
#define ESCRITURA_DIGITAL_CMD 10
#define ESCRITURA_ANALOGA_CMD 11
#define TEXTO_CMD 12  // The compiler will replace any mention of TEXTO_CMD with the value 12 at compile time.
#define LECTURA_ARDUDROID_CMD 13
#define MAX_COMMAND 20  
#define MIN_COMMAND 10 
#define LONGITUD_ENTRADA_STRING 40
#define ESCRITURA_ANALOGICA_MAX 255
#define PIN_ALTO 3
#define PIN_BAJO 2

String inText;
  //-----------------         
*/
           
           
    
