


void pendiente(){//--Modo 2    -tempMin tempMax(y=mx+b)--dibuja grafico -
//      *******************************************************************************************
          if (nModo==2){
    myTextarea.setText("PULSAR `$´ para salir, ----------       modo Activo RECTA: "+"  "+nModo);//+"     "+"temperatur= "+t1 
          fill(0,20);
        rect(0,20,width,height-80);
        stroke(255, 200, 0);//---  ocre  ----------               ---------s2 
        // strokeWeight(5);  // 
            line( 20,map(s1,-10,48,height-100,62),width-50,map(s2,-10,48,height-100,62) );
            strokeWeight(1);  // Default
          } 
  }//--dibuja grafico con --tempMin tempMax--






void circadiano(){  //modo 3    ecuaciones del Paper de -->PartonLogan1980<---- llama dentro a DibCircadiano(); la funcion que recorre 24 hs
//*******************************************************************************************  
       /* PARAMETROS      
                                Latitud del lugar  BsAs  34ª35`35"  
                                fecha  01/01/1900    
                                float incremental=0.10; // hs  centecimal  dato
                                float aManecer=9.00;// hs= Srise  centecimal  dato
                                float aNochecer= 20.00// hs =S set  centecimal  dato     
                                tn = T min  4,00 Cº    dato
                                Tmin=amanecer a las:  9,00 hs= Srise  HORA de Tmin diurna  
                                tx = T Max  16,00 Cº    dato
                                float Hs_Tmax = 17.50;// hora de la remperatura maxima
                                       // temp Max para VZ tropical =32°C a las 17h50 
                                //HORA de tmax  16,50 hs // hora de la remperatura maxima   
                                Tmedia  8,73 Cº    
                                y= deltaT  12,00 Cº    
                                ADY=( AHOU/3.14)* 24.  11,00 hs  long  fotoperiodo DIURNO  
                                ANI=(24.--ADY)  13,00 hs  long  fotoperiodo NOCTURNO  
                                nro de dia(1 a 365)      
                                float b=coef = 0.8;   //ajuste NOCHE      
                                float a=coef=1.5; //ajuste DIA      
                                        
                                z  12,00  no  se usa  
                                m  12,00  no  se usa  long  fotoperiodo DIURNO
                                n  12,00  no  se usa  long  fotoperiodo NOCTURNO
                                modelo Venezolana T1Min=16°C-T2Max=32°C
                */
 
if (nModo==3){  // modo seleccionado
myTextarea.setText("PULSAR `$´ para salir, ----------       modo Activo Circadiano: "+"  "+nModo+" Fotop.= "+fotoperiodo+" hs"+" Srise: " +aManecer+ "     Sset: "+aNochecer);//+"     "+"temperatur= "+t1 

stroke(125);//****************************para dibujar tramas 
strokeWeight(1); 
fill(0,100,100);
        for (int i = 0; i <width-70; i+=40) { //                dibuja trama Y
              line(i,0,i,height-150);
              //                 x =map(i,0,24,0,width-130);//calcula la curva 24hs dentro del ANCHO de la ventana  
                         float  hs =map(i,0,width-130,0,23.5);//calcula la hora VERTICALES
                             int h= int(hs);
                         text(h+"hs",i,height-150);  //EN LA BASE DE LA LINEA      
            }          
            stroke(0,80,20);//para dibujar tramas           
       for (int i = 0; i <height-150; i+=25) { //        dibuja trama X
                     line(0,i,width,i);//HORIZONTALES
                     //String t=nfs(abs(tempsensor-teInsta),3,0);   //nf(num, left, right)
                     
                     text(nfs(map(i,0,height-150,40,-3),2,1),10,i);//A LA IZQ DEL SCREEN
            } 
            
//dibujar tramas***********************************************************************************

//print(" hora:",RTChoraActual); //recibida del rtc arduino
hsC= float(hour())+float(minute())/60+float(second())/3600;//hora de calculo de la temperatura instant
//teInsta temp calculada en arduino

float xHora=width/2;
         xHora =map(int(hsC),0,24,10,width-100);//calcula la curva 24hs dentro del ANCHO de la ventana 
       //xHora =map(int(RTChoraActual),0,24,10,width-100);//calcula la curva 24hs dentro del ANCHO de la ventana 
      stroke (14,172,232);strokeWeight(3);
  line( xHora,70,xHora,height-230);//MARCA DE LA HORA DE LA HORA DEL CALCULO
   

      stroke (0,0,255);strokeWeight(2);
      xHora =map(8,0,24,10,width-100);//calcula la curva 24hs dentro del ANCHO de la ventana      
  //line( xHora,190,xHora,height-150);//MARCA DE LA HORA DE LA minima TEMP= amanecer
   fill(#FFCE05);
           //  x         y
    circle((xHora-8),map( 8,-2,35,height-230,33),12);//MARCA DE LA HORA DE LA minima TEMP= amanecer
  
       xHora =map((Hs_Tmax+1.5),0,24,10,width-100);//calcula la Xpos en el ANCHO de la ventana 
          // temp Max para VZ tropical =32°C a las 17h50 
      stroke (255,0,0);strokeWeight(3);
      //line( xHora,50,xHora,height-380);//MARCA DE LA HORA DE LA MAXIMA TEMP
 
        strokeWeight(1);
       //noFill();
       fill(255,0,0);
       //    map( T_cal,-2,35,height-130,33);//calcula la curva dentro del ALTO de la ventana
        //x =map(i,0,24,0,width-100);//calcula la curva 24hs dentro del ANCHO de la ventana   
       //map(TeInsta,0,              i,height-150); //
        circle(xHora,map( tempMax,-2,35,height-150,33),12);//MARCA DE LA HORA DE LA MAXIMA TEMP calcular con arcoseno
  
                                /*println ("xHora= ",xHora,"  horaINI= ",int (horaINInum));
                                println ("xHora= ",xHora,"  horaINI= ",RTChoraActual);
                                println ("xHora= ",xHora,"  horaINI= ",hs);
                                println ("xHora= ",xHora,"  horaINI= ",Hs_Tmax);
                                println ("xHora= ",xHora,"  horaINI= ",horaINI);
                                println ("xHora= ",xHora,"  horaINI= ",horaINI);
                                // line(map(TeInsta,0,              i,height-150); //dibuja lineaInsta en Y la TeInsta
                                // line(0      ,map(now.hora,    idth,i   width-130,0,23.5      );//dibuja lineaInsta X la horaActual
                                */
 
incremental=0.10; // hs  centecimal  dato
aManecer=8.00;// hs= Srise  centecimal  dato
aNochecer= 20.00;// hs =S set  centecimal  dato
fotoperiodo=aNochecer-aManecer;
Hs_Tmax = 15.75;// hora de la temperatura maxima calcularla ????
                      //HORA de tmax  16,50 hs // hora de laTemperatura maxima   
                      //  tempMin=s1;//carga variable del slider
                                           //println(s1);//int del slider 1 -> temp 1                  
                     //t1 = str(s1);//convierte un numero int en una string
                                               //  println(t1);
                                    //coloca el string en la ventana de texto=texarea-->addTextarea
                                    // funcion tempMax=s2;
                     // tempMax=s2;////carga variable del slider //int del slider 2 -> temp 2 
b = 0.8; //=coef ajuste NOCHE      
a=1.5; //=coef ajuste DIA     
deltaT=tempMax-tempMin;



//calC. algoritmo   ecuaciones del Paper de -->PartonLogan1980<----

hs=22.10;//porque fija ??????????????????????????????????????????????????????????????????????EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE
//tempMin=04.00;//activa Slider s1
//tempMax=16.00;//activa Slider s2
deltaT=tempMax-tempMin;
T_instAnterior=tempMin; //idem AManecer

//       y=     $B$9+((($B$15)*SENO((PI()*(11,9))/($B$15+2*$B$20))+$B$9)   -$B$9)     *EXP(-$B$19*F168/2)
 T_aNoche =  tempMin+(T_instAnterior                                       -tempMin)  *exp(-b    *(aNochecer-12)/2); //baja exponencialmente a la noche a partir de la temp del anochecer
// 20.00         4.0 Cº 
//y=             (($B$15) *SENO((PI()*($F9))                    /  ($B$15+2*$B$20))+$B$9)
//T_aNoche=          12   * sin(  (PI*(11.9              ))     / (12    + 2*1.5) )+  4;
T_aNoche  =      (deltaT) * sin(  (PI*(aNochecer-aManecer-0.1)) / (deltaT+(2*a)) ) + tempMin; //calc temp  Tdia la ultima hora del dia=aNochecer
// 20.00 T_aNoche 11,255189378349 Cº   ok excel idem

DibCircadiano();//            llama a la funcion que recorre 24 hs

 if ((hs-aManecer)<=12){// cal del incremento  
                  incremento = (hs- aManecer);  //    para AM incremento maximo de 12
                            }                //considera el fotoperiodo de 12hs ??? 
           else  {incremento =(hs- aManecer-12);//   para PM incremento maximo de 12              
                 }  
                 
  if ((hs>=aNochecer) || (hs<=aManecer)){//   (logical OR)   para detectar fotoperiodo
                dia=false;// es de noche
                        
        //        exp(n)Returns Euler's number e (2.71828...) raised to the power of the n parameter 
        //  incremento=suma de incrementos con un maximo de 12                 
        //             =      $B$4+(         H121 -   $B$4)*EXP(-$B$7*E122      /2) //hoja LEK   


   
// println("ES   DE    NOCHE-----------------------------------------------------------------");      
                   T_calActual =   tempMin+(T_aNoche-tempMin)*exp(-b   *incremento/2);//calc temp  Tnoche 
     if(test==true){  // flag para desarrollo habilita impresion en consola de variables y estados
//---------------------------------------------------
       //   calc. NOCHE= 8,672606201512 Cº excel idem,                a las : 21.10  hs 
                   println ("Anochece= ",aNochecer,"hs    con  ",T_aNoche," ºC");
                   println("TEMPERATURA a las ",hs, "  hs    CALC:", T_calActual,"ºC"); 
                   println ("Horas centecimal desde el Amanecer = ",incremento,"  hs ");//tiempo acumulado desde el inicio del dia (Amanecer)   incremento=(hs- Amanecer) --en horas centecimales--
                                     
                  // print("T_instAnterior= ",T_instAnterior,"ºC");         
                  print ("coef ajuste NOCHE= ",b);
                  //print (" avance de tiempo= ",a,"  hs ");//   avance de tiempo de calculo en minutos centecimales

                  //        calc. NOCHE= 8,672606201512 Cº excel,                a las : 21.10  hs 
                  println("deltaT =", deltaT,"ºC en un Fotoperiodo( horas de luz)de: ",fotoperiodo,"  hs ");   
                  println ( "   tempMax=",tempMax,"ºC a las : ",Hs_Tmax,"  hs "); 
                  println ("Amanece= ",aManecer,"  hs ","con TEMP AMANECER=",tempMin,"ºC (Temp.mínima)"); 
                                                
                 }  
                 
} // es de noche
 
     else  {   dia=true;// es de DIA   (B$3-B$4)*SENO((PI()*E122)       /    (B$6+2*B$8))+B$4)
                 //        y=($B$3-      $B$4)  *SENO((PI()*($E121))    / ($B$2  +2*$B$8)) +$B$4 //hoja LEK 
                   //                          incremento=suma de incrementos con un maximo de 12 
          
// println("ES   DE    DIA-----------------------------------------------------------------");
  T_calActual  = (deltaT) * sin( ((PI)*incremento) / (deltaT+(2*a)) ) + tempMin;          //calc temp  Tdia 
  
  if ( test==true) {// flag para desarrollo habilita impresion en consola de variables y estados
//---------------------------------------------------
                         println ("Amanece= ",aManecer,"  hs ","con TEMP AMANECER=",tempMin,"ºC (Temp.mínima)");  
                         println("TEMPERATURA a las ",hs, "  hs    CALC:", T_calActual,"ºC"); 
                         println ("Horas centecimal desde el Amanecer = ",incremento,"  hs ");//tiempo acumulado desde el inicio del dia (Amanecer)   incremento=(hs- Amanecer) --en horas centecimales-- 
                         
                         // print("T_instAnterior= ",T_instAnterior,"ºC");         
                         print ("coef ajuste DIA= ",a);
                         //print (" avance de tiempo= ",a,"  hs ");//   avance de tiempo de calculo en minutos centecimales
                        println("TEMPERATURA a las ",hs, "  hs    CALC:", T_calActual,"ºC"); 
                                  //        calc. DIA= 11,255189378349 Cº excel,                a las : 11.10  hs 
                                  //        calc. DIA= 15,332516442850 Cº excel,                a las : 71.10  hs 
                        
                        println("deltaT =", deltaT,"ºC en un Fotoperiodo( horas de luz SOLAR)de: ",fotoperiodo,"  hs ");   
                        println ( "   tempMax=",tempMax,"ºC a las : ",Hs_Tmax,"  hs "); 
                        println ("Anochece= ",aNochecer,"hs    con  ",T_aNoche," ºC"); //calcularlo 
                 }
        } //es de DIA  
  }//cierra if nmodo modo seleccionado
}// cierra void






void DibCircadiano(){  //funcion  DIBUJA  curva circadiana recorriendo 24 horas
  float  T_cal=-0.01;
  float  x=0;
  float  y=0;
  T_aNoche  =      (deltaT) * sin(  (PI*(aNochecer-aManecer-0.1)) / (deltaT+(2*a)) ) + tempMin; //calc temp  Tdia la ultima hora del dia=aNochecer
//println ("*********************************************temp anochecer= ", T_aNoche);
            // incremental=0.1;
for (float i = incremental; i < 23.99; i = i+incremental) {//abre   ------------------------------------- FOR hs cada 0.1 de hora
        hs=i;//hs cada 0.1 de hora
        
        dia=true;// es de DIA verdadero
          if ((hs>=aNochecer) || (hs<=aManecer)){//   (logical OR)   para detectar fotoperiodo
                  dia=false;}// es de noche
                  //amanece 8 hs   anochece 20 hs
                 //  dia 0hs     23.90hs ---> 0 12 AM   0 12 PM
                 //incremeno=00.00  a las 8.00 y a las 20.01
                 //incremento=11.99 a las 7.99 y a las 19.99
                                                                       
//calcula  INCREMENTO ciclo 12+12 hs sincronozado con fotoperiodo amanecer y atardecer
             incremento = (hs- aManecer);
        if ((incremento)<=12){// cal del incremento  
                  incremento = incremento;  //    para AM incremento maximo de 12
                            }                //considera el fotoperiodo de 12hs ??? 
           else  {incremento =(incremento-12);//   para PM incremento maximo de 12              
                 } 
            if (!dia){// es de NOCHE    (logical NOT)  
                     if (incremento<0.000){  
                    incremento = incremento+12;   }  
                  }   
//calcula  INCREMENTO ciclo 12+12 hs sincronozado con fotoperiodo amanecer y atardecer

if (!dia){// es de NOCHE (porque no es Dia jaja)  
        //        exp(n)Returns Euler's number e (2.71828...) raised to the power of the n parameter 
        //  incremento=suma de incrementos con un maximo de 12                 
        //             =       $B$4+(   H121 -   $B$4)*EXP(-$B$7*E122      /2) //hoja LEK                                        
                  T_cal=    tempMin+(T_aNoche-tempMin)*exp(-b   *incremento/2);                    //calc temp  Tnoche 
                  //println("ES   DE    NOCHE--------------------  ",incremento,"   ",hs,"   ",T_cal);
           /*calcula la curva dentro de la ventana grafica
                                        value  float: the incoming value to be converted
                                        start1  float: lower bound of the value's current range
                                        stop1  float: upper bound of the value's current range
                                        start2  float: lower bound of the value's target range
                                        stop2  float: upper bound of the value's target range
                  */
                                  y =map( T_cal,-2,35,height-130,33);//calcula la curva dentro del ALTO de la ventana
                                  x =map(i,0,24,0,width-100);//calcula la curva 24hs dentro del ANCHO de la ventana                   
           //calcula la curva dentro de la ventana grafica  
                  
                  
                  strokeWeight(4);
                  stroke(100,0,255);
                  point(x, y);//plotea el punto de la curva
                //  println(y);
           }// es de NOCHE
   
   
else  {//"ES   DE    DIA---
                  T_cal=   (deltaT) * sin( ((PI)*incremento) / (deltaT+(2*a)) ) + tempMin;          //calc temp  Tdia    
                 // println("ES   DE    DIA----------------------   ",incremento,"   ",hs,"   ",T_cal);
                                  y =map( T_cal,-2,35,height-130,33);//calcula la curva dentro del ALTO de la ventana
                                 //   .setPosition(20,30)
                                  x =map(i,0,24,0,width-100);//calcula la curva 24hs dentro del ANCHO de la ventana            
                  stroke(255,255,0);
                  point(x, y);//plotea el punto 
                 // println(y);
           }// es de DIA
   

}  //CIERRA   ------------------------------------- FOR hs cada 0.1 de hora   

}  // VOID funcion  DIBUJA curva circadiana








void tempCritica(){//nModo==4 //--dibuja grafico con --modelo TC
//*******************************************************************************************
                                           //mantiene a temp 1=s1 (defaut25) por 10 minutos 
                                           //comienza rampa a    m=0.25ºC/60sg 
                                           //limites de seguridad +55ºC  ó  -10ºC                                             
          if (nModo==4){
            myTextarea.setText("PULSAR `$´ para salir, ----------       modo Activo TCrítica "+"  "+nModo+"  10minutos a 25 y luego +/- 1ºC cada 4 minutos");//+"     "+"temperatur= "+t1 

                            fill(0,20);
                          rect(0,20,width,height-80);//limpia
                           stroke(255, 200, 0);//---  ocre  ----------
                           strokeWeight(5);  // Default
                            //line( x1,                          y1  x2,                          y2) desde hasta
                          line( 20,map(25,-10,48,height-100,62), 75,map(25,-10,48,height-100,62)); 
                          line( 20,map(s1,-10,48,height-100,62), 75,map(s1,-10,48,height-100,62)); 
                  if (s2<s1){   stroke(0, 80, 255);//---desciende  azul  ----------
                            line(75,map(s1,-10,48,height-100,62),width-50,map(-10,-10,48,height-100,62) ); 
                            strokeWeight(1);  // Default 
                          }
                            
                  else if (s2>s1){  stroke(255, 20, 0);//---asciende  rosa  ---------
                                 line(75,map(s1,-10,48,height-100,62),width-50,map(55,-10,48,height-100,62) );
                             strokeWeight(1);  // Default 
                          }
                  else if (s2==s1){   stroke(255, 200, 0);//---  ocre  ---------
                                 line(75,map(s1,-10,48,height-100,62),width-50,map(s2
                                 ,-10,48,height-100,62) );
                             strokeWeight(1);  // Default 
                          }
                   }
  }//--fin-------------------------dibuja grafico con --modelo TC
  
  
                                                                                            
                                                                                          /*
                                                                                                  noFill();
                                                                                                  //curveTightness(20); 
                                                                                                  stroke(255,255,255);
                                                                                                  beginShape();
                                                                                                  curveVertex(84,  91);
                                                                                                  curveVertex(84,  91);
                                                                                                  curveVertex(68,  19);
                                                                                                  curveVertex(21,  17);
                                                                                                  curveVertex(32, 100);
                                                                                                  curveVertex(32, 100);
                                                                                                  endShape();
                                                                                          */
                                                                                          /*
                                                                                                  curve()
                                                                                                  beginShape()
                                                                                                  endShape()
                                                                                                  vertex()
                                                                                                  bezier()
                                                                                                  quadraticVertex()
                                                                                           */
                                                                                          //https://forum.processing.org/one/topic/polynomial-function-math-urgent.html

void polinomio(){//nModo==6 //--curva definida por polinomio
//*******************************************************************************************
if (nModo==6){  
   fill(255);
//println(s1);//int del slider 1 -> temp 1                  
t1 = str(s1);//convierte un numero int en una string
  //  println(t1);
  //coloca el string en la ventana de texto=texarea-->addTextarea
   myTextarea.setText("PULSAR `$´ para salir, ----------       modo Activo Polinomio "+"  "+nModo+"       `ENTER´ acepta cada COEFICIENTE");//+"     "+"temperatur= "+t1 

COEFtodo =  COEF_X0 + ","+ COEF_X1 + ","+ COEF_X2+ ","+  COEF_X3+ ","+COEF_X4+ ","+ COEF_X5+ ","+ COEF_X6+ ","+TEMP1+ ","+ t1;
  
      // .setPosition(20,30)  
      //y= COEFtodo =  COEF_X0 + ","+ COEF_X1 + ","+ COEF_X2+ ","+  COEF_X3+ ","+COEF_X4+ ","+ COEF_X5+ ","+TEMP1+ ","+ t1;
      
      //polinomio circadiano--->  y = -0.000002x6 + 0.000263x5 - 0.010378x4 + 0.165335x3 - 0.993461x2 + 1.795195x + 4.399244   -->R² = 0.991943
      
      //y =  COEF_X0 + ","+ COEF_X1 + ","+ COEF_X2+ ","+  COEF_X3+ ","+COEF_X4+ ","+ COEF_X5+ ","+TEMP1+ ","+ t1;
      
      
      stroke(125);//parar dibujar tramas 
      strokeWeight(1);
        for (int a = 0; a <width; a+=40) { //dibuja trama Y
              line(a,0,a,height-150);
                         float  hs =map(a,0,width,0,24);//calcula la hora
                             int h= int(hs);
                         text(h+"hs",a,height-150);        
            }
            stroke(0,255,200);//parar dibujar tramas 
             for (int a = 0; a <height-150; a+=25) { //dibuja trama X
                     line(0,a,width,a);
            }           
      stroke(255,150,0); 
      strokeWeight(3);
      float x, y;
      float x6, x5, x4, x3, x2, x1, k;
      y=0.123456789;
        for (float i = 0; i < 24; i = i+0.01) {
       //  println ("BRUTO: ",i,"   ",y); 
        
        x6 =float(COEF_X6) * pow(i, 6);
        x5 =float(COEF_X5) * pow(i, 5);
        x4 =float(COEF_X4) * pow(i, 4);
        x3 =float(COEF_X3) * pow(i, 3);
        x2 = float(COEF_X2) * i * i;
        x1 = float(COEF_X1) * i;
        k =float(COEF_X0);
        y = x6 + x5+ x4 + x3 + x2 + x1 + k;
      // println ( k,x1,x2,x3,x4,x5,x6); 
      
      // y=map(y,-1000000,2000000000,height,5);//calcula la curva dentro del alto de la ventana
      
       y =map(y,-10,10,height,5);//calcula la curva dentro del ALTO de la ventana
       x =map(i,0,24,10,width);//calcula la curva 24hs dentro del ANCHO de la ventana
       
       point(x, y+100);//plotea el punto  
      // println (COEFtodo); 
      // println (x,"   ",y);
        }
     }
}
