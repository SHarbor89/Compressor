/*
  ==============================================================================

    Visualizer.cpp
    Created: 28 Sep 2020 3:56:03pm
    Author:  Steven Harbor

  ==============================================================================
*/

#include "Visualizer.h"

Visualizer::Visualizer() : barPos{36}
{
    thresholdImage = juce::ImageCache::getFromMemory(BinaryData::CompressorThreshold_png, BinaryData::CompressorThreshold_pngSize);
    addMouseListener(this, false);
    setOpaque(true);
    bgTexture = juce::ImageCache::getFromMemory(BinaryData::Color3_png, BinaryData::Color3_pngSize);
    waveTexture = juce::ImageCache::getFromMemory(BinaryData::Color2_png, BinaryData::Color2_pngSize);
}

void Visualizer::mouseDrag(const juce::MouseEvent& event)
{
    juce::Component::mouseDrag(event);
    barPos = event.getPosition().getY();
    audioProcessor->setThreshold(1.0f - (barPos - ceiling)/(height-ceiling));
    if (barPos > height) barPos = height;
    if (barPos < ceiling) barPos = ceiling;
}

void Visualizer::paint(juce::Graphics& g)
{
    g.setTiledImageFill(bgTexture, 0, 0, 1.0f);

    g.fillRect(getLocalBounds());

    juce::Random rand;

    auto rect = juce::Rectangle<int>();

    rect.setWidth(2);

    g.setTiledImageFill(waveTexture, 0, 0, 1.0f);

    int waveFormSize = CompressorAudioProcessor::historySize;

    std::array<float, CompressorAudioProcessor::historySize> historyArray = *history;

    for (int i = 0; i < waveFormSize; i++)
    {
        rect.setLeft(i*2);
        rect.setTop(height - 144.0f * historyArray[(*writeMarker + i) % waveFormSize]);
        rect.setRight(i * 2 + 2);
        rect.setBottom(height);
        g.fillRect(rect);
    }

    g.drawImageAt(thresholdImage, 0, barPos - thresholdImage.getHeight()/2);
}