#include <one_minute_changes/inc/DatabaseFileReader.hpp>
#include <one_minute_changes/inc/DatabaseFileWriterVer1.hpp>
#include <fstream>
#include <cstdlib>

int main()
{
  const std::string default_name = std::string(std::getenv("HOME")) + "/.guitar_learner/default.glearn";
  std::cout << default_name << "\n";
  try
  {
    std::ifstream in(default_name);
    Guitar::DatabaseFileReader::read(in);
  }
  catch (Guitar::DatabaseFileReader::VersionNotSupported version)
  {
    std::cerr << "Unable to read file\n";
  }
  Guitar::DatabaseFileWriterVer1 writer;
  std::ofstream out(default_name);
  OneMinuteChanges::OneMinuteChangesSet omc;
  writer.write(Guitar::Chord::getChords(), omc, out);

}
