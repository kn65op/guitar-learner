#include "RemoveChordCommand.h"
#include <one_minute_changes/inc/OneMinuteChangesSet.hpp>
#include <TLogger.h>

using namespace Main;

void RemoveChordCommand::process(const GuitarLearnerCommand::CommandOptions& )
{
  LOG << "entry";

  bool removed = false;
  while (!removed)
  {
    using Guitar::Chord;

    LOG << "Changing loop";
    try
    {
      Chord::ChordNameType chord_to_remove = getChordFromInput("remove");
      Chord::removeChord(chord_to_remove);

      OneMinuteChanges::OneMinuteChangesSet omc_set;
      omc_set.removeAllContainingChord(chord_to_remove);

      removed = true;
    }
    catch (NoChordPassed &)
    {
      std::cout << "\nNo chord removed\n";
      LOG << "Not removing any chord";
      return;
    }
    catch (Chord::NotExist &ex)
    {
      LOG << ex.what();
      std::cout << ex.what() << "\n";
    }
  }
}