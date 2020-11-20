/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

    Author: Steven Harbor

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
CompressorAudioProcessorEditor::CompressorAudioProcessorEditor (CompressorAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{    
    getLookAndFeel().setDefaultSansSerifTypefaceName("Impact");
    getLookAndFeel().setColour(juce::Label::textColourId, juce::Colour(0xff2a2a2a));

    //Ratio Slider
    addAndMakeVisible(ratioSlider);
    addAndMakeVisible(ratioLabel);
    addAndMakeVisible(ratioValueLabel);

    ratioSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    ratioSlider.setRange(1, 20, 1);
    ratioSlider.setValue(audioProcessor.ratio);
    ratioSlider.setCentrePosition(sliderWidth / 2, sliderHeight / 2);
    ratioSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 60, 10);
    ratioSlider.setTextValueSuffix(": 1");
    ratioSlider.setLookAndFeel(&knob);
    ratioSlider.onValueChange = [this]() {
        double newRatio = ratioSlider.getValue();
        ratioValueLabel.setText(juce::String(newRatio) + " : 1", juce::NotificationType::dontSendNotification);
        audioProcessor.setRatio(newRatio);
    };

    ratioLabel.setText("Ratio", juce::NotificationType::dontSendNotification);
    ratioLabel.setJustificationType(juce::Justification::centred);

    ratioValueLabel.setText(juce::String(ratioSlider.getValue()) + " : 1", juce::NotificationType::dontSendNotification);
    ratioValueLabel.setJustificationType(juce::Justification::centred);

    //Knee Slider
    addAndMakeVisible(kneeSlider);
    addAndMakeVisible(kneeLabel);
    addAndMakeVisible(kneeValueLabel);

    kneeSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    kneeSlider.setRange(-100, 100, 1);
    kneeSlider.setValue(audioProcessor.knee);
    kneeSlider.setCentrePosition(sliderWidth / 2, sliderHeight / 2);
    kneeSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 60, 10);
    kneeSlider.setTextValueSuffix("%");
    kneeSlider.setLookAndFeel(&knob);
    kneeSlider.onValueChange = [this]() {
        double newKnee = kneeSlider.getValue();
        kneeValueLabel.setText(juce::String(newKnee) + "%", juce::NotificationType::dontSendNotification);
        audioProcessor.setKnee(newKnee);
    };

    kneeLabel.setText("Knee", juce::NotificationType::dontSendNotification);
    kneeLabel.setJustificationType(juce::Justification::centred);

    kneeValueLabel.setText(juce::String(kneeSlider.getValue()) + "%", juce::NotificationType::dontSendNotification);
    kneeValueLabel.setJustificationType(juce::Justification::centred);

    //Attack Slider
    addAndMakeVisible(attackSlider);
    addAndMakeVisible(attackLabel);
    addAndMakeVisible(attackValueLabel);

    attackSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    attackSlider.setRange(0, 1000, 1);
    attackSlider.setValue(audioProcessor.attack);
    attackSlider.setCentrePosition(sliderWidth / 2, sliderHeight / 2);
    attackSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 60, 10);
    attackSlider.setTextValueSuffix("ms");
    attackSlider.setLookAndFeel(&knob);
    attackSlider.onValueChange = [this]() {
        double newAttack = attackSlider.getValue();
        attackValueLabel.setText(juce::String(newAttack) + " ms", juce::NotificationType::dontSendNotification);
        audioProcessor.setAttack(newAttack);
    };

    attackLabel.setText("Attack", juce::NotificationType::dontSendNotification);
    attackLabel.setJustificationType(juce::Justification::centred);

    attackValueLabel.setText(juce::String(attackSlider.getValue()) + " ms", juce::NotificationType::dontSendNotification);
    attackValueLabel.setJustificationType(juce::Justification::centred);
    
    //Release Slider
    addAndMakeVisible(releaseSlider);
    addAndMakeVisible(releaseLabel);
    addAndMakeVisible(releaseValueLabel);

    releaseSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    releaseSlider.setRange(0, 2000, 1);
    releaseSlider.setValue(audioProcessor.release);
    releaseSlider.setCentrePosition(sliderWidth / 2, sliderHeight / 2);
    releaseSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 60, 10);
    releaseSlider.setTextValueSuffix("ms");
    releaseSlider.setLookAndFeel(&knob);
    releaseSlider.onValueChange = [this]() {
        double newRelease = releaseSlider.getValue();
        releaseValueLabel.setText(juce::String(newRelease) + " ms", juce::NotificationType::dontSendNotification);
        audioProcessor.setRelease(newRelease);
    };

    releaseLabel.setText("Release", juce::NotificationType::dontSendNotification);
    releaseLabel.setJustificationType(juce::Justification::centred);

    releaseValueLabel.setText(juce::String(releaseSlider.getValue()) + " ms", juce::NotificationType::dontSendNotification);
    releaseValueLabel.setJustificationType(juce::Justification::centred);

    //Sustain Slider
    addAndMakeVisible(sustainSlider);
    addAndMakeVisible(sustainLabel);
    addAndMakeVisible(sustainValueLabel);
    
    sustainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    sustainSlider.setRange(0,1000, 1);
    sustainSlider.setValue(audioProcessor.sustain);
    sustainSlider.setCentrePosition(sliderWidth / 2, sliderHeight / 2);
    sustainSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 60, 10);
    sustainSlider.setTextValueSuffix("ms");
    sustainSlider.setLookAndFeel(&knob);
    sustainSlider.onValueChange = [this]() {
        double newSustain = sustainSlider.getValue();
        sustainValueLabel.setText(juce::String(newSustain) + " ms", juce::NotificationType::dontSendNotification);
        audioProcessor.setSustain(newSustain);
    };

    sustainLabel.setText("Sustain", juce::NotificationType::dontSendNotification);
    sustainLabel.setJustificationType(juce::Justification::centred);

    sustainValueLabel.setText(juce::String(sustainSlider.getValue()) + " ms", juce::NotificationType::dontSendNotification);
    sustainValueLabel.setJustificationType(juce::Justification::centred);

    //Peak/RMS Toggle
    addAndMakeVisible(peakRMSSlider);
    addAndMakeVisible(RMSLabel);
    addAndMakeVisible(peakLabel);

    peakRMSSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    peakRMSSlider.setRange(0, 1, 1);
    peakRMSSlider.setValue(audioProcessor.compressorType);
    peakRMSSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 60, 10);
    peakRMSSlider.setLookAndFeel(&knob);
    peakRMSSlider.onValueChange = [this]() {
        audioProcessor.toggleCompressorType();
    };

    RMSLabel.setText("RMS", juce::NotificationType::dontSendNotification);
    peakLabel.setText("Peak", juce::NotificationType::dontSendNotification);
    
    addAndMakeVisible(visualizer);
    visualizer.audioProcessor = &audioProcessor;
    visualizer.history = &audioProcessor.history;
    visualizer.writeMarker = &audioProcessor.writeMarker;

    addAndMakeVisible(inputGain);
    inputGain.audioProcessor = &audioProcessor;

    addAndMakeVisible(outputGain);
    outputGain.audioProcessor = &audioProcessor;

    addAndMakeVisible(versionNumber);
    versionNumber.setText("0.5",juce::NotificationType::dontSendNotification);

    bgTexture = juce::ImageCache::getFromMemory(BinaryData::Color1_png, BinaryData::Color1_pngSize);

    startTimerHz(30);

    setSize (600, 400);
}

CompressorAudioProcessorEditor::~CompressorAudioProcessorEditor()
{
}

//==============================================================================
void CompressorAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.setTiledImageFill(bgTexture, 0, 0, 1.0f);
    g.fillAll ();
}

void CompressorAudioProcessorEditor::timerCallback()
{
    visualizer.repaint();
    inputGain.repaint();
    outputGain.repaint();
}

void CompressorAudioProcessorEditor::resized()
{
    versionNumber.setBounds(2, 2, 30, 10);

    visualizer.setBounds(15, 15, 400, 180);

    inputGain.setBounds(510, 15, 30, 180);
    outputGain.setBounds(555, 15, 30, 180);
    
    attackSlider.setBounds(60, 275, sliderWidth, sliderHeight);
    attackLabel.setBounds(70, 345, 80, 20);
    attackValueLabel.setBounds(70, 255, 80, 20);

    kneeSlider.setBounds(150, 275, sliderWidth, sliderHeight);
    kneeLabel.setBounds(160, 345, 80, 20);
    kneeValueLabel.setBounds(160, 255, 80, 20);
    
    ratioSlider.setBounds(240, 275, sliderWidth, sliderHeight);
    ratioLabel.setBounds(250, 345, 80, 20);
    ratioValueLabel.setBounds(250, 255, 80, 20);

    sustainSlider.setBounds(330, 275, sliderWidth, sliderHeight);
    sustainLabel.setBounds(340, 345, 80, 20);
    sustainValueLabel.setBounds(340, 255, 80, 20);
        
    releaseSlider.setBounds(420, 275, sliderWidth, sliderHeight);
    releaseLabel.setBounds(430, 345, 80, 20);
    releaseValueLabel.setBounds(430, 255, 80, 20);

    peakRMSSlider.setBounds(200, 200, 90, 70);
    RMSLabel.setBounds(300, 200, 80, 20);
    peakLabel.setBounds(190, 200, 80, 20);
}