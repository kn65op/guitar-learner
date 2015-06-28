#include "../inc/ShowWorstChange.h"
#include <TLogger.h>
#include <iostream>
#include <one_minute_changes/inc/OneMinuteChangesSet.hpp>
#include <one_minute_changes/inc/Chord.hpp>
#include "DateTime/DateIO.hpp"

using namespace Main;

void ShowWorstChange::process(const CommandOptions &)
{
  using Guitar::Chord;
  LOG<< "Showing worst change for: " << result_type;

  try
  {
    auto worst_omc = getWorstChange();
    LOG<< "Worst change: " << worst_omc->print();

    std::cout << "Worst change: " << worst_omc->getFirstChord() << "->" << worst_omc->getSecondChord() << "\n";
    auto worst_result = getResultFromChange(worst_omc);
    auto datetime = std::chrono::system_clock::to_time_t(worst_result.second);
    THelper::DateTime::DateIO date;
    std::cout << "Result: " << worst_result.first << "\nWhen: " << date.getDateStringInFormat(std::localtime(&datetime), "%c") << "\n";

    std::cout << "Chords: \n";
    std::cout << Chord::getChord(worst_omc->getFirstChord());
    std::cout << "\n";
    std::cout << Chord::getChord(worst_omc->getSecondChord());

  }
  catch (OneMinuteChanges::Exceptions::NoElements&)
  {
    std::cout << "There is no one minute changes in database at all\n";
    LOG<< "There is no changes at all, exiting";
  }
  catch (Chord::NotExist &ex)
  {
    std::cout << "Invalid database\n";
    LOG<< "Problem with database: missing chord " << ex.getChord();
  }

}

OneMinuteChanges::OneMinuteChangesSet::Element ShowWorstChange::getWorstChange() const
{
  using OneMinuteChanges::OneMinuteChangesSet;

  OneMinuteChangesSet omc_set;

  switch (result_type)
  {
    case ResultType::BEST:
      return omc_set.findFirstWorstChordByBestResult();
    case ResultType::LAST:
      return omc_set.findFirstWorstChordByLastResult();
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
  throw std::runtime_error{"Invalid ResultType"};
}
