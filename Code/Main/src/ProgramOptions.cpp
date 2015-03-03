#include "../inc/ProgramOptions.h"
#include <sstream>
#include <TLogger.h>

using namespace Main;

using namespace boost::program_options;

const std::string ProgramOptions::CHANGE_CHORD_STRING = "change_chord";
const std::string ProgramOptions::ADD_CHORD_STRING = "add_chord";
const std::string ProgramOptions::LIST_CHORDS_STRING = "list_chords";
const std::string ProgramOptions::REMOVE_CHORD_STRING = "remove_chord";
const std::string ProgramOptions::ADD_ONE_MINUTE_CHANGE_STRING = "add_one_minute_change";
const std::string ProgramOptions::LIST_BEST_RESULTS_STRING = "list_best_results";
const std::string ProgramOptions::LIST_LAST_RESULTS_STRING = "list_last_results";
const std::string ProgramOptions::SHOW_WORST_CHANGE_STRING = "show_worst_change";
const std::string ProgramOptions::SHOW_LAST_RESULT_WORST_CHANGE_STRING = "show_last_result_worst_change";

ProgramOptions::ProgramOptions(int argc, const char *argv[]) :
    description("Options"),
        command(CommandType::Nothing)
{
  LOG<< "Start options parsing";
  description.add_options()
          ("help,h", "Shows help")
          (ADD_CHORD_STRING.c_str(), "Adds chord. Specify chord when prompted.")
          (LIST_CHORDS_STRING.c_str(), "List chords")
          (CHANGE_CHORD_STRING.c_str(), "Change chord")
          (REMOVE_CHORD_STRING.c_str(), "Remove chord. Specify chord when prompted.")
          (ADD_ONE_MINUTE_CHANGE_STRING.c_str(), "Add one minute change. Specify chords and result when prompted")
          (LIST_BEST_RESULTS_STRING.c_str(), "List all one minute changes with best result")
          (LIST_LAST_RESULTS_STRING.c_str(), "List all one minute changes with last result")
          (SHOW_WORST_CHANGE_STRING.c_str(), "Show worst change based on best result")
          (SHOW_LAST_RESULT_WORST_CHANGE_STRING.c_str(), "Show worst change based on last result");
  try
  {
    store(parse_command_line(argc, argv, description), vm);
  }
  catch (const error & ex)
  {
    error_string = ex.what();
  }
  notify(vm);
  findFirstCommand();
}

bool ProgramOptions::isHelp() const noexcept
{
  return vm.count("help") != 0 || !error_string.empty();
}

std::string ProgramOptions::help() const noexcept
{
  std::stringstream ss;
  if (!error_string.empty())
  {
    ss << error_string << "\n";
  }
  ss << description;
  return ss.str();
}

CommandType ProgramOptions::getCommand() const noexcept
{
  return command;
}

void ProgramOptions::findFirstCommand()
{
  if (vm.count(ADD_CHORD_STRING))
  {
    command = CommandType::AddChord;
  }
  else if (vm.count(LIST_CHORDS_STRING))
  {
    command = CommandType::ListChords;
  }
  else if (vm.count(CHANGE_CHORD_STRING))
  {
    command = CommandType::ChangeChord;
  }
  else if (vm.count(REMOVE_CHORD_STRING))
  {
    command = CommandType::RemoveChord;
  }
  else if(vm.count(ADD_ONE_MINUTE_CHANGE_STRING))
  {
    command = CommandType::AddOneMinuteChange;
  }
  else if(vm.count(LIST_BEST_RESULTS_STRING))
  {
    command = CommandType::ListBestResults;
  }
  else if(vm.count(LIST_LAST_RESULTS_STRING))
  {
    command = CommandType::ListLastResults;
  }
  else if(vm.count(SHOW_LAST_RESULT_WORST_CHANGE_STRING))
  {
    command = CommandType::ShowLastResultWorstChange;
  }
  else if(vm.count(SHOW_WORST_CHANGE_STRING))
  {
    command = CommandType::ShowWorstChange;
  }
}
