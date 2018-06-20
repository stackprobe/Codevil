C:\Factory\Tools\RDMD.exe /RC out

COPY /B Codevil\Release\Codevil.exe out\Codevil.exe

C:\Factory\Tools\xcp.exe doc out

C:\Factory\SubTools\zip.exe /G out Codevil
C:\Factory\Tools\summd5.exe /M out

PAUSE
