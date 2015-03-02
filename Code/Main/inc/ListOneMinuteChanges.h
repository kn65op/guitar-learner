#pragma once

#include "GuitarLearnerCommand.h"
#include <one_minute_changes/inc/OneMinuteChangesSet.hpp>

namespace Main
{

class ListOneMinuteChanges : public GuitarLearnerCommand
{
public:
  enum class ResultType
  {
    BEST,
    LAST
  };
  ListOneMinuteChanges(ResultType result) : result_type(result)
  {}
  virtual void process(const CommandOptions &) override;
private:
  ResultType result_type;

  OneMinuteChanges::OneMinuteChange::ResultType getResultFromChange(const OneMinuteChanges::OneMinuteChangesSet::Element& change) const;
};

}
