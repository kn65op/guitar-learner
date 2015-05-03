#pragma once

#include "GuitarLearnerCommand.h"

namespace Main
{

class ConfigCommand : public GuitarLearnerCommand
{
public:
  void process(const Main::GuitarLearnerCommand::CommandOptions& options);
};

}
