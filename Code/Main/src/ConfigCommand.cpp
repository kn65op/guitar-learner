#include "../inc/ConfigCommand.h"
#include <Configuration/EqualsSignConfiguratorIO.hpp>

using namespace Main;

void ConfigCommand::process(const CommandOptions& options)
{
  const std::string default_config_file = osPaths->getHomeDir() + "/.guitar_learner/config.config";
  if (options.size() == 1)
  {

  }
  else if (options.size() == 2)
  {

  }
}