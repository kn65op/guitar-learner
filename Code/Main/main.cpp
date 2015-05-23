#include <one_minute_changes/inc/DatabaseFileReader.hpp>
#include <one_minute_changes/inc/DatabaseFileWriterVer1.hpp>
#include <fstream>
#include <cstdlib>
#include "Main/inc/ProgramOptions.h"
#include "inc/CommandFactory.h"
#include "main_helper.hpp"
#include <TLogger.h>

int main(int argc, const char *argv[])
{
  TLogger::LoggerFacade logger(TLogger::LoggerType::FILE, TLogger::LogFileOnEntry::CREATE_WITH_DATE, TLogger::LogFileOnExit::REMOVE, getLogFileName());

  Main::ProgramOptions po(argc, argv);
  if (po.isHelp())
  {
    std::cout << po.help();
    return 0;
  }

  std::string db_filename = getDBFileName();
  LOG << "Reading db from file: " << db_filename;
  try
  {
    readDB(db_filename);
  }
  catch (Guitar::DatabaseFileReader::VersionNotSupported &version)
  {
    std::cerr << "Unable to read database file, not supported version: " << version.version_from_file << "\n";
    return 1;
  }

  try
  {
    LOG<< "Executing command";
    auto command_options = createCommandOptions(argc, argv);
    Main::CommandFactory::createCommand(po.getCommand())->process(command_options);
    LOG << "Command executed";
  }
  catch (Main::CommandFactory::InvalidCommand &ex)
  {
    std::cout << po.help();
    return 1;
  }

  LOG<< "Creating DatabaseFileWriter";
  Guitar::DatabaseFileWriterVer1 writer;
  LOG<< "Created DatabaseFileWriter";
  LOG<< "Opening default file";
  std::ofstream out(db_filename);
  LOG<< "Opened default file";
  LOG<< "Creating One minute changes set";
  OneMinuteChanges::OneMinuteChangesSet omc;
  LOG<< "Created One minute changes set";
  LOG<< "writing chords and others to database";
  writer.write(Guitar::Chord::getChords(), omc, out);
  LOG<< "written chords and others to database";
}
