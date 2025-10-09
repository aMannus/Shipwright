#pragma once
#ifndef ARCHIPELAGO_CONSOLE_WINDOW_H
#define ARCHIPELAGO_CONSOLE_WINDOW_H

#include <libultraship/libultraship.h>
#include <vector>
#include <list>
#include "window/gui/GuiWindow.h"
#include "ArchipelagoTypes.h"

class ArchipelagoConsoleWindow final : public Ship::GuiWindow {
  public:
    using GuiWindow::GuiWindow;
    ~ArchipelagoConsoleWindow(){};

    static ImVec4 getColorVal(const AP_Text::TextColor color);

  protected:
    void InitElement() override{};
    void DrawElement() override;
    void UpdateElement() override{};
};

void ArchipelagoConsole_SendMessage(const char* fmt, ...);
void ArchipelagoConsole_PrintJson(const std::vector<AP_Text::ColoredTextNode> nodes);

#endif // ARCHIPELAGO_CONSOLE_WINDOW_H