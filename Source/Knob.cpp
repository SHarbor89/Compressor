/*
  ==============================================================================

    Knob.cpp
    Created: 7 Oct 2020 3:27:04pm
    Author:  Steven Harbor

  ==============================================================================
*/

#include "Knob.h"

Knob::Knob()
{
    knobImages[0] = juce::ImageCache::getFromMemory(BinaryData::CompressorKnob0001_png, BinaryData::CompressorKnob0001_pngSize);
    knobImages[1] = juce::ImageCache::getFromMemory(BinaryData::CompressorKnob0002_png, BinaryData::CompressorKnob0002_pngSize);
    knobImages[2] = juce::ImageCache::getFromMemory(BinaryData::CompressorKnob0003_png, BinaryData::CompressorKnob0003_pngSize);
    knobImages[3] = juce::ImageCache::getFromMemory(BinaryData::CompressorKnob0004_png, BinaryData::CompressorKnob0004_pngSize);
    knobImages[4] = juce::ImageCache::getFromMemory(BinaryData::CompressorKnob0005_png, BinaryData::CompressorKnob0005_pngSize);
    knobImages[5] = juce::ImageCache::getFromMemory(BinaryData::CompressorKnob0006_png, BinaryData::CompressorKnob0006_pngSize);
    knobImages[6] = juce::ImageCache::getFromMemory(BinaryData::CompressorKnob0007_png, BinaryData::CompressorKnob0007_pngSize);
    knobImages[7] = juce::ImageCache::getFromMemory(BinaryData::CompressorKnob0008_png, BinaryData::CompressorKnob0008_pngSize);
    knobImages[8] = juce::ImageCache::getFromMemory(BinaryData::CompressorKnob0009_png, BinaryData::CompressorKnob0009_pngSize);
    knobImages[9] = juce::ImageCache::getFromMemory(BinaryData::CompressorKnob0010_png, BinaryData::CompressorKnob0010_pngSize);
    knobImages[10] = juce::ImageCache::getFromMemory(BinaryData::CompressorKnob0011_png, BinaryData::CompressorKnob0011_pngSize);
    knobImages[11] = juce::ImageCache::getFromMemory(BinaryData::CompressorKnob0012_png, BinaryData::CompressorKnob0012_pngSize);
    knobImages[12] = juce::ImageCache::getFromMemory(BinaryData::CompressorKnob0013_png, BinaryData::CompressorKnob0013_pngSize);
    knobImages[13] = juce::ImageCache::getFromMemory(BinaryData::CompressorKnob0014_png, BinaryData::CompressorKnob0014_pngSize);
    knobImages[14] = juce::ImageCache::getFromMemory(BinaryData::CompressorKnob0015_png, BinaryData::CompressorKnob0015_pngSize);
    knobImages[15] = juce::ImageCache::getFromMemory(BinaryData::CompressorKnob0016_png, BinaryData::CompressorKnob0016_pngSize);
    knobImages[16] = juce::ImageCache::getFromMemory(BinaryData::CompressorKnob0017_png, BinaryData::CompressorKnob0017_pngSize);
    knobImages[17] = juce::ImageCache::getFromMemory(BinaryData::CompressorKnob0018_png, BinaryData::CompressorKnob0018_pngSize);
    knobImages[18] = juce::ImageCache::getFromMemory(BinaryData::CompressorKnob0019_png, BinaryData::CompressorKnob0019_pngSize);
    knobImages[19] = juce::ImageCache::getFromMemory(BinaryData::CompressorKnob0020_png, BinaryData::CompressorKnob0020_pngSize);
    knobImages[20] = juce::ImageCache::getFromMemory(BinaryData::CompressorKnob0021_png, BinaryData::CompressorKnob0021_pngSize);
    knobImages[21] = juce::ImageCache::getFromMemory(BinaryData::CompressorKnob0022_png, BinaryData::CompressorKnob0022_pngSize);
    knobImages[22] = juce::ImageCache::getFromMemory(BinaryData::CompressorKnob0023_png, BinaryData::CompressorKnob0023_pngSize);
    knobImages[23] = juce::ImageCache::getFromMemory(BinaryData::CompressorKnob0024_png, BinaryData::CompressorKnob0024_pngSize);
    knobImages[24] = juce::ImageCache::getFromMemory(BinaryData::CompressorKnob0025_png, BinaryData::CompressorKnob0025_pngSize);
    knobImages[25] = juce::ImageCache::getFromMemory(BinaryData::CompressorKnob0026_png, BinaryData::CompressorKnob0026_pngSize);
    knobImages[26] = juce::ImageCache::getFromMemory(BinaryData::CompressorKnob0027_png, BinaryData::CompressorKnob0027_pngSize);
    knobImages[27] = juce::ImageCache::getFromMemory(BinaryData::CompressorKnob0028_png, BinaryData::CompressorKnob0028_pngSize);
    knobImages[28] = juce::ImageCache::getFromMemory(BinaryData::CompressorKnob0029_png, BinaryData::CompressorKnob0029_pngSize);
    knobImages[29] = juce::ImageCache::getFromMemory(BinaryData::CompressorKnob0030_png, BinaryData::CompressorKnob0030_pngSize);

    toggleImages[0] = juce::ImageCache::getFromMemory(BinaryData::CompressorToggle0001_png, BinaryData::CompressorToggle0001_pngSize);
    toggleImages[1] = juce::ImageCache::getFromMemory(BinaryData::CompressorToggle0002_png, BinaryData::CompressorToggle0002_pngSize);
}
Knob::~Knob()
{
}

void Knob::drawRotarySlider(juce::Graphics& g,
    int x, int y, int width, int height,
    float sliderPosProportional,
    float rotaryStartAngle,
    float rotaryEndAngle,
    juce::Slider&)
{
    g.drawImageAt(knobImages[round(29 * sliderPosProportional)], x, y);
}

void Knob::drawLinearSlider(juce::Graphics& g, int x, int y, int width, int height,
    float sliderPos, float minSliderPos, float maxSliderPos,
    const juce::Slider::SliderStyle, juce::Slider& s)
{    
    g.drawImageAt(toggleImages[s.getValue()],x,y);
}