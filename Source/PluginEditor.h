/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"


//==============================================================================
/**
*/
class TheDanenAudioProcessorEditor  : public AudioProcessorEditor, public Slider::Listener,public Button::Listener,public Timer
{
public:
    TheDanenAudioProcessorEditor (TheDanenAudioProcessor&);
    ~TheDanenAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    void sliderValueChanged(Slider* slider) override;
    void buttonClicked(Button* button) override;
    void timerCallback() override;
    
private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    TheDanenAudioProcessor& processor;
    
    
    Slider intensityKnob;
    Slider filterKnob;
    
    ToggleButton wholeButton;   // Interface buttons to switch between different
    ToggleButton halfButton;    // time Subdivisions
    ToggleButton quarterButton;
    ToggleButton dottedEightButton;
    ToggleButton eightButton;
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TheDanenAudioProcessorEditor)
};










