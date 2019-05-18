C:\Factory\Tools\RDMD.exe /RC out

SET RAWKEY=e80cca5f50729c8f517534c5173d7264

C:\Factory\SubTools\makeAESCluster.exe Picture.txt     out\Picture.dat     %RAWKEY% 110000000
C:\Factory\SubTools\makeAESCluster.exe Music.txt       out\Music.dat       %RAWKEY% 120000000
C:\Factory\SubTools\makeAESCluster.exe SoundEffect.txt out\SoundEffect.dat %RAWKEY% 130000000
C:\Factory\SubTools\makeAESCluster.exe Etcetera.txt    out\Etcetera.dat    %RAWKEY% 140000000

COPY /B Codevil\Release\Codevil.exe out\Codevil.exe

out\Codevil.exe /L
IF ERRORLEVEL 1 START ?_LOG_ENABLED

C:\Factory\Tools\xcp.exe doc out

C:\Factory\SubTools\zip.exe /G out Codevil
C:\Factory\Tools\summd5.exe /M out

PAUSE
