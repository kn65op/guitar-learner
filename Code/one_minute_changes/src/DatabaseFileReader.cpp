#include "../inc/DatabaseFileReader.hpp"
#include "../inc/DatabaseFileReaderVer1.hpp"
#include <memory>
#include "Stream/StreamOperations.hpp"

using Guitar::DatabaseFileReader;
using Guitar::DatabaseFileReaderVer1;
using Guitar::Chord;

void DatabaseFileReader::read(std::istream &in)
{
  std::string version = Stream::StreamOperations::getLineRegardlessLineEnding(in);
  std::unique_ptr<DatabaseFileReader> reader;
  if (version == "Ver: 1")
  {
    reader = std::unique_ptr<DatabaseFileReader>(new DatabaseFileReaderVer1());
  }
  if (reader)
  {
    reader->readChords(in);
    reader->readOneMinuteChanges(in);
  }
  else
  {
    throw VersionNotSupported(version);
  }

}