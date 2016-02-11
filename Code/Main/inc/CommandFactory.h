#pragma once

#include "ProgramOptions.h"
#include "ListChordsCommand.h"
#include "AddChordCommand.h"
#include <memory>
#include "ChangeChordCommand.h"
#include "GuitarLearnerCommand.h"
#include "RemoveChordCommand.h"
#include "AddOneMinuteChangeCommand.h"
#include "ListOneMinuteChanges.h"
#include "ConfigCommand.h"
#include "ShowWorstChanges.h"

namespace Main
{

class CommandFactory
{
public:

  class InvalidCommand
  {
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
    case CommandType::AddOneMinuteChange:
      return std::make_unique<AddOneMinuteChangeCommand>();
    case CommandType::ListBestResults:
      return std::make_unique<ListOneMinuteChanges>(ListOneMinuteChanges::ResultType::BEST);
    case CommandType::ListLastResults:
      return std::make_unique<ListOneMinuteChanges>(ListOneMinuteChanges::ResultType::LAST);
    case CommandType::ShowWorstChange:
      return std::make_unique<ShowWorstChanges>(ShowWorstChanges::ResultType::BEST);
    case CommandType::ShowLastResultWorstChange:
      return std::make_unique<ShowWorstChanges>(ShowWorstChanges::ResultType::LAST);
    case CommandType::Config:
      return std::make_unique<ConfigCommand>();
    }
    throw InvalidCommand();
  }

};

}
