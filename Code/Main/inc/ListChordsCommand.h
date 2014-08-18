#pragma once

#include <Main/inc/Command.h>
namespace Main
{

class ListChordsCommand : public Command
{
public:
  void process(const Main::Command::CommandOptions& options);
};
}
