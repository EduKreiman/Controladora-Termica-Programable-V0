//----------------FUNCIONES DE ------- interfase CP5
//  VER   definiciones en setup
                              
                              /*  //LLAMAR A void leerBotones()
                              cp5.addButton("EVENTO").setLabel("EVENTO")// EVENTO: int E = 0;   int ESTADO_E=0;// Flag DE CONTROL
                              cp5.addButton("START").setLabel("START")// START:  int S = 0;     int ESTADO_S=0;// Flag DE CONTROL
                              cp5.addButton("ABORT").setLabel("ABORT") .setValue(0)
                              // ABORTint A = 0; variable to store the value read
                              // int ESTAnt_S=0;// Flag DE CONTROL
                              // int ESTADO_A=0;// Flag DE CONTROL
                              cp5.addButton("DATAset").setValue(33)
                              
                              */



//TOMA la variable local DEL BOTON  ENVIA CARACTERES DE COMANDO A ARDUINO
void controlEvent(ControlEvent theEvent) {
   n = 0;
 // println(theEvent.getController().getName());//eco boton pulsado
  
  
 if(theEvent.isAssignableFrom(Textfield.class)) {
                                          println("controlEvent: recibió UN string del Controller '"
                                                  +theEvent.getName()+"': "
                                                  +theEvent.getStringValue()
                                                  );
   // String entracaja=theEvent.getStringValue();
entracaja=theEvent.getStringValue();
   // saveStrings( dataPath("text_area.txt"), split(entracaja+" "+hs     +":"+         ":"+hs       , ENTER)) ;
                                  listaCaja = split(entracaja, ENTER) ;
   
   /*
   syntax  :    split(value, delim)
   EJEMPLO:  
   String    men = "Chernenko,Andropov,Brezhnev";
                                 String[] list = split(men, ',');
                              // list[0] is now "Chernenko", list[1] is "Andropov"...
                              */
  
  saveStrings( dataPath("text_area.txt"), split(entracaja+" "+hour( )+":"+minute( )+":"+second( ), ENTER)) ;
   // saveStrings( dataPath("text_area.txt"), listaCaja[1]+" "+hour( )+":"+minute( )+":"+second( )) ;
    /*
    output.println("     ");
    output.print("  Texto cajita evento:  ");
    output.print(hour( )+":");
    output.print(minute( )+":");
    output.println(second( )+"     "+",");
    output.print(entracaja+"<----- este es el texto") ;  
    */
  }
  
  if(theEvent.isAssignableFrom(Textfield.class)) {
                                          println("controlEvent: recibió UN string del Controller '"
                                                  +theEvent.getName()+"': "
                                                  +theEvent.getStringValue()
                                                  );
                                                  
                                                  //String entracaja=theEvent.getStringValue();
 //entracaja= entracaja+","+theEvent.getStringValue();
                                             //   saveStrings( dataPath("Coeficiente_1.txt"), split(entracaja, ENTER)) ;//----------------->graba en archivo al pusar ENTER
                                              entracaja=COEFtodo+","+theEvent.getStringValue();
                                             saveStrings( dataPath("Coeficiente_1.txt"), split(entracaja, ENTER)) ;//----------------->graba en archivo al pusar ENTER
                                        
                                        // saveStrings( dataPath("Coeficiente_1.txt"), split(entracaja, F9)) ;
                                      // saveStrings( dataPath("text1_area.txt"), theEvent.getStringValue(), ENTER) ;//----------------->graba en archivo al pusar ENTER
                                                 // PROBAR SAVE FILE
                        }
}


public void clear() {
  cp5.get(Textfield.class,"Texto_EVENTO").clear();//borra la caja "Texto_del_EVENTO"
      }


//ABRE PLANILLA EXCEL CARGA DATOS EN COLUMNAS ESPERA RECIBUIR ANOTACION GUARDA HOJA
//https://www.instructables.com/Mediciones-Directas-a-Excel/ 
/*
uso la capacidad de Excel para leer datos desde un sitio web (web-query) 
de modo que el acceso a la información es a través de una conexión TCP.IP sobre la red LAN o Internet. 
chip ESP8266  que controla un stack TCP.IP y permite configurar fácilmente un servidor web, 
*/

// EL BOTON EVENTO SE CODEA SOLO EN PROCESSING 
// 0-controller with name DATAset que usa la variable local theValue






//public void EVENTO(int theValue) {//In Processing, all fields and methods are public unless otherwise specified by the private keyword.
// println ("Tvalue= ",theValue); 
void EVENTON() {// FUNCION --------------------- EVENTO N
nEvento=nEvento+1;
imprime_en_consola();//linea NNNN  vuelca para DEBUG los datos del evento---->se usara para GUARDAR en archivo del evento
                  
fill(0,0,0);
rect(60,60,30,30);//------limpia señal grafica del evento

}//FIN -------------------------------------------------------------------------------------------------------------EVENTON





void DATAset(int theValue) {// SETEA= ENVIA PARAMETROS SET COMPLETO A ARDUINO- DISPONIBLES PARA UN START/INICIO
  // function DATAset will receive changes from 
  println("button event desde DATAset: "+theValue); 
 // nEvento=0;
  println("  llama a funcion  enviaDATAset() en LINEA 324 de PROCESSING");                                                                
       yaSeteado=true;       //control de funcion dataset yaSeteado=true; se hace false luego de abort o final de ciclo
 enviaDATAset() ;     // void enviaDATAset(){  myPort.write('5'); en LINEA 324 }   ver lineas 234 y 243       
      //incluye un  myPort.write('5')
       println(" Datos seteados y Registro bloqueado");
        //se activa en linea 328 DE ARDUINO
                                                               // if ( yaSeteado !=true) { 
                                                                                            // int value = 0;//variable local
                                                                                          //if (value == 0) {
                                                                                            //myPort.write('1');        //enviar un 1 enciende led 13 en arduino board
                                                                                            //println("1A  haciendo un eco en la consola-->mouse released"); 
                                                                                            //  println ("Tvalue= ",thevalue);
                                                                                           // value = 255;
                                                                                          //} else {
                                                                                           // value = 0;
                                                                                           //  println("1 B  haciendo un eco en la consola-->mouse released"); 
                                                                                           // println (value);
                                                                     //  }else if( yaSeteado ==true) {
                                                                                 //       println("Datos Bloqueados hasta nuevo Inicio o Abort-> DATOSseteados");
                                                                                 //       print ("tempMin= "+seteatempMin);//dataset
                                                                                 //       print ("   tempMax= "+ seteatempMax);//dataset
                                                                                 //       println ("  nModo= "+seteanModo);//dataset
                                                                                 //                  myPort.write('1'); 
                                                                                                // myPort.write("SETEA");        //enviar COMANDO A ARDUINO
                                                                                                 //myPort.write('1');        //enviar un 1 enciende led 4 en arduino board 
                                                                             
                                                                                               /*
                                                                                                 print ("tempMin= "+tempMin);//dataset
                                                                                                print ("   tempMax= "+ tempMax);//dataset
                                                                                                println ("  nModo= "+nModo);//dataset
                                                                                                */
                                                                        // }
}//FIN----------------------------------------------------------- void DATAset(int theValue)



//2- -----------------------------------controller with name START 
void START(int theValue) {//usa la variable local theValue
// function START will receive changes from 
println("button event desde START: "+theValue);
yaSeteado=false;       //control de funcion dataset yaSeteado=true; se hace false luego de abort o final de ciclo
println("0-->START"+"  yaSeteado=false "); 
nEvento=0;
 //int value = 0;//variable local
 // if (value == 0) {                              
             println("             Envia COMANDO START A ARDUINO ");  
             myPort.write("2");        //enviar COMANDO A ARDUINO
                int horaINInum=(hour( )*60*60+60*minute( )+second( )); //tomar la hora del start             // LUEGO VENDRA DEL RTC DE ARDUINO
        
               //  } 
}//----FIN-----------------------------------controller with name START


//3- ---------------------------controller with name ABORT 
void ABORT(int theValue) {//usa la variable local theValue
// function ABORT will receive changes from 
yaSeteado=false;       //control de funcion dataset yaSeteado=true; se hace false luego de abort o final de ciclo
nEvento=0;
   println("1 button ABORT: "+"  yaSeteado=false "+theValue);
    myPort.write("3");        //enviar COMANDO A ARDUINO
}//----FIN-----------------------------------controller  with name ABORT



//----------------------- interfase CP5 para lista desplegable de seleccion de modos
void Modo(int n)  {//                   para lista desplegable de seleccion de modos
     /* request the selected item based on index n
          here an item is stored as a Map  with the following key-value pairs:
          name, the given name of the item
          text, the given text of the item by default the same as name
          value, the given value of the item, can be changed by using .getItem(n).put("value", "abc"); 
                              a value here is of type Object therefore can be anything
          color, the given color of the item, how to change, see below
          view, a customizable view, is of type CDrawable 
     */ 
    CColor c = new CColor();
  c.setBackground(color(255,255,0));
//cp5.get(ScrollableList.class, "dropdown").getItem(n).put("color", c);

  
  nModo = n;//pasa item seleccionado  "n"  a variable global  nModo
  println("Modo seleccionado= "+nModo);
  //List l = Arrays.asList("0 SOAK", "1 TERMOSTATO", "2 RAMPA y=mx+b", "3 CIRCADIANO", "4 Temperatura Crítica", "5 por ARCHIVO CVS", "6 Polinomio NN","7 TEMPORIZADO");// CASOS PARA SELECCIONAR MODO

  if (nModo==0){ //myPort.write(nModo);        //enviar un 1
                print("-->MODO   LIBRE  AUTONOMO");
                fill(0,180);
              rect(0,20,width,height-80); //limpia pantalla
              }//-
  if (nModo==1){ // myPort.write(nModo);        //enviar un 1
                  print("-->MODO MANTIENE Termostato  ");
                   fill(0,180);
                rect(0,20,width,height-80);//limpia pantalla
                }//-       
  if (nModo==2){  
                       
                  print("-->MODO RAMPA LINEAL ");
                  
                  fill(0,20);//limpia pantalla
                rect(0,20,width,height-80);
                }//-
  if (nModo==3){  
                               
                  print("-->modelo  CIRCADIANO PARTON&LOGAN");
                  
                   fill(0,180);//limpia pantalla
                       //fill(0,200,0,180);//limpia pantalla
                rect(0,80,width,height-80);
                }//-
  
  if (nModo==4){ 
    print("-->Modelo Temperatura Crítica ");//
                  
                   fill(0,180);//limpia pantalla
                rect(0,20,width,height-80); 
                tempCritica();
                }//-
  
  if (nModo==5){  print("-->MODO  lee ARCHIVO CVS");
                                   /*  archivos CSV son un tipo de documento en formato abierto sencillo para representar datos en forma de tabla   */
                     fill(0,180);//limpia pantalla
                  rect(0,20,width,height-80);
                  }
  if (nModo==6){ 
                                  //myPort.write("5");        //enviar un 5
                    print("Polinomio NN");
                     fill(0,180);
                  rect(0,20,width,height-80);
                  }//- 
  if (nModo==7){  
                                   //myPort.write("5");        //enviar un 5
                  print("-->MODO  TEMPORIZADO");
                   fill(0,180);//limpia pantalla
                rect(0,20,width,height-80);
                }//-         
 }//------------------------------fin void Modo(int n) 
 
 
  





void enviaDATAset(){//             llamada DESDE  la funcion  DATAset en linea 122




       seteatempMin = tempMin;//dataset  float seteatempMin;//dataset
       seteatempMax = tempMax;//dataset  float seteatempMax;//dataset
       seteanModo = nModo;//dataset      int seteanModo;//dataset
       print ("BLOQ-tempMin=    "+seteatempMin);//dataset
       print ("   BLOQ-tempMax= "+ seteatempMax);//dataset
       println ("   BLOQ-nModo= "+seteanModo);//dataset
    
    myPort.write("5");  //                  0    ACTIVA LINEA 374 EN ARDUINO 318
     myPort.write((byte)(seteatempMin));// 11 You can always send the value from Processing as a string
     myPort.write((byte)(seteatempMax));// 12 You can always send the value from Processing as a string
//--------------------------- es un problema de secuencia  no de tipo de dato la posicion 14 no se recibe
myPort.write((byte)(float(seteanModo)));// 13 seteanModo es INT  You can always send the value from Processing as a string 
myPort.write((byte)(float(nEvento)));//    14 EVENTO es INT You can always send the value from Processing as a string 

//--------------------------- es un problema de secuencia  no de tipo de dato la psicion 14 no se recibe
//myPort.write((byte)(float(seteanModo)));// 14  no se recibe
myPort.write((byte)(s3*10));//    sens nro= 15float

//myPort.write((byte)(s4*100));//    sens nro= 16 float s4 = eficiencia % cold/hot
int s4i=int(s4*10);
myPort.write((s4i));//    sens nro= 16 float s4 = eficiencia % cold/hot
println(" SEN 16                            s4:"+s4);

myPort.write((byte)(s5*10));//   sens nro= 17float 
// myPort.write(nf(s5, 1, 3));//   sens nro= 17float 


/*
println(" SEN 16                            s4:"+s4);
 print(" SEN 17  Prints 9,01 instead 9.01         s5:");println(nf(s5, 1, 3));// Prints "9,01" instead "9.01"
//--------------------------- es un problema de secuencia  no de tipo de dato la psicion 14 no se recibe

float ww=1.14;

myPort.write(nf(ww));// 15 seteanModo es INT  You can always send the value from Processing as a string 

myPort.write(nf(ww));// 16 seteanModo es INT  You can always send the value from Processing as a string 
myPort.write(nf(ww));// 17 seteanModo es INT  You can always send the value from Processing as a string 




//myPort.write ((byte)(10.01));// 
//myPort.write((byte)(float(nEvento)));//    14 EVENTO es INT You can always send the value from Processing as a string 
//--------------------------- es un problema de secuencia  no de tipo de dato la psicion 14 no se recibe
println(" CONTROL   ----------------------------------  CONTROL");                               
println("  SEN 14                        event:"+float(nEvento));
//println("  SEN 14                        event:"+((byte)(float(nEvento))));
*/
    
println(" CONTROL   ----------------------------------  CONTROL");  
   
/*
        seteaNciclos=Nciclos;//            5 cantidad de ciclos para modos ciclables
        seteatiempoCorrida=tiempoCorrida;//6 tiempo de la corrida para temp critica y para rampa
        seteatiempoMaximo=tiempoMaximo;//  7 tiempo de seguridad para termostato
  
                                                                                                  */ 
                                                                                                    /* DA ERROR METODO WRITE(BYTE)
                                                                                                 en Processing: Siempre puede enviar el valor de Processing como string (una cadena).
                                                                                                             construir  un  string (una cadena) a partir de un float             
                                                                                                                            no esta en processing     sprintf(buffer, "s5: %d.%d", s5*100 / 100 , s5*100 % 100); //probar esta aplicacion                                    y
                                                                                                
                                                          luego, en el extremo de Arduino, prepare los bytes
                                                                                                                               y
                                                                                                            convertir la cadena a un float usando
                                                                                                                        float f = strtof (data);
                                                                                               
                                                                                                  
                                                                                                 usar en processing la funcion de formateo nfs(float.entero . decimal); 
                                                                                                  // f = -9.012;
                                                                                                  //  String sf = nfs(s5, 2, 3); 
                                                                                                  //println(sf);  // Prints "-009.01200" 
                                                                                                
                                                                                                // ------->>> para construir    string (una cadena) a partir de un float                           
                                                                                                   int precision = 100;
                                                                                                   int psuedoFloat = myFloat * precision ;
                                                                                                   sprintf(buffer, "myFloat: %d.%d", psuedoFloat / precision , psuedoFloat % precision);  
                                                                                                  >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>     
                                                                                                       int psuedoFloat = s5 * precision ;// aqui coloco el float a conertir s5 histeresis =0.65
                                                                                                       sprintf(buffer, "s5: %d.%d", s5*100 / 100 , s5*100 % 100); //probar esta aplicacion 
                                                                                                      <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
                                                                                                      
                                                                                                      se utiliza para enviar una salida formateada a la cadena. En lugar de imprimir en la consola,
                                                                                                      */
 
 }//---------------fin enviaDATAset()
