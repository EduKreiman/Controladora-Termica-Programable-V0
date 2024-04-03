# Controladora-Térmica-Programable
Es un desarrollo con varias versiones  que crecen en prestaciones y complejidad.
Todas las versiones basicamente como su nombre lo indica son capaces de controlar la energia que entrega una fuente dealimentacion para obtener una respuesta termica a lo largo del tiempo de una placa Peltier.
El uso incicial fue en respuesta a la necesidad del Laboratorio de Evolucion de la Facultad de Ciencias Exactas de la UNBA para estudiar la respuesta termica, el desarrollo y su adaptacion en ciertos insectos (vg.: drosofila melanogaster),
que sirven de modelos de estudio.

VERSION 00  AUTONOMO-FIJO
El sistema esta contenido en un microcontrolador Arduino UNO.
Funcionamiento es autónomo y continuo, repitiendo un programa termico circadiano que sigue modelo de Parton&Logan, 1980.
Un reloj interno (RTC), con batería de  10 años de duración, entrega los datos que sirven de input para el cálculo de la ecuación para la curva circadiana.
Esto le permite al sistema soportar interrupciones de alimentación, ya que el ciclo se reinicia en según la hora del reloj interno.
Usa un sensor de temperatura DallasTemperature (o Maxim Systems) Modelo 18b20, cuya lectura (Ti) es comparada con la temperatura de calculo para cada instante (Tcal), 
El signo de (Ti-Tcal) dispara la rutina frio/calor, activando la rama correspondiente del puente-H. 
El módulo de (Ti-Tcal) es entregado a la rutina PID que regula el valor de ancho de pulso (PWM) del punte-H. 
Esta versión utiliza un puente H de componentes discretos de construccion sencilla.
El control de la temperatura se logra a través de una placa peltier, tanto para el ciclo de calor como el ciclo de enfriamiento.
Los seteos iniciales fijos se alojan en un sketch independiente que se puede modificar desde el IDE de arduino

La interfase de usuario:
consta de un par de leds (rojo y verde) que indican el estado de enfriamiento o calentamiento, 
otro led que pulsa al rimo de cada lectura de temperatura como indicador de funcionamiento correcto. 
La llave on/off de la Fuente de alimentacion habilita el funcionamiento del equipo.

