#pragma once

#include "DatabaseFileWriter.hpp"

namespace Guitar
{

class DatabaseFileWriterVer1 : public DatabaseFileWriter
{
public:
  void write(const Chord::Chords &chords, const OneMinuteChanges::OneMinuteChangesSet &omcs, std::ostream &out) const override;
};
}
