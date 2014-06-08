#ifndef ONEMINUTECHANGE_H
#define ONEMINUTECHANGE_H

#include <string>
#include <vector>

namespace OneMinuteChanges
{
class OneMinuteChange
{
public:
  OneMinuteChange(const std::string & chordA, const std::string & chordB);
  
  bool operator==(const OneMinuteChange &other) const;
  void addResult(int result);
  int bestResult() const;
private:
  typedef std::vector<int> Results;
  
  std::string first;
  std::string second;
  Results results;
};

bool operator!=(const OneMinuteChange &first, const OneMinuteChange &other);
}

#endif // ONEMINUTECHANGE_H
