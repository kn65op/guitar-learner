#ifndef ONEMINUTECHANGE_H
#define ONEMINUTECHANGE_H

#include <string>
#include <vector>
#include <iostream>
#include <chrono>
#include <stdexcept>

#include "Chord.hpp"

namespace OneMinuteChanges
{

class IOneMinuteChange
{
public:
  using Clock = std::chrono::system_clock;
  using StoredDuration = std::chrono::seconds;
  using DateType = Clock::time_point;
  using ResultValue = int;
  using ResultType = std::pair<ResultValue, DateType>;
  using Results = std::vector<ResultType>;

  class NoResultsError : public std::logic_error
  {
  public:
    NoResultsError(const std::string& message) : std::logic_error(message) {}

  };

  virtual ~IOneMinuteChange() = default;

  virtual bool operator==(const IOneMinuteChange &other) const = 0;
  virtual void addResult(ResultValue result) = 0;
  virtual ResultType bestResult() const = 0;
  virtual ResultType lastResult() const = 0;
  virtual const Results& getResults() const = 0;
  virtual std::string getFirstChord() const = 0;
  virtual std::string getSecondChord() const = 0;
  virtual std::string print() const = 0;
  virtual bool hasResults() const = 0;
};

class OneMinuteChange : public IOneMinuteChange
{
public:
  OneMinuteChange(const Guitar::Chord::ChordNameType & chordA, const Guitar::Chord::ChordNameType & chordB);
  OneMinuteChange(std::istream &is);

  bool operator==(const IOneMinuteChange &other) const override;
  void addResult(ResultValue result) override;
  ResultType bestResult() const override;
  ResultType lastResult() const override;
  const Results& getResults() const override;
  std::string getFirstChord() const override;
  std::string getSecondChord() const override;
  std::string print() const override;
  bool hasResults() const override;

private:
  std::string first;
  std::string second;
  Results results;

  static DateType getNow();
};

bool operator!=(const OneMinuteChange &first, const OneMinuteChange &other);
std::ostream & operator<<(std::ostream & os, const OneMinuteChange &omc);

inline bool operator<=(const IOneMinuteChange::ResultType& first, const IOneMinuteChange::ResultType& second)
{
  return first.first <= second.first;
}

}

#endif // ONEMINUTECHANGE_H
