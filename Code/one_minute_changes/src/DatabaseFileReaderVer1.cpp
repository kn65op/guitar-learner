#include "../inc/DatabaseFileReaderVer1.hpp"
#include <one_minute_changes/inc/OneMinuteChangesSet.hpp>
#include <memory>
#include <cstdlib>

using Guitar::DatabaseFileReaderVer1;
using Guitar::Chord;

void DatabaseFileReaderVer1::readChords(std::istream &in) const
{
  std::string chords_str;
  std::getline(in, chords_str);
  int chords = std::atoi(chords_str.c_str());
  for (int i = 0; i < chords; ++i)
  {
    std::string chord_line;
    std::getline(in, chord_line);
    Guitar::Tab tab{in};
    Chord::add(chord_line, tab);
  }
}

void DatabaseFileReaderVer1::readOneMinuteChanges(std::istream &in) const
{
  OneMinuteChanges::OneMinuteChangesSet omcs(in);
}
