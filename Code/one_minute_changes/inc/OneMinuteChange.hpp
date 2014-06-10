#ifndef ONEMINUTECHANGE_H
#define ONEMINUTECHANGE_H

#include <string>
#include <vector>

namespace OneMinuteChanges
{
class OneMinuteChange
{
public:
  typedef std::vector<int> Results;
  
  OneMinuteChange(const std::string & chordA, const std::string & chordB);
  
  bool operator==(const OneMinuteChange &other) const;
  void addResult(int result);
  int bestResult() const;
  const Results& getResults() const;
private:
  std::string first;
  std::string second;
  Results results;
};

bool operator!=(const OneMinuteChange &first, const OneMinuteChange &other);
}

#endif // ONEMINUTECHANGE_H
