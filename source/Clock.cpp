#include <string>
#include "Clock.h" 

using namespace std;

//Public methods
Clock::Clock()
{
  this->hours = 23;//-1;
  this->minutes = 40;//-1;
  this->seconds = 40;//-1;
  this->year = -1;
  this->month = -1;
  this->day = -1;
  this->currentMs = 0;
}

string Clock::Show()
{
  string retString;
  if (this->isTimeSet())
  {
    if (this->hours < 10)
      retString.append("0");
    retString.append(to_string(this->hours));
    retString.append(":");
    if (this->minutes < 10)
      retString.append("0");
    retString.append(to_string(this->minutes));
    retString.append(":");
    if (this->seconds < 10)
      retString.append("0");
    retString.append(to_string(this->seconds));
  }
  else
  {
    retString.append("--:--");
  }
  return retString;
}

void Clock::Tick(int newRuntimeMs)
{
  if (!this->isTimeSet())
    return;
  if (this->currentMs == 0)
    this->currentMs = newRuntimeMs;

  int msDiff = newRuntimeMs - this->currentMs;
  int seconds = msDiff / 1000;
  int remainderMs = msDiff % 1000;
  for(int i = 0; i < seconds; i++)
  {
    this->incrementSecond();
  }
  this->currentMs = newRuntimeMs - remainderMs;
};

//Private methods
bool Clock::isTimeSet()
{
  if (this->hours == -1 || this->minutes == -1 || this->seconds == -1)
    return false;
  return true;
};
void Clock::incrementHour()
{
  if (this->hours < 23)
    this->hours++;
  else
    this->hours = 0;
};
void Clock::incrementMinute()
{
  if (this->minutes < 59)
    this->minutes++;
  else
  {
    this->incrementHour();
    this->minutes = 0;
  }
};
void Clock::incrementSecond()
{
  if (this->seconds < 59)
    this->seconds++;
  else
  {
    this->incrementMinute();
    this->seconds = 0;
  }
};
