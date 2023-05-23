# Pixie

Pixie is a pixel art editor written in C++ and SDL2 still in early stages of development

### Requirements
- Any c++ compiler thats supports c++20
- cmake >= 3.18

### TODO
- [Planned Features](planned_features.md)
- [Planned Bug fixes](planned_bugfixes.md)

### Screenshots
![](Screenshots/plain.png)
![](Screenshots/super_mushroom_in_editor.png)
![](Screenshots/super_mushroom.png)

### Building
Currently, only Linux is supported

Build and run:
```bash
git clone https://github.com/wwsmiff/pixel_art_editor
cd pixel_art_editor
cmake -S . -B build # To initialize cmake
cmake --build build # To build the project
./build/Pixie # To run the project
```

### Contributing
 - [contributing.md](contributing.md)

### Libraries used
 - [SDL2](http://libsdl.org/)
 - [gvdi](https://github.com/karnkaul/gvdi/)
 - [stb_image_writer.h](https://github.com/nothings/stb/blob/master/stb_image_write.h)
 - [portable-file-dialogs](https://github.com/samhocevar/portable-file-dialogs)
