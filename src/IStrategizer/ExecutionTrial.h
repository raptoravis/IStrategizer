///> [Serializable]
#ifndef EXECUTIONTRIAL_H
#define EXECUTIONTRIAL_H

#include "EngineObject.h"
#include "TypesMetaData.h"
#include "ConditionEx.h"

namespace IStrategizer
{
    ///> class=ExecutionTrial
    class ExecutionTrial : public EngineObject
    {
        OBJECT_SERIALIZABLE(ExecutionTrial, &m_lastExecutionState, &m_failedAliveCondition);
    public:
        typedef Serialization::SVector<ExecutionTrial> List;

        ExecutionTrial() {}
        ExecutionTrial(ExecutionStateType lastExecutionState, ConditionEx* failedAliveCondition) :
            m_lastExecutionState(lastExecutionState),
            m_failedAliveCondition(failedAliveCondition) {}

        ExecutionStateType ExecutionState() const { return m_lastExecutionState; }
        ConditionEx* FailedAliveCondition() const { return m_failedAliveCondition; }

    private:
        ///> type=int
        ExecutionStateType m_lastExecutionState;
        ///> type=ConditionEx*
        ConditionEx* m_failedAliveCondition;
    };
}

#endif // EXECUTIONTRIAL_H