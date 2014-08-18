#pragma once
#include <vector>
#include <string>

namespace Main
{
  
class Command
{
public:
  virtual ~Command() {}
  typedef std::vector<std::string> CommandOptions;
  
  virtual void process(const CommandOptions &) = 0;
};

}