/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "HighPassFilter.h"


//==============================================================================
/**
*/
class TheDanenAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    TheDanenAudioProcessor();
    ~TheDanenAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect () const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    float lfoFreq = 1.2f;
    float lfoDepth = 0.0f;
    
    HighPassFilter hpf1;
    
private:
    
    
    
    float x = 0.0f;
    
    
    
    float sawtoothSynth(float angle);
    float lfo = 0.0f;
    float lfoAmp = 0.0f;
    float lfoOffset = 0.0f;
    float currentAngle = 0.0f;
    float angleChange = 0.0f;
    
    
    int Fs = 48000;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TheDanenAudioProcessor)
};
