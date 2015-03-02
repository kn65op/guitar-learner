#include <TLogger.h>
#include <one_minute_changes/inc/OneMinuteChangesSet.hpp>
#include <iostream>
#include "../inc/ListBestResults.h"

using namespace Main;

void ListBestOneMinuteChanges::process(const CommandOptions &)
{
  LOG << "Start listing best one minute changes";
  using OneMinuteChanges::OneMinuteChangesSet;

  OneMinuteChangesSet omc_set;

  std::cout << "Changes: ";
  for (const auto & omc : omc_set)
  {
    std::cout << "Change: " << omc->getFirstChord() << "->" << omc->getSecondChord() << ":\t";
    std::cout << omc->bestResult() << "\n";
  }
}
