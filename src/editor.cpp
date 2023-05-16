#include <SDL2/SDL.h>
#include <cstdlib>
#include <fstream>
#include <iostream>

#include <gvdi/gvdi.hpp>

#include "editor.h"
#include "export.h"
#include "macros.h"

namespace Pixie
{
bool Editor::running = true;
Editor::Editor()
    : mWindow("Editor", Pixie::Size(WINDOW_WIDTH, WINDOW_HEIGHT)),
      mCanvasSize(512, 512), mBlockSize(16), mScale(1),
      mGrid((this->mCanvasSize.w / this->mBlockSize.w) *
                (this->mCanvasSize.h / this->mBlockSize.h),
            0xffffffff)
{
  /* Do not disable compositor in Xorg */
  putenv((char *)"SDL_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR=0");

  if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
  {
    std::cerr << "Failed to initialize SDL2, " << SDL_GetError() << std::endl;
    exit(1);
  }

  for (auto &x : this->mGrid)
    x = 0x00000000;

  this->mainloop();
}

Editor::~Editor() { SDL_Quit(); }

void Editor::draw()
{
  /* Grid */
  uint32_t startX = 100 /* * this->mScale */;
  uint32_t startY = 100 /* * this->mScale */;

  for (uint32_t y = 0; y < (this->mCanvasSize.h); y += this->mBlockSize.h)
  {
    for (uint32_t x = 0; x < (this->mCanvasSize.w); x += this->mBlockSize.w)
    {
      SDL_Rect tmp = {static_cast<int32_t>(x + startX),
                      static_cast<int32_t>(y + startY),
                      static_cast<int32_t>(this->mBlockSize.w),
                      static_cast<int32_t>(this->mBlockSize.h)};
      Pixie::Rgba current =
          this->mGrid.at((y / this->mBlockSize.h) *
                             (this->mCanvasSize.w / this->mBlockSize.w) +
                         (x / this->mBlockSize.w));
      if (current.hex())
      {
        SDL_SetRenderDrawColor(this->mWindow.mRenderer.get(), current.r,
                               current.g, current.b, current.a);
        SDL_RenderFillRect(this->mWindow.mRenderer.get(), &tmp);
      }
    }
  }

  SDL_SetRenderDrawColor(this->mWindow.mRenderer.get(), 0, 0, 0, 255);
  for (uint32_t i = 0; i < (this->mCanvasSize.h + this->mBlockSize.h);
       i += (this->mBlockSize.h * this->mScale))
    SDL_RenderDrawLine(this->mWindow.mRenderer.get(), startY, i + startY,
                       this->mCanvasSize.w + startY, i + startY);
  for (uint32_t i = 0; i < (this->mCanvasSize.w + this->mBlockSize.w);
       i += (this->mBlockSize.w * this->mScale))
    SDL_RenderDrawLine(this->mWindow.mRenderer.get(), i + startX, startX,
                       i + startX, this->mCanvasSize.h + startX);
}

void Editor::update() {}

void Editor::save()
{
  std::ofstream savefile("save.pixie");
  savefile << this->mCanvasSize.w << '\n';
  savefile << this->mCanvasSize.h << '\n';

  for (const auto &x : this->mGrid)
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
  this->mGrid.clear();
  this->mGrid.resize(width * height);
  size_t counter = 0;
  while (std::getline(savefile, line))
  {
    this->mGrid.at(counter) = Pixie::Rgba(std::stoul(line));
    counter++;
  }

  savefile.close();
}

void Editor::mainloop()
{
  SDL_Event event;
  gvdi::Instance mainInstance{{600, 800}, "Tools"};

  while (this->running)
  {
    gvdi::Frame frame{mainInstance};

    if (SDL_PollEvent(&event))
    {
      this->mWindow.handleEvents();
      if (event.window.windowID == SDL_GetWindowID(this->mWindow.mWindow.get()))
      {
        if (event.window.event == SDL_WINDOWEVENT_CLOSE)
          this->running = false;
        if (event.type == SDL_KEYDOWN)
        {
          switch (event.key.keysym.sym)
          {
          case SDLK_DOWN:
            this->mScale = (this->mScale > 1) ? this->mScale - 1 : 1;
            break;
          case SDLK_UP:
            this->mScale = (this->mScale <= 10) ? this->mScale + 1 : 10;
            break;
          }
        }

        if (event.type == SDL_MOUSEBUTTONDOWN)
        {

          if (this->mWindow.mMouseX > 100 &&
              this->mWindow.mMouseX < (100 + this->mCanvasSize.w) &&
              this->mWindow.mMouseY > 100 &&
              this->mWindow.mMouseY <
                  (100 +
                   this->mCanvasSize
                       .h)) /* A very temporary and crappy fix for preventing a
                               crash when clicking outside the grid */
          {
            if (event.button.button == SDL_BUTTON_LEFT)
            {
              Pixie::Rgba &current = this->mGrid.at(
                  ((this->mWindow.mMouseY - 100) / this->mBlockSize.h) *
                      (this->mCanvasSize.w / this->mBlockSize.w) +
                  ((this->mWindow.mMouseX - 100) / this->mBlockSize.w));
              current = 0xFF0000FF;
            }

            else if (event.button.button == SDL_BUTTON_RIGHT)
            {
              Pixie::Rgba &current = this->mGrid.at(
                  ((this->mWindow.mMouseY - 100) / this->mBlockSize.h) *
                      (this->mCanvasSize.w / this->mBlockSize.w) +
                  ((this->mWindow.mMouseX - 100) / this->mBlockSize.w));
              current = 0x00000000;
            }
          }
        }
      }
    }

    ImGui::Begin("Tools", nullptr);

    if (ImGui::Button("Clear"))
    {
      for (auto &x : this->mGrid)
        x = 0x00000000;
    }
    if (ImGui::Button("Export to PPM"))
    {
      Pixie::Image input(this->mCanvasSize.w / this->mBlockSize.w,
                         this->mCanvasSize.h / this->mBlockSize.h);

      Pixie::Image::fromRaw(input, this->mGrid);
      ImGui::Begin("Finished exporting!");
      Pixie::Image target = Image::upscale(input, this->mBlockSize.w);
      Pixie::Image::exportToPPM(target, "output.ppm");
      ImGui::OpenPopup("Message");
      if (ImGui::BeginPopup("Message"))
      {
        ImGui::Text("Finished exporting!");
        ImGui::EndPopup();
      }
    }

    if (ImGui::Button("Export to PNG"))
    {
      Pixie::Image input(this->mCanvasSize.w / this->mBlockSize.w,
                         this->mCanvasSize.h / this->mBlockSize.h);

      Pixie::Image::fromRaw(input, this->mGrid);
      Pixie::Image target = Image::upscale(input, this->mBlockSize.w);
      Pixie::Image::exportToPNG(target, "output.png");
      ImGui::OpenPopup("Message");
      if (ImGui::BeginPopup("Message"))
      {
        ImGui::Text("Finished exporting to PNG!");
        ImGui::EndPopup();
      }
    }

    ImGui::End();

    SDL_SetRenderDrawColor(this->mWindow.mRenderer.get(), 255, 255, 255, 255);
    SDL_RenderClear(this->mWindow.mRenderer.get());
    this->draw();
    SDL_RenderPresent(this->mWindow.mRenderer.get());
  }
}
}; // namespace Pixie
