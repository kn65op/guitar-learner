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
  EXPECT_EQ(Chord::size(), 0u);
}

TEST_F(ChordTest, AfterChordAdditionShouldHaveOneElement)
{
  Tab tab;
  Chord::add("A", tab);
  EXPECT_EQ(1u, Chord::size());
}

TEST_F(ChordTest, AfterClearChordsShouldBeEmpty)
{
  Tab tab;
  Chord::add("A", tab);
  ASSERT_EQ(1u, Chord::size());
  Chord::clear();
  EXPECT_EQ(0u, Chord::size());
}

TEST_F(ChordTest, GetChordsShouldReturnAddedChords)
{
  Tab tab;
  Chord::add("A", tab);
  Chord::add("B", tab);
  ASSERT_EQ(2u, Chord::size());

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

TEST_F(ChordTest, GetChordShouldThrowNotExistWhenGetNotExistedChord)
{
  EXPECT_THROW(Chord::getChord("A"), Chord::NotExist);
}

TEST_F(ChordTest, GetChordShouldReturnChordWithSameTab)
{
  Tab tab{1, 2, 3, 4, 5, 6};
  Chord::add("B", tab);
  EXPECT_EQ(tab.print(), Chord::getChord("B").getTab().print());
}

TEST_F(ChordTest, ChordShouldNotChangeNotexistingElements)
{
  EXPECT_THROW(Chord::changeChords("A", Tab{}), Chord::NotExist);
}

TEST_F(ChordTest, ChordShouldChangeTab)
{
  Tab old_tab;
  Tab new_tab{1, 2, 3, 4, 5, 6};
  Chord::add("A", old_tab);
  Chord::changeChords("A", new_tab);
  EXPECT_NE(old_tab.print(), Chord::getChord("A").getTab().print());
  EXPECT_EQ(new_tab.print(), Chord::getChord("A").getTab().print());
}

TEST_F(ChordTest, ChordShouldRemoveChordWhenPrompted)
{
  Tab tab;
  Chord::add("A", tab);
  ASSERT_EQ(1u, Chord::size());
  Chord::removeChord("A");
  EXPECT_EQ(0u, Chord::size());
}

TEST_F(ChordTest, ChordShouldThrowWhenTryToRemoveNotExistingChord)
{
  EXPECT_THROW(Chord::removeChord("A"), Chord::NotExist);
}

TEST_F(ChordTest, ChordShouldThrowWhenTryToRemoveNotExistingChordAndSomeOtherChordsExixsts)
{
  Tab tab;
  Chord::add("A", tab);
  ASSERT_EQ(1u, Chord::size());
  EXPECT_THROW(Chord::removeChord("b"), Chord::NotExist);
  ASSERT_EQ(1u, Chord::size());
}

TEST_F(ChordTest, ShouldNotFindNotExistingChord)
{
  EXPECT_FALSE(Chord::exists("A"));
}

TEST_F(ChordTest, whenAvailable_ShouldFindNotExistingChord)
{
  Tab tab;
  Chord::add("A", tab);
  EXPECT_TRUE(Chord::exists("A"));
  EXPECT_FALSE(Chord::exists("W"));
}