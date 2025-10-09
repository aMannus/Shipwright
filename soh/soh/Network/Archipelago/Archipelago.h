#pragma once
#ifdef __cplusplus
#include "soh/Enhancements/randomizer/randomizerTypes.h"
#include "soh/Enhancements/randomizer/static_data.h"
#include <vector>
#include <nlohmann/json.hpp>
#include <queue>
#include "ArchipelagoTypes.h"

// Forward declaration
class APClient;

namespace AP_Client_consts {
static constexpr int MAX_ADDRESS_LENGTH = 64;
static constexpr int MAX_PLAYER_NAME_LENGHT = 17;
static constexpr int MAX_PASSWORD_LENGTH = 32;

static constexpr char const* AP_GAME_NAME = "Ship of Harkinian";
static constexpr int MAX_RETRIES = 3;
} // namespace AP_Client_consts

class ArchipelagoClient {
  public:
    struct ApItem {
        std::string itemName;
        std::string locationName;
        std::string playerName;
        unsigned int flags;
        uint64_t index;
    };

    static ArchipelagoClient& GetInstance();

    bool StartClient();
    bool StopClient();

    void GameLoaded();
    void StartLocationScouts();
    void SynchItems();
    void SynchSentLocations();
    void SynchReceivedLocations();

    // getters
    const std::string GetSlotName() const;

    uint8_t GetConnectionStatus();
    void OnItemGiven(uint32_t rc, GetItemEntry gi, uint8_t isGiSkipped);
    void SendDeathLink();
    void SetDeathLinkTag();
    const nlohmann::json GetSlotData();
    const std::vector<ApItem>& GetScoutedItems();

    bool IsConnected();
    void CheckLocation(RandomizerCheck SoH_check_id);

    void OnItemReceived(const ApItem apItem);
    void QueueItem(const ApItem item);
    void QueueExternalCheck(int64_t apLocation);

    void SendGameWon();
    void SendMessageToConsole(const std::string message);
    void Poll();
    void ResetQueue();

    bool slotMatch(const std::string& slotName, const std::string& roomHash);

    std::unique_ptr<APClient> apClient;
    bool itemQueued;
    bool disconnecting;
    bool isDeathLinkedDeath;
    int retries;
    std::string uri;
    std::string password;

  protected:
    ArchipelagoClient();

  private:
    ArchipelagoClient(ArchipelagoClient&) = delete;
    void operator=(const ArchipelagoClient&) = delete;

    bool isRightSaveLoaded() const;

    std::string uuid;

    static std::shared_ptr<ArchipelagoClient> instance;
    static bool initialized;

    bool gameWon;

    nlohmann::json slotData;
    std::set<int64_t> locations;
    std::vector<ApItem> scoutedItems;
    std::queue<ApItem> receiveQueue;
};

void LoadArchipelagoData();
void SaveArchipelagoData(SaveContext* saveContext, int sectionID, bool fullSave);
void InitArchipelagoData(bool isDebug);
extern "C" {
#endif // END __cplusplus
void Archipelago_InitSaveFile();
#ifdef __cplusplus
}
#endif
