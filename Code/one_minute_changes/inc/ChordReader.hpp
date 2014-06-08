#ifndef CHORDREADER_H
#define CHORDREADER_H

#include "Chord.hpp"
#include <istream>

namespace Guitar
{
  
class ChordReader
{
public:
  class VersionNotSupported
  {
  };
  
  static void read(std::istream &in);
protected:
  virtual void readChords(std::istream &in) const = 0;
};

class ChordReaderVer1 : public ChordReader
{
protected:
  void readChords(std::istream &in) const override;
};

}

#endif // CHORDREADER_H
