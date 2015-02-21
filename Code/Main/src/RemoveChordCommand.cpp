#include "../inc/RemoveChordCommand.h"
#include <TLogger.h>

using namespace Main;

void RemoveChordCommand::process(const GuitarLearnerCommand::CommandOptions& options)
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
      Chord::getChord(chord_to_change);
    }
    catch (NoChordPassed &)
    {
      std::cout << "\nNo chord removed\n";
      LOG << "Not removing any chord";
      return;
    }
  }

}