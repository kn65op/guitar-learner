#include "AddChordCommand.h"
#include <one_minute_changes/inc/Chord.hpp>
#include <one_minute_changes/inc/Tab.hpp>
#include <one_minute_changes/inc/OneMinuteChangesSet.hpp>
#include <iostream>
#include <TLogger.h>

using namespace Main;

void Main::AddChordCommand::process(const Main::GuitarLearnerCommand::CommandOptions&)
{
  LOG << "Add chord command";
  std::cout << "State symbol for chord: ";
  Guitar::Chord::ChordNameType chord_name;
  std::cin >> chord_name;
  if (Guitar::Chord::exists(chord_name))
  {
    LOG << "Chord exists: " << chord_name;
    std::cout << "Chord already exists\n";
    return;
  }
  Guitar::Tab chord_tab = getTabFromInput(std::cout, std::cin);
  LOG << "Tab from frets created";

  OneMinuteChanges::OneMinuteChangesSet omc_set;
  for (const auto & chord : Guitar::Chord::getChords())
  {
    omc_set.add(std::make_shared<OneMinuteChanges::OneMinuteChange>(chord.first, chord_name));
  }

  Guitar::Chord::add(chord_name, chord_tab);
  LOG << "Adding chord";
  std::cout << "Chord added\n";
}
