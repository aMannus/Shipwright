
#include "Notification.h"
#include <libultraship/libultraship.h>
#include "soh/OTRGlobals.h"

extern "C" {
#include "functions.h"
#include "macros.h"
#include "variables.h"
}

namespace Notification {

static uint32_t nextId = 0;
static std::vector<Options> notifications = {};

void Window::Draw() {
    auto vp = ImGui::GetMainViewport();

    const float margin = 30.0f;
    const float padding = 10.0f;

    int position = CVarGetInteger(CVAR_SETTING("Notifications.Position"), 3);

    // Top Left
    ImVec2 basePosition;
    switch (position) {
        case 0: // Top Left
            basePosition = ImVec2(vp->Pos.x + margin, vp->Pos.y + margin);
            break;
        case 1: // Top Right
            basePosition = ImVec2(vp->Pos.x + vp->Size.x - margin, vp->Pos.y + margin);
            break;
        case 2: // Bottom Left
            basePosition = ImVec2(vp->Pos.x + margin, vp->Pos.y + vp->Size.y - margin);
            break;
        case 3: // Bottom Right
            basePosition = ImVec2(vp->Pos.x + vp->Size.x - margin, vp->Pos.y + vp->Size.y - margin);
            break;
        case 4: // Hidden
            return;
    }

    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0, 0, 0, 0));
    ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0, 0, 0, 0));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 4.0f);

    for (int index = 0; index < notifications.size(); ++index) {
        auto& notification = notifications[index];
        int inverseIndex = -ABS(index - (notifications.size() - 1));

        ImGui::SetNextWindowViewport(vp->ID);
        // Fade out
        if (notification.remainingTime < 4.0f) {
            ImGui::PushStyleVar(ImGuiStyleVar_Alpha, (notification.remainingTime - 1) / 3.0f);
        } else {
            ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 1.0f);
        }

        ImGui::SetNextWindowSize(ImVec2(0, vp->Size.y - (margin * 2)));
        ImGui::Begin(("Notification#" + std::to_string(notification.id)).c_str(), nullptr,
                     ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoFocusOnAppearing |
                         ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar |
                         ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoMove |
                         ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings);

        ImGui::SetWindowFontScale(CVarGetFloat(CVAR_SETTING("Notifications.Size"), 1.8f)); // Make this adjustable

        ImVec2 notificationPos;
        switch (position) {
            case 0: // Top Left
                notificationPos = ImVec2(basePosition.x, basePosition.y);
                break;
            case 1: // Top Right
                notificationPos = ImVec2(basePosition.x - ImGui::GetWindowSize().x, basePosition.y);
                break;
            case 2: // Bottom Left
                notificationPos = ImVec2(basePosition.x, basePosition.y - (ImGui::GetWindowSize().y + padding));
                break;
            case 3: // Bottom Right
                notificationPos = ImVec2(basePosition.x - ImGui::GetWindowSize().x,
                                         basePosition.y - (ImGui::GetWindowSize().y + padding));
                break;
        }

        ImGui::SetWindowPos(notificationPos);

        // If bottom aligned
        if (position == 2 || position == 3) {
            ImGui::SetCursorPosY(ImGui::GetWindowSize().y - (60 * (inverseIndex + 1)));
        } else {
            ImGui::SetCursorPosY(60 * inverseIndex);
        }

        ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0, 0, 0, 0.5));

        if (ImGui::BeginChild(("Notification#" + std::to_string(notification.id)).c_str(), ImVec2(0, 0),
                              ImGuiChildFlags_AlwaysUseWindowPadding | ImGuiChildFlags_AlwaysAutoResize |
                                  ImGuiChildFlags_AutoResizeX | ImGuiChildFlags_AutoResizeY)) {

            if (notification.itemIcon != nullptr) {
                ImGui::Image(
                    Ship::Context::GetInstance()->GetWindow()->GetGui()->GetTextureByName(notification.itemIcon),
                    ImVec2(32, 32));
                ImGui::SameLine();
            }
            if (!notification.prefix.empty()) {
                ImGui::TextColored(notification.prefixColor, "%s", notification.prefix.c_str());
                ImGui::SameLine();
            }
            ImGui::TextColored(notification.messageColor, "%s", notification.message.c_str());
            if (!notification.suffix.empty()) {
                ImGui::SameLine();
                ImGui::TextColored(notification.suffixColor, "%s", notification.suffix.c_str());
            }
            ImGui::EndChild();
        }

        ImGui::PopStyleColor();

        ImGui::End();
        ImGui::PopStyleVar();
    }

    ImGui::PopStyleVar();
    ImGui::PopStyleColor(2);
}

void Window::UpdateElement() {
    for (int index = 0; index < notifications.size(); ++index) {
        auto& notification = notifications[index];

        // decrement remainingTime
        notification.remainingTime -= ImGui::GetIO().DeltaTime;

        // remove notification if it has expired
        if (notification.remainingTime <= 0) {
            notifications.erase(notifications.begin() + index);
            --index;
        }
    }
}

void Emit(Options notification) {
    notification.id = nextId++;
    if (notification.remainingTime == 0.0f) {
        notification.remainingTime = CVarGetFloat(CVAR_SETTING("Notifications.Duration"), 10.0f);
    }
    notifications.push_back(notification);
    if (!notification.mute) {
        Audio_PlaySoundGeneral(NA_SE_SY_METRONOME, &gSfxDefaultPos, 4, &gSfxDefaultFreqAndVolScale,
                               &gSfxDefaultFreqAndVolScale, &gSfxDefaultReverb);
    }
}

} // namespace Notification
