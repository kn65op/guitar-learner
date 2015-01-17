#pragma once

#include "Command.h"

namespace Main
{

class AddChordCommand : public Command
{
public:
  void process(const Main::Command::CommandOptions& options);
};
}
