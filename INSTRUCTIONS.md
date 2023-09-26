
# Ejecución y Recompilación del Proyecto ThetaBetaRatioCalculator

Este documento proporciona instrucciones sobre cómo ejecutar y recompilar el proyecto.

## 1. Ejecutar el Proyecto

Para ejecutar el proyecto por primera vez, sigue estos pasos desde la raíz del proyecto:

1. Navega a la carpeta `src`:
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

5. Ejecuta el binario generado:
    ```bash
    ./ThetaBetaRatioCalculator
    ```

## 2. Recompilar el Proyecto

Si has hecho cambios en el código y necesitas recompilar el proyecto, sigue estos pasos desde la raíz del proyecto:

1. Navega a la carpeta `build`:
    ```bash
    cd build
    ```

2. Compila el proyecto:
    ```bash
    make clean
    make
    ```

3. Ejecuta el binario generado:
    ```bash
    ./ThetaBetaRatioCalculator
    ```

Con estos pasos, podrás ejecutar y recompilar el proyecto cada vez que hagas cambios en el código fuente.
