
//NOTAS --------VERSION_00   05-2024 PARA GITHUB-------------------------
/* FUNCIONAMIENTO AUTONOMO COM OPCION DE MONITOREO y REGISTRO DE DATTALOGER VIA PC CON PROCESSING
LA ACTIVACION DE LAS RUTINAS de fotoperiodo() y  DE CONTROL TERMICO(nMODO) con  SUS PARAMETROS SE HACEN MODIFICANDO EN EL ARDUINO IDE EL ARCHIVO Parametror.ino

NO USA grabaMEM() ni leeMEM()
SE REEMPLAZA POR LLAMADA DE LA FUNCION PARAMETROR(), 
SE INCLUYE LLAMADA DE LA FUNCION PARAMETROR() EN  grabaMEM()  y leeMEM()

Dado que el testeo de rampaTermica tiene una duracion maxima de 90 /120 minutos se deshabilita para esta funcion el autoreset 
llama a autoReset(); solo si nModo es distinto que 2
o se lo setea en 120 minutos
*/


//04-2022 ------------------->PARA SUBIR con NANO usar old bootloader
//     SKETCH               variables  Glob
//           ocupa               ocupa     LIBRES
//18792 bytes (58%)     1231 bytes 54%      925 bytes 06-JUN22

//20694 bytes (67%)     1116 bytes (54%)    932   rehubico  sonda de disipador en el interior de la camara
//Usa 2 librerias  de rRTC una para memoria otra para reloj
//22626 bytes (73%)     1132 bytes (55%)    916  librerias ds3231_simple.cpp y .h LIBRERIA CRAKEADA --> de:DateTime a:  DateSTime


//DETECTAR QUE PLACA ESTOY USANDO POR SOFT:
//https://forum.arduino.cc/t/identificar-una-placa-arduino-por-algun-numero-serie/550698/8
//http://blog.elcacharreo.com/2013/10/22/arduino-faq-como-detectar-desde-codigo-que-placa-de-arduino-se-esta-usando/


/* para circadiano Venezolana  la rutina tiene fija       ---------> CONTROLyAJUSTE_VZmedia25
                                tempMin=14.00;//activa Slider s1 // modo tropical VZ
                                tempMax=33.00;//activa Slider s2 // modo tropical VZ
                                deltaT=0;
                                deltaT=tempMax-tempMin;
                                */
//258   tempMin=19.00;//activa Slider s1 // modo tropical VZ
//259  tempMax=33.00;//activa Slider s2 // modo tropical VZ



// set de variabes fijadas para version VZ circad  //fijo para entrega 07-09  // CONTROLyAJUSTE_VZmedia25
//------------------------------------------------------------------------------
//LOCK VARIABLE AJUSTE HORA SOLO 1 SHOT   int ajuste =1; linea 345   
//solo un ajuste de hora por corrida para solicitar otro requiere pasar por reset  que es automatico cada 15 minutos
//BLOQUEO ABORT  SOLO POR HARD

//SOLO SI  if (hora<23)PERMITE AJUSTE HORA    if (hora<23){//evita error de lectura  linea 786
//nModo = 3;// 3= circadiano para test autonomo linea 240 linea 58 MenRTC
//814   if ((now.minute() - minutAnt) == 15) {  //auto reset
// select sonda sensor Azul Blanco  linea 481
//tempActual = sensorDS18B20.getTempC(Blanco);  en camara Labo Exactas 
//lin 278  float s3 = 0.70;//pid RANGO DE ACCION SOLO +/-0.7ºC QUEDA 255 O CERO
// lin 623       s3=0.70;//pid RANGO DE ACCION SOLO +/-0.7ºC QUEDA 255 O CERO
// lin 727       s3=0.70;//fijo para entrega 
//lin 573 if(dataIN == '5'){ //si recibimos un 5  DE PROCESSING ->funcion enviadataset()
//lin 214  float T1 =16.01;       //tempArranque -GOAL->  temp de inicio         --carga inicial para desarrollo
///lin 215  float T2 =32.00;          // tempSET -META->  temp a llegar en rampa --carga inicial para desarrollo

//lin 278  float s3 = 0.70;//pid multiplicar y dividir por 100 para recibir decimales
//lin 251  float s4 = 85;//pid  valor %  rango 0 a 100
//lin 592   s4=85;//fijo para entrega
//lin 732   s4 = 85;             //fijo para entrega   PROC PIDE SETEO DATOS 
//lin 252  float s5 = 0.14;//pid Tmargen  multiplicar y dividir por 100 para recibir decimales
//                               Tmargen=0.180;//REVISAR  RUTINAS01 LINEA 101 pseudoPID_log

//----------------------------------------------
// set de variabes fijadas para version TEMP cte 30 grados 12-04-2023

//------------------------------------------------------------------------------
// Tinstant=30.00 ;  linea 169 rutinasMODO
//nModo = 2; lineal() linea 107 MemRTC  //nModo=2; //REVISAR QUEDA FIJO  cte 30 
//linea 28  rutinasModo--- if (      nModo == 2 ){//sens nro= 13 float nModo =Serial.read();  
                        //Lineal ();//llama funcion que   entrega Tinstant
//lin 207  float T1 =30;       //tempArranque -GOAL->  temp de inicio         --carga inicial para desarrollo
//lin 208  float T2 =30;           // tempSET -META->  temp a llegar en rampa ---carga inicial para desarrollo



//reducir uso memoria con:

//eliminar variables no usadas
//eliminar variables encadenadas
//usar booleanas
///limitar el uso de print en conSola  porque toma mucho tiempo del procesador

#include <avr/wdt.h>  //watch-dog-Timer, esta librería  dispara una interrupcion que llama una funcion  cuando se acaba el tiempo
//#include <WatchDog.h>	//esta librería  dispara una interrupcion que llama una funcion (que puede resetear el MCU)  cuando se acaba el tiempo


#include <MemoryFree.h>

bool test = false;  //boolean test=true; PARA DESARROLLO MONITOREADO se habilita con switch de evento del pcb
bool test01 = false;  //boolean test=true; PARA DESARROLLO MONITOREADO de modos

#include <SoftwareSerial.h>
SoftwareSerial BT1(7, 8);  // RX | TX // Ojo. invertir en el BlueTooth
#include <OneWire.h>
#include <DallasTemperature.h>
  //#include <ds3231.h>// libreria de arduino parece mas liviana   https://www.arduino.cc/reference/en/libraries/ds3231/
  //                                                               https://github.com/NorthernWidget/DS3231
 
#include <RTClib.h>  // ---paraRTC real clock time    https://adafruit.github.io/RTClib/html/class_r_t_c___d_s3231.html
RTC_DS3231 rtc;      // Declaramos un RTC DS3231

//#include <Wire.h>
//#include <AT24CX.h>  //BIB  memoriA eeprom en modulo RTC DS3231
//AT24C32 EepromRTC;   //Declaramos EepromRTC  clase con tamaño de página predefinido

//datos a guadar en EepromRTC
/*
// byte variable_byte=128;
int variable_int = 3000;
// long variable_long=48300011;
float variable_float = 3.14;
char cadena[30] = "time= hh:mm:ss";
*/

int aAT24;
float bAT24;
float cAT24;
float dAT24;
float eAT24;
float fAT24;
float gAT24;
char cadena2[30];
char cadena[30] = "time= hh:mm:ss";
//datos a guadar en EepromRTC


// Instancia a las clases OneWire y DallasTemperature
#define pinDatosDQ 4                // Pin donde se conecta el bus OneWire -------> pin digital D4
OneWire oneWireObjeto(pinDatosDQ);  //pin digital 4                 como bus OneWire clase OneWire
//OneWire oneWireObjeto(4); //pin digital 4                 como bus OneWire clase OneWire
DallasTemperature sensorDS18B20(&oneWireObjeto);  //Declara un  objeto para el sensor clase DallasTemperature
//-> Sensor 1 : 0x28, 0xAA, 0x6C, 0x86, 0x38, 0x14, 0x01, 0x1F  // -------->ETIQUETA AZUL supongo INDEX(0)
//-> Sensor 2 : 0x28, 0x96, 0xDB, 0x95, 0xF0, 0x01, 0x3C, 0x07 // -------->ETIQUETA BLANCA supongo INDEX(1)
// por Addresses  matriz de long 8 x 8
uint8_t Azul[8] = { 0x28, 0xAA, 0x6C, 0x86, 0x38, 0x14, 0x01, 0x1F };    // -------->ETIQUETA AZUL supongo INDEX(0)
uint8_t Blanco[8] = { 0x28, 0x96, 0xDB, 0x95, 0xF0, 0x01, 0x3C, 0x07 };  // -------->ETIQUETA BLANCA supongo INDEX(1)
                                                                         //sensors.getTempC(deviceAddress);

/*In general, the const keyword is preferred for defining constants and 
should be used instead of #define.
********************Notes and Warnings**************
There is no semicolon after the #define statement. If you include one, the compiler will throw cryptic errors further down the page.
this is an error               #define ledPin 3; // this is an error
this is an error               #define ledPin  = 3 // this is also an error
Similarly, including an equal sign after the #define statement will also generate a cryptic compiler error further down the page.
*/

const int pinEVENTO = A0;  // BOTON EVENTO
const int pinSTART = A1;   // BOTON START/INICIO
const int pinABORT = A2;   // BOTON  ABORT/Stop
const int pinPOTE = A3;    // pote  usar pin analog read MONITOREAR TENSION PUENTE H
const int pinCirca = 10;   //pwm desde zocalo SD led frontal ROJO
const int pinTCrict = 11;  //pwm desde zocalo SD led frontal YELLOW
const int pinAlone = 12;   //    desde zocalo SD led frontal YELLOW

// protocolo de comunicacion I2C Arduino UNO, NANO reserva por default -> SDA = A4 y SCL = A5 NANO
//#define SCL 5  protocolo de comunicacion I2C   The compiler will replace any mention of scl with the value 5 at compile time.
//#define SDA 4  protocolo de comunicacion I2C


//--DEFINE Arduino pines DIGITALES
const int BUZZER = 2;  //D2 reservalo para usar hard interrupt
                       //pin digital D3    //D3 reservalo para usar hard interrupt
                       //  pinDatosDQ 4 // Pin del Sensor Peltier donde se conecta el bus OneWire -------> pin digital D4

const int pinINVERSOR_A = 5;  //Dp05 pinA Puente H   USAR  PINES – 5 y 6 cuando usa LIBRERIA TIMERONE Timer0 evita COMFLICTO con PWM
const int pinINVERSOR_B = 6;  //Dp06 pinB Puente H
                              //  7 LIBRE 
                              //  8 LIBRE 

const int pinOPTOCUPLER = 9;  // Led OPTOCUPLER cable verde de fuente
//                    10  LIBRE 
const int pinFOTOPERIODO =11;//
//                    12  LIBRE 
const int LedPin = 13;  //onboard PCB y led AZUL frontal, tambien usado por comunicacion
//--DEFINE Arduino pines DIGITALES

int horaAnt = 0;         //hora de inicio del setup para resetear por software cada N horas
int minutAnt = 0;        //hora de inicio del setup para resetear por software cada N horas
boolean LEDState = LOW;  //APAGA el LED
boolean status = LOW;    //Estado del led
char dataIN;             // Data recibida desde el Puerto serial
String ENTROPIA = "EstadoBombaTermica";  //"COOLING"


float tempActual = 0.1;
int temp;  // Variable sensor de temperatura
float RawValue = 0.1;
float value;
float T1 =30;       //tempArranque -GOAL->  inicio         --carga inicial para desarrollo
float T2 =30;       // tempSET -META->  temp a llegar en rampa ---carga inicial para desarrollo
float Tmargen = 0.15;  //histeresis de termostato, Tmargen  pseudo PID viene de slider s5
int PwFrio = 255;
int PwHot = 255;

float deltaTemp = 0.1;      // instantanea para display
float tempAMBIENT = 0;      //rtc
float tempAMBanterior = 0;  //rtc
float tempAnt = 0;          //almacenar la temperatura en una variable  del tipo float.
float tempDisAnt = 0;
float tempTT = 0;           //variable local en rutina TERMOSTATO

int nEvent = 0;  // contador de eventos
int nLectu;      // contador de LECTURAS DE TEMPERATURA

int E = 0;              // EVENTO  variable to store the value read
bool ESTADO_E = false;  // Flag DE CONTROL
int S = 0;              // START   variable to store the value read HACER VARIABLES BOOLEANAS
bool ESTADO_S = false;  // Flag DE CONTROL
int A = 0;              // ABORT   variable to store the value read HACER VARIABLES BOOLEANAS
bool ESTAnt_S = false;
bool ESTADO_A = false;  // Flag DE CONTROL
bool LLegueT1 = false;  // Flag DE CONTROL DEL TERMOSTATO

//PARA VALIDAR LO RECIBIDO LO REENVIA A PROCESSING EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE
int nModo = 3;  // 3= circadiano para test autonomo es lo que guarda la eprom del rtc linea 58
//unsigned int nModo;  /////////////////

int nEvento = 0;  //PARA VALIDAR LO RECIBIDO LO REENVIA A PROCESSING EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE

String inText;

char buf1[20];  //character array to save the output string into.

float s3 = 0.70;  //pid multiplicar y dividir por 100 para recibir decimales 
float s4 = 85;    //pid  valor %  rango 0 a 100
float s5 = 0.15;  //pid Tmargen  multiplicar y dividir por 100 para recibir decimales


float Tinstant = 0;
float sgCorrida = 0;
//bool tempo240k=false;
//bool Ciclico=false;
unsigned long miliAhora = 0;
unsigned long miliStart = 0;
unsigned long miliSoak = 0;
unsigned long miliAvance = 0;
float mRecta = 0.25 / 60000;  //   m=1 grado cada 4 minutos
int x = 0;


//Prototipos de las funciones para definirles el alcance *********************************
void TERMOSTAT(float _T1, float _T2, float _margen);  //Prototipo
void avisala();
void pseudoPID_log();

void flashAzul();
void Voltimetro();

void rutMODO();       //rutinasMODO

void monitoreo();  //boolean test=true; PARA DESARROLLO MONITOREADO
void R_circadiano();  //rutinasMODO


void R_TCritica();    //rutinasMODO
void R_termos();      //rutinasMODO
void Lineal();        //rutinasMODO
void fotoperiodo();   // 05-2024
void Parametror();    // 05-2024-----AJUSTESySETEOS();// reemplaza a leeMeM en desarollo o seteo fijo

//01-2024  void ENVIADATA();
//01-2024  void ENVIAstatus();
//01-2024  void Boton();  //Prototipo
//void EstadosyBotones();//Prototipo
//01-2024  void envia_BT();

//void grabaMEM();  // guarda datos en memRTC
//void leeMEM();    // lectura y presentacion y recupera datos en variables
void autoReset();
void software_Reboot();// esta funcion se llama cada N horas  para evitar bloqueos. 

//***************************************************** DESCOMENTAR  para activar AUTO-RESET
/* void software_Reboot()	{		// esta funcion resetea el arduino y se llama cada 2 horas  para evitar bloqueos.			
                                             //usarlo para time en soak o para tiempo entre de lecturas	

                                            wdt_enable(WDTO_15MS);        //watchdogTIMER  buenisimo Timer por INTERRUPCION                        
                                            while(1)	{	}		
                                        }			
 */

/*para restablecer la placa, se implementa un ciclo corto,(15 milisegundos) 	WDTO_15MS				
                                      cuando el tiempo de espera expira, el sistema se reinicia									
                                      al llamar a la funcion      software_Reboot     reiniciando la placa a los 15 ms.
                                      Processing recupera la coneccion luego del reset
                                      
//***************************************************** DESCOMENTAR para activar AUTO-RESET
//                  void(* resetFunc) (void) = 0; //declare reset function @ address 0   enviado por referencia de C++
*/

//void wdt_delay(unsigned long msec);//Prototipo
//void wdt_reload();
//void Tempo240k();//si es necesario reemplazar con wdt_delay
//Prototipos de las funciones para definirles el alcance *********************************

float hs = 0;  // circadiano hora reloj format centecimal
float T_calActual = 0;
float TempDisip = 0;
float incremento = 0;
float Suma = 0;
float SumaDisip = 0;
float aManecer = 8.00;    // hs= Srise  centecimal  dato
float aNochecer = 20.00;  // hs =S set  centecimal  dato
const float b = 0.8;      //=coef ajuste NOCHE
const float a = 1.5;      //=coef ajuste DIA
float tempMin = 19.00;    //activa Slider s1 // modo tropical VZ
float tempMax = 33.00;    //activa Slider s2 // modo tropical VZ
float deltaT = 0;
float T_aNoche = 0;
//----------
float m = 46.3;  //ecuacion de la recta
int b0 = 68;     //ecuacion de la recta
float delta;
float tension = 0;             // voltimetro
int ajuste =1; //solo un ajuste de hora por corrida para solicitar otro requiere pasar por reset  que es automatico cada 15 minutos
//-----------05-2024
int tomas=5000;// Set min interval in milliseconds between 2 measurements. Default 10000 set in setup() method.
int rstMin = 49;         // tiempo en minutos para disparar auto reset
int reinicio = 15;
int Mreinicio = 1;
float adjSensor = 0;  //COEF DE CALIBRACION DEL SENSOR   tempActual linea 483  
float HcRTC = 0.123456789;// fotoperiodo 
float hcOn  = 0.123456789;// fotoperiodo   
float hcOff = 0.123456789;//fotoperiodo 
float XhcOn = 0.123456;//    fotoperiodo 
float hhSX  = 0.123456789;// fotoperiodo 



void setup() {         //----------------------------------------------------------------------------- INICIO SETUP
  wdt_disable();       //siempre es bueno deshabilitarlo al comienzo
  Serial.begin(9600);  //  Inicia la comunicación serie para monitor
  Serial.println("apago WDT");
  BT1.begin(9600);  //  Inicia la comunicación serie para bluetooth

  sensorDS18B20.begin();  // Inicia el bus 1-Wire para sensores de TEMPERATURA
                          //Serial.print("freeMemory()=");  Serial.println(freeMemory());

  pinMode(pinEVENTO, INPUT);  // SI analogRead 0 and 5 volts into integer values between 0 and 1023
  pinMode(pinSTART, INPUT);   // pull down con resistencia 10K en PCB
  pinMode(pinABORT, INPUT);

  pinMode(pinOPTOCUPLER, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(LedPin, OUTPUT);         //13 idem Avisa -> led azul  ver hardware
  pinMode(pinCirca, OUTPUT);       //led frontal rojo
  pinMode(pinTCrict, OUTPUT);      //led frontal  yellow
  pinMode(pinAlone, OUTPUT);       //led frontal  yellow PARA USARLO COMO HARD AUTO RESET
 //-----------------------salidas PWM para PUENTE H
  pinMode(pinINVERSOR_A, OUTPUT);  // pinA Puente H
  pinMode(pinINVERSOR_B, OUTPUT);  // pinB Puente H 
  
  analogWrite(pinINVERSOR_A, 0);  //POR DEFAULT APAGADOS
  analogWrite(pinINVERSOR_B, 0);  //  son PWM      rango= 0 a 255

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
    Serial.println("modulo_RTC");
  if (!rtc.begin()) {  //--------------verifica el RTC conectado
    Serial.println("No_hay_modulo_RTC");
                while (1)
                    ;  //espera un microsegundo
                    }  //--------------verifica el RTC conectado
        
         // Ponemos en hora, solo la primera vez, luego comentar y volver a cargar.
         // Ponemos en hora con los valores de la fecha y la hora en que el sketch ha sido compilado.
         // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));// Fijar a fecha y hora de COMPILACION el sketch
  
  //  reporte de error: no usar  este ajuste automatico
  //    https://enioea2hw.wordpress.com/2020/04/09/reloj-dual-con-rct3231-y-arduino/#more-4372
  //----------- Modulo RTC

 // MODO AUTONOMO CIRCADIANO CON AUTO RESET
  DateTime now = rtc.now();  //toma datos del modulo RTC
  horaAnt = now.hour();      //hora de inicio del setup y control de reset cada N horas
  minutAnt = now.minute();
  // MODO AUTONOMO CIRCADIANO CON AUTO RESET

//memoria EEPROM EN Mmodulo RTC
  //ASIGNA LA DIECCION DEL MODULO ademas por Hard soldando A1 A2 A3 A GND EN EL MODULO x+x2+x3 --> 1 +	2 +	4	=7
  //AT24CX(byte index, byte pageSize);
  //AT24C32(0x57);  //ASIGNA LA DIECCION DEL MODULO de memoria EEPROM por soft

  leeMEM();  // lectura y presentacion y recupera datos en variables
 
  avisala();
  avisala();
  avisala();
  digitalWrite(pinOPTOCUPLER, HIGH);  //
  delay(500);
  digitalWrite(pinOPTOCUPLER, LOW);  //
  delay(500);
  digitalWrite(pinOPTOCUPLER, HIGH);  //
  delay(500);
  digitalWrite(pinOPTOCUPLER, LOW);  //
  delay(500);
  digitalWrite(pinOPTOCUPLER, HIGH);  //
  delay(500);
  digitalWrite(pinOPTOCUPLER, LOW);  //
  delay(500);
  digitalWrite(pinOPTOCUPLER, HIGH);  //
  Serial.println("fin setup");

}  //----------------------------------------------------------------------------- ---- FIN SETUP



//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<AQUI COMIENZA EL  LOOP DEL CUERPO PRINCIPAL



void loop() {
  avisala();digitalWrite(pinTCrict,HIGH);  delay(75);  digitalWrite(pinTCrict,LOW);
  //test=true;
  test = false;
  //-------------------------------------LEE SENSORES
  Suma = 0;
  SumaDisip = 0;
  for (x = 0; x < 5; x = x + 1) {  //toma 5 mediciones   // lee por address
              sensorDS18B20.requestTemperatures();  // comando  de toma temperatura a los sensores
                // Para que podamos identificar cada sensor por su índice y leer la temperatura.
                // cada DS18B20 tiene asignada una dirección única de 64 bits
                // SONDA Index(1) PLACA PELTIER  BOMBA DE CALOR TempDisip     ador placa sobre Peltier SOLO REFERENCIA
                //DeviceAddress address2 = {0x28, 0x96, 0xDB, 0x95, 0xF0, 0x1, 0x3C, 0x7};//  etiqueta AZUL   sensor TempDisip
              // SONDA Index(0) AIRE  CAMARA   INDOR          tempActual ESTA VARIABLE ACCIONA TERMOSTATO
              //DeviceAddress address1 = {0x28, 0xAA, 0x6C, 0x86, 0x38, 0x14, 0x1, 0x1F};// sensor peltier
              // SONDA TempRTC  AIRE  AMBIENTAL  
              //tempActual = sensorDS18B20.getTempC(Azul);  en taller                                                     SOLO REFERENCIA
              tempActual = sensorDS18B20.getTempC(Blanco); // en camara Labo Exactas linea 481
              //tempActual = sensorDS18B20.getTempC(Azul);  // lee por address entrega FLOAT con SIGNO
                                                          // Lee por index
                                                          //Trata todo el bus como una matriz de sensores y les asigna un índice.
                                                          // Lee por index  guarda datos de sensores INDEXADOS DS18B20 entrega FLOAT con SIGNO
                                                          //tempActual = sensorDS18B20.getTempCByIndex(0);//etiqueta AZUL   Lee por index  guarda datos de sensores INDEXADOS DS18B20 entrega FLOAT con SIGNO
                                                          //TempDisip  = sensorDS18B20.getTempCByIndex(1);//etiqueta Blanco
              // si tengo mas de 1 sensor
              TempDisip = 0.1;
              int deviceCount = sensorDS18B20.getDeviceCount();
                        if (deviceCount > 0) {// si tengo mas de 1 sensor
                          TempDisip = sensorDS18B20.getTempC(Azul);
                        }  //ver si disponible para esta version clon

              tempActual = tempActual + adjSensor;  //COEF DE CALIBRACION DEL SENSOR  ESTA VARIABLE ACCIONA TERMOSTATO
              TempDisip = TempDisip + adjSensor;    //COEF DE CALIBRACION DEL SENSOR
              Suma = tempActual + Suma;
              SumaDisip = TempDisip + SumaDisip;
  }//toma 5 mediciones   // lee por address

  tempActual = Suma / x;      //tempActual ESTA VARIABLE ACCIONA TERMOSTATO //este promedio lo repite en processing
  TempDisip = SumaDisip / x;  //este promedio lo repite en processing
  DateTime now = rtc.now();   //toma datos del modulo RTC
  Serial.print(" ATT... reset en: ");
  Serial.println(now.minute() - minutAnt);
  tempAMBIENT = rtc.getTemperature();  // LEER TEMPERATURA DEL modulo RTC  DEVUELVE   Current temperature (float)
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

//Dado que la prueba de rampa tiene una duracion maxima de 90 /120 minutos se deshabilita para esta funcion el autoreset /o se lo setea en 120 minutos
if (nModo!=2){autoReset();	}//void software_Reboot()	{	// esta funcion resetea el arduino y se llama cada 2 horas  para evitar bloqueos.	
//Dado que la prueba de rampa tiene una duracion maxima de 90 /120 minutos se deshabilita para esta funcion el autoreset /o se lo setea en 120 minutos

   // leeMEM();
  //ENVIADATA();  //01-2024                         //  Serial.print("2- ");//Serial.print("2-tempActual: ");
                                                               //ENVIAstatus();  //Serial.print("6-enviaSTATUS ");//
  if ((tempActual != tempAnt) || (tempDisAnt != TempDisip)) {  //atencion con las operaciones con float cuyas comparaciones dan diferentes
            tempAnt = tempActual;
            tempDisAnt = TempDisip;
            nLectu = nLectu + 1;  //INCREMENTA NRO lectura
            //ENVIADATA();//  Serial.print("2- ");//Serial.print("2-tempActual: ");
            //01-2024   envia_BT(); 
  }  //  cuando cambia tempSensor--->

  S = digitalRead(pinSTART);  // read the input pin devuelve   HIGH or LOW reposo es LOW presionado es HIGH
  S = HIGH;
  A = digitalRead(pinABORT);   // read the input pin devuelve   HIGH or LOW reposo es LOW presionado es HIGH
  E = digitalRead(pinEVENTO);  // A0
  if (E == HIGH) {             // " pulsador E hard PARA DESARROLLO"   EVENTO SOLO desde PROCESSING PARA GUARDAR EN FILE
          digitalWrite(BUZZER, 1);
          delay(75);
          digitalWrite(BUZZER, 0);
          //Usare el PuLSADOR  para desarrollo toggle de variables test=false
          //luego se habilitara el selector rotativo y leds
          test = !test;
          for (int avi = 0; avi <= 5; avi = avi + 1) { avisala(); }
          delay(150);
          if (test) {
                    delay(150);
                    for (int avi = 0; avi <= 2; avi = avi + 1) { avisala(); }
                    Serial.println("1 ESTA ACTIVO test==true por pulsador E hard PARA DESARROLLO");
                  }
  }
  //-----------------------------------------LEE SENSORES



  //ESCUCHA/RECIBE   si los datos están disponibles para leer  y  envia comfirmacion
                                 // obtiene un número entero con el número de bytes (caracteres) disponibles para leer o capturar desde el puerto serie,
                                 //si el número es 0, significa que no hay datos almacenados.
                                 //El buffer puede almacenar un máximo de 64 bytes.(8 CARACTERES ASCII ???)
                                 // asyncSerial.AsyncRecieve();//aqui devuelve un array( byte data[dataLength];//  BUFER[TAMAÑO])  con los datos leidos







  //ESCUCHA/RECIBE  --->>>>>>>>>>>>>ATENCION EVALUA PULSADORES SOLO SI SERIAL.AVAIABLEavailable
  // ubicado aqui es muy similar a una llamada por Serial.Event()
 
  if (Serial.available() > 0) {  //ESCUCHA/RECIBE   si los datos están disponibles para leer  y  envia comfirmacion
                                 // obtiene un número entero con el número de bytes (caracteres) disponibles para leer o capturar desde el puerto serie,
                                 //si el número es 0, significa que no hay datos almacenados.
                                 //El buffer puede almacenar un máximo de 64 bytes.(8 CARACTERES ASCII ???)
                                 // asyncSerial.AsyncRecieve();//aqui devuelve un array( byte data[dataLength];//  BUFER[TAMAÑO])  con los datos leidos

    //Serial.read()---The first byte of incoming serial data available (or -1 if no data is available) - int.
    //char dataIN; // Dato recibido desde el Puerto serial
    dataIN = Serial.read();            // PASAR   ??  dataIN   ??  POR REFERENCIA
   // para ser consistente con la forma en que está enviando desde Processing  myPort.write('3');
    // else if (dataIN == 3) {  // PROCESSING PIDE ajuste hora del RTC   en processing pulsa tecla & / H linea 697 
    //dataIN == '4'|| || dataIN == "4"|| dataIN == 'T'  
    //digitalWrite (BUZZER,1);
   // delay(50);
   // digitalWrite (BUZZER,0);
if (dataIN == '4' || 4) {            // PROCESSING PIDE TEST
                                         //PROCESSING ->funcion enviadataset() desde-> linea 122  en linea 324//232 Pr
                                         // avisala();
                                         //recibeFLOAT_NAIVE();   // SIN FUNCIONES Serial
                                         //leerlos y guardarlos en dataIN
/*digitalWrite(pinTCrict,HIGH);  delay(2500);  digitalWrite(pinTCrict,LOW);delay(500);
digitalWrite(pinTCrict,HIGH);  delay(2500);  digitalWrite(pinTCrict,LOW);delay(500);
//digitalWrite(pinTCrict,HIGH);  delay(2500); 
 digitalWrite(pinTCrict,LOW);
 */
       Serial.print("Estoy_recibiendo_un_4=");
        Serial.println(dataIN);
 digitalWrite(pinTCrict,HIGH); delay(250);  digitalWrite(pinTCrict,LOW);
     delay(250);  
     digitalWrite(pinTCrict,HIGH); delay(250);  digitalWrite(pinTCrict,LOW);
     delay(250);  
     digitalWrite(pinTCrict,HIGH); delay(250);  digitalWrite(pinTCrict,LOW);
     delay(250);  
     digitalWrite(pinTCrict,HIGH); delay(250);  digitalWrite(pinTCrict,LOW);
  digitalWrite (BUZZER,1);
    delay(75);
    digitalWrite (BUZZER,0);
     delay(75);
    digitalWrite (BUZZER,1);
    delay(75);
    digitalWrite (BUZZER,0);
  
     
     
     
      T1 = Serial.read();                //T1 = value; sens nro= 11 --GOAL// myPort.write((byte)(seteatempMin));// 11
      if (T1 >= 127) { T1 = T1 - 256; }  //sistema binario para representar números con signo: complemento a uno, 
      T1=11.11;
      T2 = Serial.read();                //T2 = value; sens nro= 12 --META//myPort.write((byte)(seteatempMax));// 12
      if (T2 >= 127) { T2 = T2 - 256; }  //sistema binario para representar números con signo: complemento a uno, 
        T2=22.22;
      nModo = Serial.read();             //sens nro= 13 float nModo =Serial.read(); //myPort.write((byte)(float(seteanModo)));// 13 seteanModo es INT
     nModo =3;
      //se guarda en epromm del RTC a recuperar luego del reset
      nEvento = Serial.read();  //sens nro= 14 float evento =Serial.read(); ---->>>>>revisar no llega  myPort.write((byte)(float(nEvento)));//    14 EVENTO es INT
      s3 = Serial.read();       //      sens nro= 15 float s3 = *100//myPort.write((byte)(s3*10));
      s3=1.10;
      s3=0.70;
      //s3 = s3 / 10;
      // Serial.println(s3);
      s4 = Serial.read();  //    es % rango 0 a 100  sens nro= 16 float s4 = //myPort.write((byte)(s4*100));//
      s4 = s4 ;       //revisar
      s4 = 85;             //fijo para entrega 
                           // Serial.println(s4);
      s5 = Serial.read();  //      sens nro= 17 float s5 = *100  decodifica de 0 a 255 ???//myPort.write((byte)(s5*10));
      s5 =0.14;//fijo para entrega
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
 grabaMEM();
     // avisala();  //guarda datos de variables a recuperar luego del reset
                  //devuelve lectura para control de desarrollo -->quedaran solo las cargas de las variables seteadas
  // ENVIAstatus();
     // avisala();  //ficha enviadata linea 70
                  // ENVIADATA();//---------------->>>>>>>>>>>>>>>>>>>>>prueba envio sensores

 digitalWrite(pinTCrict,LOW);
}//si recibimos un 4  DE PROCESSING
// FIN PROCESSING PIDE TEST
   
   
   
   
    if (S == HIGH || dataIN == '2'|| dataIN == 2) {  // // PROCESSING PIDE  START
      Serial.print("1- ");             //PALABRA del PAQUETE
      Serial.print("Estoy_recibiendo_un_START_2=");
      Serial.println(dataIN);  //Enviamos los datos en forma de byte
      ESTADO_S = 1;
      ESTADO_A = 0;
      digitalWrite(pinOPTOCUPLER, HIGH);
    digitalWrite (BUZZER,1);
    delay(75);
    digitalWrite (BUZZER,0);
     delay(75);
    digitalWrite (BUZZER,1);
    delay(75);
    digitalWrite (BUZZER,0);      
      
    }

  



//fijo para entrega
                /*
                    // para ser consistente con la forma en que está enviando desde Processing  myPort.write('3');
                    // else if (dataIN == 3) {  // PROCESSING PIDE ajuste hora del RTC   en processing pulsa tecla & / H linea 697
                    if (A == HIGH || dataIN == 3 || dataIN == '3'){  // PROCESSING PIDE ABORT o STOP
                      ESTADO_S = 0;
                      ESTADO_A = 1;  // FIN DE CICLO  Ó ABORT MISION------------BOTON/PIN A2-----------------ROJO
                      for (int avi = 0; avi <= 3; avi = avi + 1) { avisala(); }
                      avisala();
                      Serial.print("3- ");  //PALABRA del PAQUETE
                      Serial.print("Estoy_recibiendo_un_ABORT_3=");
                        Serial.println(dataIN);      
                      //Serial.println(dataIN);  //Enviamos los datos en forma de byte
                      digitalWrite (BUZZER,1);
                    delay(75);
                    digitalWrite (BUZZER,0);
                    delay(75);
                    digitalWrite (BUZZER,1);
                    delay(75);
                    digitalWrite (BUZZER,0);
                      digitalWrite(pinOPTOCUPLER, LOW);                   
                    }
*/




     if (dataIN == '5'  || dataIN == 5 ) {            // PROCESSING PIDE SETEAR VARIALES  DATAset
       Serial.print("Estoy_recibiendo_un_5_DATASET=");
Serial.println(dataIN);       
                                         //PROCESSING ->funcion enviadataset() desde-> linea 122  en linea 324//232 Pr
                                         // avisala();
                                         //recibeFLOAT_NAIVE();   // SIN FUNCIONES Serial
                                         //leerlos y guardarlos en dataIN
      //  digitalWrite(pinTCrict,HIGH);  delay(4500);  digitalWrite(pinTCrict,LOW);//avisala(); 

      T1 = Serial.read();                //T1 = value; sens nro= 11 --GOAL// myPort.write((byte)(seteatempMin));// 11
      if (T1 >= 127) { T1 = T1 - 256; }  //sistema binario para representar números con signo: complemento a uno, 
      //T1=11.89;
      T2 = Serial.read();                //T2 = value; sens nro= 12 --META//myPort.write((byte)(seteatempMax));// 12
      if (T2 >= 127) { T2 = T2 - 256; }  //sistema binario para representar números con signo: complemento a uno, 
        //T2=22.89;
      nModo = Serial.read();             //sens nro= 13 float nModo =Serial.read(); //myPort.write((byte)(float(seteanModo)));// 13 seteanModo es INT
      //se guarda en epromm del RTC a recuperar luego del reset
      nEvento = Serial.read();  //sens nro= 14 float evento =Serial.read(); ---->>>>>revisar no llega  myPort.write((byte)(float(nEvento)));//    14 EVENTO es INT
      s3 = Serial.read();       //      sens nro= 15 float s3 = *100//myPort.write((byte)(s3*10));
      s3=0.70;//fijo para entrega 
      //s3 = s3 / 10;
      // Serial.println(s3);
      s4 = Serial.read();  //    es % rango 0 a 100  sens nro= 16 float s4 = //myPort.write((byte)(s4*100));//
     // s4 = s4 ;       //revisar
      s4 = 85;             //fijo para entrega 
                           // Serial.println(s4);
      s5 = Serial.read();  //      sens nro= 17 float s5 = *100  decodifica de 0 a 255 ???//myPort.write((byte)(s5*10));
     
     
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
      grabaMEM();
     // avisala();  //guarda datos de variables a recuperar luego del reset
                  //devuelve lectura para control de desarrollo -->quedaran solo las cargas de las variables seteadas
      // ENVIAstatus(); 01-2024
      avisala();  //ficha enviadata linea 70
                  // ENVIADATA();//---------------->>>>>>>>>>>>>>>>>>>>>prueba envio sensores
                  digitalWrite (BUZZER,1);
    delay(75);
    digitalWrite (BUZZER,0);
     delay(75);
    digitalWrite (BUZZER,1);
    delay(75);
    digitalWrite (BUZZER,0);
    }             //si recibimos un 5  DE PROCESSING

   

         //else if (dataIN == '7') {  // PROCESSING PIDE ajuste hora del RTC   en processing pulsa tecla & / H linea 697
         // para ser consistente con la forma en que está enviando desde Processing
      if (dataIN == 7  || dataIN ==  '7') {  // PROCESSING PIDE ajuste hora del RTC   en processing pulsa tecla & / H linea 697
      avisala();
      Serial.print("Estoy_recibiendo_AJUSTE DE HORA_7=");
        Serial.println(dataIN);
      Serial.print("---------recibi 7 via puerto serial------AjustaHora-------------------");
      //  Serial.println ( Serial.read());// print as an ASCII-encoded decimal
      // Serial.println (( Serial.read() , DEC) );// print as an ASCII-encoded decimal
      // ENVIAstatus(); //ficha enviadata linea 70
      //recibir la fecha de processing y ajustar la hora con el dato recibido
      //rtc.adjust(DateTime(2021, 2, 21,8, 11, 45));  este llega bien
      if (ajuste ==1){
        ajuste=0;                 
      int ano = Serial.read();
      int mes = Serial.read();
      int dia = Serial.read();
      int hora = Serial.read();
      int minut = Serial.read();
      int seg = Serial.read();
                  if (hora<23){//evita error de lectura
                              rtc.adjust(DateTime(ano, mes, dia, hora, minut, seg));
                                                digitalWrite(BUZZER, 1);
                                                    delay(75);
                                                    digitalWrite(BUZZER, 0);
                                                    delay(75);
                                                digitalWrite(BUZZER, 1);
                                                    delay(75);
                                                    digitalWrite(BUZZER, 0);
                                        }
      //Serial.print("6-enviaSTATUS ");//
      //01-2024   ENVIAstatus();  // ENVIAstatus(); //ficha enviadata linea 70  // Serial.print(now.hour(), DEC);//sens nro= 18 // hora
                      // ENVIAstatus(); //ficha enviadata linea 70  // Serial.print(now.minute(), DEC);//sens nro= 19 // minuto de 0 a 59
                      // ENVIAstatus(); //ficha enviadata linea 70  // Serial.print(now.hour(), DEC);//sens nro= 20 // seg
                      // ENVIAstatus(); //ficha enviadata linea 70  // Serial.print(now.hour(), DEC);//sens nro= 21 //  mes
                      }
    } //si recibimos un 7  DE PROCESSING

     if (dataIN == '9'|| dataIN == 9) {  // PROCESSING PIDE UN RESET                        _resetXsoftCall.pde
      digitalWrite(pinTCrict,HIGH);  delay(4500);  digitalWrite(pinTCrict,LOW);
                               //envia comfirmacion A PROCESING
      Serial.print("9- ");     //PALABRA del PAQUETE
      Serial.print("Estoy_recibiendo_un_RESETEO_9=");
          Serial.println(dataIN);  //Enviamos los datos en forma de byte
                               // accion-->  "HAGO UN RESET DEL ARDUINO"con la rutina    -->   resetFunc();
                               //  resetFunc();//RESET por direccion CERO del ARDUINO
                               // void(* resetFunc) (void) = 0; //declare reset function @ address 0   enviado por referencia de C++
      grabaMEM();              //guarda datos de variables a recuperar luego del reset
      avisala();
                        digitalWrite(BUZZER, 1);
                            delay(75);
                            digitalWrite(BUZZER, 0);
                            delay(75);
                        digitalWrite(BUZZER, 1);
                            delay(75);
                            digitalWrite(BUZZER, 0);
      digitalWrite(pinOPTOCUPLER, LOW);
      digitalWrite(pinCirca, LOW);
      digitalWrite(pinTCrict, LOW);
      digitalWrite(pinAlone, LOW);
      software_Reboot();
    }  //si recibimos un 9  DE PROCESSING



  }  //cierre ESCUCHA/RECIBE  y  envia comfirmacion

  //EstadosyBotones();//evalua FLAGs---------y--------evalua estado
  rutMODO();  //entrega Tinstant para parametrizar el termostato  --con Tinstant -----
  //Serial.print("6-enviaSTATUS ");//
  //              ENVIAstatus();
  pseudoPID_log();
  TERMOSTAT(Tinstant, tempActual, Tmargen);  //-- SOAK T1-- LLEVA LA PLACA A T1
  //boolean test=true; PARA DESARROLLO MONITOREADO



  //if ((now.hour()-horaAnt) == 1){// reset por wdt cada N horas para prevenir bloqueos y overflow/saturacion
  Serial.print("reset en: ");
  Serial.println(now.minute() - minutAnt);
  wdt_disable();                         //siempre es bueno deshabilitarlo al comienzo
  if ((now.minute() - minutAnt) == 15) {  //auto reset
                                         /*  instance-method hour
                                                                          @return Hour (0--23).  uint8_t  entero sin signo de 8 bits. 
                                                                          // In DateTime
                                                                          public: uint8_t hour() const
                                                                          uint8_t  entero sin signo de 8 bits. 
                                                                          uint_fast8_t es el int sin signo más rápido con al menos 8 bits. 
                                                                          uint_least8_t int sin fsigno con al menos 8 bits.
                                                                          */
                                         //horaAnt=now.hour();	// se define en el setup cada vez que reinicia


    //Serial.println(F("nModo INT ;t1  FLOAT;hot_cool  INT ;t2  FLOAT; time stamp"));
    grabaMEM();  //  guarda los datos de seteo en la EEPROM del RTC
                 //alcanza tiempo para grabar antes del reset  ???
                 software_Reboot();// reset por wdt cada N horas para prevenir bloqueos y overflow/saturacion
  }
  ENVIAstatus();
  test = false;
  monitoreo();  //boolean test=true; PARA DESARROLLO MONITOREADO consola arduino solo
}  // FIN LOOP