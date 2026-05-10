#pragma once
#ifndef ARCHIPELAGO_HINT_WINDOW_H
#define ARCHIPELAGO_HINT_WINDOW_H

#include <libultraship/libultraship.h>
#include <vector>
#include "ship/window/gui/Gui.h"
#include "ArchipelagoTypes.h"

class ArchipelagoHintWindow final : public Ship::GuiWindow {
  public:
    using GuiWindow::GuiWindow;
    ~ArchipelagoHintWindow(){};

  protected:
    void InitElement() override{};
    void DrawElement() override;
    void UpdateElement() override{};

  private:
    enum HintTableColumns : int { COL_RECIEVING, COL_ITEM, COL_FINDING, COL_LOCATION, COL_STATUS };

    void addName(const std::string& name, bool is_us);
    void addItem(const AP_Hint::Hint& hint);
    void addLocation(const AP_Hint::Hint& hint);
    void addEntrance(const AP_Hint::Hint& hint);
    void addStatus(const AP_Hint::Hint& hint);
    void addStatusCombo(const AP_Hint::Hint& hint);
    AP_Text::TextColor getStatusColor(const AP_Hint::HintStatus status) const;
    void sortHints(ImGuiTableSortSpecs* sort_specs);
};

void ArchipelagoHintWindow_UpdateHints(std::vector<AP_Hint::Hint>& new_hints);
void ArchipelagoHintWindow_ChangeHintableItems(const std::vector<int64_t>& hintableItems);
void ArchipelagoHintWindow_ClearItemSuggestions();

#endif // ARCHIPELAGO_HINT_WINDOW_H