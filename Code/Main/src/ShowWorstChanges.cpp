#include "../inc/ShowWorstChanges.h"

#include <TLogger.h>
#include <iostream>
#include <one_minute_changes/inc/OneMinuteChangesSet.hpp>
#include <one_minute_changes/inc/Chord.hpp>
#include "DateTime/DateIO.hpp"

using namespace Main;

void ShowWorstChanges::process(const CommandOptions &)
{
  using Guitar::Chord;
  LOG<< "Showing worst change for: " << result_type;

  try
  {
    auto worstChanges = getWorstChanges();

    std::cout << "Worst changes:";

    for (const auto &change : worstChanges)
    {
      LOG << "One of worst changes: " << change->print();
      std::cout << "\n";
      std::cout << change->getFirstChord() << "->" << change->getSecondChord() << "\n";
      auto worst_result = getResultFromChange(change);
      auto datetime = std::chrono::system_clock::to_time_t(worst_result.second);
      THelper::DateTime::DateIO date;
      std::cout << "Result: " << worst_result.first << "\nWhen: " << date.getDateStringInFormat(std::localtime(&datetime), "%c") << "\n";
      std::cout << "Chords: \n";
      std::cout << Chord::getChord(change->getFirstChord());
      std::cout << "\n";
      std::cout << Chord::getChord(change->getSecondChord());
    }
  }
  catch (OneMinuteChanges::Exceptions::NoElements&)
  {
    std::cout << "There is no one minute changes in database at all\n";
    LOG << "There is no changes at all, exiting";
  }
  catch (Chord::NotExist &ex)
  {
    std::cout << "Invalid database\n";
    LOG << "Problem with database: missing chord " << ex.getChord();
  }

}

OneMinuteChanges::OneMinuteChangesSet::ContainerType ShowWorstChanges::getWorstChanges() const
{
  using OneMinuteChanges::OneMinuteChangesSet;

  OneMinuteChangesSet omc_set;

  switch (result_type)
  {
    case ResultType::BEST:
      return omc_set.findWorstChangesByBestResult();
    case ResultType::LAST:
      return omc_set.findWorstChangesByLastResult();
  }
  throw std::runtime_error("Invalid result type");
}

OneMinuteChanges::OneMinuteChange::ResultType ShowWorstChanges::getResultFromChange(const OneMinuteChanges::OneMinuteChangesSet::Element& change) const
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
