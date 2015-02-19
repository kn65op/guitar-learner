#pragma once

#include "Command.h"

namespace Main
{

class AddChordCommand : public GuitarLearnerCommand
{
public:
  void process(const Main::GuitarLearnerCommand::CommandOptions& options);
};
}
