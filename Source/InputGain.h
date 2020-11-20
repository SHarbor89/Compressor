/*
  ==============================================================================

    InputGain.h
    Created: 10 Oct 2020 9:31:43am
    Author:  Steven Harbor

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"

class InputGain : public juce::Component
{
public:
    InputGain();
    void mouseDrag(const juce::MouseEvent& event) override;
    void paint(juce::Graphics& g);
    CompressorAudioProcessor* audioProcessor{ nullptr };
private:
    float barPos = 36, ceiling = 36, height = 180, width = 30;
    juce::Image thresholdImage, bgTexture, meterTexture;
    juce::Rectangle<float> leftMeter, rightMeter;
};