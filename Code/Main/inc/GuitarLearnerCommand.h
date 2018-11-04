#pragma once
#include <vector>
#include <string>
#include <one_minute_changes/inc/Tab.hpp>
#include <one_minute_changes/inc/Chord.hpp>
#include <istream>
#include <ostream>
#include <array>
#include <TLogger.h>

namespace Main
{

class GuitarLearnerCommand
{
public:
  virtual ~GuitarLearnerCommand() = default;
  typedef std::vector<std::string> CommandOptions;

  virtual void process(const CommandOptions &) = 0;

protected:
  using Tab = Guitar::Tab;

  Tab getTabFromInput(std::ostream &ostream = std::cout, std::istream & istream = std::cin) const noexcept
  {
    ostream << "State tab from up, write fret number:\n";
    const unsigned fret_count = 6;
    std::array<int, fret_count> frets;
    for (unsigned i = 0; i < fret_count; ++i)
    {
      istream >> frets[i];
      if (istream.good())
      {
        LOG << "read frets[" << i << "] = " << frets[i];
      }
      else
      {
        ostream << "Invalid input, please write only numbers, start again with " << i + 1 << " fret:\n";
        LOG << "Input was not a number";
        istream.clear();
        istream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        --i;
      }
    }
    return Tab{frets[0], frets[1], frets[2], frets[3], frets[4], frets[5]};
  }

  using ChordName = Guitar::Chord::ChordNameType;

  class NoChordPassed
  {
  };

  class InvalidIntegerRead
  {
  };

  ChordName getChordFromInput(const std::string &operation, std::ostream &ostream = std::cout, std::istream &istream = std::cin) const
  {
    ChordName chord;
    ostream << "What chord to " << operation << " (EOF to cancel)? ";
    istream >> chord;
    LOG << "Chord readed: " << chord;

    if (chord == "\0")
    {
      throw NoChordPassed{};
    }
    return chord;
  }

  int getResultFromInput(std::ostream &ostream = std::cout, std::istream &istream = std::cin) const
  {
    ostream << "Write result: ";

    int result;
    istream >> result;
    if (!istream.failbit)
    {
      istream.clear();
      throw InvalidIntegerRead();
    }

    return result;
  }
};

}