#pragma once

#include "GuitarLearnerCommand.h"

namespace Main
{

class ChangeChordCommand : public GuitarLearnerCommand
{
public:
  void process(const CommandOptions &) override;
};

}
