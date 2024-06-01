void Voltimetro(){  //El código lee el voltaje en analogPin y lo muestra.
int sensorValue; // variable que almacena el valor raw (0 a 1023) 
//float tension=0; // variable que almacena el voltaje (0.0 a 25.0) 

   sensorValue = analogRead(pinPOTE); //realizar la lectura    pinPOTE es A3 
  /* 5 voltios / 1024 unidades o , 0,0049 voltios (4,9 mV) por unidad.
COMANDO analogReference(type)   Configura el voltaje de referencia utilizado para la entrada analógica 
(es decir, el valor utilizado como la parte superior del rango de entrada). 
Las opciones son:EXTERNAL: 
the voltage applied to the AREF pin (0 to 5V only) is used as the reference.
Don’t use anything less than 0V or more than 5V for external reference voltage on the AREF pin! 
If you’re using an external reference on the AREF pin, 
you must set the analog reference to EXTERNAL before calling analogRead().
   */ 
       //    map       (value, fromLow, fromHigh,    toLow,  toHigh)    
 tension = fmap(sensorValue, 0,           1023,      0.0,    16.5254); //llama  funcion para  cambiar escala a 0.0 - 25.0 
   
 //  tension = fmap(sensorValue, 0,           1023,      0.0,    20.6098); //llama  funcion para  cambiar escala a 0.0 - 25.0 
   
   
   Serial.println(value); // mostrar el valor por serial 
   delay(1000); } 

   //The map() function uses integer math so will not generate fractions
   //if your project requires precise calculations 
   //(e.g. voltage accurate to 3 decimal places), please consider avoiding map() and 
   //implementing the calculations manually in your code yourself.
   
   // funcion para cambio de escala MAPEO entre floats 
   //    map   (value, fromLow,          fromHigh,         toLow,        toHigh)
   float fmap(float x, float in_min, float in_max, float out_min, float out_max) 
   { return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min; }
