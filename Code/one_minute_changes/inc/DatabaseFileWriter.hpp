#ifndef CHORDWRITER_H
#define CHORDWRITER_H

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


class DatabaseFileWriterVer1 : public DatabaseFileWriter
{
public:
  void write(const Chord::Chords &chords, std::ostream &out);
};
}

#endif // CHORDWRITER_H
