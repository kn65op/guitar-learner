#ifndef PROGRAMOPTIONS_H
#define PROGRAMOPTIONS_H

#include <boost/program_options.hpp>

namespace Main
{
class ProgramOptions
{
public:
  ProgramOptions(int argc, char *argv[]);
  boost::program_options::variables_map vm;
private:
  boost::program_options::options_description description;
};
}

#endif // PROGRAMOPTIONS_H
