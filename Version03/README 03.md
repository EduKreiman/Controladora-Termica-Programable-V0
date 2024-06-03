VERSION 03 AUTONOMO-CONFIGURABLE OLED: El sistema esta contenido en un microcontrolador Arduino UNO. El funcionamiento es aut�nomo y continuo, repitiendo un programa termico seleccionado, entre los que est�n rampas t�rmicas ascendentes y descendentes, temperaturas constantes y el ciclo dirario de Parton&Logan, 1980. Asimismo controla simulaci�n del ciclo de fotoperiodo diario cargando la hora de amanecer y anochecer en el sketch "parametror.ino"

La interfase de usuario consta de un display oled que junto con 3 pulsadores y un selector rotativo permiten a travez de menues sucesivos configurar todas las variables y seleccionar las rutinas termicas y el fotoperiodo.
  
Asimismo,un par de leds rojo y verde que indican el estado de enfriamiento o calentamiento respectivamente, y un tercer led que pulsa al ritmo de cada lectura de temperatura como indicador de funcionamiento correcto. La llave on/off de la fuente de alimentacion habilita el funcionamiento del equipo.

Un reloj interno (RTC), con bater�a de 10 a�os de duraci�n, entrega el input para el c�lculo de la ecuaci�n para el ciclo diario. Esto le permite al sistema soportar interrupciones de alimentaci�n, ya que el ciclo se reinicia en seg�n la hora del reloj interno. Usa un sensor de temperatura Dallas Temperature (o Maxim Systems) Modelo 18b20, cuya lectura (Ti) es comparada con la temperatura de calculo para cada instante (Tcal). El signo de Ti-Tcal dispara la rutina frio/calor, activando la rama correspondiente del puente-H seg�n la rutina seleccionada. El valor de ancho de pulso (PWM) que recibe el puente-H es funci�n del m�dulo de Ti-Tcal, corregida por la rutina PID (Proporcional, Integral, Derivada).

Esta versi�n utiliza un puente H industrial de calidad automotriz con sistemas embebidos de proteccion termica e inversion de polaridad. 
se incluye en esta version un control de corriente / potencia entregada a la placa peltier para reducir el efecto Joule en la fase de enfriamiento. este se control se realiza con un modulo sensor de corriente por efecto Hall.

El control de la temperatura se logra a trav�s de una placa peltier, tanto para el ciclo de calor como el ciclo de enfriamiento.

Referencias: Parton, W. J., & Logan, J. A. (1981). A model for diurnal variation in soil and air temperature. Agricultural Meteorology, 23, 205-216. https://doi.org/10.1016/0002-1571(81)90105-9