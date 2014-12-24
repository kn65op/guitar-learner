#include <one_minute_changes/inc/DatabaseFileReader.hpp>
#include <one_minute_changes/inc/DatabaseFileWriterVer1.hpp>
#include <fstream>
#include <cstdlib>
#include "Main/inc/ProgramOptions.h"
#include "inc/CommandFactory.h"
#include <TLogger.h>

int main(int argc, const char *argv[])
{
  
  TLogger::LoggerFacade logger(TLogger::LogFileOnEntry::OVERRIDE);
  const std::string default_name = std::string(std::getenv("HOME")) + "/.guitar_learner/default.glearn";
//  std::cout << default_name << "\n";
  try
  {
    std::ifstream in(default_name);
    Guitar::DatabaseFileReader::read(in);
  }
  catch (Guitar::DatabaseFileReader::VersionNotSupported version)
  {
    std::cerr << "Unable to read database file\n";
  }
  
  Main::ProgramOptions po(argc, argv);
  
  if (po.isHelp())
  {
    std::cout << po.help();
    return 0;
  }
  
  try
  {
    Main::CommandFactory::createCommand(po.getCommand())->process(Main::Command::CommandOptions());
  }
  catch (Main::CommandFactory::InvalidCommand &ex)
  {
    std::cout << po.help();
    return 1;
  }
  
  Guitar::DatabaseFileWriterVer1 writer;
  std::ofstream out(default_name);
  OneMinuteChanges::OneMinuteChangesSet omc;
  writer.write(Guitar::Chord::getChords(), omc, out);

}
