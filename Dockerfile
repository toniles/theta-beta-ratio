FROM ubuntu:20.04

# Evita que se solicite la configuración de la zona horaria durante la instalación
ENV DEBIAN_FRONTEND=noninteractive

# Instala las dependencias necesarias
RUN apt-get update && apt-get install -y \
    qt5-default \
    wget \
    binutils && \
    rm -rf /var/lib/apt/lists/*

# Descarga linuxdeployqt
RUN wget -P /tmp https://github.com/probonopd/linuxdeployqt/releases/download/continuous/linuxdeployqt-continuous-x86_64.AppImage \
    && chmod a+x /tmp/linuxdeployqt-*.AppImage
