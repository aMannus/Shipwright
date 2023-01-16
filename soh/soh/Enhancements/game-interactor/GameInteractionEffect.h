#ifndef GameInteractionEffect_h
#define GameInteractionEffect_h

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif
extern uint32_t GameInteractor_NoUI;
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
enum GameInteractionEffectQueryResult {
    Possible                = 0x00,
    TemporarilyNotPossible  = 0x01,
    NotPossible             = 0xFF
};

class GameInteractionEffectBase {
public:
    virtual GameInteractionEffectQueryResult CanBeApplied() = 0;
    virtual void Apply() = 0;
    virtual void Remove() = 0;
};

namespace GameInteractionEffect {
    class AddHeartContainer: public GameInteractionEffectBase {
        GameInteractionEffectQueryResult CanBeApplied() override;
        void Apply() override;
        void Remove() override;
    };

    class RemoveHeartContainer: public GameInteractionEffectBase {
        GameInteractionEffectQueryResult CanBeApplied() override;
        void Apply() override;
        void Remove() override;
    };

    class FillMagic: public GameInteractionEffectBase {
        GameInteractionEffectQueryResult CanBeApplied() override;
        void Apply() override;
        void Remove() override;
    };

    class EmptyMagic: public GameInteractionEffectBase {
        GameInteractionEffectQueryResult CanBeApplied() override;
        void Apply() override;
        void Remove() override;
    };

    class GiveRupees: public GameInteractionEffectBase {
        GameInteractionEffectQueryResult CanBeApplied() override;
        void Apply() override;
        void Remove() override;
    };

    class TakeRupees: public GameInteractionEffectBase {
        GameInteractionEffectQueryResult CanBeApplied() override;
        void Apply() override;
        void Remove() override;
    };

    class NoUI: public GameInteractionEffectBase {
        GameInteractionEffectQueryResult CanBeApplied() override;
        void Apply() override;
        void Remove() override;
    };

    class HighGravity: public GameInteractionEffectBase {
        GameInteractionEffectQueryResult CanBeApplied() override;
        void Apply() override;
        void Remove() override;
    };

    class LowGravity: public GameInteractionEffectBase {
        GameInteractionEffectQueryResult CanBeApplied() override;
        void Apply() override;
        void Remove() override;
    };

    class KillPlayer: public GameInteractionEffectBase {
        GameInteractionEffectQueryResult CanBeApplied() override;
        void Apply() override;
        void Remove() override;
    };

    class FreezePlayer: public GameInteractionEffectBase {
        GameInteractionEffectQueryResult CanBeApplied() override;
        void Apply() override;
        void Remove() override;
    };

    class BurnPlayer: public GameInteractionEffectBase {
        GameInteractionEffectQueryResult CanBeApplied() override;
        void Apply() override;
        void Remove() override;
    };

    class ElectrocutePlayer: public GameInteractionEffectBase {
        GameInteractionEffectQueryResult CanBeApplied() override;
        void Apply() override;
        void Remove() override;
    };

    class KnockbackPlayer: public GameInteractionEffectBase {
        GameInteractionEffectQueryResult CanBeApplied() override;
        void Apply() override;
        void Remove() override;
    };

    class GiveHealth: public GameInteractionEffectBase {
        GameInteractionEffectQueryResult CanBeApplied() override;
        void Apply() override;
        void Remove() override;
    };

    class TakeHealth: public GameInteractionEffectBase {
        GameInteractionEffectQueryResult CanBeApplied() override;
        void Apply() override;
        void Remove() override;
    };

    class GiantLink: public GameInteractionEffectBase {
        GameInteractionEffectQueryResult CanBeApplied() override;
        void Apply() override;
        void Remove() override;
    };

    class MinishLink: public GameInteractionEffectBase {
        GameInteractionEffectQueryResult CanBeApplied() override;
        void Apply() override;
        void Remove() override;
    };

    class InvisibleLink: public GameInteractionEffectBase {
        GameInteractionEffectQueryResult CanBeApplied() override;
        void Apply() override;
        void Remove() override;
    };

    class PaperLink: public GameInteractionEffectBase {
        GameInteractionEffectQueryResult CanBeApplied() override;
        void Apply() override;
        void Remove() override;
    };

    class DisableZTargeting: public GameInteractionEffectBase {
        GameInteractionEffectQueryResult CanBeApplied() override;
        void Apply() override;
        void Remove() override;
    };

    class PacifistMode: public GameInteractionEffectBase {
        GameInteractionEffectQueryResult CanBeApplied() override;
        void Apply() override;
        void Remove() override;
    };

    class WeatherRainstorm: public GameInteractionEffectBase {
        GameInteractionEffectQueryResult CanBeApplied() override;
        void Apply() override;
        void Remove() override;
    };

    class ReverseControls: public GameInteractionEffectBase {
        GameInteractionEffectQueryResult CanBeApplied() override;
        void Apply() override;
        void Remove() override;
    };

    class ForceIronBoots: public GameInteractionEffectBase {
        GameInteractionEffectQueryResult CanBeApplied() override;
        void Apply() override;
        void Remove() override;
    };

    class ForceHoverBoots: public GameInteractionEffectBase {
        GameInteractionEffectQueryResult CanBeApplied() override;
        void Apply() override;
        void Remove() override;
    };

    class GiveDekuShield: public GameInteractionEffectBase {
        GameInteractionEffectQueryResult CanBeApplied() override;
        void Apply() override;
        void Remove() override;
    };

    class IncreaseRunSpeed: public GameInteractionEffectBase {
        GameInteractionEffectQueryResult CanBeApplied() override;
        void Apply() override;
        void Remove() override;
    };

    class DecreaseRunSpeed: public GameInteractionEffectBase {
        GameInteractionEffectQueryResult CanBeApplied() override;
        void Apply() override;
        void Remove() override;
    };

    class OneHitKO : public GameInteractionEffectBase {
        GameInteractionEffectQueryResult CanBeApplied() override;
        void Apply() override;
        void Remove() override;
    };

    class IncreaseDamageTaken: public GameInteractionEffectBase {
        GameInteractionEffectQueryResult CanBeApplied() override;
        void Apply() override;
        void Remove() override;
    };

    class DecreaseDamageTaken : public GameInteractionEffectBase {
        GameInteractionEffectQueryResult CanBeApplied() override;
        void Apply() override;
        void Remove() override;
    };

    class SpawnEnemy: public GameInteractionEffectBase {
        GameInteractionEffectQueryResult CanBeApplied() override;
        void Apply() override;
        void Remove() override;
    };
}

#endif /* __cplusplus */
#endif /* GameInteractionEffect_h */
