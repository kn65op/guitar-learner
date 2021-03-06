#include "ChangeChordCommand.h"

#include <iostream>
#include <TLogger.h>
#include <one_minute_changes/inc/Chord.hpp>

using namespace Main;

void ChangeChordCommand::process(const CommandOptions &)
{
  using Guitar::Chord;
  LOG<< "Entering ChangeChordCommand";
  bool changed = false;
  while (!changed)
  {
    LOG << "Changing loop";
    try
    {
      Chord::ChordNameType chord_to_change = getChordFromInput("change");
      Chord::getChord(chord_to_change);
      Tab changed_tab = getTabFromInput();
      Chord::changeChords(chord_to_change, changed_tab);
      std::cout << "Chord changed\n";
      LOG << "Chord changed";

      changed = true;
    }
    catch (Chord::NotExist &ex)
    {
      LOG << ex.what();
      std::cout << ex.what() << "\n";
    }
    catch(NoChordPassed &)
    {
      std::cout << "\nNo chord changed\n";
      LOG << "Not changing any chord";
      return;
    }
  }
}