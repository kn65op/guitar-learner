#include "../inc/DatabaseFileWriterVer1.hpp"
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
    LOG << "Saving chord " << chord.first;
    LOG << "Saving chord " << chord.second;
    out << chord.second;
    LOG << "Saved chord" << chord.second;
  }
  LOG << "Saving omc";
  out << omcs.print();
}
