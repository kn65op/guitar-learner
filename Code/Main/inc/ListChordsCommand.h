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
    for (auto chord : chords)
    {
      showChord(chord.second);
    }
  }

  template <typename Chord> void showChord(const Chord & chord)
  {
      std::cout << "Chord: " << chord << "\n";
  }
};
}
