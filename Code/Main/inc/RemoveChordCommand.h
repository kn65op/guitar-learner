#pragma once

#include "GuitarLearnerCommand.h"

namespace Main
{

class RemoveChordCommand : public GuitarLearnerCommand
{
public:
  void process(const GuitarLearnerCommand::CommandOptions& options) override;
};

}
