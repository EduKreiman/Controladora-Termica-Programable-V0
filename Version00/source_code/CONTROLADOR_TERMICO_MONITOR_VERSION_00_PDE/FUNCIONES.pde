void dibujaGrafico() {//--dibuja grafico con mapeo de inByte--puntoTemp(){//--dibuja grafico con --tempsensor-------------------------
stroke(100, 75);
fill  (80, 75);    
    rect(0,height -20,width, 14); //rect(a, b, c, d)//limpia punto y texto templMax
    rect(0,height-121,width, 14); //rect(a, b, c, d)//limpia punto y texto templMin
  //rect(0, -6+map(tempMin, 20, 41, height, 0 ),width, 12); //rect(a, b, c, d)
 //      a         b                              c     d 
  
   strokeWeight(1);
   
  for (int a = 0; a <width; a+=40) { //dibuja trama X
        line(a,50,a,height-130);
      }
       for (int a = 0; a <height; a+=50) { //dibuja trama Y
        line(0,a,width,a);
      }

// -----------------------imprime tempMin  
  tempMin=s1;//variable del slider
          stroke(0, 255, 0);//verde
          fill(0, 255, 0);//verde
          circle(20,height-115, 10);//x,y,diametro 
          text(tempMin, 40, (height-109));  
       // text(tempMin, 40, 5+map(tempMin, 20, 41, height, 0));
// ------------------imprime tempMax/final  
  tempMax=s2; //variable del slider
          stroke(255, 0, 0);//rojo
          fill( 255, 0, 0);//rojo
          text("Tº final", width-90,53);
          text(tempMax, width-160,53);
          circle(width-20, 48,10);//x,y,diametro

          float setYpoint=-80;
 
         //--dibuja grafico con --tempsensor--
               stroke(180, 34, 255);//-------------------punto  VIOLETA  sensor PELTIER
               fill(180, 34, 255);
               //       X ,                    Y                           , DIAMETRO
               circle(xPos,(setYpoint+ map(tempsensor, -10, 38,height-100, 100))  ,6);
        //--dibuja grafico con --teInsta--
               stroke(0, 255, 0);//----------------------punto  VERDE TEMP  GOAL/CALCULO/
               fill(0, 255, 0);
               circle(xPos, (setYpoint+map(teInsta, -10, 38,height-100, 100)),3);         
                          
                          
                          if (xPos >= width) { // SI LLEGO AL BORDE DERECHO VUELVE
                            xPos = 0;
               fill(0, 0, 0);//negro
               rect(0, 30, width, height); // background(0);// limpia el fondo del grafico
                          } else {// incrementa la posicion horizontal en  X
                            xPos=(xPos+1);//  1 pixel por cuadro de processing (24fps)                                         
                          } 
                                     
 
               
}  //-------------------------------- fin dibujaGrafico()


void imprime_en_consola()//-------Escribe  los datos en monitor para DEBUG 
{  
  
//   COLOCAR AQUI EL RESTO DE DATOS A GUARDAR
           // HACER MATRIZ RECORRIDA POR FOR ??? 
 println("-------------------------------------------------------------");
 println("Operador: ",Operador," Proceso nro= ", proceso_nro);
 println("Laboratorio de evolucion IEGEBA 47");
println("EVENTO nro= "+nEvento," --------------------------------------------");
print("tiempo desde start: ",segCorrida, "sg");
              // LOS TOMA DEL SISTEMA DEL PC SE CAMBIARAN POR LOS RECIBIDOS DESDE EL ARDUINO RTC
              //println(hour( )+":");  print(minute( )+":");print(second( )+",");
print(" hora:",RTChoraActual); //recibida del rtc arduino
println(" fecha= ",RTCfecha);  //recibida del rtc arduino                   
  print("temperatura ambiente= ",tamb);//recibida del rtc arduino
  //println("  humedad= ",h);
  //print(" temperatura ambiente= ",t+ " ºC");
  println(" Temp Sensor Peltier = "+tempsensor + " ºC");//tempsensor es float
    //op =map(float(int (inByte)),-10,);//roja
  print(" TEMP1: ",tempMin+",");//dataset
  print(" TEMP2: ",tempMax+",");//dataset
  println(" Modo= ",nModo+",");//dataset

 
  println("////////////////////////////////////////////////////////////////////");
  println("val recibido de ardu: ");
  println(dataIN);
  print("\n ");// SALTO DE LINEA  Imprima una nueva línea utilizando el carácter \n de la secuencia de escape en Java
  print("Temperatura inByteRaw = ",inByteRaw); //dato bruto 
  print("\n ");// SALTO DE LINEA  Imprima una nueva línea utilizando el carácter \n de la secuencia de escape en Java
 // print(" inByte = ",inByte); //dato mapeado
 //println(inString);
  println("////////////////////////////////////////////////////////////////////");
  print("\n ");// SALTO DE LINEA  Imprima una nueva línea utilizando el carácter \n de la secuencia de escape en Java
    //println("data RTC: "+inRtc);//
     
 // print("\n ");// SALTO DE LINEA
} //------------fin-- --------------Escribimos  los datos en monitor para DEBUG 



void grabaArchivo() // output   datalogger.txt
{//--------------Escribe  los datos en el archivo de txt: temperatura,tiempo (h/m/s),etc
delay(50);
//println("REGISTRE DATA");
               output.print("  "+",");//columna vacia
               output.print("  "+",");//columna vacia
               output.print(" Corrida: "+",");output.print(segCorrida+" seg ,");
               output.print("  "+",");//columna vacia
               output.print("  "+",");//columna vacia
               output.print(" Chamber: "+",");output.print(tempsensor + ", ºC     ,");//tempsensor es float
               output.print(" MetaInsta: "+",");output.print(teInsta + ", ºC     ,");//tempsensor es float
               output.print(" BbaTermica: "+",");output.print(TempDisip + ", ºC     ,");//Serial.print(TempDisip);//    sens nro= 28 //
               output.print("  "+",");//columna vacia
               output.print(" Aire: "+",");output.print(tamb + ",");
               output.print(hour( )+":");// LOS TOMA DEL SISTEMA DEL PC
               output.print(minute( )+":");
               output.print(second( )+",");
               output.print (day()+"/");
               output.print (month()+"/");
               output.print (year()+",");
               output.print("TomaNro= "+ Lectun +",   ");
               output.print("Modo "+","+ nModo+",   ");
               output.print("puente H "+","+ tension+",   "); // tension puente H  //    sens nro= 29 //float tension=0;
               
               
                if(nEvento!=nEventoA)  {// guarda solo si hubo un evento
                   output.println("EVENTO= "+ nEvento +",");
                   nEventoA=nEvento;
                   
                                         output.println("     ");
                                         output.print("  Texto de la cajita evento:  ");
                                         output.println("<----- este es el texto") ; 
                                         output.println(" "+hour( )+":"+minute( )+":"+second( ));
                   //saveStrings( dataPath("text_area.txt"), split(entracaja+" "+hour( )+":"+minute( )+":"+second( ), ENTER)) ;
                   
                                                  output.println( listaCaja);//[Ljava.lang.String;@7d8cafcf            output.println( listaCaja);
                                                  output.println(entracaja) ;//4.4000087873,1.7940130544, -0.9931090066,0.1653098494,-0.0103796399,0.0002635128,25,16,ñlnj vzvzvzmgastr 
                                                  output.println(" <-----ESTE");
                                                     
                   }
   else if (nEvento==nEventoA)  {//  
               output.print("  "+",");//columna vacia
               output.print("  "+",");//columna vacia
               output.print(" T1 Min: "+",");output.print(tempMin+",");
               output.print("T2 Max "+",");output.print(tempMax+",");
               output.print("freeMemory "+",");output.print(freeMemory+",");
              
                         
       
  output.println(",");// SALTO DE LINEA
   }
    output.print("STATUS-SE 2"+",");output.print(Status +",");//-----------------------------
    output.print("pseudoPID-RANGO SE 15"+",");output.print(s3 +",");
    output.print("pseudoPID-HOT/COOL SE 16"+",");output.print(s4 +",");
    output.print("pseudoPID-HISTERESIS SE 17"+",");output.print(s5 +",");
    output.print(" Hora Calc"+",");output.print(hsC +",");
  
  // COLOCAR AQUI EL RESTO DE DATOS A GUARDAR
  // agregar aqui nuevas variables como:
// tiempo maximo
// nro de ciclos
    // HACER MATRIZ RECORRIDA POR FOR ???
  
} //------------fin---Escribimos los datos en el archivo de texto 

  
   

void keyPressed() {      
  //Cuando se pulsa una tecla
   //GRABA AL PUSAR ENTER KEY
    //saveStrings( dataPath("text_area.txt"), split(myTextarea.getText(), ENTER) );//evento nro fecha*/ 
    
  if (key=='$') {//Pulsar la tecla  $ para salir del programa  
  // if (key=='e' || key=='E') {//Pulsar la tecla E para salir del programa  
    output.flush(); // Escribe los datos restantes en el archivo
    output.close(); // Final del archivo
    exit();//Salimos del programa
     }
     
   if(key=='ñ') {// String[]: string array to be written
   // graba en archivo el contenido del areaTexto
   //saveStrings( dataPath("text_area.txt"), split(myTextarea.getText(), ENTER) );//evento nro fecha*/
   
   
                }
} //-----------------cierre void keyPressed()





//-------------------------------------
/*
//long[] pulso={20000, 20000, 20000}; //________ time schedule in msec
void timer() {
  //tr  = animator[step] - ( millis() - ts ) ; //_ for show remaining time only
  if ( millis() - ts > pulso[step] ) {
    // do whatever you have to do
    
   // println(timeString() + " end step "+step);
    step++;
    ts = millis();
    if ( step >= animator.length ) step = 0; //- auto repeat
  }
}//fin timer

*/
