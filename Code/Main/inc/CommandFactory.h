#pragma once
#include "ProgramOptions.h"
#include "ListChordsCommand.h"
#include "AddChordCommand.h"
#include <memory>
#include "ChangeChordCommand.h"
#include "GuitarLearnerCommand.h"
#include "RemoveChordCommand.h"

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
      return std::make_unique<AddChordCommand>();
    case CommandType::ListChords:
      return std::make_unique<ListChordsCommand>();
    case CommandType::ChangeChord:
      return std::make_unique<ChangeChordCommand>();
    case CommandType::RemoveChord:
      return std::make_unique<RemoveChordCommand>();
    throw InvalidCommand();

    }
    throw InvalidCommand();
  }
};

}
