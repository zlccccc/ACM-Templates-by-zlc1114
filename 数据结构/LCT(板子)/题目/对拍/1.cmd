@echo off
:start
1.exe>1.txt
A.exe<1.txt>2.txt
B.exe<1.txt>3.txt
fc /n 2.txt 3.txt
if not errorlevel 1 goto start
pause