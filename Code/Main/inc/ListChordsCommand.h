#pragma once

#include <Main/inc/Command.h>
namespace Main
{

class ListChordsCommand : public GuitarLearnerCommand
{
public:
  void process(const Main::GuitarLearnerCommand::CommandOptions& options);
};
}
