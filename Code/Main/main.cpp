#include <one_minute_changes/inc/DatabaseFileReader.hpp>
#include <one_minute_changes/inc/DatabaseFileWriterVer1.hpp>
#include <fstream>
#include <cstdlib>
#include "Main/inc/ProgramOptions.h"
#include "inc/CommandFactory.h"
#include <TLogger.h>
#include <Factory.hpp>

int main(int argc, const char *argv[])
{

  TLogger::LoggerFacade logger(TLogger::LoggerType::FILE);
  LOG << "TEST LOG";
  THelper::OS::Factory osFactory;
  auto osPaths = osFactory.getPaths();
//  const std::string default_name = osPaths->getHomeDir() + "/.guitar_learner/default.glearn";
  std::string default_name = "base.base";
  LOG << "Using default file name: " << default_name;
  try
  {
    std::ifstream in(default_name);
    if (in.is_open())
    {
      Guitar::DatabaseFileReader::read(in);
    }
    else
    {
      std::cerr << "Unable to read database file, does not exists, will be created\n";
    }
  }
  catch (Guitar::DatabaseFileReader::VersionNotSupported &version)
  {
    std::cerr << "Unable to read database file, not supported version: " << version.version_from_file << "\n";
  }

  Main::ProgramOptions po(argc, argv);

  if (po.isHelp())
  {
    std::cout << po.help();
    return 0;
  }

  try
  {
    LOG << "Executing command";
    Main::CommandFactory::createCommand(po.getCommand())->process(Main::GuitarLearnerCommand::CommandOptions());
    LOG << "Command executed";
  }
  catch (Main::CommandFactory::InvalidCommand &ex)
  {
    std::cout << po.help();
    return 1;
  }

  LOG << "Creating DatabaseFileWriter";
  Guitar::DatabaseFileWriterVer1 writer;
  LOG << "Created DatabaseFileWriter";
  LOG << "Opening default file";
  std::ofstream out(default_name);
  LOG << "Opened default file";
  LOG << "Creating One minute changes set";
  OneMinuteChanges::OneMinuteChangesSet omc;
  LOG << "Created One minute changes set";
  LOG << "writing chords and others to database";
  writer.write(Guitar::Chord::getChords(), omc, out);
  LOG << "written chords and others to database";
}
