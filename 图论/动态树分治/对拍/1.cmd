@echo off
:start
1.exe>1.txt
@echo testing
A.exe<1.txt>2.txt
@echo print A OK
B.exe<1.txt>3.txt
@echo print B OK
fc /n 2.txt 3.txt
if not errorlevel 1 goto start
pause