#pragma once
#include <vector>
#include <string>

namespace Main
{

class GuitarLearnerCommand
{
public:

  virtual ~GuitarLearnerCommand()
  {
  }
  typedef std::vector<std::string> CommandOptions;

  virtual void process(const CommandOptions &) = 0;
};

}