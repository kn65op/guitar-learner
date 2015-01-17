#pragma once

#include "Command.h"

namespace Main
{

class RemoveChordCommand : public Command
{
public:
  void process(const CommandOptions &) override;
};

}
