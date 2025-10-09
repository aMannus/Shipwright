#include "ArchipelagoConsoleWindow.h"

#include "soh/SohGui/UIWidgets.hpp"
#include "soh/SohGui/SohGui.hpp"
#include "soh/OTRGlobals.h"
#include "ArchipelagoTypes.h"

std::vector<std::vector<AP_Text::ColoredTextNode>> Items;
bool autoScroll = true;

using namespace UIWidgets;

void ArchipelagoConsole_SendMessage(const char* fmt, ...) {
    char buf[1024];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buf, IM_ARRAYSIZE(buf), fmt, args);
    buf[IM_ARRAYSIZE(buf) - 1] = 0;
    va_end(args);
    AP_Text::ColoredTextNode node;
    node.text = std::string(buf);
    node.color = AP_Text::TextColor::COLOR_WHITE;
    if (strstr(buf, "[ERROR]")) {
        node.color = AP_Text::TextColor::COLOR_ERROR;
    } else if (strstr(buf, "[LOG]")) {
        node.color = AP_Text::TextColor::COLOR_LOG;
    }
    std::vector<AP_Text::ColoredTextNode> line;
    line.push_back(node);
    Items.push_back(line);
    if (Items.size() > 50) {
        Items.erase(Items.begin());
    }
}

void ArchipelagoConsole_PrintJson(const std::vector<AP_Text::ColoredTextNode> nodes) {
    Items.push_back(nodes);
    if (Items.size() > 50) {
        Items.erase(Items.begin());
    }
}

void ArchipelagoConsoleWindow::DrawElement() {
    ImGui::SeparatorText("Archipelago Log");

    ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.15f, 0.15f, 0.15f, 1.0f));
    ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 8.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(15.0f, 12.0f));
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 1.0f));

    if (ImGui::BeginChild("ScrollingRegion", ImVec2(0, 400), ImGuiChildFlags_AlwaysUseWindowPadding,
                          ImGuiWindowFlags_HorizontalScrollbar)) {

        for (const std::vector<AP_Text::ColoredTextNode>& line : Items) {
            for (const AP_Text::ColoredTextNode& node : line) {
                ImGui::PushStyleColor(ImGuiCol_Text, getColorVal(node.color));
                ImGui::TextUnformatted(node.text.c_str());
                ImGui::SameLine();
                ImGui::PopStyleColor();
            }
            ImGui::NewLine();
        }

        // Keep up at the bottom of the scroll region if we were already at the bottom at the beginning of the frame.
        // Using a scrollbar or mouse-wheel will take away from the bottom edge.
        if (autoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY()) {
            ImGui::SetScrollHereY(1.0f);
        }
    }
    ImGui::EndChild();
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 8.0f);

    static char textEntryBuf[1024];
    static bool keepFocus = false;

    if (keepFocus) {
        ImGui::SetKeyboardFocusHere();
        keepFocus = false;
    }

    PushStyleInput(THEME_COLOR);
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(10.0f, 8.0f));
    if (ImGui::InputText("##AP_MessageField", textEntryBuf, 1023, ImGuiInputTextFlags_EnterReturnsTrue)) {
        ArchipelagoClient::GetInstance().SendMessageToConsole(std::string(textEntryBuf));
        textEntryBuf[0] = '\0';
        keepFocus = true;
    }
    ImGui::PopStyleVar();
    PopStyleInput();

    ImGui::SameLine();

    if (UIWidgets::Button("Send", UIWidgets::ButtonOptions().Color(THEME_COLOR).Size(ImVec2(0.0, 0.0)))) {
        ArchipelagoClient::GetInstance().SendMessageToConsole(std::string(textEntryBuf));
        textEntryBuf[0] = '\0';
        keepFocus = true;
    }

    ImGui::PopStyleColor();
    ImGui::PopStyleVar(4);
};

ImVec4 ArchipelagoConsoleWindow::getColorVal(const AP_Text::TextColor color) {
    using apt = AP_Text::TextColor;
    switch (color) {
        case apt::COLOR_ERROR:
            return ImVec4(1.0f, 0.4f, 0.4f, 1.0f);
        case apt::COLOR_LOG:
            return ImVec4(0.7f, 0.7f, 1.0f, 1.0f);
        case apt::COLOR_BLACK:
            return ImVec4(0.000f, 0.000f, 0.000f, 1.00f);
        case apt::COLOR_RED:
            return ImVec4(0.933f, 0.000f, 0.000f, 1.00f);
        case apt::COLOR_GREEN:
            return ImVec4(0.000f, 1.000f, 0.498f, 1.00f);
        case apt::COLOR_YELLOW:
            return ImVec4(0.980f, 0.980f, 0.824f, 1.00f);
        case apt::COLOR_BLUE:
            return ImVec4(0.392f, 0.584f, 0.929f, 1.00f);
        case apt::COLOR_CYAN:
            return ImVec4(0.000f, 0.933f, 0.933f, 1.00f);
        case apt::COLOR_MAGENTA:
            return ImVec4(0.933f, 0.000f, 0.933f, 1.00f);
        case apt::COLOR_SLATEBLUE:
            return ImVec4(0.427f, 0.545f, 0.910f, 1.00f);
        case apt::COLOR_PLUM:
            return ImVec4(0.686f, 0.600f, 0.937f, 1.00f);
        case apt::COLOR_SALMON:
            return ImVec4(0.980f, 0.502f, 0.447f, 1.00f);
        case apt::COLOR_ORANGE:
            return ImVec4(1.000, 0.467f, 0.000f, 1.000f);
        case apt::COLOR_GRAY:
            return ImVec4(0.53f, 0.53f, 0.53f, 1.00f);
        case apt::COLOR_WHITE:
        case apt::COLOR_DEFAULT:
        default:
            return ImVec4(0.93f, 0.93f, 0.93f, 1.00f);
    };
}
