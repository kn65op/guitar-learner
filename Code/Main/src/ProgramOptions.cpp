#include "../inc/ProgramOptions.h"
#include <sstream>
#include <TLogger.h>

using namespace Main;

using namespace boost::program_options;

const std::string ProgramOptions::CHANGE_CHORD_STRING = "change_chord";
const std::string ProgramOptions::ADD_CHORD_STRING = "add_chord";
const std::string ProgramOptions::LIST_CHORDS_STRING = "list_chords";
const std::string ProgramOptions::REMOVE_CHORD_STRING = "remove_chords";

ProgramOptions::ProgramOptions(int argc, const char *argv[]) :
    description("Options"),
        command(CommandType::Nothing)
{
  LOG<< "Start options parsing";
  description.add_options()
  ("help,h", "Shows help")
  (ADD_CHORD_STRING.c_str(), "Adds chord. Specify chord when prompted and one string at time.")
  (LIST_CHORDS_STRING.c_str(), "List chords")
  (CHANGE_CHORD_STRING.c_str(), "Change chord")
  (REMOVE_CHORD_STRING.c_str(), "Remove chord");
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
  if (vm.count(ADD_CHORD_STRING) != 0)
  {
    command = CommandType::AddChord;
  }
  if (vm.count(LIST_CHORDS_STRING) != 0)
  {
    command = CommandType::ListChords;
  }
  if (vm.count(CHANGE_CHORD_STRING) != 0)
  {
    command = CommandType::ChangeChord;
  }
}
