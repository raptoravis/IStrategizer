///> [Serializable]
#ifndef MOVEENTITYACTION_H
#define MOVEENTITYACTION_H

#include "Action.h"
#ifndef VECTOR2_H
#include "Vector2.h"
#endif

namespace IStrategizer
{
    ///> class=MoveEntityAction
    ///> parent=Action
    class MoveEntityAction : public Action
    {
        OBJECT_SERIALIZABLE(MoveEntityAction);

    public:
        MoveEntityAction();
        MoveEntityAction(const PlanStepParameters& p_parameters);
        bool PreconditionsSatisfied();
        bool AliveConditionsSatisfied();
        bool SuccessConditionsSatisfied();

    protected:
        void OnSucccess(const WorldClock& p_clock);
        void OnFailure(const WorldClock& p_clock);
        void HandleMessage(Message* p_pMsg, bool& p_consumed);
        void InitializePostConditions();
        void InitializePreConditions();
        bool ExecuteAux(const WorldClock& p_clock);

    private:
        TID _entityId;
        Vector2 _position;
    };
}

#endif // MOVEENTITYACTION_H
