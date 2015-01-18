#pragma once

#include <boost/program_options.hpp>
#include <string>

namespace Main
{

enum class CommandType
{
  Nothing,
  AddChord,
  ListChords,
  ChangeChord
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

  const static std::string ADD_CHORD_STRING;
  const static std::string LIST_CHORDS_STRING;
  const static std::string CHANGE_CHORD_STRING;
};
}
