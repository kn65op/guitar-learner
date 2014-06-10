#include "../inc/DatabaseFileWriter.hpp"

using Guitar::DatabaseFileWriterVer1;
using Guitar::Chord;

void DatabaseFileWriterVer1::write(const Chord::Chords &chords, std::ostream &out)
{
  out << "Ver: 1\n";
  out << chords.size() << "\n";
  for (auto &chord : chords)
  {
    out << chord.second;
  }
}