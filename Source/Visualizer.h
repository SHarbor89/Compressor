/*
  ==============================================================================

    Visualizer.h
    Created: 28 Sep 2020 3:56:03pm
    Author:  Steven Harbor

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"

class Visualizer : public juce::Component
{
public:
    Visualizer();
    void paint(juce::Graphics& g) override;
    void mouseDrag(const juce::MouseEvent& event) override;
    CompressorAudioProcessor* audioProcessor{nullptr};
    std::array<float, CompressorAudioProcessor::historySize>* history{ nullptr };
    int* writeMarker{ nullptr };
    int barPos = 36;
private:
    //juce::Rectangle<float> bg;
    juce::Image thresholdImage;
    juce::Image bgTexture, waveTexture;
    juce::Slider thresholdSlider;
    float height = 180, width = 400, ceiling = 36;
};