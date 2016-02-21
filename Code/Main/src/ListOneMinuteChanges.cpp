#include "ListOneMinuteChanges.h"

#include <TLogger.h>
#include <one_minute_changes/inc/OneMinuteChangesSet.hpp>
#include <iostream>
#include "DateTime/DateIO.hpp"

using namespace Main;

struct FillWith
{
  FillWith(unsigned size) :size(size)
  {
  }

  const unsigned size;
  const char character = ' ';
};

std::ostream& operator<<(std::ostream & out, FillWith filler)
{
  return out << std::setw(filler.size) << std::setfill(filler.character);
}

void ListOneMinuteChanges::process(const CommandOptions &)
{
  switch (result_type)
  {
    case ResultType::BEST:
    case ResultType::LAST:
      return showChangesWithResults();
    case ResultType::NO_RESULTS:
      return showChangesWithoutResults();
  }
}

void ListOneMinuteChanges::showChangesWithResults() const
{
  LOG << "Start listing one minute changes";
  using OneMinuteChanges::OneMinuteChangesSet;

  OneMinuteChangesSet omc_set;

  THelper::DateTime::DateIO date;
  std::cout << "Changes:\n";
  for (const auto & omc : omc_set)
  {
    const std::string delimeter = "\t";
    const FillWith spacesBeforeChord{6};
    const FillWith spacesBeforeArrow{4};
    std::cout << "Change: " << spacesBeforeChord << omc->getFirstChord() << spacesBeforeArrow << "->" << spacesBeforeChord << omc->getSecondChord() << " :  ";
    try
    {
      LOG << "Getting inforamtion about change result";
      const auto result = getResultFromChange(omc);
      auto datetime = std::chrono::system_clock::to_time_t(result.second);
      const FillWith spacesBeforeResult{4};
      std::cout << spacesBeforeResult << result.first << "   on: " << date.getDateStringInFormat(std::localtime(&datetime), "%c") << "\n";
    }
    catch (const OneMinuteChanges::IOneMinuteChange::NoResultsError noResults)
    {
      LOG << "Change has no results";
      std::cout << "No results for this change\n";
    }
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
  LOG << "Invalid result type";
  throw std::runtime_error{"Invalid ResultType"};
}
