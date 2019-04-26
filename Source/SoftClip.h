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
    
    float getDrive(){
        return drive;
    };
    
private:

    
    // Variables for Soft Clipper
    float drive = 1.f;
    
};


#endif /* SoftClip_h */
