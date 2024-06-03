#include <Wire.h>


/*CONTROLADOR_TERMICO_CIRCADIANO_ENCODER_OLED                        19-03-2023
  CONTROLADOR_TERMICO_Oled_FotopAJUSTESmenu05_sinSerialPrint_2023

diseño y programacion EDUARDO KREIMAN
consultas y asesorias 054-011-5472-5201
ekreiman@gmail.com

IMPORTANTE: CARGAR TODAS LAS LIBRERIAS ANTES DE SUBIR EL SKETCH A LA PLACA

LA RUTINA: Parametror();//AJUSTESySETEOS(); CONTROLA LOS PARAMETROS INICIALES
LA LINEA 420 INICIALIZA EL RTC 
-------------------------------------------------------------------------------------------------------

oled.setFont(System5x7);
*/

/*
 pasta térmica 
 Un exceso de pasta térmica empeorará el rendimiento térmico del sistema. 
 Lo ideal «menos es más» es una capa de pasta térmica casi transparente.

 TempCamara Ti= 18.20ºC   Tcal 17.02ºC   DELTA Goal/Camara 1.17ºC    Tmin set 16.10ºC     TempAire exterior= 22.25ºC SaltoTº Int/Ext= -4.05ºC 
 
fuente 11.03v out pwm255 10.45v    Serial.voltimetro=4.86v / 5.36v

127 08---> 10v45  4.71 A

127 05--->fuente 11.03v 10v45  2.71 A ----FUXIN  TEC1-127 05fx  dbc 2013/10--https://www.airecontrol.com.ar/tec1---12705fx.html--
          
          fuente 11.03v  6v77  1.97 A r=27ohms   out pwm255   Serial.voltimetro=4.77v    24-04-2023

cambio peltier 14-04-2023 camara frigobar gris

REPOSITORIO:    Eduarq NUBE  e01kreiman@gmail.com
https://docs.google.com/document/d/1vcTVYxaLnhMcUdjbMWwd1TrjF9DZqiPkKovk91h1lXA/edit?usp=share_link

Compartir "ControladoraTérmica"    https://drive.google.com/drive/folders/1YoPP9A5MYGMUdpDPp951JbSK1InDlZAB?usp=share_link

/*
/********************************************************************/

#include "DS18B20Events.h"
#define ONE_WIRE_BUS 12
// Setup a oneWire instance to communicate with any OneWire devices(not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature dallasTemperature(&oneWire);// Init DallasTemperature

DS18B20Events thermometer(0);//Init thermometer with index 0 (default)

#include "SSD1306Ascii.h"
#include "SSD1306AsciiAvrI2c.h"

// 0X3C+SA0 - 0x3C or 0x3D
#define I2C_ADDRESS 0x3C

#define RST_PIN -1 // Define proper RST_PIN if required.

SSD1306AsciiAvrI2c oled;  //DISPLAY MONOCROMATICO 128 X 64 PIXELS

float volatile Tactual = -12.34;
//-----------------------------------------------

bool test = false;  //boolean test=true; PARA DESARROLLO MONITOREADO se habilita en PARAMETROR
bool test01 = false;  //boolean test=true; PARA DESARROLLO MONITOREADO de modos se habilita en PARAMETROR

#include <AT24CX.h>  //BIB  memoriA eeprom en modulo RTC DS3231
AT24C32 EepromRTC;   //Declarar EepromRTC  clase con tamaño de página predefinido

//MODELO DE datos a guadar en EepromRTC
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
char cadenaTiempo;
//char cadena2[30];
//char cadena[30] = "time= hh:mm:ss";
//datos a guadar en EepromRTC
float  MTimeStart;
bool MpasoSoak;
float HcRTC = 0.123456789;// fotoperiodo 
float hcOn  = 0.123456789;// fotoperiodo   
float hcOff = 0.123456789;//fotoperiodo 
float XhcOn = 0.123456;//    fotoperiodo 
float hhSX  = 0.123456789;// fotoperiodo 

const int Sw3 = A1;  // BOTON SwB
const int Sw2 = A2;  // BOTON SwA

//sensors.getTempC(DeviceAddress);// //-> Sensor 3 : 0x28, 0x1A, 0x37, 0x76, 0xE0, 0x01, 0x3C, 0xE0 // -------->ETIQUETA negra termocontraible

#include "EasyBuzzer.h"
const int BUZZER = A0;  //buzzer  con led azul en paralelo usa pasivo con trNPN buffer rutina de tono 450Hz  libreria easyBuzzer
unsigned int frequency = 400;
unsigned int onDuration = 500;
unsigned int offDuration = 500;
unsigned int beeps = 5;
unsigned int pauseDuration = 500;
unsigned int cycles = 10;


// protocolo de comunicacion I2C Arduino UNO, NANO reserva por default -> SDA = A4 y SCL = A5 NANO
//#define SCL 5  protocolo de comunicacion I2C   The compiler will replace any mention of scl with the value 5 at compile time.
//#define SDA 4  protocolo de comunicacion I2C   The compiler will replace any mention of scl with the value 4 at compile time.

#include <Encoder.h>
// Change these two numbers to the pins connected to your encoder.
//   avoid using pins with LEDs attached
//   Best Performance: both pins have interrupt capability
//   Good Performance: only the first pin has interrupt capability
//   Low Performance:  neither pin has interrupt capability
//NANO  PIN con habilidad de INTERRUPT= D3 y D2
//              DT, CLK
// clase   objeto
   Encoder myEnc(3,2);// PINES DIGITALES CON INTERRUPCION INVIERTE EL ORDEN INVIERTE SENTIDO DE lectura del GIRO
//int contador = 0;
long oldPosition = -999;
#define boton 4  // BOTON DEL Encoder ROTATIVO
#define pinFOTOPERIODO 11

#include <RTClib.h>  // ---paraRTC real clock time    https://adafruit.github.io/RTClib/html/class_r_t_c___d_s3231.html
//   clase objeto
RTC_DS3231 rtc;      // Declaramos un RTC DS3231
//#include <DS3231.h>// libreria de arduino parece mas liviana   https://www.arduino.cc/reference/en/libraries/ds3231/
//                                                               https://github.com/NorthernWidget/DS3231
//The Library assumes that the DS3231 has an I2C address of 0x68.
// is a splice of Ayars' (http://hacks.ayars.org/2011/04/ds3231-real-time-clock.html) and Jeelabs/Ladyada's

//#include <MemoryFree.h>//usada solo en desarrollo del soft

#include <avr/wdt.h>  //watch-dog-Timer, esta librería  dispara una interrupcion que llama una funcion  cuando se acaba el tiempo
//***************************************************** DESCOMENTAR para activar AUTO-RESET
//                  void(* resetFunc) (void) = 0; //declare reset function @ address 0   enviado por referencia de C++
//***************************************************** DESCOMENTAR  para activar AUTO-RESET
/*para restablecer la placa, se implementa un ciclo corto,(15 milisegundos) 	WDTO_15MS				
                                      cuando el tiempo de espera expira, el sistema se reinicia									
                                      al llamar a la funcion      software_Reboot     reiniciando la placa a los 15 ms.
                                      Processing recupera la coneccion luego del reset

                                        void software_Reboot()				
                                          {			
                                            wdt_enable(WDTO_15MS);        //watchdogTIMER  buenisimo Timer por INTERRUPCION
                                                                          //usarlo para time en soak o para tiempo entre de lecturas	
                                              while(1)		
                                              {		
                                              }		
                                          }			
                                      */



/*
PUENTE H 
DRIVER MONSTER :--- VNH2SP30 full-bridge motor driver
MonsterMotor uses two VNH2SP30 high-current full-bridge motor drivers.

The motor variable in each function should be either a 0 or a 1.
pwm in the motorGo function should be a value between 0 and 255.

5  pwm in the motorGo function should be a value between 0 and 255.
7  variable in each   function should be either a 0 or a 1.
8  variable in each   function should be either a 0 or a 1.
*/

#define BRAKEVCC 0
#define CW 1
#define CCW 2
#define BRAKEGND 3
#define CS_THRESHOLD 100
/*  
motor A
Pines 5 y 6 son PWM.
Pines 4 y 9 controlan el giro del primer motor.

motor B
Pines 5 y 6 son PWM.
Pines 7 y 8 controlan el giro del segundo motor.

para cada chip
            6 ENA/DIAGA Status of high side and low side switches A; open drain output
5 INA Clockwise input
8 PWM PWM input
          9 CS Output of current sense
11 INB Counter clockwise input
          10 ENB/DIAGB Status of high side and low side switches B; open drain output

tabla de Verdad

INA  INB  1/2puente-A    1/2puente-B     MODO 
1     1        H             H           freno en  alta
      0                      L           giro horario

0     1        L             H           giro ant-horario
      0                      L           freno en  baja GND


MONSTER MOTO de Sparkfun. 
https://github.com/sparkfun/Monster_Moto_Shield/tree/Hv12Fv10
Voltaje máximo: 16V
Corriente pico máxima: 30 A
      con hasta 6A, los chips apenas se calentarán perceptiblemente.
Corriente Continua Práctica: 14 A
Detección de corriente disponible para pin analógico Arduino
resistencia MOSFET: 19 mΩ (por pierna)
Frecuencia máxima PWM: 20 kHz
Apagado térmico
Apagado por subtensión y sobretensión

VNH2SP30 pin definitions
 xxx[0] controls '1' outputs
 xxx[1] controls '2' outputs 
 */
//define array para 2 puentes H
int inApin[2] = { 7, 4 };  //  INA: Clockwise input          sentido horario      FRIO
int inBpin[2] = { 8, 9 };  //  INB: Counter-clockwise input  sentido anti-horario CALOR
int pwmpin[2] = { 5, 6 };  //  PWM input

//estos pines no estaran conectados
int cspin[2] = { 2, 3 };  //    CS: Current sense ANALOG input
int enpin[2] = { 0, 1 };  //    EN: Status of switches output (Analog pin)

//int statpin = 13;// led onboard

const int pinOPTOCUPLER = 9;  // Led OPTOCUPLER cable verde de fuente
const int pinPOTE = A3;       // pote  usar pin analog read MONITOREAR TENSION PUENTE H
int horaAnt = 0;              //hora de inicio del setup para resetear por software cada N horas
int minutAnt = 0;             //hora de inicio del setup para resetear por software cada N horas

unsigned long volatile tiempoLectura = 0;   // Tiempo en que se presionó el botón
unsigned long volatile duracionLectura = 0; // D

//boolean LEDState = LOW;       //APAGA el LED
//boolean status = LOW;         //Estado del led
//char dataIN;                  // Data recibida desde el Puerto serial
//char val; // Data recibida desde el Puerto serial
String ENTROPIA = "EstadoBombaTermica";  //"COOLING"

float tempActual = 0.1;
int temp;  // Variable sensor de temperatura
//float RawValue = 0.1;
//float value;
float T1 = 0.01;      //tempArranque -GOAL->  temp de inicio         --carga inicial para desarrollo   
float T2 = 0.01;      // tempSET -META->  temp a llegar en rampa ---carga inicial para desarrollo
float Tmargen = 0.01;  //histeresis de termostato, Tmargen  pseudo PID viene de slider s5
int PwFrio = 0;
int PwHot = 0;

//float deltaTemp = 0.1;      // instantanea para display
float tempAMBIENT = 0;      //rtc
float tempAMBanterior = 0;  //rtc
float tempAnt = 0;          //almacenar la temperatura en una variable  del tipo float.
//float tempDisAnt = 0;
float tempTT = 0;  //variable local en rutina TERMOSTATO

//int nEvent = 0;         // contador de eventos
//int nLectu;             // contador de LECTURAS DE TEMPERATURA
bool LLegueT1 = false;  //   Flag DE CONTROL DEL TERMOSTATO

 
int nModo = 0; 

//char buf1[20];  //character array to save the output string into.
float s3 = 0;  //pid 
float s4 = 0;    //pid  valor %  rango 0 a 100
//float s5 = 0.15;  //pid Tmargen  multiplicar y dividir por 100 para recibir decimales
//float volatile Tinstant = 0;
float  Tinstant = 0;
//float sgCorrida = 0;

float Avance=0;
float TimeStart=0;
//unsigned long miliAhora = 0;
//unsigned long miliStart = 0;
bool pasoSoak=true; 
//unsigned long miliSoak = 0;
//unsigned long miliAvance = 0;
//4 minutos centesimales= 0.066666666; pendiente=  1/0.066666666= 15
float mRecta =0;   //0.000004167;   //0.25 / 60;    unidad second()  pendiente de la recta  m=1 grado cada 4 minutos

// second() 0 a 59 if second < 1 sumar 59 a la variable

int x = 0;
float incrementa=0.00;
float incrementador=0.1;
//Prototipos de las funciones para definirles el alcance *********************************
void TERMOSTAT(float _T1, float _T2, float _margen);  //Prototipo
void ENVIADATA();
void ENVIAstatus();
void pseudoPID_log();
void done();
//void enviaOLED();
void avisala();
void grabaMEM();  // guarda datos en memRTC
void leeMEM();    // lectura y presentacion y recupera datos en variables
void Voltimetro();

void motorGo(uint8_t motor, uint8_t direct, uint8_t pwm);

void leeStepper(int _Fila,int _Columna);
void leeStepper(int _Fila,int _Columna,int _S,bool _I);  //     0 a 7  , 0 a 239, 1 ó 2,  0 ó  1
void Parametror();//AJUSTESySETEOS();
void Aceptor();

void displayOLED(); //0  hoja principal default muestra estado y temp actual

void menuSeteador();//1

void menuModo();    //2 
             void rutMODO();       //rutinasMODO
             void Lineal();        //rutinasMODO
             void R_circadiano();  //rutinasMODO
             void LinealCTE();     //rutinasMODO
               //void R_TCritica();//rutinasMODO
               //void R_termos();  //rutinasMODO 

void menuTEMP();    //3  T1 Y T2

void menuFOTO();    //4  SUNSET Y SUNRISE

void fotoperiodo();// REGULA ILUMINACION DENTRO DE LA CAMARA  

void blinkFOTOPERIODO();//AVISO con luz INTERMITENTE EN CAMARA

//void software_Reboot();  // esta funcion se llama cada N horas  para evitar bloqueos. EN nano NO FUNCIONA SOLO SI SE CAMBIA EL BOOTLOADER CON UNO
void autoReset(); //Dado que la prueba de rampa tiene una duracion maxima de 90 /120 minutos se deshabilita para esta funcion el autoreset /o se lo setea en 120 minutos
void temperatureChanged(uint8_t index, float tempC);
float obtenerHoraCentesimal();
//Prototipos de las funciones para definirles el alcance *********************************



                    // https://www.electrodaddy.com/las-matematicas-en-arduino/
float hs = 0;  // uso en circadiano hora reloj format centecimal
float T_calActual = 0;
//float TempDisip = 0;
float incremento = 0;
float Suma = 0;
float SumaDisip = 0;
float aManecer = 8.00;    // hs= Srise  centecimal  dato
float aNochecer = 20.00;  // hs =S set  centecimal  dato
const float b = 0.8;      //=coef ajuste NOCHE
const float a = 1.5;      //=coef ajuste DIA
float tempMin = 16.00;    //activa Slider s1 // modo tropical VZ
float tempMax = 32.00;    //activa Slider s2 // modo tropical VZ
float deltaT = 0;
float T_aNoche = 0;
//----------
float m = 46.3;  //ecuacion de la recta
int b0 = 68;     //ecuacion de la recta
float delta;
float tension = 0;             // voltimetro
float adjSensor = 0;  //COEF DE CALIBRACION DEL SENSOR   tempActual linea 483  
int ajuste = 1;                // Bloquea solo 1 ajuste de hora por corrida para solicitar otro requiere pasar por reset que es automatico cada 15 minutos
float ajustambiental = -3.25;  // corretor de desvio del sensor de temperatura tempAMBIENT
int rstMin = 49;         // tiempo en minutos para disparar auto reset
int reinicio = 15;
int Mreinicio = 1;

int newPosition = 0;
float PosiDec =0.01; 
float oldtempActual = -0.01;

bool paso = false;
bool Seteador = false;
bool setFoto= false;//4
bool setTEMP= false;//3
bool setMODO=true;  //2
bool Bot = false;
bool acepta=true;

int LASTposition=0;
bool Decimal= false;
int contador = 0;
bool miniMenu=true;//circular entre T1 y T2
int tomas=5000;// Set min interval in milliseconds between 2 measurements. Default 10000 set in setup() method.

void setup() {  //oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
  //Serial.begin(19200);
  //asyncTask1.Start(); //avisala(); //conflicto con encoder ????
  //asyncTask2.Start();                         
                        
  DS18B20Events::setup(&dallasTemperature);  // Link DS18B20Events to DallasTemperature object  USA PASO DE VALORES POR REFERENCIA  ::  ?????
  DS18B20Events::setInterval(tomas);          // Set min interval in milliseconds between 2 measurements. Default 10000 set in setup() method.

  thermometer.onChange = temperatureChanged; // subscribe to temperature changed event

  oled.begin(&Adafruit128x64, I2C_ADDRESS);
  // Call oled.setI2cClock(frequency) to change from the default frequency.

  oled.setFont(Adafruit5x7);
  oled.clear();
 
  uint32_t m = micros();
  wdt_disable();  //siempre es bueno deshabilitarlo al comienzo
 // Serial.println(F("apago WDT"));

  // PULSADORES SELECTORES
  pinMode(Sw3, INPUT);           // pin ardu A1   pull down con resistencia 1K5 y FILTRO 100NF en PCB
  pinMode(Sw2, INPUT);           // pin ardu A2   pull down con resistencia 1K5 y FILTRO 100NF en PCB
  pinMode(boton, INPUT_PULLUP);  // pin del pulsador del Stepper rotatvo siempre UP
  pinMode(pinOPTOCUPLER, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(pinFOTOPERIODO, OUTPUT);
  
  //----------- Modulo RTC
 // Serial.println("modulo_RTC");
  if (!rtc.begin()) {  //--------------verifica el RTC conectado
  //  Serial.println("No_hay_modulo_RTC");
    while (1);  //espera un microsegundo
  }//--------------verifica el RTC conectado
      
          // Poner en hora solo la primera vez,con los valores de la fecha y la hora en que el sketch ha sido COMPILADO
        //  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));// Fijar a fecha y hora de COMPILACION el sketch // luego comentar y volver a cargar.
        //  reporte de error: no usar  este ajuste automatico
        //    https://enioea2hw.wordpress.com/2020/04/09/reloj-dual-con-rct3231-y-arduino/#more-4372
//----------- Modulo RTC

  DateTime now = rtc.now();  //toma datos del modulo RTC

  horaAnt = now.hour();     //hora de inicio del setup y control de reset cada N horas
  minutAnt = now.minute();  //minuto de inicio del setup y control de reset cada N minutos                        
                             //memoria EEPROM EN Mmodulo RTC  068 para EL RELOJ Y 057 para LA MEMORIA
  /*ASIGNA LA DIrECCION DEL MODULO ademas por Hard soldando A1 A2 A3  A GND=0   EN EL MODULO 0x+0x2+0x3 --> 0x1 +0x2 + 0x4	=0
                                                                     A VCC=1   EN EL MODULO x+x2+x3 -------> 1 + 2  +	 4	=7                            
   AT24C32(0x57);  //ASIGNA LA DIRECCION DEL MODULO de memoria EEPROM por soft
  // Search at [57]: FOUND!  con sketch     AT24CX_search_ICmem.ino
  */
Parametror();//AJUSTESySETEOS();// reemplaza a leeMeM en desarollo o seteo fijo

leeMEM();  // lectura y presentacion y recupera datos en variables

EasyBuzzer.setPin(14);

digitalWrite(pinOPTOCUPLER, HIGH);  // D 09  conecta fuente de poder +5v y +12v
avisala();//el tiempo de esta funcion reemplaza delay
blinkFOTOPERIODO();

  //Serial.print(F("FIN DEL SETUP--------------------------------------------------------------"));
 }  //oooooooooooooooooo FIN  SETUP oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo





void loop() {
  tempAMBIENT = rtc.getTemperature();          // LEER TEMPERATURA DEL modulo RTC  DEVUELVE   Current temperature (float)

  tempAMBIENT = tempAMBIENT + ajustambiental;  // corrector de desvio del sensor de temperatura del moduloRTC
  
  thermometer.loop();                   // Mandatory to measure temperature and fire an event if needed
  
 tempActual = thermometer.getTempC();  // Get last measured tempC if needed.
 tempActual = tempActual + adjSensor; // corrector de desvio del sensor de temperatura DS18b20
            if (tempActual != oldtempActual) {
              oled.clear();
              oldtempActual = tempActual;
            }


//asyncTask1.Update(asyncTask2);//necesario llamar frecuentemente al método Update() funcion definida antes del setup
//asyncTask2.Update(asyncTask1);//coflicto ???


EasyBuzzer.update();  //Always call this function in the loop for EasyBuzzer to work. 

//Dado que la prueba de rampa tiene una duracion maxima de 90 /120 minutos se deshabilita para esta funcion el autoreset /o se lo setea en 120 minutos
if (nModo!=2){autoReset();	}//void software_Reboot()	{	// esta funcion resetea el arduino y se llama cada 2 horas  para evitar bloqueos.	
//Dado que la prueba de rampa tiene una duracion maxima de 90 /120 minutos se deshabilita para esta funcion el autoreset /o se lo setea en 120 minutos

Aceptor();// lee el pulsador del rotor (swC=OK) , cambia las variables  Bot (togle)  y acepta=true; 
          // Bot = digitalRead(boton);// si se pulsa  su valor va a BAJO == false 

displayOLED();// hoja default muestra estado y temp actual  muestra siempre             

fotoperiodo();//controla luz led en camara


//  SwA=Sw2  llama a menuSeteador que entra en un while y se CONTROLA con la variable bool Seteador--> si Seteado r== true entra en un while 
//               menuSeteador llamará las rutinas: 1progs/modos  2temp  3foto  NNno opcion    
if (digitalRead(Sw2) == HIGH) {  Seteador = !Seteador; avisala(); }// ---------->>>> entra y sale del  menuSeteador  ><<<<<<<<<<<---------   

// ooooooooooooooooooooooooo ooooooooooo  while de seteador
paso = false;// evita parpadeo de sobreimpresion del display
while (Seteador == true)  
                {   motorGo(0, 2, 0);//quita energia en puente H mientras setea
                   // atencion aqui    autoReset();//actualizado dentro del while 
   
                    if (digitalRead(Sw2) == HIGH) { Seteador = !Seteador; }// ---------->>>> entra y sale del seteador  con SwA><<<<<<<<<<<---------

                               leeMEM();

                    Aceptor();//lee el pulsador del rotor (swC=OK) , cambia la variable  Bot (togle)  y acepta=true;   
                    menuSeteador(); //----- void menuSeteador(){// 1-                      
  }  // oooooooooooooooooooooooooooooooooo cierra while de seteador

rutMODO();  //   llama a la funcion termica corespondiente para obtener      Tinstant para parametrizar LA FUNCION  termostato
pseudoPID_log();  // ajuste  PWM pseudoPID evalua delta(local) y setea PwHot y PwFrio
TERMOSTAT(Tinstant, tempActual, Tmargen);  // LLEVA LA PLACA A T1  Tinstant
//Serial.print(F("MemoryFree()= "));  Serial.println(freeMemory());
}

