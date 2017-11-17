#include <string>
#include <stdint.h>

using namespace std;

class Clock
{
  private:
    int8_t hours;
    int8_t minutes; 
    int8_t seconds;
    int8_t year;
    int8_t month;
    int8_t day;
    uint32_t currentMs;
  
    bool isTimeSet();
    void incrementHour();
    void incrementMinute();
    void incrementSecond();
  public:
    Clock();
    string Show();
    void Tick(int newRuntimeMs);
};
