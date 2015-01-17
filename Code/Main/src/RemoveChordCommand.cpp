#include "../inc/RemoveChordCommand.h"
#include <TLogger.h>

using namespace Main;

void RemoveChordCommand::process(const CommandOptions &argumets)
{
  while (bool not_removed = false)
  {
    static int i = 2;
    LOG << i;
    not_removed = i;
  }
}