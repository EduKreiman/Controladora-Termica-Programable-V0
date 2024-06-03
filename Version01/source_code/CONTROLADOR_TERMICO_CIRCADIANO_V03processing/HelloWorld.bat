
@ECHO OFF




@ECHO OFF

ECHO Hello World! Your first batch file was printed on the screen successfully. 

PAUSE



		Rem   RENAME [drive:][path][directoryname1 | filename1] [directoryname2 | filename2]
rename "TESTA.txt" "TESTB.txt"



		Rem   Example
@echo off 
echo %DATE%
		Rem Output
		Rem The current date will be displayed in the command prompt. For example,

		Rem Mon 12/28/2015
@echo off 
echo %TIME%
------------------------
@echo off
cd
	Rem Copies lists.txt to the present working directory.
	Rem If there is no destination identified , it defaults to the present working directory.
copy c:\lists.txt

	Rem The file lists.txt will be copied from C:\ to C:\tp location
copy C:\lists.txt c:\tp

	Rem  The  command will copy the file lists.txt to the tp folder.
	Rem sintax:   Xcopy [source][destination]

Xcopy c:\lists.txt c:\tp\

	Rem Quotation marks are required if the file name contains spaces
copy “C:\My File.txt”

	Rem Copies all the files in F drive which have the txt file extension to the current working directory copy
F:\*.txt
	Copies all files from dirA to dirB. Note that directories nested in dirA will not be copied
copy C:\dirA dirB

	Rem  The  command will copy the file lists.txt to the tp folder.
	Rem sitax:   Xcopy [source][destination]

Xcopy c:\lists.txt c:\tp\

