/*
  ==============================================================================

    HighPassFilter.h
    Created: 12 Apr 2019 11:52:56pm
    Author:  Sean Newell

  ==============================================================================
*/

#ifndef HighPassFilter_h
#define HighPassFilter_h


class HighPassFilter {
    
public:
    // Functions for HPF
    float processSample(float x,int channel){
        
        float y;
        
        y = (1.f - mix) * x + (-mix * delaySample[channel]);
        
        delaySample[channel] = x;
        
        return y;
    };
    
    
    void setAmount(float a){
        if (a >= 0 && a <= 1) {
            amount = a;
            mix = amount * 0.5f;
        }
    };
    
    float getAmount(){
        return amount;
    };
    
private:
    
    float amount = 1.0f;
    
    float mix = 0.5f;
    
    float delaySample[2] = {0.0f};
    
};


#endif
