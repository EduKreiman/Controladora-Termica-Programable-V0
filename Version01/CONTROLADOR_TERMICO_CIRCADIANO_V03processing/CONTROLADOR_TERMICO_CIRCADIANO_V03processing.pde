//temperatura_LADOarduinoNNN.INO
//temperaturaLADOprocessingNNNTexto.PDE------------------------------------------------------
//  https://arduino123.blogspot.com/p/lm35-de-t.html
//  CÓDIGO GUI CON PROCESSING
//  GRAFICA DATOS TEMP Y HUMEDAD:  http://www.practicasconarduino.com/manualrapido/representacin_grfica_de_medidas_con_processing.html
//  GRAFICA DATOS TEMP Y HUMEDAD _en_la_nube http://www.practicasconarduino.com/manualrapido/visualizacin_de_datos_en_la_nube_internet_de_las_cosas.html

/*
 // Graphing sketch
 This program takes ASCII-encoded strings from the serial port at 9600 baud
 and graphs them.
 It expects values in the range 0 to 1023,
 followed by a newline,
 or newline and carriage return
 */


//---------------------------------------------------
boolean test=false;// flag para desarrollo habilita impresion en consola de variables y estados
//---------------------------------------------------
import processing.serial.*;
Serial myPort;       // Crea Objecto de la Serial class
PrintWriter output;  //  Crear el archivo de texto donde guardar los datos


import controlP5.*;//by Andreas Schlegel, 2012
//https://sojamo.de/libraries/controlP5/reference/index.html
import java.util.*;//PARA ControlP5_ScrollableList

ControlP5 cp5;       // Crea Objecto de ControlP5 class
//  Chart myChart;//desetimado
Textarea myTextarea;//CAMBIADO POR TEXTVALUE-->
String Texto_EVENTO = "CARPE DIEM";
String textValue = "";//EEEEEEEEEEEEEEEEEEEEEEEEEEEEEE
int xPos = 1;         // posicion horizontal en el grafico
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
float bgcolor;      // Background color
float fgcolor;      // Fill color
float xpos, ypos;   // Starting position of the ball
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

float inByte = 0;// se carga con la llamada de la funcion serialEvent
float inByteRaw=22;
float tempMin = 25.123;
float tempMax = 32.003;
float tempsensor=0.01;//del bulbo de peltier
float TempDisip=0;//del bulbo de Disipador evalua salto termico sistema
float tamb = 15.22;
String inString=" ";
String inRtc=" ";
float h ;//      dht.readHumidity();//----------- para sensor Ambiental DTH022
float t ;//      dht.readTemperature();//----------- para sensor Ambiental DTH022

String horaINI= (hour( )+":"+minute( )+":"+second( ));

/*sprintf(buf1, "%02d:%02d:%02d %02d/%02d/%02d",  now.hour(), now.minute(), now.second(), now.day(), now.month(), now.year()); //DEL RTC DE ARDUINO
no existe en processing ---> usar:
usar en processing la funcion de formateo nfs(float.entero . decimal); 
                                // f = -9.012;
                                //  String sf = nfs(s5, 2, 3); 
                                //println(sf);  // Prints "-009.01200" 
*/


int horaINInum=(hour( )*60*60+60*minute( )+second( ));             // LUEGO VENDRA DEL RTC DE ARDUINO
//horaINInum=   tomar la hora del start
int  segCorrida=int(horaINI);
String RTChoraActual; //entra via serial
int proceso_nro=887;
String Operador="Dr Lucas Kreiman";
String RTCfecha;
int horaActual;
int n=0;//nro de evento
int  nModo= 0;

boolean overRect = false;//  Estado del mouse si está encima de rect o no
boolean status=false; //     Estado del color de rect
String texto="LED OFF";//    Texto del status inicial del LED

String dataIN;
//String val;

boolean yaSeteado=false;       //control de funcion dataset
float seteatempMin;//dataset
float seteatempMax;//dataset
int seteanModo;//dataset


//Para saber si hemos hecho contacto con el microcontrolador haciendo un handshake
boolean firstContact = true;//CUANDO INICIA SOY EL PRIMER CONTACTO

// identifica PAQUETE compuesto de PALABRAS RECIBIDO-------COMPARANDO CON CONSTANTES   -> mostraN <-- ---------------
/*     Nuestra función setup() actúa de la misma forma que usamos para escribir en serial,
 a excepción de que agregamos la línea myPort.buferuntil (´n´n);
 Esta línea nos deja guardar los datos de entrada en un buffer hasta que encontremos el carácter en específico que estamos buscando,
 en este caso un retorno de carrera (\n).
 Ya que lo que enviamos desde Arduino,
 sabemos que utilizamos la forma Serial.println, el´ln´ al final
 significa que el string está terminado con un retorno de carrera
 así que sabemos que esa será la última cosa que vamos a ver
 */
//para comparar con lo recibido desde arduino que le agrega un espacio al final como SEPARADOR

//String mostra="2-tempActual:";// paquete temperatura sensor recibido desde arduino
String mostra=             "2-";// paquete temperatura sensor recibido desde arduino con un espacio al final como SEPARADOR

//String mostra0="1-desdeArduinoEnvioDATOS-->hola_mundo:";// paquete STRING del HOLAmundo
String mostra0=            "1-";// paquete STRING del HOLAmundo

String mostra1=  "3-HoraFecha=";// paquete STRING del RTC desde arduino

String mostra2=    "4-rtcTemp=";// paquete STRING del RTC desde arduino

//String mostra3="5-RESPONDE_DATASET:"; // respuesta desde arduino con un espacio al final como SEPARADOR
String mostra3="5-"; // respuesta desde arduino con un espacio al final como SEPARADOR

//String mostra4="6-DTHambiental";// paquete STRING del DTH desde arduino     Serial.print("6-DTHambiental ");//ENCABEZADO
String mostra4="6-enviaSTATUS";// paquete enviaSTATUS desde arduino

int nEvento=0;//nro de evento


int segIni=0;
//variables de contoles P5
int s1 = 25;//temp1
int s2 = 38;//temp2
float s3 =2.00;// DELTA T max  rango de accion        pseudo pid log
float s4 = 38;//PORCENTAJE DE eficiencia=( hot/cool)  SE ENVIA  MULT POR 100pseudo pid log
float s5 = 0.335;//HISTERIESIS  margen                SE ENVIA  MULT POR 100            pseudo pid log
/*
 int nb1 = 50;
 int nb2 = 50;
 
 int k1 = 50;
 int k2 = 50;
 
 boolean t1 = false;
 boolean t2 = false;
 */

int myColor = color(125);
int c1, c2;
float n0, n1;
// LINECHART
int tor  = 10;
int gain = 10;
int store = 0;
/*
                                      //https://antiepoke.wordpress.com/2013/04/05/puerto-serie-en-processing/
 //** ###################################################################
 // variables globales DE GRAFIKA
 char[] datosc=new char[13];          // Array de almacen de trama recibida en el puerto serie
 int[] datos2=new int[17];            // Array de datos ajustados para guardar en archivo
 int[][] pantalla=new int[700][2];    // Array para la visualización de datos en pantalla (ORIGINALES)
 int[][] pantalla1=new int[700][2];   // Array para la visualización de datos en pantalla (MODIFICADOS A LA ESCALA)
 
 int muestras;                        // Indica la ubicación donde se almacenará la muestra actual en el array pantalla1
 int velmuestras= 1;                  // Indica el periodo de muestreo en ms
 //char inByte;                         // Almacena el byte recibido del puerto serie
 int m;                               // Almacena el tiempo actual del programa
 int index=0;                         // Index del array de datos de entrada del puerto
 String tipocaptura="Iniciar Captura";// Mensaje de button1
 boolean ktr_traza=false;             // Control de Inicio-fin de trama del puerto
 boolean ktr_captura=false;           // Control de captura de datos del puerto
 boolean ktr_incio=false;             // Control del inicio de captura de datos
 */


// Constantes globales
//int largew=660;                      // Largo de la ventana de la gráfica
/*
                                      int button1x=275;                    // Posición x del botón de inicio-fin
 int button1y=309;                    // Posición y del botón de inicio-fin
 int button1width=150;                 // Ancho del botón de inicio-fin
 int button1high=27;                  // Alto del botón de inicio-fin
 */

/*
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
 //para ------------  ---------   ArduDroid
 */

//ControlP5_imputData

//polinomio circadiano--->  y = -0,000002x6 + 0,000263x5 - 0,010378x4 + 0,165335x3 - 0,993461x2 + 1,795195x + 4,399244   -->R² = 0,991943
//                          y = -0,0000021414x6 + 0,0002635128x5 - 0,0103796399x4 + 0,1653098494x3 - 0,9931090066x2 + 1,7940130544x + 4,4000087873
String COEF_X0 = "4.4000087873";
String COEF_X1 = "1.7940130544";
String COEF_X2 = " -0.9931090066";
String COEF_X3 = "0.1653098494";
String COEF_X4 = "-0.0103796399";
String COEF_X5 = "0.0002635128";
String COEF_X6 = "-0.0000021414";
//polinomio circadiano--->  y = -0,000002x6 + 0,000263x5 - 0,010378x4 + 0,165335x3 - 0,993461x2 + 1,795195x + 4,399244   -->R² = 0,991943

String COEFtodo = "0.01";
//int s1 = -10;
String TEMP1="25";
String t1;
//Textarea myTextarea;//
String entracaja="";
//ControlP5_imputData   void imputData(){



//   ---------------curva circadiana MODELO PARTON&LOGAN
float T_instAnterior=4.000;//  excel t = 4ºC   4.251ºC//4.278084 ºC  8.10hs
//  float i=0.1;//avance de tiempo de calculo en minutos centecimales
//"i" se usa en el loop for para hacer el barrido de 24hs
//float hs =map(i,0,width,0,24);//calcula la hora reemplazar por RTC o clocK de sistema   --en horas centecimales--

float hsC= float(hour())+float(minute())/60+float(second())/3600;
float hs=8.10;//HORA ACTUAL
float  deltaT =tempMax - tempMin;//amplitud termica de la fecha/ DEL SETEO

boolean dia = true;
float T_calActual ; // valor a calcular para cada instante
float incremental=0.050; // hs  centecimal  dato
//incremento=suma de incremental con un maximo de 12 //considera el fotoperiodo de 12hs ???
float incremento;
float aManecer =  7.55;// hs= Srise  centecimal  dato
float aNochecer= 20.00;// hs =Sset  centecimal  dato
float  T_aNoche=15.03;// TEMP DEL INSTANTE DEL ANOCHECER a partir de aqui tiene que comenzar a descender la Temperatura
float Hs_Tmax = 17.50;// hora de la Temperatura maxima (nunca en la noche)
// temp Max para VZ tropical =32°C a las 17h50
//HORA de tmax  16,50 hs // hora de la Temperatura maxima
float fotoperiodo=99.01;
float b = 0.8; //=coef ajuste NOCHE
float a = 1.5; //=coef ajuste DIA
//       ---------------------------------
String Status ="No Data Aun";
boolean grab =true;
int LectuAnt=0;// toma o lectura Anterior
int Lectun=0;
int nEventoA=0;// evento Anterior
float teInsta = -11.1111;
long[] pulso={20000, 20000, 20000}; //________ time schedule in msec
int step = 0;
long ts;

float freeMemory;
float tension=0;//VOLTIMETRO
  String[] listaCaja;
void setup () {//------------------------------------------------------------------------------------------------------------------------------------
  //size(700,380); // set the window size:
  size(800, 530); // set the window size:
  background(50, 50, 50);// set initial background:
  output = createWriter("datalogger.txt"); //Creamos el archivo de texto alojado en la carpeta del programa

  //1-List all the available serial ports printArray(Serial.list())
  printArray(Serial.list());

  //2- colocar el Nro del array del puerto disponible a usar y Abre el puerto que sea que estés usando.
  //pensar usar un dialogo en consola con una variable????
  //?????? void myPort = new Serial(this, Serial.list()[1], 9600);// clase Serial
  //pensar usar un dialogo en consola con una variable????
  myPort = new Serial(this, Serial.list()[1], 9600);// clase Serial

  //3-don't generate a serialEvent() unless you get a newline character:
  // read bytes into a buffer until you get a linefeed (ASCII 10):
  //myPort.bufferUntil('\n');  //ejemplo:   SerialCallResponseASCII

  //------------------------------------------------------------------------------------- interfase CP5
  cp5 = new ControlP5(this);
  //------------------------------------------------------------------------------------- interfase CP5

  //y= COEFtodo =  COEF_X0 + ","+ COEF_X1 + ","+ COEF_X2+ ","+  COEF_X3+ ","+COEF_X4+ ","+ COEF_X5+ ","+TEMP1+ ","+ t1;
  //polinomio circadiano--->  y = -0.000002x6 + 0.000263x5 - 0.010378x4 + 0.165335x3 - 0.993461x2 + 1.795195x + 4.399244   -->R² = 0.991943
  //11111111111111111 encima del graficador 1111111111111111111111111111111111111111111
  //--------------cajas de coeficientes para polinomio circadiano
  cp5.addTextfield("COEF_X0")// ---//caja imput de 1 linea
    .setPosition(20, 30).setSize(50, 15)//("COEF_X0")// ---//caja imput de 1 linea
    .setFont(createFont("arial", 10))
    .setAutoClear(false)// TRUE=vacia la caja luego del ENTER
    .setValue("-4.399244");//esto cierra la definicion del boton

  /*  cp5.addBang("Clear X0")//boton pulsador
   .setPosition(120,20).setSize(80,10)
   .getCaptionLabel().align(ControlP5.CENTER, ControlP5.CENTER)
   ; //esto cierra la definicion del boton
   */

  cp5.addTextfield("COEF_X1")// ---//caja imput de 1 linea
    .setPosition(22+1*55, 30).setSize(50, 15)
    .setFont(createFont("arial", 10))
    .setAutoClear(false)// TRUE=vacia la caja luego del ENTER
    .setValue("1.795195");
  ;//esto cierra la definicion del boton

  /* cp5.addBang("clear X1")//boton pulsador
   .setPosition(120,20+(1*40)).setSize(80,10)
   .getCaptionLabel().align(ControlP5.CENTER, ControlP5.CENTER)
   ;//esto cierra la definicion del boton
   */
  cp5.addTextfield("COEF_X2")// ---//caja imput de 1 linea
    .setPosition(22+2*55, 30).setSize(50, 15)
    .setFont(createFont("arial", 10))
    .setAutoClear(false)// TRUE=vacia la caja luego del ENTER
    .setValue("- 0.993461");
  ;
  /* cp5.addBang("clear X2")//boton pulsador
   .setPosition(120,20+(2*40)).setSize(80,10)
   .getCaptionLabel().align(ControlP5.CENTER, ControlP5.CENTER)
   ;//esto cierra la definicion del boton
   */

  cp5.addTextfield("COEF_X3")// ---//caja imput de 1 linea
    .setPosition(22+3*55, 30).setSize(50, 15)
    .setFont(createFont("arial", 10))
    .setAutoClear(false)// TRUE=vacia la caja luego del ENTER
    .setValue(" 0.165335");
  ;
  /* cp5.addBang("clear X3")//boton pulsador
   .setPosition(120,20+(3*40)).setSize(80,10)
   .getCaptionLabel().align(ControlP5.CENTER, ControlP5.CENTER)
   ; //esto cierra la definicion del boton
   */
  cp5.addTextfield("COEF_X4")// ---//caja imput de 1 linea
    .setPosition(22+4*55, 30).setSize(50, 15)
    .setFont(createFont("arial", 10))
    .setAutoClear(false)// TRUE=vacia la caja luego del ENTER
    .setValue("- 0.010378")
    ;

  /* cp5.addBang("clear X4")//boton pulsador
   .setPosition(120,20+(4*40)).setSize(80,10)
   .getCaptionLabel().align(ControlP5.CENTER, ControlP5.CENTER)
   ; //esto cierra la definicion del boton
   */
  cp5.addTextfield("COEF_X5")// ---//caja imput de 1 linea
    .setPosition(22+5*55, 30).setSize(50, 15)
    .setFont(createFont("arial", 10))
    .setAutoClear(false)// TRUE=vacia la caja luego del ENTER
    .setValue(" 0.000263");
  ;
  /*cp5.addBang("clear X5")//boton pulsador
   .setPosition(120,20+(5*40)).setSize(80,10)
   .getCaptionLabel().align(ControlP5.CENTER, ControlP5.CENTER)
   ; //esto cierra la definicion del boton
   */
  cp5.addTextfield("COEF_X6")// ---//caja imput de 1 linea
    .setPosition(22+6*55, 30).setSize(50, 15)
    .setFont(createFont("arial", 10))
    .setAutoClear(false)// TRUE=vacia la caja luego del ENTER
    .setValue(" -0.000002");
  ;  //esto cierra la definicion del boton

  /*cp5.addBang("clear X6")//boton pulsador
   .setPosition(120,20+(5*40)).setSize(80,10)
   .getCaptionLabel().align(ControlP5.CENTER, ControlP5.CENTER)
   ; //esto cierra la definicion del boton
   */
  //--------------cajas de coeficientes para polinomio circadiano

  noStroke();

  cp5.addSlider("s1")   // VARIABLE Y OBJETO es S1

    .setLabel("T1-GOAL")// float tempMin = 25.123;//modelo VZ=17°C
    .setPosition(10, height-97).setSize(150, 15)
    .setFont(createFont("arial", 12))
    .setColorBackground(    color(100, 0, 100))//Color del botón el sin puntero del ratón encima
    .setColorForeground(    color(10, 100, 10)) //Color del botón con puntero del ratón encima
    .setColorActive(color(0, 200, 120))//Color cuando se da click
    .setValue(16).setRange(-10, 48); //esto cierra la definicion del boton //modelo VZ=16°C setValue(17)
  //cp5.addSlider("s1") .setLabel("TEMP   1")

  cp5.addSlider("s2")

    .setLabel("T2-META")// float tempMax = 38.123;
    .setPosition(350, height-97).setSize(150, 15)
    .setFont(createFont("arial", 12))
    .setColorBackground(    color(100, 0, 100))//Color del botón el sin puntero del ratón encima
    .setColorForeground(    color(10, 100, 10)) //Color del botón con puntero del ratón encima
    .setColorActive(color(0, 200, 120))//Color cuando se da click
    .setValue(32).setRange(-10, 48);  //esto cierra la definicion del boton //modelo VZ=32°C setValue(32)
  //cp5.addSlider("s2") .setLabel("TEMP   2")

  // -----caja imput de 1 linea---------------------
  cp5.addTextfield("TEMP-1box") // VARIABLE Y OBJETO

    .setPosition(25, height-174).setSize(80, 20)
    .setFont(createFont("arial", 12))
    .setText("25")// base std del modelo Temp Critica  cargarlo a la variable del slider ---->s1
    .setAutoClear(false)// TRUE=vacia la caja luego del ENTER
    ;//esto cierra la definicion del boton

  /* cp5.addBang("clear T")//boton pulsadorclear T
   .setPosition(320,230).setSize(80,10)
   .getCaptionLabel().align(ControlP5.CENTER, ControlP5.CENTER)
   ;  */

  cp5.addTextfield("Texto_EVENTO")// --------------------elegir esta
    .setPosition(360, height-145).setSize(100, 25)
    .setFont(createFont("arial", 9))
    .setAutoClear(false)
    ;//esto cierra la definicion del boton

  cp5.addBang("clear")//boton pulsador
    .setPosition(460, height-145).setSize(25, 25)
    .getCaptionLabel().align(ControlP5.CENTER, ControlP5.CENTER)
    ;  //esto cierra la definicion del boton




  //2222222222222222222222222debajo del graficador222222222222222222222222222222222222222
  myTextarea = cp5.addTextarea("txt")//ventana de texto para indicaciones
    .setPosition(width-100, 90).setSize(100, 120)
    .setFont(createFont("arial", 12))
    .setLineHeight(12).setColor(color(255))
    .setColorBackground(color(60))
    .setColorForeground(color(255, 255, 255));
  ;

  cp5.addSlider("s3")
    .setLabel("DeltaT PID ")
    .setRange(0, 10) .setValue(1.10)
    .setFont(createFont("arial", 9))
    .setPosition(10, height-80).setSize(110, 15);

  cp5.addSlider("s4").setLabel("Hot/Cool % PID ")
    .setRange(0, 100) .setValue(85)
    .setFont(createFont("arial", 9))
    .setPosition(210, height-80).setSize(110, 15);

  cp5.addSlider("s5").setLabel("Histeresis-PID ")
    .setRange(0, 3) .setValue(0.14)
    .setFont(createFont("arial", 9))
    .setPosition(440, height-80).setSize(110, 15);

  // aqui solo define , las acciones se realizan en la pestaña ->FUNparaCP5
  cp5.addButton("EVENTON").setLabel("EVENTO")// EVENTO: int E = 0;   int ESTADO_E=0;// Flag DE CONTROL
    .setValue(99)
    //.setPosition(360,height-145)
    .setPosition(360, height-175).setSize(127, 30)
    .setColorBackground(    color(0, 0, 255))//Color del botón el sin puntero del ratón encima
    .setColorActive(color(0, 200, 120))//Color cuando se da click
    .setColorForeground(    color(100, 0, 255)) //Color del botón con puntero del ratón encima
    .getCaptionLabel() //Las líneas desde .getCaptionLabel() deben ir seguidas
    .setFont(createFont("", 12))  // y se aplican a la fuente del botón
    .toUpperCase(false)          //Evita que el texto quede todo en mayúscula
    //.setText("Color")            //Texto del botón
    .setColor(color(255, 255, 255)); //Color del Texto
  ; //esto cierra la definicion del boton

  cp5.addButton("ABORT").setLabel("ABORT")
    .setValue(22)
    .setPosition(200, height-130).setSize(60, 30)
    .setColorBackground(color(255, 0, 255))//Color del botón el sin puntero del ratón encima
    .setColorActive(color(0, 0, 0))//Color cuando se da click
    .setColorForeground(color(255, 0, 0)) //Color del botón con puntero del ratón encima
    .getCaptionLabel() //Las líneas desde .getCaptionLabel() deben ir seguidas
    .setFont(createFont("", 12))  // y se aplican a la fuente del botón
    .toUpperCase(false)          //Evita que el texto quede todo en mayúscula
    //.setText("Color")            //Texto del botón
    .setColor(color(255, 255, 255)); //Color del Texto
  ;  //esto cierra la definicion del boton

  cp5.addButton("START").setLabel("START")// START:  int S = 0;     int ESTADO_S=0;// Flag DE CONTROL
    .setValue(1)
    .setPosition(260, height-130).setSize(60, 30)
    .setColorBackground(color(210, 200, 0))//Color del botón el sin puntero del ratón encima
    .setColorActive(color(0))//Color cuando se da click
    .setColorForeground(color(0, 0, 255)) //Color del botón con puntero del ratón encima
    .getCaptionLabel() //Las líneas desde .getCaptionLabel() deben ir seguidas
    .setFont(createFont("", 12))  // y se aplican a la fuente del botón
    .toUpperCase(false)          //Evita que el texto quede todo en mayúscula
    //.setText("Color")            //Texto del botón
    .setColor(color(255, 255, 255)); //Color del Texto
  ; //esto cierra la definicion del boton


  cp5.addButton("DATAset").setLabel("LockDATA") //  variable tmb es le nombre de la funcion a llamar -rotulo es el txt de la etiqueta boton
    .setValue(33)
    .setPosition(width-195, height-130).setSize(60, 30)
    .setColorBackground(color(255, 120, 120))//Color del botón el sin puntero del ratón encima
    .setColorActive(color(0, 0, 0))//Color cuando se da click
    .setColorForeground(color(0, 0, 255)) //Color del botón con puntero del ratón encima
    .getCaptionLabel() //Las líneas desde .getCaptionLabel() deben ir seguidas
    .setFont(createFont("", 12))  // y se aplican a la fuente del botón
    .toUpperCase(false)          //Evita que el texto quede todo en mayúscula
    //.setText("Color")            //Texto del botón
    .setColor(color(255, 255, 255)); //Color del Texto
  ; //esto cierra la definicion del boton

  /*EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE
   myTextarea = cp5.addTextarea("txt")
   .setPosition(600,70)
   .setSize(90,140)
   .setFont(createFont("arial",12))
   .setLineHeight(12)
   .setColor(color(255))
   .setColorBackground(color(25))
   .setColorForeground(color(255,255,255));
   ;
   myTextarea.setText("Area para escribir notas y eventos"
   +"                              "
   +" Lorem Ipsum has been the industry's standard dummy text"
   +" ever since the 1500s, when an unknown printer took a galley of type"
   +" Lorem Ipsum"
   +" Lorem Ipsum"
   );
   */  //EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE

  // add a ScrollableList, by default it behaves like a DropdownList
  //List l = Arrays.asList("0 SOAK", "1 TERMOSTATO", "2 RAMPA y=mx+b", "3 CIRCADIANO", "4 Temperatura Crítica", "5 por ARCHIVO CVS", "6 Polinomio NN","7 TEMPORIZADO");// CASOS PARA SELECCIONAR MODO
  List l = Arrays.asList("0     LIBRE  AUTONOMO", "1 TERMOSTATO", "2 RAMPA y=mx+b", "3 CIRCADIANO", "4 Temperatura Crítica", "5 por ARCHIVO CVS", "6 Polinomio NN", "7 TEMPORIZADO");// CASOS PARA SELECCIONAR MODO
  cp5.addScrollableList("Modo")//titulo de la lista y nombre de la funcion asociada VOID
    //cp5.addScrollableList("dropdown")
    .setPosition(width-100, height-260)
    .setSize(130, 135)//--->>h=7items+1titulo*15 de h cajita=120
    .setBarHeight(15)
    .setItemHeight(15)//cajita
    .addItems(l)
    .setType(ScrollableList.LIST); // currently supported DROPDOWN and LIST;
  //----------------fin------- interfase CP5
  // lista los metodos disponibles de cp5 ?????   //       cp5.printPublicMethodsFor(Chart.class);
}// ---------------------------------------------------------------------CIERRE DE SETUP



void draw () {//************************************************************************************************************************************************
  if ( dataIN!=null) {//sin este if da error de puntero al inicio por que aun no leyo el puerto
    HANDS_SHAKE();//--------------------FUNCION HANDS_SHAKE   establece comunicacion bidireccional En pestaña comunicacion_01
    //--------------------reescriibir para que funcione en modo autonomo---- seleccionarble desde persiana ????
  }//
  // background(0);//limpia en cada frame
  hsC= float(hour())+float(minute())/60+float(second())/3600;
  imputData();

  pendiente();//--dibuja recta y=mx+b  habilitada por nModo
  tempCritica();//--dibuja habilitada por nModo
  circadiano();//--dibuja habilitada por nModo
  polinomio();//--dibuja habilitada por nModo

  // --------------------imprime en ventana grafica
  //armar funcion void graficaENventana(){
  //ARRIBA ------------------------------------------------------------
  fill(50, 170, 255);//AZUL CLARO
  stroke(50, 170, 255);
  rect(0, 4, width, 22);// posX posY tamaño X Y --cinta 21 -- para cubrir texto anterior simil background(0);
  fill(255, 255, 255);//negro
  stroke(127, 34, 255);



  fill(0, 75);//
  stroke(0, 75);
  rect(0, 50, width, 21); // posX posY tamaño X Y --cinta 21 --para cubrir texto anterior tempMax

  if (inByte!=tempsensor) {//si hay cambio lo muestra
    fill(50, 170, 255);
    stroke(50, 170, 255);
    rect(150, 4, 250, 21); // posX posY tamaño X Y --cinta 21 --para cubrir texto anterior simil background(0);
  }//si hay cambio lo muestra




  PFont f = loadFont("Arial-BoldMT-20.vlw");//Tipo de fuente
  fill(0, 0, 0);      //texto de color negro
  textFont(f, 18);
  text("Chamber= "+tempsensor+" ºC", 20, 20);
  textFont(f, 11);
  //fill(255, 200, 25);      //texto de color ORO
   fill(131, 4, 15);      //texto de color Mora
  noStroke();
  String t=nfs(abs(tempsensor-teInsta), 1, 3);   //nf(num, left, right)
  text("Delta T=  "+t, 215, 20); //
  fill(0, 0, 0);      //texto de color negro
  text("Meta= "+nfs(teInsta,2,2)+" ºC", 320, 20); 
  text("BbaTermica= "+TempDisip+" ºC", 410, 20);

  text("Aire= "+tamb+" ºC", 533, 20);
  text("ModoActivo= "+nModo, 635, 20);

  text("pulsar $ p/Salir ", width-80, 20);

  //ARRIBA ------------------------------------------------------------

  //abajo -------------------------------------------------------

  //fill(255,10);//
  stroke(100, 75);
  fill  (80, 0);
  rect(0, height-54, width, 21); // posX posY tamaño X Y --cinta 21 --para cubrir texto anterior
  // rect(0,height-54,width,11); // posX posY tamaño X Y --cinta 21 --para cubrir texto anterior


  // text("Hora Inicio=   "+horaINI, 25,height-40); //desde el pulso del boton  start
  //  text("EventoNro=    "+nEvento, 160,height-40);
  // text("TomaNro=      "+ Lectun, 250,height-40);

  fill  (0, 50, 20);

  rect(0, height -54, width, 25); //rect(a, b, c, d)//limpia punto y texto templMax

  fill(255, 255, 255);// texto blanco
  noStroke();
  text("PULSAR & ResetArduino,   PULSAR @ AjustaHora  SALIR pulsar $ ", 25, height-40); // tension= float(sensors[29]);  //    sens nro= 29 //float tension=0; en enviastatus
 text("Puente H= " +nfs(tension, 2, 2)+" v", 450, height-40); // tension= float(sensors[29]);  //    sens nro= 29 //float tension=0; en enviastatus
  text("Mfree=   " +nfs(freeMemory, 3, 0), 650, height-40); // http://localhost:8053/reference/nfs_.html
                /*
                Función de utilidad para formatear números en strings. 
                Similar a nf(), pero deja un espacio en blanco delante de los números positivos para que se alineen con los números negativos a pesar del símbolo menos. 
                ay dos versiones: una para formatear flotantes y otra para formatear enteros. 
                Los valores de los parámetros dígitos, izquierdo y derecho siempre deben ser números enteros positivos.
                Returns  String or String[]
                */

  text("Hora Inicio=   "+horaINI, 25, height-6); //desde el pulso del boton  start
  text("Evento=   "+nEvento, 160, height-6);
  text("Toma=   "+ Lectun, 250, height-6);

  horaActual=(hour( )*60*60+60*minute( )+second( ));             // LUEGO VENDRA DEL RTC DE ARDUINO
  segCorrida=  horaActual-horaINInum;
  text(horaActual-horaINInum+" sg de corrida", 350, height-6);

  text(" Hora Calc= "+hsC, 470, height-6);
  text(Status, 650, height-6); //

  //   fill(0,255,0);      //texto de color blanco
  //  text("SOAK" , 490,height-5); //
  //  circle(460, height-10,10);//x,y,diametro
  //if(LLegue==true) {
  //  fill(255,255,255);}      //texto de color blanco
  //delay(40);
  // circle(460, height-10,10);//x,y,diametro
  //  fill(255,255,255);      //texto de color blanco
  //abajo -------------------------------------------------------



  if (Lectun != LectuAnt) {// N =NUMERO DE TOMA O LECTURA LLEGA DESDE ARDUINO  n=int(sensors[2]);// verificar que esta enviando arduino aqui LINEA102procCOM
    //EN ARDUINO la variable ---lin 115---->int nLectu;// contador de LECTURAS DE TEMPERATURA -lin 249---->solo registra las diferentes y ENVIADATA();

    // EN ARDUINO la variable EVENTO se llama ---lin 120---->int nEvent=0;// contador de eventos NO se usa SE ACTUALIZA SOLO EN PROCCESING
    // println(" Lectun nuevaN ",Lectun,"  ",grab);
    //println(" Lectunt= ",Lectun,"  ",grab);
    //println(" toma nueva ",n,"  ",grab);
    LectuAnt=Lectun;
    grab =false; //graba archivo-----------------
    if (grab ==false) {//colocar SOLO si start graba ARCHIVO
      grabaArchivo();  //colocada aqui evita colisiones: no envia si esta recibiendo en el bufer
      grab =true;
      // println("lo pude grabar",grab);
    }   //graba archivo-----------------
  }  //graba archivo---si hay nueva lectura peltier


  dibujaGrafico();// corre a 24fps????

  if (keyPressed) {//------------------------keyPressed----------
    if (key == 'D' || key == 'd') {
      println("TAMBIEN PUEDO ENVIAR con letras fijas DEBUG");//hace un eco en la consola
      delay(10);
    }
    if (key=='&') {//RESET DE ARDUINO POR SOFT VER LINEA 410 INO  y comprobar luego que sigue conectado con  el arduino
              //if (key=='R' || key=='r') {//RESET DE ARDUINO POR SOFT VER LINEA 410 INO  y comprobar luego que sigue conectado con  el arduino
      //esto se repite dentro de arduino por ruina de autoreset
       println(" RESET DE ARDUINO POR SOFT VER LINEA 410 INO  -> ");
  
    output.print("RESET DE ARDUINO POR SOFT VER LINEA 410 INO  ->"+" ");
   
    output.print (day()+"/");
    output.print (month()+"/");
    output.print (year()+"-->");
       
    output.print(hour( )+":");
    output.print(minute( )+":");
    output.println(second( )+",");
    
    grabaArchivo(); // output   datalogger.txt
    myPort.clear();//Si el carácter existe limpiar el buffer de datos y
    myPort.write("9");//RESET DE ARDUINO POR SOFT VER LINEA 410 INO
     
      
    }    //_resetXsoftCall


if (key == '@' ) { //SOLICITA REajuste hora del RTC   en processing pulsa tecla @ enviabdo  else if (dataIN == '7')
            //if (key == 'H' || key == 'h') { //SOLICITA REajuste hora del RTC   en processing pulsa tecla H  enviabdo  else if (dataIN == '7')
      // Fijar a fecha y hora específica. En el ejemplo, 21 de Enero de 2016 a las 03:00:00
      // rtc.adjust(DateTime(2016, 1, 21, 3, 0, 0));
      println("SOLICITA REajuste hora del RTC   en processing pulsa tecla H");
// Fijar a fecha y hora específica. En el ejemplo, 21 de Enero de 2016 a las 03:00:00
// rtc.adjust(DateTime(2016, 1, 21, 3, 0, 0));

for (int i = 0; i < 3; i = i+1) {
       myPort.clear();//Si el carácter existe limpiar el buffer de datos y
     myPort.write("7");///SOLICITA REajuste hora del RTC   en processing pulsa tecla H
    //             for (int j = 10; j < 17; j= j+1) {
      //myPort.write(j);
      //}
     
      myPort.write (year());//10  1myPort.write((byte)(
      myPort.write (month()); //11 2
      myPort.write (day());//12 3
     
    myPort.write(hour( )); //13 4
    myPort.write(minute( ));//14 5
   myPort.write(second( ));//15 6
      
      println(hour( ),minute( ),second( ));
     
      
       delay(10);
    //  myPort.write("7");///SOLICITA REajuste hora del RTC   en processing pulsa tecla H
      
      }
     // delay(10);
    }




    if (key=='$') {
  //if (key=='e' || key=='E') {
      output.flush(); // Escribe los datos restantes en el archivo
      output.close(); // Final del archivo
      // PERO ANTES
      exit();// PERO ANTES Salimos del programa
      //ejecutar un batch:
      //  open("rundll32 SHELL32.DLL,ShellExec_RunDLL  copiararchivo.bat");
      //ejEcutar un batch desde processing COPIA EL DATALOGGER CON NOMBRE + FECHA  Y  LO PONE EN EL ESCRITORIO.
      //Archivo bat copiar archivos y ejecutarlo al inicio como administrador en windows

      //myfile.bat =  copiararchivo.bat
      //comandos: copy "D:\archivo_origenDATALOGGER.txt" "C:\archivo_destinoDATALOGGERddmmaa.txt" pause. ...
      //un archivo bat -> copiararchivo.bat
    }
  } //-----------------cierre keyPressed----------
  
}      //***************** cierre draw
