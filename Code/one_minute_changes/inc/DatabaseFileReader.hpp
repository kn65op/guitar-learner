#ifndef CHORDREADER_H
#define CHORDREADER_H

#include "Chord.hpp"
#include <istream>

namespace Guitar
{
  
class DatabaseFileReader
{
public:
  class VersionNotSupported
  {
  };
  
  static void read(std::istream &in);
protected:
  virtual void readChords(std::istream &in) const = 0;
};

class DatabaseFileReaderVer1 : public DatabaseFileReader
{
protected:
  void readChords(std::istream &in) const override;
};

}

#endif // CHORDREADER_H
