/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

    Author: Steven Harbor

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Visualizer.h"
#include "Knob.h"
#include "InputGain.h"
#include "OutputGain.h"

//==============================================================================
/**
*/
class CompressorAudioProcessorEditor  : public juce::AudioProcessorEditor
    , public juce::Timer
{
public:
    CompressorAudioProcessorEditor (CompressorAudioProcessor&);
    ~CompressorAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    void timerCallback() override;

private:
    juce::Slider gainSlider;
    juce::Label gainLabel;
    juce::Label gainValueLabel;
    
    juce::Slider ratioSlider;
    juce::Label ratioLabel;
    juce::Label ratioValueLabel;

    juce::Slider kneeSlider;
    juce::Label kneeLabel;
    juce::Label kneeValueLabel;

    juce::Slider attackSlider;
    juce::Label attackLabel;
    juce::Label attackValueLabel;

    juce::Slider releaseSlider;
    juce::Label releaseLabel;
    juce::Label releaseValueLabel;

    juce::Slider sustainSlider;
    juce::Label sustainLabel;
    juce::Label sustainValueLabel;

    juce::Slider peakRMSSlider;
    juce::Label RMSLabel;
    juce::Label peakLabel;

    juce::Label versionNumber;
    
    juce::Image bgTexture;
    int sliderHeight = 100, sliderWidth = 100;
    CompressorAudioProcessor& audioProcessor;
    Knob knob;
    InputGain inputGain;
    OutputGain outputGain;
    Visualizer visualizer;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CompressorAudioProcessorEditor)
};