#ifndef TAB_H
#define TAB_H

#include <ostream>
#include <istream>
#include <array>

namespace Guitar
{
  
class ITab
{
public:
  virtual ~ITab() {}
  virtual std::string print() const = 0;
};

class Tab : public ITab
{
public:
  Tab();
  explicit Tab(int fret1, int fret2, int fret3, int fret4, int fret5, int fret6);
  Tab(std::istream & in);
  
  std::string print() const override;
private:
  
  static const int stream_count = 6;
  
  std::array<int, stream_count> frets;
  void parseInputStream(std::istream &in);
};

std::ostream & operator<<(std::ostream & out, const ITab &tab);

}

#endif // TAB_H
