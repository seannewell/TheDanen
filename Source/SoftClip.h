/*
  ==============================================================================

    SoftClip.h
    Created: 13 Apr 2019 9:20:01am
    Author:  Sean Newell

  ==============================================================================
*/

#ifndef SoftClip_h
#define SoftClip_h



class SoftClip {
    
    
public:
    float processSample(float x){
        float y;
        
        y = (2.0f/M_PI) * atanf(drive * x);
        
        return y;
    };
    
    void setDrive(float d){
        if (d <= 11.0f) {
            if (d >= 1.0f){
                drive = d;
            }
        }
    };
    // Reason: we want to control how a variable is manipulated
    
    float getDrive(){
        return drive;
    };
    
private:
    // Good practice: make variables private,
    // create "get" and "set" methods for their use
    
    // Variables for Soft Clipper
    float drive = 1.0f;
    
};


#endif /* SoftClip_h */
