#include "../inc/ListOneMinuteChanges.h"

#include <TLogger.h>
#include <one_minute_changes/inc/OneMinuteChangesSet.hpp>
#include <iostream>
#include "DateTime/DateIO.hpp"

using namespace Main;

void ListOneMinuteChanges::process(const CommandOptions &)
{
  LOG << "Start listing best one minute changes";
  using OneMinuteChanges::OneMinuteChangesSet;

  OneMinuteChangesSet omc_set;

  DateTime::DateIO date;
  std::cout << "Changes:\n";
  for (const auto & omc : omc_set)
  {
    std::cout << "Change: " << omc->getFirstChord() << "->" << omc->getSecondChord() << ":\t";
    const auto result = getResultFromChange(omc);
    auto datetime = std::chrono::system_clock::to_time_t(result.second);
    std::cout << result.first << "\ton: " << date.getDateStringInFormat(std::localtime(&datetime), "%A %c") << "\n";
  }
}

OneMinuteChanges::OneMinuteChange::ResultType ListOneMinuteChanges::getResultFromChange(const OneMinuteChanges::OneMinuteChangesSet::Element& change) const
{
  switch (result_type)
  {
    case ResultType::BEST:
      return change->bestResult();
    case ResultType::LAST:
      return change->lastResult();
  }
  throw std::runtime_error{"Invalid ResultType"};
}
