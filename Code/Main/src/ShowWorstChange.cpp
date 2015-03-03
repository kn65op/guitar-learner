#include "../inc/ShowWorstChange.h"
#include <TLogger.h>
#include <iostream>
#include <one_minute_changes/inc/OneMinuteChangesSet.hpp>

using namespace Main;

void ShowWorstChange::process(const CommandOptions &)
{
  LOG << "Showing worst change for: " << result_type;

  auto worst_omc = getWorstChange();
  LOG << "Worst change: " << worst_omc->print();

  std::cout << "Worst change: " << worst_omc->getFirstChord() << "->" << worst_omc->getSecondChord() << "\n";
  std::cout << "Result: " << getResultFromChange(worst_omc) << "\n";
}

OneMinuteChanges::OneMinuteChangesSet::Element ShowWorstChange::getWorstChange() const
{
  using OneMinuteChanges::OneMinuteChangesSet;

  OneMinuteChangesSet omc_set;

  switch (result_type)
  {
    case ResultType::BEST:
      return omc_set.findWorstChord();
    case ResultType::LAST:
      return omc_set.findLastWorstChord();
  }
  throw std::runtime_error("Invalid result type");
}

OneMinuteChanges::OneMinuteChange::ResultType ShowWorstChange::getResultFromChange(const OneMinuteChanges::OneMinuteChangesSet::Element& change) const
{
  switch (result_type)
  {
    case ResultType::BEST:
      return change->bestResult();
    case ResultType::LAST:
      return change->lastResult();
  }
  return 0;
}