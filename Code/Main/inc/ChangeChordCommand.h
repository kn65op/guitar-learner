#pragma once

#include "Command.h"

namespace Main
{

class ChangeChordCommand : public GuitarLearnerCommand
{
public:
  void process(const CommandOptions &) override;
};

}
