#pragma once

#include "Chord.hpp"
#include "OneMinuteChangesSet.hpp"
#include <ostream>

namespace Guitar
{
class DatabaseFileWriter
{
public:
  virtual ~DatabaseFileWriter() {}
  virtual void write(const Chord::Chords & chords, const OneMinuteChanges::OneMinuteChangesSet & omcs, std::ostream &out) const = 0;
};

}
  