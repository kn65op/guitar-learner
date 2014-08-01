#ifndef ONEMINUTECHANGE_H
#define ONEMINUTECHANGE_H

#include <string>
#include <vector>

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
};

class OneMinuteChange : public IOneMinuteChange 
{
public:
  OneMinuteChange(const std::string & chordA, const std::string & chordB);
  
  bool operator==(const OneMinuteChange &other) const;
  void addResult(int result);
  int bestResult() const;
  int lastResult() const;
  const Results& getResults() const;
private:
  std::string first;
  std::string second;
  Results results;
};

bool operator!=(const OneMinuteChange &first, const OneMinuteChange &other);
}

#endif // ONEMINUTECHANGE_H
