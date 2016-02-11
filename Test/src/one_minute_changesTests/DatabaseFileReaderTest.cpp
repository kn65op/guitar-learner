#include "one_minute_changes/inc/DatabaseFileReader.hpp"
#include <one_minute_changes/inc/OneMinuteChangesSet.hpp>
#include "TabMock.hpp"
#include <gtest/gtest.h>

using namespace ::testing;
using Guitar::DatabaseFileReader;
using Guitar::Chord;
using Guitar::ut::TabMock;
using OneMinuteChanges::OneMinuteChangesSet;

struct DatabaseFileReaderTest : public Test
{

  void TearDown() override
  {
    Chord::clear();
    OneMinuteChangesSet().clear();
  }

  bool expectTabPrintedAsReadedWithoutCarriageReturn(const std::string& expected, const Guitar::Tab& actual)
  {
    std::string expected_without_carriage{expected};
    std::string::size_type pos;
    while ((pos = expected_without_carriage.find('\r')) != std::string::npos)
    {
      expected_without_carriage.replace(pos, 1, "");
    }
    return expected_without_carriage == actual.print();
  }
};

TEST_F(DatabaseFileReaderTest, DatabaseFileReaderShouldThrowIfNotSupportedVersion)
{
  const std::string format_header = "Ver: -1\n";
  std::stringstream oss;
  oss << format_header;

  EXPECT_THROW(DatabaseFileReader::read(oss), DatabaseFileReader::VersionNotSupported);
}

TEST_F(DatabaseFileReaderTest, DatabaseFileReaderShouldReadVer1File)
{
  const std::string format_header = "Ver: 1\n";
  const std::string format_chords_size = "2\n";
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

  const std::string format_changes_size = "2\n";
  const std::string format_change1 = "A\nD\n" "2\n1 1\n2 2\n";
  const std::string format_change2 = "A\nE\n" "3\n5 1\n2 2\n1 3\n";

  const std::string format = format_header + format_chords_size + format_chord1 + format_tab1 + format_chord2 + format_tab2 + format_changes_size + format_change1 + format_change2;

  std::stringstream oss;
  oss << format;

  DatabaseFileReader::read(oss);
  OneMinuteChangesSet omcs;

  EXPECT_EQ(2, Chord::size());
  EXPECT_NO_THROW(Chord::getChords().at("A"));
  EXPECT_NO_THROW(Chord::getChords().at("B"));
  EXPECT_TRUE(expectTabPrintedAsReadedWithoutCarriageReturn(format_tab1, Chord::getChord("A").getTab()));
  EXPECT_TRUE(expectTabPrintedAsReadedWithoutCarriageReturn(format_tab2, Chord::getChord("B").getTab()));
  EXPECT_EQ(omcs.findFirstWorstChangeByBestResult()->bestResult().first, 2);
  EXPECT_EQ(omcs.findFirstWorstChangeByLastResult()->lastResult().first, 1);
}

TEST_F(DatabaseFileReaderTest, DatabaseFileReaderShouldReadVer1FileInDosFormat)
{
  const std::string format_header = "Ver: 1\r\n";
  const std::string format_chords_size = "2\r\n";
  const std::string format_chord1 = "A\r\n";
  const std::string format_tab1 = "    1   2   3   4   5   6   7   8   9  10 \r\n"
      "E |---|---|---|---|---|-0-|---|---|---|---\r\n"
      "H |---|---|---|---|-0-|---|---|---|---|---\r\n"
      "G |---|---|---|-0-|---|---|---|---|---|---\r\n"
      "D |---|---|---|---|---|---|---|---|---|---\r\n"
      "A |---|---|---|---|---|---|---|---|---|---\r\n"
      "E |---|---|-0-|---|---|---|---|---|---|---\r\n";
  const std::string format_chord2 = "B\r\n";
  const std::string format_tab2 = "    1   2   3   4   5   6   7   8   9  10 \r\n"
      "E |-X-|---|---|---|---|---|---|---|---|---\r\n"
      "H |---|---|---|---|---|---|---|---|---|---\r\n"
      "G |---|---|---|---|---|---|---|---|---|-0-\r\n"
      "D |---|---|-0-|---|---|---|---|---|---|---\r\n"
      "A |---|---|---|---|---|---|---|---|---|-0-\r\n"
      "E |---|---|---|---|---|---|---|---|---|---\r\n";

  const std::string format_changes_size = "2\r\n";
  const std::string format_change1 = "A\r\nD\n" "2\r\n1 1\n2 3\r\n";
  const std::string format_change2 = "A\r\nE\n" "3\r\n5 1\n2 2\r\n1 3\n";

  const std::string format = format_header + format_chords_size + format_chord1 + format_tab1 + format_chord2 + format_tab2 + format_changes_size + format_change1 + format_change2;

  std::stringstream oss;
  oss << format;

  DatabaseFileReader::read(oss);
  OneMinuteChangesSet omcs;

  EXPECT_EQ(2, Chord::size());
  EXPECT_NO_THROW(Chord::getChords().at("A"));
  EXPECT_NO_THROW(Chord::getChords().at("B"));
  EXPECT_TRUE(expectTabPrintedAsReadedWithoutCarriageReturn(format_tab1, Chord::getChord("A").getTab()));
  EXPECT_TRUE(expectTabPrintedAsReadedWithoutCarriageReturn(format_tab2, Chord::getChord("B").getTab()));
  EXPECT_EQ(omcs.findFirstWorstChangeByBestResult()->bestResult().first, 2);
  EXPECT_EQ(omcs.findFirstWorstChangeByLastResult()->lastResult().first, 1);
}