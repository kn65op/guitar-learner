#include "ListChordsCommand.h"
#include <one_minute_changes/inc/Chord.hpp>
#include <iostream>

using namespace Main;

void ListChordsCommand::process(const Main::GuitarLearnerCommand::CommandOptions& chords)
{
  using Guitar::Chord;

  if (chords.empty())
  {
    showChords(Chord::getChords());
  }
  else
  {
    for (const auto & chordName : chords)
    {
      showChord(Chord::getChord(chordName));
    }
  }
}
