#pragma once

#include "DatabaseFileWriter.hpp"

namespace Guitar
{
class DatabaseFileWriterVer1 : public DatabaseFileWriter
{
public:
  void write(const Chord::Chords &chords, std::ostream &out);
};
}
