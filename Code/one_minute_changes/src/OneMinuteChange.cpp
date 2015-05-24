#include "../inc/OneMinuteChange.hpp"
#include <algorithm>
#include <sstream>

using OneMinuteChanges::OneMinuteChange;

OneMinuteChange::OneMinuteChange(const Guitar::Chord::ChordNameType &chordA, const Guitar::Chord::ChordNameType &chordB) :
    first(std::min(chordA, chordB)),
    second(std::max(chordA, chordB)),
    results() {}

OneMinuteChange::OneMinuteChange(std::istream &is)
{
  is >> first;
  is >> second;
  Results::size_type size;
  is >> size;
  for (Results::size_type i = 0; i < size; ++i)
  {
    ResultValue res;
    is >> res;
    StoredDuration::rep read_rep;
    is >> read_rep;
    StoredDuration dur{read_rep};
//    std::chrono::duration<StoredDuration> duration{dur};
    results.push_back(std::make_pair(res, DateType{dur}));
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

void OneMinuteChange::addResult(ResultValue result)
{
  results.push_back(std::make_pair(result, getNow()));
}

OneMinuteChange::ResultType OneMinuteChange::bestResult() const
{
  auto max = std::max_element(results.begin(), results.end());
  if (max != results.end())
  {
    return *max;
  }
  return {0, getNow()};
}

const OneMinuteChange::Results& OneMinuteChange::getResults() const
{
  return results;
}

OneMinuteChange::ResultType OneMinuteChange::lastResult() const
{
  if (results.empty())
  {
    return {0, getNow()};
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
  //ss << std::chrono::duration_cast<StoredDuration>(add_date.time_since_epoch()).count() << "\n";
 // ss << add_date.time_since_epoch().count() << "\n";
  ss << results.size() << "\n";
  for (auto res : results)
  {
    ss << res.first << " "  <<
        std::chrono::duration_cast<StoredDuration>(res.second.time_since_epoch()).count() << "\n";
  }
  return ss.str();
}

std::ostream& OneMinuteChanges::operator<<(std::ostream &os, const OneMinuteChange& omc)
{
  os << omc.print();
  return os;
}

OneMinuteChange::DateType OneMinuteChange::getNow()
{
  return std::chrono::system_clock::now();
}