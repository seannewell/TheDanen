/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
TheDanenAudioProcessorEditor::TheDanenAudioProcessorEditor (TheDanenAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (320, 268);
    
    // Intensity knob
    intensityKnob.addListener(this);
    intensityKnob.setBounds(42,46,112,235);
    intensityKnob.setRange(0.1f, 1.0f);
    intensityKnob.setNumDecimalPlacesToDisplay(2);
    //intensityKnob.setTextValueSuffix(" Hz");
    //intensityKnob.setTextBoxStyle(Slider::TextBoxBelow, false, 80, 40);
    intensityKnob.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    intensityKnob.setTextBoxStyle(Slider::NoTextBox, false, 100, 100);
    //intensityKnob.setColour(Slider::textBoxOutlineColourId, Colours::black);
    addAndMakeVisible(intensityKnob);
    
    filterKnob.addListener(this);
    filterKnob.setBounds(168,46,112,235);
    filterKnob.setRange(0.0f, 0.8f);
    filterKnob.setTextBoxStyle(Slider::NoTextBox, false, 100, 100);
    filterKnob.setNumDecimalPlacesToDisplay(2);
    filterKnob.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    addAndMakeVisible(filterKnob);
    
    
    // Time Division Box
    wholeButton.addListener(this);
    wholeButton.setColour(wholeButton.tickColourId, Colour::fromRGB(79, 52, 1));
    wholeButton.setColour(wholeButton.tickDisabledColourId, Colour::fromRGB(79, 52, 1));
    wholeButton.setButtonText("1");
    wholeButton.setBounds((getWidth()/6 * 1) -7,225,50,50);
    wholeButton.setToggleState(true,dontSendNotification);
    wholeButton.setRadioGroupId(1);
    addAndMakeVisible(wholeButton);
    
    halfButton.addListener(this);
    halfButton.setColour(wholeButton.tickColourId, Colour::fromRGB(79, 52, 1));
    halfButton.setColour(wholeButton.tickDisabledColourId, Colour::fromRGB(79, 52, 1));
    halfButton.setBounds((getWidth()/6 * 2)-7,225,50,50);
    halfButton.setRadioGroupId(1);
    addAndMakeVisible(halfButton);
    
    quarterButton.addListener(this);
    quarterButton.setColour(wholeButton.tickColourId, Colour::fromRGB(79, 52, 1));
    quarterButton.setColour(wholeButton.tickDisabledColourId, Colour::fromRGB(79, 52, 1));
    quarterButton.setBounds((getWidth()/6 * 3)-7,225,50,50);
    quarterButton.setRadioGroupId(1);
    addAndMakeVisible(quarterButton);
    
    dottedEightButton.addListener(this);
    dottedEightButton.setColour(wholeButton.tickColourId, Colour::fromRGB(79, 52, 1));
    dottedEightButton.setColour(wholeButton.tickDisabledColourId, Colour::fromRGB(79, 52, 1));
    dottedEightButton.setBounds((getWidth()/6 * 4)-7,225,50,50);
    dottedEightButton.setRadioGroupId(1);
    addAndMakeVisible(dottedEightButton);
    
    eightButton.addListener(this);
    eightButton.setColour(wholeButton.tickColourId, Colour::fromRGB(79, 52, 1));
    eightButton.setColour(wholeButton.tickDisabledColourId, Colour::fromRGB(79, 52, 1));
    eightButton.setBounds((getWidth()/6 * 5)-7,225,50,50);
    eightButton.setRadioGroupId(1);
    addAndMakeVisible(eightButton);
}

TheDanenAudioProcessorEditor::~TheDanenAudioProcessorEditor()
{
}

//==============================================================================
void TheDanenAudioProcessorEditor::paint (Graphics& g)
{
    // Background Color
    g.fillAll(Colours::ivory);
    
    g.setGradientFill(ColourGradient(Colours::orange, 0, 0, Colours::lightyellow, 250, 60, true));
    g.setOpacity(0.7);
    g.fillRect(0,0,320,268);
    
    g.setColour (Colour::fromRGB(173, 116, 6));
    g.drawRoundedRectangle(58,15, 199, 70, 10, 2);
    
    
    // Plugin Name
    g.setColour (Colour::fromRGB(173, 116, 6));

    g.setFont (Font ("DraftWerk", 44.0f, Font::plain));
    g.drawFittedText ("THE DANEN", 77,-25,160,150, Justification::centred, 1);
    
    
    
    // Knobs
    g.setFont(17.0f);
    getLookAndFeel().setColour(Slider::thumbColourId, Colour::fromRGB(173, 116, 6));
    getLookAndFeel().setColour(Slider::rotarySliderFillColourId,Colour::fromRGBA(173, 116,6,230));
    getLookAndFeel().setColour(Slider::rotarySliderOutlineColourId,Colour::fromRGB(79, 52, 1));
    g.drawText("INTENSITY", 42, 108, 112, 235, Justification::centred, false);
    g.drawText("FILTER", 168,108, 112, 235, Justification::centred, false);
    
    
    // Button Labels
    g.setFont(13.0f);
    g.drawFittedText ("1", (getWidth()/6 * 1),225,50,50, Justification::centred, 1);
    g.drawFittedText ("1/2", (getWidth()/6 * 2),225,50,50, Justification::centred, 1);
    g.drawFittedText ("1/4", (getWidth()/6 * 3),225,50,50, Justification::centred, 1);
    g.drawFittedText (".1/8", (getWidth()/6 * 4),225,50,50, Justification::centred, 1);
    g.drawFittedText ("1/8", (getWidth()/6 * 5),225,50,50, Justification::centred, 1);

    
    // (Our component is opaque, so we must completely fill the background with a solid colour)
//    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
//
//    g.setColour (Colours::white);
//    g.setFont (15.0f);
//    g.drawFittedText ("Hello World!", getLocalBounds(), Justification::centred, 1);
}

void TheDanenAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

void TheDanenAudioProcessorEditor::sliderValueChanged(Slider* slider){
    if (slider == &intensityKnob){
        *processor.lfoDepth = slider->getValue();
        processor.softClipper.setDrive(slider->getValue() * 10);
    }
    
    if (slider == &filterKnob){
        processor.hpf1.setAmount(slider->getValue());
    }
    
    startTimer(60);
    
}


void TheDanenAudioProcessorEditor::buttonClicked(Button* button){
    // convert BPM to frequency to note length
    if (button == &wholeButton){
        processor.lfoFreq = (processor.getBPM()/60) / 4;
    }
    if (button == &halfButton){
        processor.lfoFreq = (processor.getBPM() / 60) / 2;
        
    }
    if (button == &quarterButton){
        processor.lfoFreq = (processor.getBPM() / 60) / 1;
    }
    if (button == &dottedEightButton){
        processor.lfoFreq = (processor.getBPM() / 60) / 0.75f;
    }
    if (button == &eightButton){
        processor.lfoFreq = (processor.getBPM() / 60) / 0.5f;
    }
}

void TheDanenAudioProcessorEditor::timerCallback()
{
    if (intensityKnob.getValue() != *processor.lfoDepth){
        //intensityKnob.setValue(*processor.lfoDepth);
    }
    
    if (filterKnob.getValue() != processor.hpf1.getAmount()){
        //filterKnob.setValue(processor.hpf1.getAmount());
    }
    
    
    stopTimer();
    
}










