#include "one_minute_changes/inc/DatabaseFileReader.hpp"       
#include "TabMock.hpp"
#include <gtest/gtest.h>

using namespace ::testing;
using Guitar::DatabaseFileReader;
using Guitar::Chord;
using Guitar::ut::TabMock;

struct DatabaseFileReaderTest : public Test
{
  void TearDown() override
  {
    Chord::clear();
  }
};

TEST_F(DatabaseFileReaderTest, DatabaseFileReaderShouldReadVer1File)
{
  const std::string format_header = "Ver: 1\n";
  const std::string format_size = "2\n";
  const std::string format_chord1 = "A\n";
  const std::string format_tab1 = "    1   2   3   4   5   6   7   8   9  10 \n"
            "E |---|---|---|---|---|-0-|---|---|---|---\n" 
            "H |---|---|---|---|-0-|---|---|---|---|---\n" 
            "G |---|---|---|-0-|---|---|---|---|---|---\n" 
            "D |---|---|---|---|---|---|---|---|---|---\n" 
            "A |---|---|---|---|---|---|---|---|---|---\n" 
            "E |---|---|-0-|---|---|---|---|---|---|---\n";
  const std::string format_chord2 = "B\n";
  const std::string format_tab2 = "    1   2   3   4   5   6   7   8   9  10 \n"
            "E |-X-|---|---|---|---|---|---|---|---|---\n" 
            "H |---|---|---|---|---|---|---|---|---|---\n" 
            "G |---|---|---|---|---|---|---|---|---|-0-\n" 
            "D |---|---|-0-|---|---|---|---|---|---|---\n" 
            "A |---|---|---|---|---|---|---|---|---|-0-\n" 
            "E |---|---|---|---|---|---|---|---|---|---\n";
  
  const std::string format = format_header + format_size + format_chord1 + format_tab1 + format_chord2 + format_tab2;
  
  std::stringstream oss;
  oss << format;
  
  DatabaseFileReader::read(oss);
  
  EXPECT_EQ(2, Chord::size());
  EXPECT_NO_THROW(Chord::getChords().at("A"));
  EXPECT_NO_THROW(Chord::getChords().at("B"));
}