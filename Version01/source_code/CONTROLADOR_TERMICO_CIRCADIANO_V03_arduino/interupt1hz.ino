/******interrupts1Hz.ino *****************************************************************
Combinando RTClib con las funciones de temporización avr-libc
    ================================================== =

La forma estándar de obtener la hora y la fecha actuales con RTClib es
llamar al
método now() de la clase RTC apropiada. 
Esto, sin embargo, es algo lento, ya que implica comunicarse con el RTC a través del bús I2C

Un método alternativo, más ligero, consiste en configurar el RTC para 
entregar pulso 1 Hz   a un pin de interrupción y 
contando los segundos en el manejador de interrupciones. 
El cronometraje es entonces enteramente manejado en el Arduino, 
La comunicación I2C con el RTC solo durante la fase de inicialización.

En Arduinos basados ​​en AVR (Uno, Nano, Micro, ...), 
la biblioteca principal de Arduino está construido sobre avr-libc, 
que es una implementación del estándar Biblioteca C para la plataforma AVR. 
Esta biblioteca proporciona el estándar C funciones para manejar el tiempo:
[1] time(), gmtime(), mktime(), etc. 
El La función time() normalmente se usa para recuperar la hora actual del sistema operativo, 
pero como no tenemos sistema operativo, el avr-libc proporciona sus propias funciones no estándar para implementar una fuente de tiempo:

             - set_system_time()    inicializa la idea de la biblioteca de la hora actual
             - system_tick()        incrementa el tiempo del sistema en un segundo.

Este boceto demuestra cómo combinar RTClib y avr-libc 
para manejar el cronometraje completamente en el Arduino 
desde una interrupción entregado por el RTC:

             - RTClib se utiliza para configurar el RTC y recuperar la hora inicial
             - avr-libc se usa para el cronometraje regular

Este boceto solo funciona en Arduinos basados ​​en AVR, ya que se basa en
funciones no estándar proporcionadas por avr-libc.
*/
