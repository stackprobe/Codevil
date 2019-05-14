C:\Factory\Tools\RDMD.exe /RC out

C:\Factory\SubTools\makeDonutCluster.exe Picture.txt     out\Picture.dat
C:\Factory\SubTools\makeDonutCluster.exe Music.txt       out\Music.dat
C:\Factory\SubTools\makeDonutCluster.exe SoundEffect.txt out\SoundEffect.dat
C:\Factory\SubTools\makeDonutCluster.exe Etcetera.txt    out\Etcetera.dat

COPY /B Donut2\Donut2\bin\Release\Donut2.exe out
COPY /B Donut2\Donut2\bin\Release\Chocolate.dll out
COPY /B Donut2\Donut2\bin\Release\DxLib.dll out
COPY /B Donut2\Donut2\bin\Release\DxLib_x64.dll out
COPY /B Donut2\Donut2\bin\Release\DxLibDotNet.dll out

C:\Factory\Tools\xcp.exe res out

C:\Factory\SubTools\zip.exe /G out Donut2
C:\Factory\Tools\summd5.exe /M out

PAUSE
