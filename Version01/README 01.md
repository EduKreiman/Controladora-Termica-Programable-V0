VERSION 01 AUTONOMO-CONFIGURABLE: El sistema esta contenido en un microcontrolador Arduino UNO. El funcionamiento es autónomo y continuo, repitiendo un programa termico seleccionado, entre los que están rampas térmicas ascendentes y descendentes, temperaturas constantes y el ciclo dirario de Parton&Logan, 1980. Asimismo controla simulación del ciclo de fotoperiodo diario cargando la hora de amanecer y anochecer en el sketch "parametror.ino"

La interfase de usuario consta de un par de leds rojo y verde que indican el estado de enfriamiento o calentamiento respectivamente, y un tercer led que pulsa al ritmo de cada lectura de temperatura como indicador de funcionamiento correcto. La llave on/off de la fuente de alimentacion habilita el funcionamiento del equipo.

Asimismo de incluyen un programa escrito en processing y una aplicacion para android . Al correr el programa de processing y conectarlo via puerto serial permite el monitoreo en tiempo real,la configuracion de parametros y la elección de la rutina térmica activa. eSTE mismo programa graba en el equipo donde está corriendo un archivo de registro a modo de datalogger.

Simultaneamente la aplicacion para android se conecta via Bluetooth con la controladora y permite el monitoreo en tiempo real,la configuracion de parametros y la elección de la rutina térmica activa.

Un reloj interno (RTC), con batería de 10 años de duración, entrega el input para el cálculo de la ecuación para el ciclo diario. Esto le permite al sistema soportar interrupciones de alimentación, ya que el ciclo se reinicia en según la hora del reloj interno. Usa un sensor de temperatura Dallas Temperature (o Maxim Systems) Modelo 18b20, cuya lectura (Ti) es comparada con la temperatura de calculo para cada instante (Tcal). El signo de Ti-Tcal dispara la rutina frio/calor, activando la rama correspondiente del puente-H según la rutina seleccionada. El valor de ancho de pulso (PWM) que recibe el puente-H es función del módulo de Ti-Tcal, corregida por la rutina PID (Proporcional, Integral, Derivada).

Esta versión utiliza un puente H de fabricación artesanal (DIY) a partir de componentes accesibles. El control de la temperatura se logra a través de una placa peltier, tanto para el ciclo de calor como el ciclo de enfriamiento.

Referencias: Parton, W. J., & Logan, J. A. (1981). A model for diurnal variation in soil and air temperature. Agricultural Meteorology, 23, 205-216. https://doi.org/10.1016/0002-1571(81)90105-9
