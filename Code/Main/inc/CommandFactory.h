#pragma once
#include "ProgramOptions.h"
#include "Command.h"
#include "ListChordsCommand.h"
#include "AddChordCommand.h"
#include <memory>
#include "ChangeChordCommand.h"

namespace Main
{

class CommandFactory
{
public:

  class InvalidCommand
  {
  public:
  };
  using CommandPtr = std::shared_ptr<GuitarLearnerCommand>;

  static CommandPtr createCommand(CommandType command)
  {
    switch (command)
    {
    case CommandType::Nothing:
      throw InvalidCommand();
    case CommandType::AddChord:
      return std::make_shared<Main::AddChordCommand>();
    case CommandType::ListChords:
      return std::make_shared<Main::ListChordsCommand>();
    case CommandType::ChangeChord:
      return std::make_shared<Main::ChangeChordCommand>();
    }
    throw InvalidCommand();
  }
};

}
