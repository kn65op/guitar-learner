#ifndef ONEMINUTECHANGE_H
#define ONEMINUTECHANGE_H

#include <string>
#include <vector>
#include <iostream>

#include "Chord.hpp"

namespace OneMinuteChanges
{

class IOneMinuteChange
{
public:
  using ResultType = int;
  typedef std::vector<ResultType> Results;

  virtual ~IOneMinuteChange()
  {
  }

  virtual bool operator==(const IOneMinuteChange &other) const = 0;
  virtual void addResult(ResultType result) = 0;
  virtual ResultType bestResult() const = 0;
  virtual ResultType lastResult() const = 0;
  virtual const Results& getResults() const = 0;
  virtual std::string getFirstChord() const = 0;
  virtual std::string getSecondChord() const = 0;
  virtual std::string print() const = 0;
};

class OneMinuteChange : public IOneMinuteChange
{
public:
  OneMinuteChange(const Guitar::Chord::ChordNameType & chordA, const Guitar::Chord::ChordNameType & chordB);
  OneMinuteChange(std::istream &is);

  bool operator==(const IOneMinuteChange &other) const override;
  void addResult(ResultType result) override;
  ResultType bestResult() const override;
  ResultType lastResult() const override;
  const Results& getResults() const override;
  std::string getFirstChord() const override;
  std::string getSecondChord() const override;
  std::string print() const override;
private:
  std::string first;
  std::string second;
  Results results;
};

bool operator!=(const OneMinuteChange &first, const OneMinuteChange &other);
std::ostream & operator<<(std::ostream & os, const OneMinuteChange &omc);
}

#endif // ONEMINUTECHANGE_H
