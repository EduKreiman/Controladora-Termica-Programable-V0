
//      leeStepper((X, Y);
void leeStepper(int _Columna,int _Fila){//-----------------------------
newPosition = myEnc.read()/4;  //numero de pulso del stepper rotativo sobre coodenadas de  Tinstant
            oled.setCursor(_Columna,_Fila);//Column is expressed in pixels, but Row in rows of 8 pixels.     
                  oled.print(F("    "));//limpia campo
                  oled.setCursor(_Columna,_Fila);
                  oled.print(newPosition);// sobreimprime nuevo valor
          if (newPosition != oldPosition) {
                  oldPosition = newPosition;  
            oled.setCursor(_Columna,_Fila);     
                  oled.print(F("    "));//limpia campo
            oled.setCursor(_Columna,_Fila);
                  oled.print(newPosition);// sobreimprime nuevo valor
                  delay(500);
           }
 }//------------------fin----leeStepper()-------------------


 //                   Columna,  Fila,          S,    I
 //                   0 a 239, 0 a 7  , 1 ó 2,  0 ó  1
void leeStepper(int _Columna,int _Fila,int _S,bool _I){//-----------------------------
newPosition = myEnc.read()/4;  //numero de pulso del stepper rotativo sobre coodenadas de  Tinstant
/*
oled.set1X();
    oled.setCursor(0, 7);       //Column is expressed in pixels, but Row in rows of 8 pixels.
    oled.setInvertMode(1 % 2);  //1 es true
    //oled.println("012345678901234567890");//setCursor(0, 8)
     oled.setInvertMode(1%2);//1 es true
     oled.setInvertMode(0%2);//0 es false */

    if (_S== 1) {//tamaño 1/8  chico
    oled.set1X(); }

    if (_S== 2) {//tamaño 1/4  grande
    oled.set2X(); }

    if (_I== false) {//0 normal((NO inverso)
    oled.setInvertMode(0%2);//0 es false
    }

    if (_I== true) {//1  inverso
    oled.setInvertMode(1%2);//1 es true
      }

            oled.setCursor(_Columna,_Fila);//Column is expressed in pixels, but Row in rows of 8 pixels.     
                  oled.print(F("        "));//limpia campo
                  oled.setCursor(_Columna,_Fila);
                  oled.print(newPosition,0);// sobreimprime nuevo valor
          if (newPosition != oldPosition) {
                  oldPosition = newPosition;  
            oled.setCursor(_Columna,_Fila);     
                  oled.print(F("        "));//limpia campo
            oled.setCursor(_Columna,_Fila);
                  oled.print(newPosition);// sobreimprime nuevo valor
                  delay(200);
           }
           //oled.setInvertMode(0%2);//0 es false
           //oled.set1X();//tamaño 1/8  chico
 }//------------------fin----leeStepper()-------------------




   
