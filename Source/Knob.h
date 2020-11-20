/*
  ==============================================================================

    Knob.h
    Created: 7 Oct 2020 3:27:04pm
    Author:  Steven Harbor

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class Knob : public juce::LookAndFeel_V4
{
public:
    Knob();
    ~Knob();
    void drawRotarySlider(juce::Graphics& g,
        int x, int y, int width, int height,
        float sliderPosProportional,
        float rotaryStartAngle,
        float rotaryEndAngle,
        juce::Slider&) override;
    void drawLinearSlider(juce::Graphics&, int x, int y, int width, int height,
        float sliderPos, float minSliderPos, float maxSliderPos,
        const juce::Slider::SliderStyle, juce::Slider&) override;

private:
    std::array<juce::Image, 30> knobImages;
    std::array<juce::Image, 2> toggleImages;
};