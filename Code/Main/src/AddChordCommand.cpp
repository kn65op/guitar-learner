#include "../inc/AddChordCommand.h"
#include <one_minute_changes/inc/Chord.hpp>
#include <one_minute_changes/inc/Tab.hpp>
#include <iostream>

using namespace Main;

void Main::AddChordCommand::process(const Main::Command::CommandOptions& options)
{
  std::cout << "State symbol for chord: ";
  Guitar::Chord::ChordNameType chord_name;
  std::cin >> chord_name;
  std::cout << "State tab from up, write fret number:\n";
  const unsigned fret_count = 6;
  std::array<unsigned, fret_count> frets;
  for (unsigned i = 0; i < fret_count; ++i)
  {
    std::cin >> frets[i];
  }
  Guitar::Tab chord_tab{frets[0], frets[1], frets[2], frets[3], frets[4], frets[5]};
  Guitar::Chord::add(chord_name, chord_tab);
  std::cout << "Chord added\n";
}
