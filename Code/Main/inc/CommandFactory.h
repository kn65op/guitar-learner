#pragma once
#include "ProgramOptions.h"
#include "ListChordsCommand.h"
#include "AddChordCommand.h"
#include <memory>
#include "ChangeChordCommand.h"
#include "GuitarLearnerCommand.h"

namespace Main
{

class CommandFactory
{
public:

  class InvalidCommand
  {
  public:
  };
  using CommandPtr = std::unique_ptr<GuitarLearnerCommand>;

  static CommandPtr createCommand(CommandType command)
  {
    switch (command)
    {
    case CommandType::Nothing:
      throw InvalidCommand();
    case CommandType::AddChord:
      return std::make_unique<Main::AddChordCommand>();
    case CommandType::ListChords:
      return std::make_unique<Main::ListChordsCommand>();
    case CommandType::ChangeChord:
      return std::make_unique<Main::ChangeChordCommand>();
    case CommandType::RemoveChord:
    throw InvalidCommand();

    }
    throw InvalidCommand();
  }
};

}
