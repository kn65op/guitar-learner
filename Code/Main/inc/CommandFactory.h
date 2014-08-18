#pragma once
#include "ProgramOptions.h"
#include "Command.h"
#include "ListChordsCommand.h"
#include <memory>

namespace Main
{
  
class CommandFactory
{
public:
  class InvalidCommand
  {
  public:
  };
  using CommandPtr = std::shared_ptr<Command>;
  static CommandPtr createCommand(CommandType command)
  {
    switch (command)
    {
      case CommandType::Nothing:
        throw InvalidCommand();   
      case CommandType::AddChord:
        throw InvalidCommand();         
      case CommandType::ListChords:
        return std::make_shared<Main::ListChordsCommand>();
    }
    throw InvalidCommand();         
  }
};
  
}
