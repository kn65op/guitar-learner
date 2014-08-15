#pragma once

#include "Chord.hpp"
#include <istream>

namespace Guitar
{
  
class DatabaseFileReader
{
public:
  virtual ~DatabaseFileReader() {};
  
  class VersionNotSupported
  {
  };
  
  static void read(std::istream &in);
protected:
  virtual void readChords(std::istream &in) const = 0;
  virtual void readOneMinuteChanges(std::istream &in) const = 0;
};

}
