#ifndef CHORDWRITER_H
#define CHORDWRITER_H

#include "Chord.hpp"
#include <ostream>

namespace Guitar
{
class ChordWriter
{
public:
  virtual ~ChordWriter() {}
  virtual void write(const Chord::Chords & chords, std::ostream &out) = 0;
};


class ChordWriterVer1 : public ChordWriter
{
public:
  void write(const Chord::Chords &chords, std::ostream &out);
};
}

#endif // CHORDWRITER_H
