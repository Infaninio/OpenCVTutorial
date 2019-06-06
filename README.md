# OpenCVTutorial
Tutorials of the OpenCV Project


## OpoenCV Installation Linux(Beispiel, Ubuntu 18.04)

Updaten des OS
```bash
sudo apt-get update
sudo apt-get upgrade
```

###Installation der benötigten Zusatzpakete
```bash
sudo apt-get install build-essential unzip pkg-config
sudo apt-get install libjpeg-dev libpng-dev libtiff-dev

sudo apt-get install libavcodec-dev libavformat-dev libswscale-dev libv4l-dev
sudo apt-get install libxvidcore-dev libx264-dev

sudo apt-get install libgtk-3-dev
sudo apt-get install libatlas-base-dev gfortran

sudo apt-get install python3-dev
```

###Installation von Git und Cmake
```bash
sudo apt-get install git
sudo apt-get install cmake
```

###Erstellen der Build Umgebung
```bash
mkdir opencv_build
cd opencv_build


###Klonen des OpenCV Git Repositories
```bash
git clone https://github.com/opencv/opencv.git
git clone https://github.com/opencv/opencv_contrib.git
```
```bash
cd opencv
mkdir build
cd build
```


###Konfiguration des Builds mit cmake
Weitere Parameter und Konfigurationsmöglichkeiten (z.B. CUDA) können unter docs.opencv.org eingesehen werden.
Eine möglichst Einfache Einstellung wurde hier verwendet.
```bash
cmake -D CMAKE_BUILD_TYPE=RELEASE \
    -D CMAKE_INSTALL_PREFIX=/usr/local \
    -D INSTALL_C_EXAMPLES=ON \
    -D INSTALL_PYTHON_EXAMPLES=ON \
    -D OPENCV_GENERATE_PKGCONFIG=ON \
    -D OPENCV_EXTRA_MODULES_PATH=~/opencv_build/opencv_contrib/modules \
    -D BUILD_EXAMPLES=ON ..
```

###Build Prozess starten
Mithilfe von `nproc` kann die Anzahl der verfügbaren threads angezeigt werden. Die Anzahl wird hinter dem folgenden -j angegeben. Hier 4
```bash
make -j4
sudo make install
```


###Zum Überprüfen der Installation
```bash
pkg-config --modversion opencv4
```