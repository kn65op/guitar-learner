#pragma once

#include "GuitarLearnerCommand.h"
namespace Main
{

class ListChordsCommand : public GuitarLearnerCommand
{
public:
  void process(const Main::GuitarLearnerCommand::CommandOptions& options);
};
}
