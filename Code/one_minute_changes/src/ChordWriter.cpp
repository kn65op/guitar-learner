#include "../inc/ChordWriter.hpp"

using Guitar::ChordWriterVer1;
using Guitar::Chord;

void ChordWriterVer1::write(const Chord::Chords &chords, std::ostream &out)
{
  out << "Ver: 1\n";
  for (auto &chord : chords)
  {
    out << chord.second;
  }
}