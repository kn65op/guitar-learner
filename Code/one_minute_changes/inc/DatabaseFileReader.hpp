#pragma once

#include "Chord.hpp"
#include <istream>

namespace Guitar
{

class DatabaseFileReader
{
public:

  virtual ~DatabaseFileReader()
  {
  };

  struct VersionNotSupported
  {
    VersionNotSupported(const std::string &read_version = "not read any version") :
      version_from_file(read_version)
    { }

    const std::string version_from_file;
  };

  static void read(std::istream &in);
protected:
  virtual void readChords(std::istream &in) const = 0;
  virtual void readOneMinuteChanges(std::istream &in) const = 0;

  static std::string cleanCarriageReturn(const std::string &text);
};

}
