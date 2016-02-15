#include "ListChordsCommand.h"
#include <one_minute_changes/inc/Chord.hpp>
#include <iostream>

using namespace Main;

void ListChordsCommand::process(const Main::GuitarLearnerCommand::CommandOptions&)
{
  using Guitar::Chord;
  std::cout << "Number of chords: " << Chord::size() << "\n\n";
  for (auto c : Chord::getChords())
  {
    std::cout << "Chord: " << c.second << "\n";
  }
}
