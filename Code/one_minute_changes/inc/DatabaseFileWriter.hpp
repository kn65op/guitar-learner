#pragma once

#include "Chord.hpp"
#include <ostream>

namespace Guitar
{
class DatabaseFileWriter
{
public:
  virtual ~DatabaseFileWriter() {}
  virtual void write(const Chord::Chords & chords, std::ostream &out) = 0;
};

}
