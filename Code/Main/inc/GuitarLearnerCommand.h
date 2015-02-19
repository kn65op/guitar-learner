#pragma once
#include <vector>
#include <string>
#include <one_minute_changes/inc/Tab.hpp>
#include <istream>
#include <ostream>
#include <array>
#include <TLogger.h>

namespace Main
{

class GuitarLearnerCommand
{
public:

  virtual ~GuitarLearnerCommand()
  {
  }
  typedef std::vector<std::string> CommandOptions;

  virtual void process(const CommandOptions &) = 0;

protected:
  using Tab = Guitar::Tab;

  Tab getTabFromInput(std::ostream &ostream, std::istream & istream) const
  {
    ostream << "State tab from up, write fret number:\n";
    const unsigned fret_count = 6;
    std::array<int, fret_count> frets;
    for (unsigned i = 0; i < fret_count; ++i)
    {
      istream >> frets[i];
      LOG << "read frets[" << i << "] = " << frets[i];
    }
    return Tab{frets[0], frets[1], frets[2], frets[3], frets[4], frets[5]};
  }
};

}