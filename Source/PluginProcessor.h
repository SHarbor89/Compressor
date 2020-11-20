/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

    Author: Steven Harbor

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
*/
class CompressorAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    CompressorAudioProcessor();
    ~CompressorAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    

    //==============================================================================
    void setInputGain(double newGain);
    void setOutputGain(double newGain);
    void setThreshold(double newThreshold);
    void setRatio(double newRatio);
    void setKnee(double newKnee);
    void setAttack(double newAttack);
    void setRelease(double newRelease);
    void setSustain(double newSustain);
    void toggleCompressorType();

    static const int historySize = 200;
    std::array<float,historySize> history;
    int writeMarker = 0;
    float leftInputLevel = 0, rightInputLevel = 0, leftOutputLevel = 0, rightOutputLevel = 0;
    bool compressorType = false;
    double inputGain = 1.0, outputGain = 1.0, threshold = 1, ratio = 1, knee = 0, attack = 0, release = 0, sustain = 0;
private:
    
    
    int counter = 0, waveFormAccuracy = 160;
    juce::dsp::Compressor<float> compressor;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CompressorAudioProcessor)
};
