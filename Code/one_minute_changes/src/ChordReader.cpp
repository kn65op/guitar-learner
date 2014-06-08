#include "../inc/ChordReader.hpp"
#include <memory>

using Guitar::ChordReader;
using Guitar::ChordReaderVer1;
using Guitar::Chord;

void ChordReader::read(std::istream &in)
{
  std::string version;
  std::getline(in, version);
  std::unique_ptr<ChordReader> reader;
  if (version == "Ver: 1")
  {
    reader = std::unique_ptr<ChordReader>(new ChordReaderVer1());
  }
  if (reader)
  {
    reader->readChords(in);
  }
  else
  {
    throw VersionNotSupported();
  }
    
}

void ChordReaderVer1::readChords(std::istream &in) const
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