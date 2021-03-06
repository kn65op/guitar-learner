#pragma once

#include "GuitarLearnerCommand.h"
#include <ostream>
#include <one_minute_changes/inc/OneMinuteChangesSet.hpp>

namespace Main
{

class ShowWorstChanges : public GuitarLearnerCommand
{
public:
  enum class ResultType
  {
    BEST,
    LAST
  };

  ShowWorstChanges(ResultType result) :
      result_type(result)
  {
  }

  void process(const CommandOptions &) override;

private:
  const ResultType result_type;

  OneMinuteChanges::OneMinuteChangesSet::ContainerType getWorstChanges() const;
  OneMinuteChanges::OneMinuteChange::ResultType getResultFromChange(const OneMinuteChanges::OneMinuteChangesSet::Element& change) const;
};

inline std::ostream& operator<<(std::ostream &out, const ShowWorstChanges::ResultType& result_type)
{
  using ResultType = ShowWorstChanges::ResultType;
  switch (result_type)
  {
    case ResultType::BEST:
      out << "BEST";
      return out;
    case ResultType::LAST:
      out << "LAST";
      return out;
  }
  out << "invalid result type";
  return out;
}

}
