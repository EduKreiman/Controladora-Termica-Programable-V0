

// temperatura LADOarduino processing00n------------------------------------------------------
// //REESTRUCTURA DE : version:   controlador_rampa2020_09.INO
///-->  LA RAMPA DE LA MUERTE >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> 

//04-2022 ------------------->PARA SUBIR con NANO usar old bootloader
//     SKETCH               variables  Glob
//           ocupa               ocupa     LIBRES
//18792 bytes (58%)     1231 bytes 54%      925 bytes 06-JUN22
//19582 bytes (60%)     1113 bytes 54%      935 bytes 12-JUN22
//19902 bytes (61%)     1229 bytes 59%      819 bytes 13-JUN22  2 sensores disip + peltier --->los serial print consumen memoria
//19806 bytes (61%)     1207 bytes 58%)     841 bytes 17-JUN22  boolean test=true; PARA DESARROLLO MONITOREADO
//20530 bytes (63%)     1225 bytes (59%)    823 bytes 17-JUN22  soak en termostat/funcion tempo240k()
//20530 bytes (63%)      DESHABILITO ARDUDROID Y SUS VARIABLES PERO NO CAMBIA LA OCUPACION DE MEMORIA PORQUE????
//22664 bytes (70%)     1362 bytes (66%)    686 bytes 19-JUN22 lib PID 
//21368 bytes (66%)     1306 bytes (63%)    742 bytes 19-JUN22 lib AutoPID
//22026 bytes (68%)     1555 bytes (75%)    493 bytes para las variables locales
//23308 bytes (72%)     1691 bytes (82%)    357 bytes 25-JUN22
//21964 bytes (68%)     1530 bytes (74%)    518 bytes 26-JUN22 sin autoPID, sin encoder
//21844 bytes (67%)     1568 bytes (76%)    480 bytes
//22026 bytes (68%)     1578 bytes (77%)    470 bytes pseudo PID_log
//22470 bytes (69%)     1764 bytes (86%)    284 bytes 
//21538 bytes (66%)     1726 bytes (84%)    322 bytes liberando memoria version minima overflow en 11hs aprox 23.25 a 10.15
//21670 bytes (70%)     1740 bytes (84%)    308 bytes  //12:28:46.980 -> freeMemory()=358 
//20484 bytes (66%)     1670 bytes (81%)    378 bytes  //13:21:59.430 -> freeMemory()=326  sin modulo rtc
//21802 bytes (70%)     1722 bytes (84%)    326 CON modulo rtc
//22066 bytes (68%)     1772 bytes (86%)    276           14:26:04.706-> freeMemory()=210 CON modulo rtc
//22074 bytes (68%)     1772 bytes (86%)    276 14:42:37.353 -> freeMemory()=206  linea print en 2- para output dalagoller
//21864 bytes (67%)     1752 bytes (85%)    296 bytes elimino for loop 7 de promedio de lecturas.elimino print free mem solo envia data 
//21812 bytes (67%)     1750 bytes (85%)    298 bytes  anulo la variable ESTAnt_S= 1-> freeMemory()=232
                                                      //Poca memoria disponible, se pueden producir problemas de estabilidad.
//21780 bytes (67%)     1750 bytes (85%)    298//usando Serial.print(F(" "));-> freeMemory()=312
//21800 bytes (67%)     1670 bytes (81%)    378 //reinstalo librerias onewire y rtc -> freeMemory()=312
//21714 bytes (67%)     1670 bytes (81%)    378 bytes // switches Normal Bajo-->pull down protegen de reseteos ante bajadas de tension
//21872 bytes (67%)     1692 bytes (82%)    356 con watch-dog y autoreset
//21932 bytes (67%)     1694 bytes (82%)    354 bytes -> freeMemory()=296
//                                 (80%) o  394 SOLO COMANDO watch-dog y autoreset DESHABILITADOS freeMemory()=274 en linea 54
//21844 bytes (67%)     1704 bytes (83%)    344 bytes elimino libreria DTH
//21932 bytes (67%)     1708 bytes (83%)    340 
//19948 bytes (61%)     1029 bytes (50%)    1019 bytes comente todos las llamadas avisala y  HOO!! --> freeMemory()=910???
//FUNCION autoreset --> void(* resetFunc) (void) = 0;  --> DESCOMENTAR para activar AUTO-RESET --> 
//18870 bytes (61%)     1049 bytes (51%)    999 bytes  AUTO-RESET --> y reset por tecla R en procesing -> freeMemory()=943
//18854 bytes (58%)     1069 bytes (52%)    979 bytes -> freeMemory()=160 digitalwrite buzzer
//20622 bytes (63%)     1710 bytes (83%)    338 bytes puente gnd power on verde 04-07-22  freeMemory()=279
//re habilito el EL OPTOCOUPLER
//20522 bytes (63%)     1646 bytes (80%)    402 bytes cambio fuente,reset con funcion software_Reboot() WDT  cada 2 horas y con  tecla R desde procesing freeMemory()=339
//20460 bytes (63%)     1646 bytes (80%)    402 bytes reemplazo and por &&, elimino else  balance en termostato freeMemory()=343
//21064 bytes (65%)     1110 bytes (54%)    938 pongo Serial.print(F(" ")); freeMemory()=889
//20462 bytes (63%)     1116 bytes (54%)    932 bytes Reporte de error: no usar  ajuste automatico del RTC
//20500 bytes (63%)     1108 bytes (54%)    940 bytes SERIAL READ decodifica de 0 a 255 revisar clase stream()  freeMemory()=891
//20694 bytes (67%)     1116 bytes (54%)    932   rehubico  sonda de disipador en el interior de la camara
//Usa 2 librerias  de rRTC una para memoria otra para reloj
//22626 bytes (73%)     1132 bytes (55%)    916  librerias ds3231_simple.cpp y .h LIBRERIA CRAKEADA --> de:DateTime a:  DateSTime
//23724 bytes (77%)     1178 bytes (57%)    870  grabaMEM()  y leeMEM()
//23734 bytes (77%)     1178 bytes (57%)    870  coef de ajuste sensor temp +0.89
//23746 bytes (77%)     1178 bytes (57%)    870  funcion voltimetro sale por ENVIAstatus() y por test=true(modo desarrollo)
//24040 bytes (78%)     1178 bytes (57%)    870  habilito parte de rutinas modo ,  "ABORT"     bloqueado recepcion de  PROCESSING 
//24774 bytes (80%)     1182 bytes (57%)    866 2% incrementado por--- if 7 ajusta HORArtc ---
//24766 bytes (76%)     1238 bytes (60%)    810 correccion en - if 7 ajusta HORArtc
//24922 bytes (77%)     1254 bytes (61%)    794

                                /* para circadiano Vz la rutina tiene fija 
                                tempMin=16.00;//activa Slider s1 // modo tropical VZ
                                tempMax=32.00;//activa Slider s2 // modo tropical VZ
                                deltaT=0;
                                deltaT=tempMax-tempMin;
                                */
//reducir uso memoria con:
//usando Serial.print(F(" "));
//eliminar variables no usadas
//eliminar variables encadenadas
//usar booleanas
//se desinstalo la lectora de memoria SD        MAY-22
//limitar el uso de print en conSola  porque toma mucho tiempo del procesador

#include <avr/wdt.h> //watch-dog-Timer, esta librería  dispara una interrupcion que llama una funcion  cuando se acaba el tiempo
//#include <WatchDog.h>	//esta librería  dispara una interrupcion que llama una funcion (que puede resetear el MCU)  cuando se acaba el tiempo 



#include <MemoryFree.h>
//***************************************************** DESCOMENTAR para activar AUTO-RESET
    //                  void(* resetFunc) (void) = 0; //declare reset function @ address 0   enviado por referencia de C++
//***************************************************** DESCOMENTAR  para activar AUTO-RESET
                                      /*para restablecer la placa, se implementa un ciclo corto,(15 milisegundos) 					
                                      cuando el tiempo de espera expira, el sistema se reinicia									
                                      al llamar a la funcion      software_Reboot     reiniciando la placa a los 15 ms.
                                      Processing recupera la coneccion luego del reset

                                        void software_Reboot()				
                                          {			
                                            wdt_enable(WDTO_15MS);        //watchdogTIMER esta buenisime Timer por INTERRUPCION
                                                                          //usarlo para time en soak o para tiempo entre de lecturas	
                                              while(1)		
                                              {		
                                              }		
                                          }			

                                      */

bool test=false;//boolean test=true; PARA DESARROLLO MONITOREADO se habilita con switch de evento del pcb
//bool test=true;//boolean test=true; PARA DESARROLLO MONITOREADO se habilita con switch de evento del pcb
//bool test01=true;//boolean test=true; PARA DESARROLLO MONITOREADO de modos
bool test01=false;//boolean test=true; PARA DESARROLLO MONITOREADO de modos

#include <SoftwareSerial.h>
SoftwareSerial BT1(7, 8); // RX | TX // Ojo. invertir en el BlueTooth
#include <OneWire.h>
#include <DallasTemperature.h>
              //#include <ds3231.h>// libreria de arduino parece mas liviana   https://www.arduino.cc/reference/en/libraries/ds3231/
              //                                                               https://github.com/NorthernWidget/DS3231
              // is a splice of Ayars' (http://hacks.ayars.org/2011/04/ds3231-real-time-clock.html) and Jeelabs/Ladyada's
              //                                   ver pulso 1 segundo por interrupcion en pestaña DOCUMENTACION


#include <RTClib.h>// ---paraRTC real clock time    https://adafruit.github.io/RTClib/html/class_r_t_c___d_s3231.html
RTC_DS3231 rtc;// Declaramos un RTC DS3231
#include <DS3231_Simple.h> // archivo crackeado  de:DateTime a:  DateSTime
DS3231_Simple Clock;// Declaramos un Clock DS3231
 
 
//datos a guadar en RTC RAMPA
//void grabaMEM()// guarda datos en memRTC
//void leeMEM(){// lectura y presentacion y recupera datos en variables
//-----------------------
              struct MyLogDataStructure {//define estructura de datos 
                  // the maximum amount of data we can store is 7 bytes--> se hacen 2 registros seguidos con diferentes datos
                          unsigned int nModo;      // 2 Bytes  2
                          unsigned int te1;  // 2 Bytes  2 recibe int x 100
                          //float te1;      //           4 Bytes  6--------
                        // float t2;      //          4 Bytes 10
                        // unsigned int hot_cool;  //  2 Bytes 12
                                                // --------------
                                              //   12 Bytes                                                                  
                  };



// Instancia a las clases OneWire y DallasTemperature
#define pinDatosDQ 4 // Pin donde se conecta el bus OneWire -------> pin digital D4  
OneWire oneWireObjeto(pinDatosDQ); //pin digital 4                 como bus OneWire clase OneWire
//OneWire oneWireObjeto(4); //pin digital 4                 como bus OneWire clase OneWire
DallasTemperature sensorDS18B20(&oneWireObjeto);//Declara un  objeto para el sensor clase DallasTemperature
//-> Sensor 1 : 0x28, 0xAA, 0x6C, 0x86, 0x38, 0x14, 0x01, 0x1F  // -------->ETIQUETA AZUL supongo INDEX(0)
//-> Sensor 2 : 0x28, 0x96, 0xDB, 0x95, 0xF0, 0x01, 0x3C, 0x07 // -------->ETIQUETA BLANCA supongo INDEX(1)
// por Addresses  matriz de long 8 x 8
uint8_t Azul[8] = { 0x28, 0xAA, 0x6C, 0x86, 0x38, 0x14, 0x01, 0x1F };// -------->ETIQUETA AZUL supongo INDEX(0)
uint8_t Blanco[8] = { 0x28, 0x96, 0xDB, 0x95, 0xF0, 0x01, 0x3C, 0x07 };// -------->ETIQUETA BLANCA supongo INDEX(1)
//sensors.getTempC(deviceAddress);

/*In general, the const keyword is preferred for defining constants and 
should be used instead of #define.
********************Notes and Warnings**************
There is no semicolon after the #define statement. If you include one, the compiler will throw cryptic errors further down the page.
this is an error               #define ledPin 3; // this is an error
this is an error               #define ledPin  = 3 // this is also an error
Similarly, including an equal sign after the #define statement will also generate a cryptic compiler error further down the page.
*/
                      //--DEFINE Arduino pines UNO  analog 0 a 3       mas Analog input 4y5 para /I2C Data line
                      //         Arduino pines NANO analog 0 a 7 INCLUIDAS Analog input 4y5 para /I2C Data line
                      const int pinEVENTO= A0;   // BOTON EVENTO       
                      const int pinSTART = A1;   // BOTON START/INICIO 
                      const int pinABORT = A2;   // BOTON  ABORT/Stop  
                      const int pinPOTE  = A3;   // pote  usar pin analog read MONITOREAR TENSION PUENTE H
                      const int pinCirca = 10;   //pwm desde zocalo SD led frontal ROJO 
                      const int pinTCrict= 11 ;//pwm desde zocalo SD led frontal YELLOW
                      const int pinAlone = 12 ;//    desde zocalo SD led frontal YELLOW
                      
                      // protocolo de comunicacion I2C Arduino UNO, NANO reserva por default -> SDA = A4 y SCL = A5 NANO  
                      //#define SCL 5  protocolo de comunicacion I2C   The compiler will replace any mention of scl with the value 5 at compile time.
                      //#define SDA 4  protocolo de comunicacion I2C


                      //--DEFINE Arduino pines DIGITALES
                          // PUERTO SERIAL 0
                          // PUERTO SERIAL 1
                      const int  BUZZER = 2 ; //D2 reservalo para usar hard interrupt       
                          //pin digital D3    //D3 reservalo para usar hard interrupt
                          //  pinDatosDQ 4 // Pin del Sensor Peltier donde se conecta el bus OneWire -------> pin digital D4  
                                     
                      const int pinINVERSOR_A = 5 ;//Dp05 pinA Puente H   USAR  PINES – 5 y 6 cuando usa LIBRERIA TIMERONE Timer0 evita COMFLICTO con PWM   
                      const int pinINVERSOR_B = 6 ; //Dp06 pinB Puente H   
                                        //  7 LIBRE desde zocalo SD
                                        //  8 LIBRE desde zocalo SD
                                       
                
                      const int pinOPTOCUPLER = 9 ;// Led OPTOCUPLER cable verde de fuente
                      //                    10  LIBRE desde zocalo SD
                      //                    11  LIBRE desde zocalo SD
                      //                    12  LIBRE desde zocalo SD
                      const int        LedPin = 13 ;//onboard PCB y led AZUL frontal, tambien usado por comunicacion 

float horaAnt=0; //hora de inicio del setup para resetear por software cada N horas
boolean LEDState = LOW; //APAGA el LED
boolean status=LOW; //Estado del led
char dataIN; // Data recibida desde el Puerto serial
//char val; // Data recibida desde el Puerto serial
String ENTROPIA = "HEATING"; //"COOLING"


float tempActual = 0.1;
int temp;// Variable sensor de temperatura
float RawValue = 0.1;
float value;
float T1 =16.01;       //tempArranque -GOAL->  temp de inicio         --carga inicial para desarrollo
float T2 =32.00;           // tempSET -META->  temp a llegar en rampa ---carga inicial para desarrollo  
float Tmargen=0.15;//histeresis de termostato, Tmargen  pseudo PID viene de slider s5 
int PwFrio=255;
int PwHot=255;

float deltaTemp=0.1;    // instantanea para display 
float tempAMBIENT  = 0;//rtc
float tempAMBanterior  = 0;//rtc
float tempAnt = 0;  //almacenar la temperatura en una variable  del tipo float.
float tempDisAnt=0;
float tempTT  = 0;//variable local en rutina TERMOSTATO

int nEvent=0;// contador de eventos
int nLectu;// contador de LECTURAS DE TEMPERATURA
//unsigned long  reloj =0; //  no se usa

int E = 0;         // EVENTO  variable to store the value read 
  bool ESTADO_E=false;// Flag DE CONTROL  
int S = 0;         // START   variable to store the value read SI SON SOLO ON/OFF HACER VARIABLES BOOLEANAS
  bool  ESTADO_S= false;// Flag DE CONTROL
int A = 0;        // ABORT    variable to store the value read SI SON SOLO ON/OFF HACER VARIABLES BOOLEANAS
  bool ESTAnt_S=false;
  bool ESTADO_A=false;// Flag DE CONTROL
  bool LLegueT1=false;//   Flag DE CONTROL DEL TERMOSTATO 

//PARA VALIDAR LO RECIBIDO LO REENVIA A PROCESSING EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE
int nModo = 3;// 3= circadiano para test autonomo es lo que guarda la eprom del rtc
//cuidadoooooo  hay 2 variables definidas con el mismo nombre nModo una int y otra float ?????
//unsigned int nModo;  ////////////////////////////////////////////////coirregido  las  2 son int
           
int nEvento =0 ;//PARA VALIDAR LO RECIBIDO LO REENVIA A PROCESSING EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE

String inText;

char    buf1[20];//character array to save the output string into.

float s3 = 1.10;//pid multiplicar y dividir por 100 para recibir decimales
float s4 = 85;//pid  valor %  rango 0 a 100
float s5 = 0.14;//pid Tmargen  multiplicar y dividir por 100 para recibir decimales


float Tinstant=0;
float sgCorrida=0;
//bool tempo240k=false;
//bool Ciclico=false;
unsigned long miliAhora=0;
unsigned long miliStart=0;
unsigned long miliSoak=0;
unsigned long miliAvance=0;
float mRecta=0.25/60000;//   m=1 grado cada 4 minutos
int x=0;


//Prototipos de las funciones para definirles el alcance *********************************
void DETENCION();
void TERMOSTAT(float _T1, float _T2, float _margen);//Prototipo
void avisala() ;
void ENVIADATA();
void ENVIAstatus();

void pseudoPID_log();

void Boton();//Prototipo
void EstadosyBotones();//Prototipo
void envia_BT();
void rutMODO();//rutinasMODO
void Lineal ();//rutinasMODO
void R_circadiano();//rutinasMODO
void R_TCritica();//rutinasMODO
void R_termos();//rutinasMODO

void software_Reboot();// esta funcion se llama cada N horas  para evitar bloqueos.

void grabaMEM();// guarda datos en memRTC
void leeMEM();// lectura y presentacion y recupera datos en variables
void Voltimetro();
void monitoreo();//boolean test=true; PARA DESARROLLO MONITOREADO 

//void wdt_delay(unsigned long msec);//Prototipo
//void wdt_reload();
//void Tempo240k();//si es necesario reemplazar con wdt_delay
//Prototipos de las funciones para definirles el alcance *********************************
// https://www.electrodaddy.com/las-matematicas-en-arduino/

float hs=0;// circadiano hora reloj format centecimal
float T_calActual=0;
float TempDisip= 0;
float incremento=0;
float Suma=0;
float SumaDisip=0;
float aManecer=8.00;// hs= Srise  centecimal  dato
float aNochecer= 20.00;// hs =S set  centecimal  dato
float b = 0.8; //=coef ajuste NOCHE      
float a=1.5; //=coef ajuste DIA     
float tempMin=16.00;//activa Slider s1 // modo tropical VZ
float tempMax=32.00;//activa Slider s2 // modo tropical VZ
float deltaT=0;
float T_aNoche= 0;
//----------
 float m=46.3;  //ecuacion de la recta  
 int b0=68;     //ecuacion de la recta 
 float delta ; 
 float tension=0;  // voltimetro 

void setup() {//----------------------------------------------------------------------------- INICIO SETUP 
 Serial.begin(9600);//  Inicia la comunicación serie para monitor
    BT1.begin(9600);//  Inicia la comunicación serie para bluetooth

  sensorDS18B20.begin(); // Inicia el bus 1-Wire para sensores de TEMPERATURA
//Serial.print("freeMemory()=");  Serial.println(freeMemory());

   pinMode(pinEVENTO,INPUT);// SI analogRead 0 and 5 volts into integer values between 0 and 1023
   pinMode(pinSTART,INPUT) ;// pull down con resistencia 10K en PCB
   pinMode(pinABORT,INPUT) ;  

   pinMode(pinOPTOCUPLER, OUTPUT);
   pinMode(BUZZER, OUTPUT);
   pinMode(LedPin, OUTPUT);//13 idem Avisa -> led azul  ver hardware
                  pinMode(pinCirca,  OUTPUT);//led frontal rojo
                  pinMode(pinTCrict, OUTPUT);//led frontal  yellow  
                  pinMode(pinAlone,  OUTPUT);//led frontal  yellow PARA USARLO COMO HARD AUTO RESET
 //-----------------------salidas PWM para PUENTE H
   pinMode(pinINVERSOR_A, OUTPUT);//Dp03 pinA Puente H 
   pinMode(pinINVERSOR_B, OUTPUT);//Dp06 pinB Puente H cambiar por inconpatibilidad de libreria timerone
  
   //  son PWM      rango= 0 a 255
   analogWrite(pinINVERSOR_A,0);//POR DEFAULT APAGADOS
   analogWrite(pinINVERSOR_B,0);

avisala() ;
avisala() ;
avisala() ;

                                                                          //----------------------------------------------------------------autoreset
                                                                          //FUNCION autoreset --> void(* resetFunc) (void) = 0;  --> DESCOMENTAR para activar AUTO-RESET --> linea  62
                                                                          /*
                                                                                                    wdt_disable();
                                                                                                      wdt_enable(WDTO_8S); 
                                                                                                      delay(1000);  

                                                                                                    wdt_disable(); //siempre es bueno deshabilitarlo, si se dejó 'encendido' o si necesita tiempo de inicio

                                                                                                    Serial.print("iniciando Setup Free=");Serial.println(freeMemory()); // 
                                                                                                    //haga algunas cosas aquí

                                                                                                  //wdt_enable(WDTO_8S); // habilíta y configúra en 8 segundos
                                                                          */

                                                                          /*
                                                                          Serial.println("reset CADA 20sg"); wdt_delay (20000);//tienpo en milisegundos =20 SEGUNDOS
                                                                                                  

                                                                                                  digitalWrite(pinOPTOCUPLER, LOW);
                                                                                                  delay(2000);
                                                                                                  digitalWrite(pinOPTOCUPLER, HIGH);
                                                                                                
                                                                                  // resetFunc(); //call reset 
                                                                          Serial.println("never happens");
                                                                            */         

                                                                          //----------------------------------------------------------------autoreset

//----------- Modulo RTC 
//TEST  MODO AUTONOMO CIRCADIANO CON AUTO RESET 
//    USAR UN FLAG CON UN IF
                      
                       if (! rtc.begin()) {//--------------verifica el RTC conectado
                            Serial.println("No_hay_modulo_RTC");
                        while (1);//espera un microsegundo
                                          }//--------------verifica el RTC conectado
                                  // Ponemos en hora, solo la primera vez, luego comentar y volver a cargar.
                                  // Ponemos en hora con los valores de la fecha y la hora en que el sketch ha sido compilado.
                                  // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));// Fijar a fecha y hora de compilacion el sketch

                        //  reporte de error: no usar  este ajuste automatico
                        //    https://enioea2hw.wordpress.com/2020/04/09/reloj-dual-con-rct3231-y-arduino/#more-4372
                                                          //Si se ha perdido la alim/bateria, fijar fecha y hora
                                                          /* if (rtc.lostPower()) {// True if the bit is set (oscillator stopped) or false if it is running
                                                                                rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));// Fijar a fecha y hora de compilacion el sketch
                                                                                
                                                              }
                                                              */                                                       
//TEST  MODO AUTONOMO CIRCADIANO CON AUTO RESET                     
//----------- Modulo RTC  
DateTime now = rtc.now();//toma datos del modulo RTC 
horaAnt=now.hour();	//hora de inicio del setup y control de reset cada N horas

//----------- Modulo RTC 
//TEST  MODO AUTONOMO CIRCADIANO CON AUTO RESET 
leeMEM();// lectura y presentacion y recupera datos en variables 

digitalWrite(pinOPTOCUPLER, HIGH);// 
                            
}//----------------------------------------------------------------------------- ---- FIN SETUP



//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<AQUI COMIENZA EL  LOOP DEL CUERPO PRINCIPAL 
void loop(){
Serial.print("freeMemory()=");  Serial.println(freeMemory());

tempAMBIENT  = rtc.getTemperature();// LEER TEMPERATURA DEL modulo RTC  DEVUELVE   Current temperature (float)
                                                      // sprintf existe en arduino  Pero no maneja floats ver nota en :https://forum.arduino.cc/t/existe-sprintf-en-arduino/315583/5
                                                      // SE USA para concatenar textos con numero y hacer una sola escritura en un archivo
                                                      /*sprintf() stands for “string print format(ted)”. 

                                                              sprintf(buffer, "The %d burritos are %s degrees F", numBurritos, tempStr); 
                                                              sprintf(); //takes a minimum of 2 arguments. 
                                                      The first argument is where you plan to store the string that sprintf() will be making for you.
                                                        */
                                                            //Serial.println( buf1);
                                                            //println( buf1);//        FUNCION QUE ARMA UN STRING CON VARIABLES de  números enteros -no funca con floats
                                                            
                                                            //para float usar  --- dtostrf
                                                            // d ó i - entero decimal con signo,en lugar de formato octal o hexadecimal
                                                            // u – entero decimal sin signo , no hay puntos decimales.
                                                            // s – cadena de caracteres  
                                                            //-----------------------
                                                                                              /* Serial.println ("------------------------------------------");
                                                                                              Serial.print ("modoActivo: ");Serial.println(nModo);
                                                                                              Serial.print ("HoraModal : ");Serial.println(hs);// hs=now.second()/2.5;// 59 segundos =23.60 
                                                                                              Serial.print ("hora Calc=  ");Serial.print(now.second());Serial.println("  sg");

                                                                                              Serial.println ("------------------------------------------");
                                                                                              Serial.print ("Temp calc= ");Serial.println(T_calActual);
                                                                                              Serial.print ("Peltier  = ");Serial.println (tempActual);
                                                                                              Serial.print ("TeDisip  = ");Serial.println (TempDisip);
                                                                                              Serial.println ("///////////////////////////////////////////");
                                                          */
DateTime now = rtc.now();//toma datos del modulo RTC  
if ((now.hour()-horaAnt) == 2){//
                                                                          /*  instance-method hour
                                                                          @return Hour (0--23).  uint8_t  entero sin signo de 8 bits. 
                                                                          // In DateTime
                                                                          public: uint8_t hour() const
                                                                          uint8_t  entero sin signo de 8 bits. 
                                                                          uint_fast8_t es el int sin signo más rápido con al menos 8 bits. 
                                                                          uint_least8_t int sin fsigno con al menos 8 bits.
                                                                          */
                                                                    //horaAnt=now.hour();	// se define en el setup cada vez que reinicia
                              
                            
                              Serial.println(F("nModo INT ;t1  FLOAT;hot_cool  INT ;t2  FLOAT; time stamp"));
                              grabaMEM();//  guarda los datos de seteo en la EEPROM del RTC
                              //alcanza tiempo para grabar antes del reset  ???  
                              software_Reboot();// reset por wdt cada N horas para prevenir bloqueos y overflow/saturacion
          }
	
	
		

                                                 

//hs = now.hour()+ ( float ) now.minute()/60+  ( float )now.second()/6000;   // hora input para el calculo de la temperatura instantanea
//char    buf1[20];//character array to save the output string into.
//sprintf(     ) // stands for “string print CON formato”.
//sprintf(buf1, "%02d:%02d:%02d %02d/%02d/%02d",  now.hour(), now.minute(), now.second(), now.day(), now.month(), now.year()); 
  //sprintf(buf1,  "%hh: %mm:%ss%ss/%ddd/%mmm"   ,  now.hour(), now.minute(), char (now.second()), char (now.day()), now.month()); 
 // sprintf(buf1,  "%hh: %mm:%ss%ss/%ddd/%mmm"   ,  now.hour(), now.minute(), now.second(), now.day(), now.month(), now.year()); 

Suma=0;
SumaDisip=0;
for (x = 0; x < 7; x=x+1) { //toma 7 mediciones
                  
                  // Para que podamos identificar cada sensor por su índice y leer la temperatura.
                  // cada DS18B20 tiene asignada una dirección única de 64 bits
                  sensorDS18B20.requestTemperatures(); // comando  de toma temperatura a los sensores 

                  // SONDA Index(1) PLACA PELTIER  BOMBA DE CALOR TempDisip     ador placa sobre Peltier SOLO REFERENCIA
                                //DeviceAddress address2 = {0x28, 0x96, 0xDB, 0x95, 0xF0, 0x1, 0x3C, 0x7};//  etiqueta AZUL   sensor TempDisip
                  // SONDA Index(0) AIRE  CAMARA   INDOR          tempActual ESTA VARIABLE ACCIONA TERMOSTATO
                                //DeviceAddress address1 = {0x28, 0xAA, 0x6C, 0x86, 0x38, 0x14, 0x1, 0x1F};// sensor peltier
                  // SONDA TempRTC  AIRE  AMBIENTAL                                                       SOLO REFERENCIA
                  
                  // lee por address 
                  // identificar cada sensor , cada DS18B20 tiene asignada una dirección única de 64 bits
                  tempActual = sensorDS18B20.getTempC(Blanco);   // lee por address entrega FLOAT con SIGNO 
                                        // Lee por index
                                        //Trata todo el bus como una matriz de sensores y les asigna un índice.
                                        // Lee por index  guarda datos de sensores INDEXADOS DS18B20 entrega FLOAT con SIGNO 
                                        //tempActual = sensorDS18B20.getTempCByIndex(0);//etiqueta AZUL   Lee por index  guarda datos de sensores INDEXADOS DS18B20 entrega FLOAT con SIGNO 
                                        //TempDisip  = sensorDS18B20.getTempCByIndex(1);//etiqueta BLANCA  

                                // si tengo mas de 1 sensor
                                TempDisip=11.11;
                                int deviceCount = sensorDS18B20.getDeviceCount();
                                          if(deviceCount>0){
                                          TempDisip=sensorDS18B20.getTempC(Azul); } 

                   tempActual = tempActual+0.89;//COEF DE CALIBRACION DEL SENSOR  ESTA VARIABLE ACCIONA TERMOSTATO
                    TempDisip =  TempDisip+0.89;//COEF DE CALIBRACION DEL SENSOR
                              
                              Suma= tempActual+Suma; 
                              SumaDisip= TempDisip+SumaDisip; 
                              
                } 
    
 tempActual = Suma/x;//tempActual ESTA VARIABLE ACCIONA TERMOSTATO //este promedio lo repite en processing  
 TempDisip = SumaDisip/x;//este promedio lo repite en processing  
 

 ENVIADATA();
  ENVIAstatus();
    if ((tempActual!=tempAnt) || (tempDisAnt!=TempDisip)){//atencion con las operaciones con float cuyas comparaciones dan diferentes
                                            tempAnt=tempActual; 
                                            tempDisAnt=TempDisip; 

                              nLectu=nLectu+1;  //INCREMENTA NRO lectura                   
                                  ENVIADATA();   
                                  envia_BT();                         
                                                            /*  (T1);   //    sens nro=  1   palabra2
                                                                (nLectu);//   sens nro=  2 -->sens nro=  2 porque el primero es CERO
                                                                (nModo);//    sens nro=  3 'nModo' 
                                                                ENTROPIA); // sens nro=  4
                                                                ("conPWM=");Serial.print(PwFrio);
                                                                tempActual);//sens nro=  5 GOAL    
                                                                T2);//        sens nro=  6 META
                                                                Tinstant);//  sens nro=  7 INSTANT 
                                                                envia_BT(); 
                                                              */
                             }//  cuando cambia tempSensor---> evento,inicio, seteo data,cada 10sg,?????
                                                                                  /*
                                                                                      if abs((tempActual-TempDisip)>43) {//proteccion termica del peltier   EVALUAR VALOR ABSOLUTO SIN SIGNO abs(x)  
                                                                                          //min=-2 disip=41 delta=43
                                                                                          for (int avi=0; avi<=6;avi=avi+1) {avisala();}
                                                                                        DETENCION(); //abort
                                                                                          for (int avi=0; avi<=6;avi=avi+1) {avisala();}
                                                                                       
                                                                                        }        
                                                                                  */
// ubicado aqui es muy similar a una llamada por Serial.Event()
if (Serial.available() > 0) {  //ESCUCHA/RECIBE   si los datos están disponibles para leer  y  envia comfirmacion
                                                      // obtiene un número entero con el número de bytes (caracteres) disponibles para leer o capturar desde el puerto serie, 
                                                      //si el número es 0, significa que no hay datos almacenados. 
                                                      //El buffer puede almacenar un máximo de 64 bytes.(8 CARACTERES ASCII ???)
                                                   // asyncSerial.AsyncRecieve();//aqui devuelve un array( byte data[dataLength];//  BUFER[TAMAÑO])  con los datos leidos
                                      
                                                   //Serial.read()---The first byte of incoming serial data available (or -1 if no data is available) - int.
                       //char val; // Data recibida desde el Puerto serial                      
                              dataIN = Serial.read();  // PASAR     dataIN    POR REFERENCIA  

                                                                    //lo evalua EstadosyBotones()  con  dataIN
                                                                                  /*    if(dataIN == '1') {//1-controller   name DATAset  RECIBE DE PROCESING/// PARA DESARROLLO LO ESTA ENVIANDO 5 ACTIVA EL DATASET MAS ABAJO
                                                                                                                      //envia comfirmacion A PROCESING
                                                                                                                                Serial.print("1- "); //PALABRA del PAQUETE
                                                                                                                                Serial.print("REGISTRO_los_datos_recibidos="); 
                                                                                                                                Serial.println(dataIN); //Enviamos los datos en forma de byte 
                                                                                                                                //Serial.println(dataIN, DEC); 
                                                                                                                      // accion-->  carga datos recibidos en las correspondientes variables desde processing con la rutina enviadataset()
                                                                                                      }                                                                                                                   
                                                                                  else if(dataIN == '2'){ //2- controller  "START" RECIBE DE PROCESING                            
                                                                                                        //ESTADO_S=true; //lo evalua estados y botones con  dataIN
                                                                                                      // avisala();//envia comfirmacion BEEP  
                                                                                                                        //envia comfirmacion a PROCESSING
                                                                                                                                Serial.print("2- "); //PALABRA del PAQUETE
                                                                                                                                Serial.print("Estoy_recibiendo_un_START_2="); 
                                                                                                                                Serial.println(dataIN); //Enviamos los datos en forma de byte                                            
                                                                                                    } 
                                                                                  else if(dataIN == '3'){ //3- controller   "ABORT"       EN PROCESSING 
                                                                                                        //ESTADO_A=true; //lo evalua estados y botones dataIN
                                                                                                        // avisala();//envia comfirmacion BEEP 
                                                                                                                                Serial.print("3- "); //PALABRA del PAQUETE
                                                                                                                                Serial.print("Estoy_recibiendo_un_ABORT="); 
                                                                                                                                Serial.println(dataIN); //Enviamos los datos en forma de byte                                                          
                                                                                                    }  */ 

                    if(dataIN == '5'){ //si recibimos un 5  DE PROCESSING ->funcion enviadataset() desde-> linea 122  en linea 324//232 Pr
                                      // avisala();
                                              //recibeFLOAT_NAIVE();   // SIN FUNCIONES Serial
                                                            //leerlos y guardarlos en dataIN 
                                                              T1 =Serial.read();//T1 = value; sens nro= 11 --GOAL// myPort.write((byte)(seteatempMin));// 11
                                                                  if (T1>=127 ){  T1=T1-256; }//sistema binario para representar números con signo: complemento a uno, 
                                                              
                                                              T2 =Serial.read();//T2 = value; sens nro= 12 --META//myPort.write((byte)(seteatempMax));// 12
                                                                  if (T2>=127){  T2=T2-256; }//sistema binario para representar números con signo: complemento a uno,                                               
                                                              nModo =Serial.read();  //sens nro= 13 float nModo =Serial.read(); //myPort.write((byte)(float(seteanModo)));// 13 seteanModo es INT
                                                              //se guarda en epromm del RTC a recuperar luego del reset

                                                              
                                                              nEvento =Serial.read();//sens nro= 14 float evento =Serial.read(); ---->>>>>revisar no llega  myPort.write((byte)(float(nEvento)));//    14 EVENTO es INT
                                                              
                                                              s3=Serial.read();//      sens nro= 15 float s3 = *100//myPort.write((byte)(s3*10));
                                                              //s3=1.10;
                                                              s3=s3/10; 
                                                 // Serial.println(s3);    
                                                              s4=Serial.read();//    es % rango 0 a 100  sens nro= 16 float s4 = //myPort.write((byte)(s4*100));//
                                                              s4=s4/100;//revisar
                                                              s4=85;//fijo para entrega
                                                 // Serial.println(s4);  
                                                              s5=Serial.read();//      sens nro= 17 float s5 = *100  decodifica de 0 a 255 ???//myPort.write((byte)(s5*10));
                                                              //s5=1.40;
                                                              s5=s5/10;   
                                        /*
                                        // using an int and a base:
                                              stringOne =  String(analogRead(A0), DEC);
                                              // prints "453" or whatever the value of analogRead(A0) is
                                              Serial.println(stringOne);*/

                                         //convertir la cadena recibida en  un float usando
                                         // float f = strtof (data);  
                                         //myString.toFloat()
                                      // String jjj = String(5.698, 3); 
                                       
                                            // jjj=String (Serial.read()); 

                                                            //s5=(jjj.toFloat());//      sens nro= 17 float s5 =  ----------->>>>>>>>>>>>>>>>trunca decimales revisar envio float                                  
                                             
                                                  
                                          //devuelve lectura para control de desarrollo -->quedaran solo las cargas de las variables seteadas  
                                          
                                          ENVIAstatus();avisala(); //ficha enviadata linea 70
                                         // ENVIADATA();//---------------->>>>>>>>>>>>>>>>>>>>>prueba envio sensores
                                          grabaMEM();avisala();//guarda datos de variables a recuperar luego del reset
                                          //paquet 5 
                                        }//si recibimos un 5  DE PROCESSING

                      else if (dataIN == '9') {//                           _resetXsoftCall.pde
                                                    //envia comfirmacion A PROCESING
                                                              Serial.print("9- "); //PALABRA del PAQUETE
                                                              Serial.print("HAGO UN RESET por direccion CERO del ARDUINO"); 
                                                              Serial.println(dataIN); //Enviamos los datos en forma de byte          
                                                    // accion-->  "HAGO UN RESET DEL ARDUINO"con la rutina    -->   resetFunc();
                                                    //  resetFunc();//RESET por direccion CERO del ARDUINO
                                                   // void(* resetFunc) (void) = 0; //declare reset function @ address 0   enviado por referencia de C++
                                                grabaMEM();//guarda datos de variables a recuperar luego del reset
                                                avisala();
                                                software_Reboot();
                                              }  //si recibimos un 9  DE PROCESSING                                          
                    
                      else if (dataIN == '7') {//ajusto hora del RTC   en processing pulsa tecla H linea 697
                                               avisala();
                                               Serial.print("---------recibi 7 via puerto serial-------------------------");
                                             //  Serial.println ( Serial.read());// print as an ASCII-encoded decimal 
                                              // Serial.println (( Serial.read() , DEC) );// print as an ASCII-encoded decimal 
                                                // ENVIAstatus(); //ficha enviadata linea 70  
 
                                              
                              //recibir la fecha de processing y ajustar la hora con el dato recibido
                             //rtc.adjust(DateTime(2021, 2, 21,8, 11, 45));  este llega bien 
                             int ano=Serial.read();
                             int mes=Serial.read();
                             int dia=Serial.read();
                             int hora=Serial.read();
                             int minut=Serial.read();
                             int seg=Serial.read();                          //año               mes  21         dia           hora  18         min 19          seg  20
                                   //rtc.adjust( DateTime(Serial.read(), Serial.read(), Serial.read(), Serial.read(), Serial.read(), Serial.read()));
                                    rtc.adjust(DateTime(ano,mes,dia,hora,minut,seg));
		                                   //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));// Fijar a fecha y hora de compilacion el sketch 
                                          // ENVIAstatus(); //ficha enviadata linea 70  // Serial.print(now.hour(), DEC);//sens nro= 18 // hora
                                           ENVIAstatus(); //ficha enviadata linea 70  // Serial.print(now.minute(), DEC);//sens nro= 19 // minuto de 0 a 59 
                                            // ENVIAstatus(); //ficha enviadata linea 70  // Serial.print(now.hour(), DEC);//sens nro= 20 // seg
                                             // ENVIAstatus(); //ficha enviadata linea 70  // Serial.print(now.hour(), DEC);//sens nro= 21 //  mes


                                              }  //si recibimos un 7  DE PROCESSING 

} //cierre ESCUCHA/RECIBE  y  envia comfirmacion                                                            

EstadosyBotones();//evalua FLAGs---------y--------evalua estado  
rutMODO();    //entrega Tinstant para parametrizar el termostato  --con Tinstant ----- 
pseudoPID_log();                    
TERMOSTAT(Tinstant,tempActual,Tmargen);//-- SOAK T1-- LLEVA LA PLACA A T1 
//boolean test=true; PARA DESARROLLO MONITOREADO  
monitoreo();//boolean test=true; PARA DESARROLLO MONITOREADO                                 


                            
                            
              
}// FIN LOOP
