#pragma once

#include "DatabaseFileReader.hpp"

namespace Guitar
{
  
class DatabaseFileReaderVer1 : public DatabaseFileReader
{
protected:
  void readChords(std::istream &in) const override;
  void readOneMinuteChanges(std::istream &in) const override;
};

}
