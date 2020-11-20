/*
  ==============================================================================

    OutputGain.cpp
    Created: 10 Oct 2020 9:31:43am
    Author:  Steven Harbor

  ==============================================================================
*/

#include "InputGain.h"

InputGain::InputGain()
{
    thresholdImage = juce::ImageCache::getFromMemory(BinaryData::CompressorThreshold_png, BinaryData::CompressorThreshold_pngSize);
    addMouseListener(this, false);
    setOpaque(true);
    bgTexture = juce::ImageCache::getFromMemory(BinaryData::Color3_png, BinaryData::Color3_pngSize);
    meterTexture = juce::ImageCache::getFromMemory(BinaryData::Color2_png, BinaryData::Color2_pngSize);
}

void InputGain::mouseDrag(const juce::MouseEvent& event)
{
    juce::Component::mouseDrag(event);
    barPos = event.getPosition().getY();
    if (barPos > height) barPos = height;
    if (barPos < 0) barPos = 0;
    audioProcessor->setInputGain(1.0f - (barPos - ceiling) / (height - ceiling));
}

void InputGain::paint(juce::Graphics& g)
{
    g.setTiledImageFill(bgTexture, 0, 0, 1.0f);
    g.fillRect(getLocalBounds());
    g.setTiledImageFill(meterTexture, 0, 0, 1.0f);
    float leftGainMeterPos = height - (height - ceiling) * pow(sin(audioProcessor->leftInputLevel * juce::MathConstants<float>::halfPi), 0.25);
    float rightGainMeterPos = height - (height - ceiling) * pow(sin(audioProcessor->rightInputLevel * juce::MathConstants<float>::halfPi), 0.25);
    leftMeter.setBounds(0, leftGainMeterPos, width / 2, height - leftGainMeterPos);
    rightMeter.setBounds(width / 2, rightGainMeterPos, width / 2, height - rightGainMeterPos);
    g.fillRect(leftMeter);
    g.fillRect(rightMeter);
    //g.drawImageAt(gainMeterImage, -15, height - (height - ceiling) * pow(sin(leftGainMeterPos * juce::MathConstants<float>::halfPi),0.25));
    //g.drawImageAt(gainMeterImage, 15, height - (height - ceiling) * pow(sin(rightGainMeterPos * juce::MathConstants<float>::halfPi),0.25));
    g.drawImageAt(thresholdImage, 0, barPos - thresholdImage.getHeight()/2);
}