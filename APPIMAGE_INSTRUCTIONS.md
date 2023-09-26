
# Regeneración del AppImage para el Proyecto ThetaBetaRatioCalculator

Este documento proporciona instrucciones detalladas sobre cómo regenerar el AppImage para el proyecto.

## 1. Compilación del Proyecto

1. Asegúrate de estar en la raíz del proyecto, y navega a la carpeta `src`:
    ```bash
    cd src
    ```

2. Genera el `Makefile` en la carpeta `build`:
    ```bash
    qmake ThetaBetaRatioCalculator.pro -o ../build/Makefile
    ```

3. Navega a la carpeta `build`:
    ```bash
    cd ../build
    ```

4. Compila el proyecto:
    ```bash
    make
    ```

## 2. Preparación del Directorio AppDir

1. Desde la raíz del proyecto, navega a la carpeta `appimage`:
    ```bash
    cd appimage
    ```

2. Copia el binario compilado a `AppDir/usr/bin`:
    ```bash
    cp ../build/ThetaBetaRatioCalculator AppDir/usr/bin/
    ```

## 3. Generación del AppImage

1. Si no tienes `linuxdeployqt`, descárgalo y hazlo ejecutable:
    ```bash
    wget -c "https://github.com/probonopd/linuxdeployqt/releases/download/continuous/linuxdeployqt-continuous-x86_64.AppImage" -O linuxdeployqt
    chmod a+x linuxdeployqt
    ```

2. Usa `linuxdeployqt` para generar el AppImage:
    ```bash
    ./linuxdeployqt AppDir/usr/share/applications/*.desktop -appimage
    ```

Esto generará un nuevo archivo AppImage en tu directorio actual. Ahora puedes distribuir este archivo AppImage y los usuarios podrán ejecutar tu aplicación en muchas distribuciones de Linux sin necesidad de instalar dependencias adicionales.
