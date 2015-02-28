#include "../inc/RemoveChordCommand.h"
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
      Chord::ChordNameType chord_to_change = getChordFromInput("remove");
      Chord::removeChord(chord_to_change);

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
      std::cout << "Trying to remove not existing chord: " << ex.getChord() << "\n";
      LOG << "Trying to remove not existing chord: " << ex.getChord();
    }
  }
}