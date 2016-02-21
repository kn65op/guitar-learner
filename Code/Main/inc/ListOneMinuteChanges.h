#pragma once

#include "GuitarLearnerCommand.h"
#include "one_minute_changes/inc/OneMinuteChangesSet.hpp"

namespace Main
{

class ListOneMinuteChanges : public GuitarLearnerCommand
{
public:
  enum class ResultType
  {
    BEST,
    LAST,
    NO_RESULTS
  };
  ListOneMinuteChanges(ResultType result) : result_type(result)
  {}
  virtual void process(const CommandOptions &) override;
private:
  const ResultType result_type;

  OneMinuteChanges::OneMinuteChange::ResultType getResultFromChange(const OneMinuteChanges::OneMinuteChangesSet::Element& change) const;
  void showChangesWithResults() const;
  void showChangesWithoutResults() const;
};

}
