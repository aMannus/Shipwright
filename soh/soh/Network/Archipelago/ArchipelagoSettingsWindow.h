#pragma once
#ifndef ARCHIPELAGO_SETTINGS_WINDOW_H
#define ARCHIPELAGO_SETTINGS_WINDOW_H

#include <libultraship/libultraship.h>
#include "ship/window/gui/Gui.h"

class ArchipelagoSettingsWindow final : public Ship::GuiWindow {
  public:
    using GuiWindow::GuiWindow;
    ~ArchipelagoSettingsWindow(){};

  protected:
    void InitElement() override;
    void DrawElement() override;
    void UpdateElement() override{};
};

#endif // ARCHIPELAGO_SETTINGS_WINDOW_H