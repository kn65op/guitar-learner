#pragma once

#include "GuitarLearnerCommand.h"

namespace Main
{

class AddOneMinuteChangeCommand : public GuitarLearnerCommand
{
public:
  void process(const CommandOptions &) override;
};

}
