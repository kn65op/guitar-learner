#pragma once

#include "Command.h"

namespace Main
{

class ChangeChordCommand : public Command
{
public:
  void process(const CommandOptions &) override;
};

}
