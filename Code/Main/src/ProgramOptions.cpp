#include "../inc/ProgramOptions.h"
#include <sstream>

using namespace Main;

using namespace boost::program_options;

ProgramOptions::ProgramOptions(int argc, const char *argv[]) :
  description("Options"),
  command(CommandType::Nothing)
{
  description.add_options()
    ("help,h", "Shows help")
    ("add_chord", "Adds chord. Specify chord when prompted one string at time.")
    ("list_chords", "List chords");
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
  if (vm.count("add_chord") != 0)
  {
    command = CommandType::AddChord;
  }
  if (vm.count("list_chords") != 0)
  {
    command = CommandType::ListChords;
  }
}