#ifndef SUPA_STIMER_H
#define SUPA_STIMER_H


class STimer
{
  public:
    STimer();
    void reset(); // Use all time
    void reset_with_carry( unsigned long timeout_ms ); // Use given amount of time 
    bool check( unsigned long timeout_ms ); /// check if @param timeout_ms milliseconds has passed since last reset.
    
  protected:
    unsigned long reset_ms;
};



#endif