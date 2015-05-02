#include <one_minute_changes/inc/DatabaseFileReader.hpp>
#include <one_minute_changes/inc/DatabaseFileWriterVer1.hpp>
#include <fstream>
#include <cstdlib>
#include "Main/inc/ProgramOptions.h"
#include "inc/CommandFactory.h"
#include <TLogger.h>
#include <OS/Factory.hpp>
#include <Configuration/EqualsSignConfiguratorIO.hpp>

std::string getDBFileName()
{
  THelper::OS::Factory osFactory;
  auto osPaths = osFactory.getPaths();
  const std::string default_config_file = osPaths->getHomeDir() + "/.guitar_learner/config.config";
  const std::string default_database_name = osPaths->getHomeDir() + "/.guitar_learner/default.glearn";
  const std::string db_file_param = "database";
  THelper::Configuration::EqualsSignConfiguratorIO configuratorIO;
  THelper::Configuration::Configurator conf;

  LOG << "Opening config file: " << default_config_file;

  std::ifstream in(default_config_file);
  if (!in.is_open())
  {
    conf.storeStringParameter(db_file_param, default_database_name);
    std::ofstream out(default_config_file);
    configuratorIO.save(conf, out);
    return default_database_name;
  }
  configuratorIO.load(conf, in);
  try
  {
    return conf.loadStringParameter(db_file_param);
  }
  catch (THelper::Configuration::Configurator::NoSuchParameter&)
  {
    conf.storeStringParameter(db_file_param, default_database_name);
    std::ofstream out(default_config_file);
    configuratorIO.save(conf, out);
    return default_database_name;
  }
}

void readDB(const std::string& filename)
{
  LOG<< "Reading database from file: " << filename;
  std::ifstream in(filename);
  if (in.is_open())
  {
    Guitar::DatabaseFileReader::read(in);
  }
  else
  {
    std::cerr << "Unable to read database file, does not exists, will be created\n";
    std::cout << "Creation of file: " << filename << "\n";
  }
}

int main(int argc, const char *argv[])
{
  TLogger::LoggerFacade logger(TLogger::LoggerType::FILE);

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
    Main::CommandFactory::createCommand(po.getCommand())->process(Main::GuitarLearnerCommand::CommandOptions());
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
