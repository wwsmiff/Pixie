#include <SDL.h>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "portable-file-dialogs.h"
#include <gvdi/gvdi.hpp>

#include "editor.hpp"
#include "export.hpp"
#include "macros.hpp"
#include "rgba.hpp"
#include "rng.hpp"

namespace Pixie
{
namespace
{
std::unordered_map<uint64_t, bool> gColorList{};
}

bool Editor::running{true};
Editor::Editor()
    : mWindow("Editor", Pixie::Size(WINDOW_WIDTH, WINDOW_HEIGHT)),
      mCanvasSize(512, 512), mBlockSize(16), mScale(1),
      mGrid((this->mCanvasSize.w / this->mBlockSize.w) *
                (this->mCanvasSize.h / this->mBlockSize.h),
            0xffffffff)
{
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
  {
    std::cerr << "Failed to initialize SDL2, " << SDL_GetError() << std::endl;
    exit(1);
  }

  for (auto &x : this->mGrid)
    x = 0x00000000;

  this->mainloop();
}

void Editor::draw()
{
  /* Grid */
  uint32_t startX{100}; /* * this->mScale */
  uint32_t startY{100}; /* * this->mScale */

  for (uint32_t y = 0; y < (this->mCanvasSize.h); y += this->mBlockSize.h)
  {
    for (uint32_t x = 0; x < (this->mCanvasSize.w); x += this->mBlockSize.w)
    {
      SDL_Rect tmp = {static_cast<int32_t>(x + startX),
                      static_cast<int32_t>(y + startY),
                      static_cast<int32_t>(this->mBlockSize.w),
                      static_cast<int32_t>(this->mBlockSize.h)};
      const Pixie::Rgba &current =
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
  auto selection =
      pfd::open_file("Open", ".", {"Pixie files", "*.pixie"}).result();
  if (selection.size() > 1)
    ImGui::OpenPopup("Cannot select multiple files");
  else if (selection.empty())
    ImGui::OpenPopup("Select a file");
  else
  {
    std::ofstream savefile(selection[0]);
    savefile << this->mCanvasSize.w << '\n';
    savefile << this->mCanvasSize.h << '\n';

    for (const auto &x : this->mGrid)
      savefile << x.hex() << '\n';

    savefile.close();
  }
}

void Editor::open()
{
  auto selection =
      pfd::open_file("Open", ".", {"Pixie files", "*.pixie"}).result();
  if (selection.size() > 1)
    ImGui::OpenPopup("Cannot select multiple files");
  else if (selection.empty())
    ImGui::OpenPopup("Select a file");
  else
  {
    std::ifstream savefile(selection[0]);
    uint32_t width{}, height{};
    std::string line{};
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
}

void Editor::addPalette(uint32_t width, uint32_t height)
{
  constexpr uint32_t xPadding{2};
  constexpr uint32_t yPadding{2};
  const ImVec2 originalCursor = ImGui::GetCursorScreenPos();
  ImVec2 cursor = ImGui::GetCursorPos();
  float buttonHeight = 32;
  float buttonWidth = 32;
  ImDrawList *drawList = ImGui::GetWindowDrawList();

  std::vector<uint32_t> colors{width * height, 0};
  /* TODO: Handle conversion of ABGR to RGBA */
  colors[0] = {0xff'00'00'ff}; /* R */
  colors[1] = {0xff'00'ff'00}; /* G */
  colors[2] = {0xff'ff'00'00}; /* B */

  for (uint32_t i = 0; i < width * height; ++i)
  {
    uint64_t randomID = Pixie::RNG::generate();

    drawList->AddRectFilled(
        cursor, ImVec2(cursor.x + buttonWidth, cursor.y + buttonHeight),
        colors[i], buttonHeight, ImDrawFlags_RoundCornersNone);

    if (ImGui::InvisibleButton(std::to_string(randomID).c_str(),
                               ImVec2{buttonWidth, buttonHeight}))
    {
      for (auto &[id, value] : gColorList)
      {
        std::cout << std::hex << id << std::endl;
        value = 0;
      }

      gColorList[randomID] = 1;
    }

    cursor.x += buttonWidth;
    ImGui::SetCursorPos(cursor);
  }

  ImGui::SetCursorScreenPos(originalCursor);

  // if (ImGui::InvisibleButton("r", ImVec2(buttonWidth, buttonHeight)))
  // printf("r\n");
  // drawList->AddRectFilled(
  // cursor, ImVec2(cursor.x + buttonWidth, cursor.y + buttonHeight),
  // ImU32{0xff0000ff}, buttonHeight, ImDrawFlags_RoundCornersNone);
  // drawList->AddRect(
  // cursor, ImVec2(cursor.x + buttonWidth, cursor.y + buttonHeight),
  // ImU32{0xffffffff}, buttonHeight, ImDrawFlags_RoundCornersNone);
  //
  // ImGui::SetCursorPos({cursor.x + buttonWidth, cursor.y});
  // cursor = ImGui::GetCursorPos();
  // if (ImGui::InvisibleButton("g", ImVec2(buttonWidth, buttonHeight)))
  // printf("g\n");
  // drawList->AddRectFilled(
  // cursor, ImVec2(cursor.x + buttonWidth, cursor.y + buttonHeight),
  // ImU32{0xff00ff00}, buttonHeight, ImDrawFlags_RoundCornersNone);
  // drawList->AddRect(
  // cursor, ImVec2(cursor.x + buttonWidth, cursor.y + buttonHeight),
  // ImU32{0xffffffff}, buttonHeight, ImDrawFlags_RoundCornersNone);
  //
  // ImGui::SetCursorPos({cursor.x + buttonWidth, cursor.y});
  // cursor = ImGui::GetCursorPos();
  // if (ImGui::InvisibleButton("b", ImVec2(buttonWidth, buttonHeight)))
  // printf("b\n");
  // drawList->AddRectFilled(
  // cursor, ImVec2(cursor.x + buttonWidth, cursor.y + buttonHeight),
  // ImU32{0xffff0000}, buttonHeight, ImDrawFlags_RoundCornersNone);
  // drawList->AddRect(
  // cursor, ImVec2(cursor.x + buttonWidth, cursor.y + buttonHeight),
  // ImU32{0xffffffff}, buttonHeight, ImDrawFlags_RoundCornersNone);
}

void Editor::mainloop()
{
  SDL_Event event;
  gvdi::Instance mainInstance{{600, 800}, "Tools"};

  uint32_t start = SDL_GetTicks();
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
                       .h)) /* A very temporary and crappy fix for preventing
                               a crash when clicking outside the grid */
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

    ImGui::SetNextWindowPos({0, 0});
    ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
    ImGui::Begin("Tools", nullptr,
                 ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoDecoration);

    if (ImGui::Button("Clear", {50, 25}))
    {
      for (auto &x : this->mGrid)
        x = 0x00000000;
    }

    if (ImGui::SameLine(); ImGui::Button("Save", {50, 25}))
      this->save();
    if (ImGui::SameLine(); ImGui::Button("Open", {50, 25}))
      this->open();

    if (ImGui::Button("Export to PPM", {150, 25}))
    {
      Pixie::Image input(this->mCanvasSize.w / this->mBlockSize.w,
                         this->mCanvasSize.h / this->mBlockSize.h);

      Pixie::Image::fromRaw(input, this->mGrid);
      Pixie::Image target = Image::upscale(input, this->mBlockSize.w);

      auto selection =
          pfd::open_file("Open", ".", {"Image files", "*.ppm"}).result();
      if (selection.size() > 1)
        ImGui::OpenPopup("Cannot select multiple files");
      else if (selection.empty())
        ImGui::OpenPopup("Select a file");
      else
      {
        Pixie::Image::exportToPPM(target, selection[0]);
        ImGui::OpenPopup("Finished exporting to PPM");
      }
    }

    if (ImGui::BeginPopup("Finished exporting to PPM"))
    {
      ImGui::Text("Finished exporting to PPM");
      ImGui::EndPopup();
    }

    if (ImGui::SameLine(); ImGui::Button("Export to PNG", {150, 25}))
    {
      Pixie::Image input(this->mCanvasSize.w / this->mBlockSize.w,
                         this->mCanvasSize.h / this->mBlockSize.h);

      Pixie::Image::fromRaw(input, this->mGrid);
      Pixie::Image target = Image::upscale(input, this->mBlockSize.w);

      auto selection =
          pfd::open_file("Open", ".", {"Image files", "*.png"}).result();
      if (selection.size() > 1)
        ImGui::OpenPopup("Cannot select multiple files");
      else if (selection.empty())
        ImGui::OpenPopup("Select a file");
      else
      {
        Pixie::Image::exportToPNG(target, selection[0]);
        ImGui::OpenPopup("Finished exporting to PNG!");
      }
    }

    if (ImGui::BeginPopup("Finished exporting to PNG!"))
    {
      ImGui::Text("Finished exporting to PNG!");
      ImGui::EndPopup();
    }

    if (ImGui::BeginPopup("Cannot select multiple files"))
    {
      ImGui::Text("Cannot select multiple files");
      ImGui::EndPopup();
    }

    if (ImGui::BeginPopup("Select a file"))
    {
      ImGui::Text("Select a file");
      ImGui::EndPopup();
    }

    this->addPalette(3, 1);

    ImGui::End();

    SDL_SetRenderDrawColor(this->mWindow.mRenderer.get(), 255, 255, 255, 255);
    SDL_RenderClear(this->mWindow.mRenderer.get());
    this->draw();
    SDL_RenderPresent(this->mWindow.mRenderer.get());
  }

  SDL_Quit();
}
}; // namespace Pixie
