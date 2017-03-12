#include "ListOneMinuteChanges.h"

#include "DateTime/DateIO.hpp"
#include <TLogger.h>
#include <iostream>
#include <one_minute_changes/inc/OneMinuteChangesSet.hpp>

using namespace Main;

struct FillWith
{
  FillWith(unsigned size) : size(size)
  {
  }

  const unsigned size;
  const char character = ' ';
};

std::ostream &operator<<(std::ostream &out, FillWith filler)
{
  return out << std::setw(filler.size) << std::setfill(filler.character);
}

void showChange(std::ostream &out, const auto &change)
{
  const std::string delimeter = "\t";
  const FillWith spacesBeforeChord{6};
  const FillWith spacesBeforeArrow{4};
  out << "Change: " << spacesBeforeChord << change->getFirstChord() << spacesBeforeArrow << "->" << spacesBeforeChord
      << change->getSecondChord() << " :  ";
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

std::string ListOneMinuteChanges::getColoredResult(int result) const
{
  std::string color;
  if (result < 30)
  {
    color = "\033[1;31m";
  }
  else if (result < 40)
  {
    color = "\033[1;33m";
  }
  else if (result < 50)
  {
    color = "\033[0;34m";
  }
  else if (result < 60)
  {
    color = "\033[0;36m";
  }
  else
  {
    color = "\033[0;32m";
  }
  return color + std::to_string(result) + "\033[0m";
}

void ListOneMinuteChanges::showChangesWithResults() const
{
  LOG << "Start listing one minute changes with results";
  using OneMinuteChanges::OneMinuteChangesSet;

  OneMinuteChangesSet omc_set;

  THelper::DateTime::DateIO date;
  std::cout << "Changes:\n";
  for (const auto &omc : omc_set)
  {
    showChange(std::cout, omc);
    try
    {
      LOG << "Getting inforamtion about change result";
      const auto result = getResultFromChange(omc);
      auto datetime = std::chrono::system_clock::to_time_t(result.second);
      const FillWith spacesBeforeResult{4};
      std::cout << spacesBeforeResult << getColoredResult(result.first)
                << "   on: " << date.getDateStringInFormat(std::localtime(&datetime), "%c") << "\n";
    }
    catch (const OneMinuteChanges::IOneMinuteChange::NoResultsError noResults)
    {
      LOG << "Change has no results";
      std::cout << "No results for this change\n";
    }
  }
}

OneMinuteChanges::OneMinuteChange::ResultType
ListOneMinuteChanges::getResultFromChange(const OneMinuteChanges::OneMinuteChangesSet::Element &change) const
{
  switch (result_type)
  {
  case ResultType::BEST:
    return change->bestResult();
  case ResultType::LAST:
    return change->lastResult();
  case ResultType::NO_RESULTS:
    break;
  }
  LOG << "Invalid result type";
  throw std::runtime_error{"Invalid ResultType"};
}

void ListOneMinuteChanges::showChangesWithoutResults() const
{
  LOG << "Start listing one minute changes without results";
  OneMinuteChanges::OneMinuteChangesSet omc_set;

  for (const auto &omc : omc_set.findChangesWithoutResults())
  {
    LOG << "Showing change";
    showChange(std::cout, omc);
    std::cout << "has no results\n";
  }
}