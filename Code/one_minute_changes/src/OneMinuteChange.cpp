#include "../inc/OneMinuteChange.hpp"
#include <algorithm>
#include <sstream>

using OneMinuteChanges::OneMinuteChange;

OneMinuteChange::OneMinuteChange(const Guitar::Chord::ChordNameType &chordA, const Guitar::Chord::ChordNameType &chordB) :
    first(std::min(chordA, chordB)),
    second(std::max(chordA, chordB)),
    results() { }

OneMinuteChange::OneMinuteChange(std::istream &is)
{
  is >> first;
  is >> second;
  Results::size_type size;
  is >> size;
  for (Results::size_type i = 0; i < size; ++i)
  {
    Results::value_type res;
    is >> res;
    results.push_back(res);
  }

}

bool OneMinuteChange::operator==(const IOneMinuteChange &other) const
{
  return first == other.getFirstChord() && second == other.getSecondChord();
}

bool OneMinuteChanges::operator!=(const OneMinuteChange &first, const OneMinuteChange &other)
{
  return !(first == other);
}

void OneMinuteChange::addResult(int result)
{
  results.push_back(result);
}

int OneMinuteChange::bestResult() const
{
  auto max = std::max_element(results.begin(), results.end());
  if (max != results.end())
  {
    return *max;
  }
  return 0;
}

const OneMinuteChange::Results& OneMinuteChange::getResults() const
{
  return results;
}

int OneMinuteChange::lastResult() const
{
  if (results.empty())
  {
    return 0;
  }
  return results.back();
}

std::string OneMinuteChange::getFirstChord() const
{
  return first;
}

std::string OneMinuteChange::getSecondChord() const
{
  return second;
}

std::string OneMinuteChange::print() const
{
  std::stringstream ss;
  ss << first << "\n";
  ss << second << "\n";
  ss << results.size() << "\n";
  for (auto res : results)
  {
    ss << res << "\n";
  }
  return ss.str();
}

std::ostream& OneMinuteChanges::operator<<(std::ostream &os, const OneMinuteChange& omc)
{
  os << omc.print();
  return os;
}