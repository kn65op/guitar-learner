#pragma once

#include "GuitarLearnerCommand.h"

namespace Main
{

class ListBestOneMinuteChanges : public GuitarLearnerCommand
{
public:
  virtual void process(const CommandOptions &) override;
};

}
