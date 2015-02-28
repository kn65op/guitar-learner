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
    using OneMinuteChanges::OneMinuteChange;
    OneMinuteChangesSet omc_set;

//    OneMinuteChangesSet::Element omc = std::make_shared<OneMinuteChange>();
  }
  catch (NoChordPassed &)
  {
    std::cout << "Not adding any one minute change";
    LOG << "Not adding any one minute change";
  }
}