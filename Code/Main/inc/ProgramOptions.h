#pragma once

#include <boost/program_options.hpp>

namespace Main
{
  
enum class CommandType
{
  Nothing,
  AddChord,
  ListChords
};
  
class ProgramOptions
{
public:
  ProgramOptions(int argc, const char *argv[]);
  boost::program_options::variables_map vm;
  
  std::string help() const noexcept;
  bool isHelp() const noexcept;
  CommandType getCommand() const noexcept;
private:
  boost::program_options::options_description description;
  std::string error_string;
  CommandType command;
  
  void findFirstCommand();
};
}
