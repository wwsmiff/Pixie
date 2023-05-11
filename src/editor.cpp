#include <SDL2/SDL.h>
#include <cstdlib>
#include <fstream>
#include <iostream>

#include "editor.h"
#include "export.h"
#include "macros.h"
#include "ui/ui_button.h"
#include "ui/ui_color_palette.h"
#include "ui/ui_size.h"
#include "ui/ui_window.h"

bool Editor::running = true;
Editor::Editor()
    : _window("Editor", UISize(WINDOW_WIDTH, WINDOW_HEIGHT), nullptr),
      _canvasSize(512, 512), _blockSize(16), _scale(1),
      _grid((this->_canvasSize.w / this->_blockSize.w) *
                (this->_canvasSize.h / this->_blockSize.h),
            0xffffffff)
{
  /* Do not disable compositor in Xorg */
  putenv((char *)"SDL_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR=0");

  if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
  {
    std::cerr << "Failed to initialize SDL2, " << SDL_GetError() << std::endl;
    exit(1);
  }

  if (TTF_Init() != 0)
  {
    std::cerr << "Failed to initialize SDL2_ttf, " << TTF_GetError()
              << std::endl;
    exit(1);
  }

  for (auto &x : this->_grid)
    x = 0x00000000;

  this->mainloop();
}

Editor::~Editor() { SDL_Quit(); }

void Editor::draw()
{
  /* Grid */
  uint32_t startX = 100 /* * this->_scale */;
  uint32_t startY = 100 /* * this->_scale */;

  for (uint32_t y = 0; y < (this->_canvasSize.h); y += this->_blockSize.h)
  {
    for (uint32_t x = 0; x < (this->_canvasSize.w); x += this->_blockSize.w)
    {
      SDL_Rect tmp = {x + startX, y + startY, this->_blockSize.w,
                      this->_blockSize.h};
      UIColor current =
          this->_grid.at((y / this->_blockSize.h) *
                             (this->_canvasSize.w / this->_blockSize.w) +
                         (x / this->_blockSize.w));
      if (current.hex())
      {
        SDL_SetRenderDrawColor(this->_window._renderer, current.r, current.g,
                               current.b, current.a);
        SDL_RenderFillRect(this->_window._renderer, &tmp);
      }
    }
  }

  SDL_SetRenderDrawColor(this->_window._renderer, 0, 0, 0, 255);
  for (uint32_t i = 0; i < (this->_canvasSize.h + this->_blockSize.h);
       i += (this->_blockSize.h * this->_scale))
    SDL_RenderDrawLine(this->_window._renderer, startY, i + startY,
                       this->_canvasSize.w + startY, i + startY);
  for (uint32_t i = 0; i < (this->_canvasSize.w + this->_blockSize.w);
       i += (this->_blockSize.w * this->_scale))
    SDL_RenderDrawLine(this->_window._renderer, i + startX, startX, i + startX,
                       this->_canvasSize.h + startX);
}

void Editor::update() {}

void Editor::save()
{
  std::ofstream savefile("save.pixie");
  savefile << this->_canvasSize.w << '\n';
  savefile << this->_canvasSize.h << '\n';

  for (const auto &x : this->_grid)
    savefile << x.hex() << '\n';

  savefile.close();
}

void Editor::open()
{
  std::ifstream savefile("save.pixie");
  uint32_t width = 0, height = 0;
  std::string line;
  std::getline(savefile, line);
  width = std::stoul(line);
  std::getline(savefile, line);
  height = std::stoul(line);
  this->_grid.clear();
  this->_grid.resize(width * height);
  size_t counter = 0;
  while (std::getline(savefile, line))
  {
    this->_grid.at(counter) = UIColor(std::stoul(line));
    counter++;
  }

  savefile.close();
}

void Editor::mainloop()
{
  SDL_Event event;
  UIWindow testWindow("Tools", UISize(600, 800), &event);
  testWindow.setFont("Arial/ARIAL.TTF", 32);

  UIColorPalette palette =
      UIColorPalette(&testWindow, "palettes/sweetie-16.colors",
                     UIPosition(10, 10), UISize(8, 2), UISize(30), 0);
  UIColorPalette palette2 =
      UIColorPalette(&testWindow, "palettes/lost-century.colors",
                     UIPosition(10, 110), UISize(8, 2), UISize(30), 0);
  UIColorPalette palette3 =
      UIColorPalette(&testWindow, "palettes/tempoppy-witchy-muted.colors",
                     UIPosition(10, 210), UISize(16, 2), UISize(30), 0);
  UIButton clearButton =
      UIButton(&testWindow, "Clear", UIPosition(100, 500), UISize(70, 35),
               UIColor(0xFFFFFFFF), UIColor(0x2a2a2aFF), UIColor(0xFFFFFFFF));
  UIButton exportPPMButton = UIButton(
      &testWindow, "Export to PPM", UIPosition(100, 550), UISize(130, 32),
      UIColor(0xFFFFFFFF), UIColor(0x2a2a2aFF), UIColor(0xFFFFFFFF));
  UIButton exportPNGButton = UIButton(
      &testWindow, "Export to PNG", UIPosition(250, 550), UISize(130, 32),
      UIColor(0xFFFFFFFF), UIColor(0x2a2a2aFF), UIColor(0xFFFFFFFF));
  UIButton openButton =
      UIButton(&testWindow, "Open", UIPosition(100, 600), UISize(75, 35),
               UIColor(0xFFFFFFFF), UIColor(0x2a2a2aFF), UIColor(0xFFFFFFFF));
  UIButton saveButton =
      UIButton(&testWindow, "Save", UIPosition(200, 600), UISize(75, 35),
               UIColor(0xFFFFFFFF), UIColor(0x2a2a2aFF), UIColor(0xFFFFFFFF));

  while (this->running)
  {
    if (SDL_PollEvent(&event))
    {
      this->_window.handleEvents();

      testWindow.handleEvents();
      palette.update();
      palette2.update();
      palette3.update();

      if (event.window.windowID == SDL_GetWindowID(this->_window._window))
      {
        if (event.window.event == SDL_WINDOWEVENT_CLOSE)
          this->running = false;
        if (event.type == SDL_KEYDOWN)
        {
          switch (event.key.keysym.sym)
          {
          case SDLK_DOWN:
            this->_scale = (this->_scale > 1) ? this->_scale - 1 : 1;
            break;
          case SDLK_UP:
            this->_scale = (this->_scale <= 10) ? this->_scale + 1 : 10;
            break;
          }
        }

        if (event.type == SDL_MOUSEBUTTONDOWN)
        {

          if (this->_window._mouseX > 100 &&
              this->_window._mouseX < (100 + this->_canvasSize.w) &&
              this->_window._mouseY > 100 &&
              this->_window._mouseY <
                  (100 +
                   this->_canvasSize
                       .h)) /* A very temporary and crappy fix for preventing a
                               crash when clicking outside the grid */
          {
            if (event.button.button == SDL_BUTTON_LEFT)
            {
              UIColor &current = this->_grid.at(
                  ((this->_window._mouseY - 100) / this->_blockSize.h) *
                      (this->_canvasSize.w / this->_blockSize.w) +
                  ((this->_window._mouseX - 100) / this->_blockSize.w));
              current = UIColorPalette::selectedColor;
            }

            else if (event.button.button == SDL_BUTTON_RIGHT)
            {
              UIColor &current = this->_grid.at(
                  ((this->_window._mouseY - 100) / this->_blockSize.h) *
                      (this->_canvasSize.w / this->_blockSize.w) +
                  ((this->_window._mouseX - 100) / this->_blockSize.w));
              current = 0x00000000;
            }
          }
        }
      }

      if (openButton.clicked())
        this->open();

      if (saveButton.clicked())
        this->save();

      if (clearButton.clicked())
        for (auto &x : this->_grid)
          x = 0x00000000;

      if (exportPPMButton.clicked())
      {
        Image input(this->_canvasSize.w / this->_blockSize.w,
                    this->_canvasSize.h / this->_blockSize.h);

        Image::fromRaw(input, this->_grid);
        Image target = Image::upscale(input, this->_blockSize.w);
        Image::exportToPPM(target, "output.ppm");
      }

      if (exportPNGButton.clicked())
      {
        Image input(this->_canvasSize.w / this->_blockSize.w,
                    this->_canvasSize.h / this->_blockSize.h);

        Image::fromRaw(input, this->_grid);
        Image target = Image::upscale(input, this->_blockSize.w);
        Image::exportToPNG(target, "output.png");
      }
    }

    SDL_SetRenderDrawColor(this->_window._renderer, 255, 255, 255, 255);
    SDL_RenderClear(this->_window._renderer);

    testWindow.setBackground(UIColor(0x1a1a1aff));

    palette.draw();
    palette2.draw();
    palette3.draw();
    clearButton.draw();
    exportPPMButton.draw();
    exportPNGButton.draw();
    saveButton.draw();
    openButton.draw();

    testWindow.draw();

    this->draw();

    SDL_RenderPresent(this->_window._renderer);
  }
}
