#pragma once

#include <string>
#include "inc/GuitarLearnerCommand.h"

std::string getDBFileName();
std::string getLogFileName();
void readDB(const std::string& filename);
Main::GuitarLearnerCommand::CommandOptions createCommandOptions(int argc, const char *argv[]);
