#include "../inc/main_helper.hpp"

#include <Configuration/EqualsSignConfiguratorIO.hpp>
#include <OS/Factory.hpp>
#include <TLogger.h>
#include <one_minute_changes/inc/DatabaseFileReader.hpp>

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
