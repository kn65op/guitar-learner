#include "../inc/ConfigCommand.h"
#include <Configuration/EqualsSignConfiguratorIO.hpp>
#include <OS/Factory.hpp>
#include <fstream>

using namespace Main;

void ConfigCommand::process(const CommandOptions& options)
{
  THelper::OS::Factory osFactory;
  auto osPaths = osFactory.getPaths();
  const std::string default_config_file = osPaths->getHomeDir() + "/.guitar_learner/config.config";
  THelper::Configuration::EqualsSignConfiguratorIO confIO;
  THelper::Configuration::Configurator conf;
  {
    std::ifstream config_file(default_config_file);
    confIO.load(conf, config_file);
  }
  if (options.empty())
  {
    std::cout << "For information about possible configuration please take a look at docs/man_config.txt\n";
    return;
  }
  if (options.size() == 1)
  {
    try
    {
      std::cout << conf.loadStringParameter(options[0]) << "\n";
    }
    catch (THelper::Configuration::Configurator::NoSuchParameter &)
    {
      std::cout << "Parameter was not set\n";
    }
  }
  else if (options.size() == 2)
  {
    std::ofstream config_file(default_config_file);
    conf.storeStringParameter(options[0], options[1]);
    confIO.save(conf, config_file);
  }
}
