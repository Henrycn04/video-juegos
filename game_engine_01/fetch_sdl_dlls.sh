#!/bin/bash

set -e

# Versión de SDL que quieres usar
SDL_VERSION=2.28.5
SDL_IMAGE_VERSION=2.8.2
SDL_TTF_VERSION=2.22.0
SDL_MIXER_VERSION=2.8.0

# Directorio de salida
DIST_DIR=dist
mkdir -p $DIST_DIR

# URLs oficiales de las SDL DLLs para Windows (64-bit)
SDL_BASE_URL=https://github.com/libsdl-org
SDL_ZIP_LINKS=(
    "$SDL_BASE_URL/SDL/releases/download/release-$SDL_VERSION/SDL2-devel-$SDL_VERSION-mingw.zip"
    "$SDL_BASE_URL/SDL_image/releases/download/release-$SDL_IMAGE_VERSION/SDL2_image-devel-$SDL_IMAGE_VERSION-mingw.zip"
    "$SDL_BASE_URL/SDL_ttf/releases/download/release-$SDL_TTF_VERSION/SDL2_ttf-devel-$SDL_TTF_VERSION-mingw.zip"
    "$SDL_BASE_URL/SDL_mixer/releases/download/release-$SDL_MIXER_VERSION/SDL2_mixer-devel-$SDL_MIXER_VERSION-mingw.zip"
)

# Directorio para headers y bibliotecas
LIBS_DIR=./libs/SDL2
mkdir -p $LIBS_DIR/include $LIBS_DIR/lib

echo "Descargando y extrayendo DLLs, headers y bibliotecas..."
for ZIP_URL in "${SDL_ZIP_LINKS[@]}"; do
    ZIP_NAME=$(basename "$ZIP_URL")
    curl -LO "$ZIP_URL"
    unzip -o "$ZIP_NAME" -d tmp
done

# Copiar DLLs a dist/
find tmp -name "*.dll" -exec cp {} "$DIST_DIR/" \;

# Copiar headers y bibliotecas a libs/SDL2/
find tmp -name "include" -type d -exec cp -r {} $LIBS_DIR/ \;
find tmp -name "lib" -type d -exec cp -r {} $LIBS_DIR/ \;

# También copiar el ejecutable compilado (si existe)
if [ -f game_engine.exe ]; then
    cp game_engine.exe "$DIST_DIR/"
fi

# Limpieza
rm -rf tmp
rm -f SDL2*.zip

echo "Listo. DLLs copiados a $DIST_DIR/, headers y bibliotecas a $LIBS_DIR/"
