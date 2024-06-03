REM  copiar un archivo con otro nombre y con date time en el nombre

ECHO

@echo off 

echo %DATE%
echo %TIME%
dir c:\Users\VICTOR\Desktop\*.txt
PAUSE

Rem Lists all files with .txt extension.

rem dir E:\Users\Edu\Documents\2A-Salud\
dir E:\Users\Edu\Documents\6-DisenO\P4-bocetos\CONTROLADOR_TERMICO_CIRCADIANO_V03processing\*.txt
PAUSE
		REM sintaxis:   Xcopy c:\datalogger.txt c:\desktop\		
rem   Xcopy C:\Users\Formato\Documents\P4-bocetos\CONTROLADOR_TERMICO_CIRCADIANO_V03processing\datalogger.txt c:\desktop\dataCOPIX-01.txt
Xcopy E:\Users\Edu\Documents\6-DisenO\P4-bocetos\CONTROLADOR_TERMICO_CIRCADIANO_V03processing\datalogger.txt c:\desktop\dataCOPIA-01.txt

Rem Lists all files with .txt extension.
dir c:\Users\VICTOR\Desktop\*.txt
PAUSE

