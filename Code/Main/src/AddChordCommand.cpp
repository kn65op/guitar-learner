#include "../inc/AddChordCommand.h"
#include <one_minute_changes/inc/Chord.hpp>
#include <one_minute_changes/inc/Tab.hpp>
#include <iostream>
#include <TLogger.h>

using namespace Main;

void Main::AddChordCommand::process(const Main::GuitarLearnerCommand::CommandOptions& options)
{
  LOG << "Add chord command";
  std::cout << "State symbol for chord: ";
  Guitar::Chord::ChordNameType chord_name;
  std::cin >> chord_name;
  Guitar::Tab chord_tab = getTabFromInput(std::cout, std::cin);
  LOG << "Tab from frets created";
  Guitar::Chord::add(chord_name, chord_tab);
  LOG << "Adding chord";
  std::cout << "Chord added\n";
}
