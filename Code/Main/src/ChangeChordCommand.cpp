#include "../inc/ChangeChordCommand.h"

#include <iostream>
#include <TLogger.h>
#include <one_minute_changes/inc/Chord.hpp>

using namespace Main;

void ChangeChordCommand::process(const CommandOptions &argumets)
{
  using Guitar::Chord;
  LOG<< "Entering ChangeChordCommand";
  bool removed = false;
  while (!removed)
  {
    LOG << "Changing loop";
    std::cout << "What chord to remove (EOF to cancel)? ";
    Chord::ChordNameType chord_to_change;
    std::cin >> chord_to_change;
    LOG << "Chord to remove: " << chord_to_change;

    if (chord_to_change == "\0")
    {
      std::cout << "\nNo chord removed\n";
      LOG << "Not removing any chord";
      return;
    }

    try
    {
      Chord::getChord(chord_to_change);
      Tab changed_tab = getTabFromInput();
      Chord::changeChords(chord_to_change, changed_tab);
      std::cout << "Chord changed\n";
      LOG << "Chord changed";
    }
    catch (Chord::NotExist &ex)
    {
      LOG << "Not found chord";
      std::cout << "Not existing chord: " << chord_to_change << "\n";
      continue;
    }

    removed = true;
  }
}