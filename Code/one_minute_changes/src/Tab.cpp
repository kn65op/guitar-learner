#include "../inc/Tab.hpp"

#include <string>

using Guitar::Tab;

Tab::Tab() :
  frets{0, 0, 0, 0, 0, 0}
{
}

Tab::Tab(int fret1, int fret2, int fret3, int fret4, int fret5, int fret6) :
  frets{fret1, fret2, fret3, fret4, fret5, fret6}
{
}

std::string headerString(int n = 10)
{
  return "    1   2   3   4   5   6   7   8   9  10 \n";
}

std::string stringString(const std::string & string, int pos, int n = 10)
{
  std::string ret = string;
  ret += " ";
  if (pos == -1)
  {
    ret += "|-X-";
    for (int i = 1; i < n; ++i)
    {
      ret += "|---";
    }
  }
  else
  {
    for (int i = 1; i < n + 1; ++i)
    {
      if (pos == i)
      {
        ret += "|-0-";
      }
      else
      {
        ret += "|---";
      }
    }
  }
  return ret + "\n";;
}

std::ostream & Guitar::operator<<(std::ostream & out, const Tab &tab)
{
  
  out << headerString();
  out << stringString("E", tab.frets[0]);
  out << stringString("H", tab.frets[1]);
  out << stringString("G", tab.frets[2]);
  out << stringString("D", tab.frets[3]);
  out << stringString("A", tab.frets[4]);
  out << stringString("E", tab.frets[5]);
  return out;
}