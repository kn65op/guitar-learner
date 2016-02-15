#include "DatabaseFileWriterVer1.hpp"
#include <TLogger.h>

using Guitar::DatabaseFileWriterVer1;
using Guitar::Chord;

void DatabaseFileWriterVer1::write(const Chord::Chords &chords, const OneMinuteChanges::OneMinuteChangesSet &omcs, std::ostream &out) const
{
  LOG << "Saving database to file";
  out << "Ver: 1\n";
  out << chords.size() << "\n";
  LOG << "Chodrs size" << chords.size();
  for (auto &chord : chords)
  {
    out << chord.second;
  }
  out << omcs.print();
}
