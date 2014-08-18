#include "../inc/ProgramOptions.h"
#include <sstream>

using namespace Main;

using namespace boost::program_options;

ProgramOptions::ProgramOptions(int argc, const char *argv[]) :
  description("Options")
{
  description.add_options()
    ("help,h", "Shows help");
  try
  {
    store(parse_command_line(argc, argv, description), vm);
  }
  catch (const error & ex)
  {
    error_string = ex.what();
  }
  notify(vm);
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