#include "ListChordsCommand.h"
#include <one_minute_changes/inc/Chord.hpp>
#include <iostream>
#include "TLogger.h"

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
      try
      {
        showChord(Chord::getChord(chordName));
      }
      catch(Chord::NotExist &ex)
      {
        std::cout << ex.what() << "\n";
        LOG << ex.what();
      }
    }
  }
}
