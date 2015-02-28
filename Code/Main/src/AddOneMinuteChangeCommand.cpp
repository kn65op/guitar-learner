#include "../inc/AddOneMinuteChangeCommand.h"
#include <one_minute_changes/inc/OneMinuteChangesSet.hpp>
#include <TLogger.h>

using namespace Main;

void AddOneMinuteChangeCommand::process(const CommandOptions &)
{
  LOG << "Add one minute change command";

  using Guitar::Chord;

  try
  {
    auto first_chord = getChordFromInput("be first");
    auto second_chord = getChordFromInput("be second");

    using OneMinuteChanges::OneMinuteChangesSet;
    OneMinuteChangesSet omc_set;

    OneMinuteChangesSet::Element omc = omc_set.getChange(first_chord, second_chord);

    int result = getResultFromInput();

    omc->addResult(result);
  }
  catch (NoChordPassed &)
  {
    std::cout << "Not adding any one minute change\n";
    LOG << "Not adding any one minute change";
  }
  catch (OneMinuteChanges::Exceptions::NoChangeFound &ex)
  {
    std::cout << "There is no such change. Did you add such chords?\n";
    LOG << "Not found proper change, possibly written not existing chord";
  }
  catch (InvalidIntegerRead &)
  {
    std::cout << "Could not read result, not adding\n";
    LOG << "Could not read integer, probably some letters passed";
  }
}