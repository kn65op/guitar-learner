#include "../inc/ChangeChordCommand.h"

#include <iostream>
#include <TLogger.h>
#include <one_minute_changes/inc/Chord.hpp>

using namespace Main;

void ChangeChordCommand::process(const CommandOptions &argumets)
{
  using Guitar::Chord;
  LOG<< "Entering RemoveChordCommand";
  bool removed = false;
  while (!removed)
  {
    LOG << "Removing loop";
    std::cout << "What chord to remove (EOF to cancel)? ";
    Chord::ChordNameType chord_to_remove;
    std::cin >> chord_to_remove;
    LOG << "Chord to remove: " << chord_to_remove;

    if (chord_to_remove == "\0")
    {
      std::cout << "No chord removed";
      LOG << "Not removing any chord";
      return;
    }
    removed = true;
  }
}