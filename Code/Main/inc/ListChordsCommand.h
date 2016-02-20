#pragma once

#include "GuitarLearnerCommand.h"
namespace Main
{

class ListChordsCommand : public GuitarLearnerCommand
{
public:
  void process(const Main::GuitarLearnerCommand::CommandOptions& options);
private:
  template <typename Chords> void showChords(const Chords &chords)
  {
    std::cout << "Number of chords: " << chords.size() << "\n\n";
    for (auto c : chords)
    {
      std::cout << "Chord: " << c.second << "\n";
    }
  }
};
}
