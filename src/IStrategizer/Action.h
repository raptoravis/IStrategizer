///> [Serializable]
#ifndef ACTION_H
#define ACTION_H

#include <map>
#include <vector>
#include "PlanStepEx.h"
#include "MetaData.h"
#include "ExecutionHistory.h"

namespace IStrategizer
{
    class CompositeExpression;
    class ExecutionHistory;

    ///> class=Action
    ///> parent=PlanStepEx
    class Action : public PlanStepEx
    {
		OBJECT_SERIALIZABLE_P(Action, PlanStepEx, &m_history);

    protected:
        CompositeExpression* _preCondition;
        ///> type=ExecutionHistory
        ExecutionHistory m_history;

        Action(ActionType p_actionType, unsigned p_maxPrepTime = 0, unsigned p_maxExecTrialTime = 0, unsigned p_maxExecTime = 0);
        Action(ActionType p_actionType, const PlanStepParameters& p_parameters, unsigned p_maxPrepTime = 0,  unsigned p_maxExecTrialTime = 0, unsigned p_maxExecTime = 0);
        void State(ExecutionStateType p_state, RtsGame& game, const WorldClock& p_clock);
        void UpdateAux(RtsGame& game, const WorldClock& p_clock);
        virtual bool ExecuteAux(RtsGame& game, const WorldClock& p_clock) = 0;
        virtual void InitializePreConditions() = 0;
        virtual void OnSucccess(RtsGame& game, const WorldClock& p_clock) { FreeResources(game); };
        virtual void OnFailure(RtsGame& game, const WorldClock& p_clock) { FreeResources(game); };
        virtual void FreeResources(RtsGame& game) {}

    public:
		~Action();
        int Type() const { return PlanStepEx::_stepTypeId; }
        CompositeExpression* PreCondition() { _ASSERTE(_preCondition); return _preCondition; }
        void Reset(RtsGame& game, const WorldClock& p_clock);
        void InitializeConditions();
        void Copy(IClonable* p_dest);
        void ExecutionHistory(ExecutionHistory history) { m_history.AddRange(history); }
        bool PreconditionsSatisfied(RtsGame& game);
        IStrategizer::ExecutionHistory ExecutionHistory() const { return m_history; }
        virtual bool Execute(RtsGame& game, const WorldClock& p_clock);
        virtual bool AliveConditionsSatisfied(RtsGame& game) = 0;
        unsigned Hash(bool quantified /* = true */) const;
        virtual void Abort(RtsGame &game) { LogInfo("%s is aborting", ToString().c_str()); FreeResources(game); }
    };
}

#endif
