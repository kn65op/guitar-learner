#pragma once

#include "../inc/GuitarLearnerCommand.h"

namespace Main
{

class AddOneMinuteChangeCommand : public GuitarLearnerCommand
{
public:
  void process(const CommandOptions &) override;
};

}
