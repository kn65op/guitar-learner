#include "../inc/ListChordsCommand.h"
#include <one_minute_changes/inc/Chord.hpp>
#include <iostream>

using namespace Main;

void ListChordsCommand::process(const Main::Command::CommandOptions& options)
{
  using Guitar::Chord;
  std::cout << "Number of chords: " << Chord::size() << "\n";
  for (auto c : Chord::getChords())
  {
    std::cout << c.second;
  }
}
