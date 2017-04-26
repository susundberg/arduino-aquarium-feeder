#ifndef SUPA_DELAY_H
#define SUPA_DELAY_H

class DelayFromPin
{
   
   
 public:
    constexpr static const int delay_multiplier = (12*60); // one unit is 12h.
    
    void setup( int pin_1, int pin_2, int pin_4 );
    void loop();
    
    /// @returns delay between the holes in minutes
    int  get_delay_min();  
    
  protected:
    int pins[3];
    int delay;
};

#endif