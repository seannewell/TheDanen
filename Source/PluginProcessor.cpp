/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
TheDanenAudioProcessor::TheDanenAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    addParameter(lfoDepth = new AudioParameterFloat("lfoDepth", // parameter ID
                                               "Depth", // Name in DAW
                                               0.f, // Min value
                                               1, // Max value
                                               0.1f)); // Default Value
}

TheDanenAudioProcessor::~TheDanenAudioProcessor()
{
}

//==============================================================================
const String TheDanenAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool TheDanenAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool TheDanenAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool TheDanenAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double TheDanenAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int TheDanenAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int TheDanenAudioProcessor::getCurrentProgram()
{
    return 0;
}

void TheDanenAudioProcessor::setCurrentProgram (int index)
{
}

const String TheDanenAudioProcessor::getProgramName (int index)
{
    return {};
}

void TheDanenAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void TheDanenAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    Fs = sampleRate;
}

void TheDanenAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool TheDanenAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void TheDanenAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    const int totalNumInputChannels  = getTotalNumInputChannels();
    const int totalNumOutputChannels = getTotalNumOutputChannels();

    playHead = this->getPlayHead();
    playHead->getCurrentPosition (currentPositionInfo);
    
    //get tempo & position info from Host
    setBPM();

    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    // Update lfoAmp & Offset once per buffer
    lfoAmp = 0.5f * *lfoDepth;
    lfoOffset = (1.0f - lfoAmp);

    for (int sample = 0; sample < buffer.getNumSamples() ; ++sample){
        angleChange = lfoFreq * 2.0f * M_PI / (float)Fs;
        lfo = lfoAmp * nextLFOSample() + lfoOffset;
        
        currentAngle += angleChange;
        
        if (currentAngle > (2*M_PI)){
            currentAngle -= (2*M_PI);
        }

        for (int channel = 0; channel < totalNumInputChannels ; ++channel){
            x = buffer.getWritePointer(channel)[sample];
            
            // put signal through soft clippper
            float y = softClipper.processSample(x * lfo);

            // put signal through HPF
            y = hpf1.processSample(y, channel);
            
            buffer.getWritePointer(channel)[sample] = y;  
        }
    }
}

//==============================================================================
bool TheDanenAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* TheDanenAudioProcessor::createEditor()
{
    return new TheDanenAudioProcessorEditor (*this);
}

//==============================================================================
void TheDanenAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    ScopedPointer<XmlElement> xml (new XmlElement("TheDanenAudioProcessorParams"));
    xml->setAttribute("lfoDepth", (float)*lfoDepth);
    copyXmlToBinary(*xml, destData);
}

void TheDanenAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    ScopedPointer<XmlElement> xmlState (getXmlFromBinary(data, sizeInBytes));

    if (xmlState != nullptr){
        if(xmlState->hasTagName("TheDanenAudioProcessorParams")){
            *lfoDepth = xmlState->getDoubleAttribute("lfoDepth",0.1f);

            // variable = xmlState->getDoubleAttribute("otherID",defaultValue);
        }
    }
}

// Naive sawtooth wave
float TheDanenAudioProcessor::sawtoothSynth(){
    return 2.0f * (currentAngle/(2*M_PI)) - 1.0f;
}

// Found this function on the following website:
// http://www.martin-finke.de/blog/articles/audio-plugins-018-polyblep-oscillator/
float TheDanenAudioProcessor::polyBLEP(float t){
    float dt = angleChange / (2 * M_PI);
    // Beginning of wave
    if (t < dt) {
        t /= dt;
        return t+t - t*t - 1.f;
    }
    // End of wave
    else if (t > 1.f - dt) {
        t = (t - 1.f) / dt;
        return t*t + t+t + 1.f;
    }
    else return 0.0f;
}

float TheDanenAudioProcessor::nextLFOSample(){
    float value = 0.f;
    float t = currentAngle / (2 * M_PI);
    value = sawtoothSynth();
    value -= polyBLEP(t);
    // Prevent values from going above 1 or below 0
    if (value < 0){
        return 0;
    }
    if (value > 1){
        return 1;
    }
    return value;
}

void TheDanenAudioProcessor::setFreq(float freq){
    lfoFreq = freq;
}
float TheDanenAudioProcessor::getFreq(){
    return lfoFreq;
}


void TheDanenAudioProcessor::setBPM(){
    BPM = currentPositionInfo.bpm;
}
float TheDanenAudioProcessor::getBPM(){
    return BPM;
}





//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new TheDanenAudioProcessor();
}







