#include <gtest/gtest.h>
#include "Main/inc/ProgramOptions.h"

using namespace ::testing;
using namespace Main;

struct ProgramOptionsTest : public Test
{

};

TEST_F(ProgramOptionsTest, DefaultOptionsDontShowHelp)
{
  int argc = 1;
  const char *args[] = {"program"};
  ProgramOptions po(argc, args);
  EXPECT_FALSE(po.isHelp());
}

TEST_F(ProgramOptionsTest, WithhOptionsPrintHelpShouldBeTrue)
{
  int argc = 2;
  const char *args[] = {"program", "-h"};
  ProgramOptions po(argc, args);
  EXPECT_TRUE(po.isHelp());
}

TEST_F(ProgramOptionsTest, WithhelpOptionsPrintHelpShouldBeTrue)
{
  int argc = 2;
  const char *args[] = {"program", "--help"};
  ProgramOptions po(argc, args);
  EXPECT_TRUE(po.isHelp());
}

TEST_F(ProgramOptionsTest, HelpShouldRetunNotEmptyHelp)
{
  int argc = 1;
  const char *args[] = {"program"};
  ProgramOptions po(argc, args);
  EXPECT_NE("", po.help());
}

TEST_F(ProgramOptionsTest, ForUnrecognizedOptionPrintHelpShouldBeTrue)
{
  int argc = 2;
  const char *args[] = {"program", "--zzzzaaqqqqqhasd"};
  ProgramOptions po(argc, args);
  EXPECT_TRUE(po.isHelp());
}

TEST_F(ProgramOptionsTest, ForAddChordOptionGetCommandShouldReturnAddChordCommand)
{
  int argc = 2;
  const char *args[] = {"program", "--add_chord"};
  ProgramOptions po(argc, args);
  EXPECT_EQ(CommandType::AddChord, po.getCommand());
}

TEST_F(ProgramOptionsTest, ForListChordsOptionGetCommandShouldReturnListCommand)
{
  int argc = 2;
  const char *args[] = {"program", "--list_chords"};
  ProgramOptions po(argc, args);
  EXPECT_EQ(CommandType::ListChords, po.getCommand());
}

TEST_F(ProgramOptionsTest, ForChangeChordOptionGetCommandShouldReturnChangeChordCommand)
{
  int argc = 2;
  const char *args[] = {"program", "--change_chord"};
  ProgramOptions po(argc, args);
  EXPECT_EQ(CommandType::ChangeChord, po.getCommand());
}

TEST_F(ProgramOptionsTest, ForRemoveChordOptionGetCommandShouldReturnRemoveChordCommand)
{
  int argc = 2;
  const char *args[] = {"program", "--remove_chord"};
  ProgramOptions po(argc, args);
  EXPECT_EQ(CommandType::RemoveChord, po.getCommand());
}

TEST_F(ProgramOptionsTest, ForAddOneMinuteChangeOptionGetCommandShouldReturnAddOneMinuteChnageCommand)
{
  int argc = 2;
  const char *args[] = {"program", "--add_one_minute_change"};
  ProgramOptions po(argc, args);
  EXPECT_EQ(CommandType::AddOneMinuteChange, po.getCommand());
}

TEST_F(ProgramOptionsTest, ForListBestResultsOptionGetCommandShouldReturnListAllOneMinuteChnages)
{
  int argc = 2;
  const char *args[] = {"program", "--list_best_results"};
  ProgramOptions po(argc, args);
  EXPECT_EQ(CommandType::ListBestResults, po.getCommand());
}

TEST_F(ProgramOptionsTest, ForListLastResultsOptionGetCommandShouldReturnListAllOneMinuteChnages)
{
  int argc = 2;
  const char *args[] = {"program", "--list_last_results"};
  ProgramOptions po(argc, args);
  EXPECT_EQ(CommandType::ListLastResults, po.getCommand());
}

TEST_F(ProgramOptionsTest, ForShowWorstChangeOptionGetCommandShouldReturnShowWorstChange)
{
  int argc = 2;
  const char *args[] = {"program", "--show_worst_change"};
  ProgramOptions po(argc, args);
  EXPECT_EQ(CommandType::ShowWorstChange, po.getCommand());
}

TEST_F(ProgramOptionsTest, ForShowLastResultWorstChangeOptionGetCommandShouldReturnShowLastResultWorstChange)
{
  int argc = 2;
  const char *args[] = {"program", "--show_last_result_worst_change"};
  ProgramOptions po(argc, args);
  EXPECT_EQ(CommandType::ShowLastResultWorstChange, po.getCommand());
}

TEST_F(ProgramOptionsTest, ForConfigGetCommandShouldReturnConfig)
{
  int argc = 2;
  const char *args[] = {"program", "--config"};
  ProgramOptions po(argc, args);
  EXPECT_EQ(CommandType::Config, po.getCommand());
}
