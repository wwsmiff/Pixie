#!/bin/sh

set -xe

# Important flag, set to 1 for additional compiler flags that
# may slow down the program but enables debugging options 
# and 0 for optimal compiler flags.
DEBUG=0

INCLUDEDIR="./include"
SRCDIR="./src"
OBJDIR="./obj"
BUILDDIR="./build"
EXE="main"

CC="g++"
if [ $DEBUG -eq 1 ]
then
  CPPFLAGS="-std=c++17 -pedantic -O0 -Wall -g -Wextra -I$INCLUDEDIR"
else
  CPPFLAGS="-std=c++17 -pedantic -O3 -Wall -I$INCLUDEDIR"
fi
LIBS="-lSDL2 -lSDL2main -lSDL2_ttf -lpthread"

build() {
  mkdir -p $OBJDIR
  for file in $SRCDIR/*.cpp
  do
    $CC $CPPFLAGS -c $file -o "$OBJDIR/$(basename -- $file).o"
  done

  mkdir -p $BUILDDIR
  $CC $CPPFLAGS $OBJDIR/* -o "$BUILDDIR/$EXE" $LIBS
}

run() {
  "$BUILDDIR/$EXE"
}

clean() {
  rm -rf $BUILDDIR $OBJDIR *.ppm *.png *.jpg *.bmp
}

"$@"
