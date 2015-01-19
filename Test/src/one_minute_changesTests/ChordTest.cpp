#include "one_minute_changes/inc/Chord.hpp"
#include "TabMock.hpp"
#include <gtest/gtest.h>

using namespace ::testing;
using Guitar::Chord;
using Guitar::ut::TabMock;
using Guitar::Tab;

struct ChordTest : public Test
{

  void TearDown() override
  {
    Chord::clear();
  }
};

TEST_F(ChordTest, ChordListShouldBeEmptyAtStart)
{
  EXPECT_EQ(Chord::size(), 0);
}

TEST_F(ChordTest, AfterChordAdditionShouldHaveOneElement)
{
  Tab tab;
  Chord::add("A", tab);
  EXPECT_EQ(1, Chord::size());
}

TEST_F(ChordTest, AfterClearChordsShouldBeEmpty)
{
  Tab tab;
  Chord::add("A", tab);
  ASSERT_EQ(1, Chord::size());
  Chord::clear();
  EXPECT_EQ(0, Chord::size());
}

TEST_F(ChordTest, GetChordsShouldReturnAddedChords)
{
  Tab tab;
  Chord::add("A", tab);
  Chord::add("B", tab);
  ASSERT_EQ(2, Chord::size());

  Chord::Chords chords = Chord::getChords();
  EXPECT_EQ("A", chords.at("A").getName());
  EXPECT_EQ("B", chords.at("B").getName());
}

TEST_F(ChordTest, AddingAlreadyAddedChordShouldThrow)
{
  Tab tab;
  Chord::add("A", tab);
  ASSERT_THROW(Chord::add("A", tab), Chord::AlreadyAdded);
}

TEST_F(ChordTest, GetTabShouldReturnTab)
{
  Tab tab;
  Chord::add("A", tab);
}

TEST_F(ChordTest, ChordShouldPrintItself)
{
  const std::string format_tab = "    1   2   3   4   5   6   7   8   9  10 \nE |---|---|---|---|---|---|---|---|---|---\nH |---|---|---|---|---|---|---|---|---|---\nG |---|---|---|---|---|---|---|---|---|---\nD |---|---|---|---|---|---|---|---|---|---\nA |---|---|---|---|---|---|---|---|---|---\nE |---|---|---|---|---|---|---|---|---|---\n";
  const std::string format_chord = "A\n";
  const std::string format = format_chord + format_tab;
  Tab tab;
  Chord::add("A", tab);
  Chord A = Chord::getChords().at("A");
  std::stringstream ss;
  ss << A;
  EXPECT_EQ(format, ss.str());
}

TEST_F(ChordTest, ChordShouldNotChangeNotexistingElements)
{
  EXPECT_THROW(Chord::change("A", Tab{}), Chord::NotExist);
}

