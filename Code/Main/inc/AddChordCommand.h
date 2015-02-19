#pragma once

#include "GuitarLearnerCommand.h"

namespace Main
{

class AddChordCommand : public GuitarLearnerCommand
{
public:
  void process(const Main::GuitarLearnerCommand::CommandOptions& options);
};
}
