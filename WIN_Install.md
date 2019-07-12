#Installation von OpenCV in Windows

Leider Noch nicht Funktionsfähig, Laden der DLLs fehlt.

##Vorausetzungen
* Visual Studio 2019 Community
* GitHub Erweiterung für Visual Studio 2019 zu finden unter https://marketplace.visualstudio.com/items?itemName=GitHub.GitHubExtensionforVisualStudio



##Offizielles Tutorial
 https://docs.opencv.org/3.4/d3/d52/tutorial_windows_install.html
 
 
 ##Herunterladen der OpenCV-Verzeichnise
 Um es so einfach wie möglich zu gestalten, werden immer vorkompilierte Librarys verwendet. 
 Diese können unter folgendem Link heruntergeladen werden:
  https://sourceforge.net/projects/opencvlibrary/
  Die .exe Datei kann nun an einem beliebigen Ort entpackt werden. Dieser Ort wird im System als 
  Umgebungsvariable hinterlegt. In meinem Fall liegt das entpackte Archiv unter D:\OpenCV, 
  woraus sich folgender Pfad ergibt.
  
  ```bash
  setx -m OPENCV_DIR D:\OpenCV\opencv\build\x64\vc15
  ```
  
##Starten von Visualstudio
Im Auswahlmenü auf Code klonen oder auschecken
URL zu diesem Repository eingeben und klonen. Nun muss oben bei dem grünen "Play" Button ein Startelement
ausgewählt werden. In diesem Fall "DisplayImage.exe" (Weitere könnnen Folgen). Das Projekt kann 
gebaut werden. Bei der Ausführung kommt es noch zum Abbruch da die Dynamic Link Libraries fehlen.
Das Laden dieser Dateien muss noch in den C++-Code integriert werden.


##Workaround DLL
Die DLL Dateien welche in dem OpenCV verzeichnis unter /build/x64/vc15/bin zu finden sind in
den /bin Ordner des Repos kopieren.