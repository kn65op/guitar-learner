#ifndef ONEMINUTECHANGE_H
#define ONEMINUTECHANGE_H

#include <string>
#include <vector>
#include <iostream>

namespace OneMinuteChanges
{
  
class IOneMinuteChange
{
public:
  typedef std::vector<int> Results;
  virtual ~IOneMinuteChange() {}
  
  virtual void addResult(int result) = 0;
  virtual int bestResult() const = 0;
  virtual int lastResult() const = 0;
  virtual const Results& getResults() const = 0;
  virtual std::string getFirstChord() const = 0;
  virtual std::string getSecondChord() const = 0;
  virtual std::string print() const = 0;
};

class OneMinuteChange : public IOneMinuteChange 
{
public:
  OneMinuteChange(const std::string & chordA, const std::string & chordB);
  OneMinuteChange(std::istream &is);
  
  bool operator==(const OneMinuteChange &other) const;
  void addResult(int result) override;
  int bestResult() const override;
  int lastResult() const override;
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
