#include "../inc/ProgramOptions.h"

using namespace Main;

using namespace boost::program_options;

ProgramOptions::ProgramOptions(int argc, char *argv[]) :
  description("Options")
{
  description.add_options();
  store(parse_command_line(argc, argv, description), vm);
  notify(vm);
}