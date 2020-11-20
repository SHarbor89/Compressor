/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

    Author: Steven Harbor

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
CompressorAudioProcessor::CompressorAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    for (int i = 0; i < historySize; i++) history[i] = 0;
}

CompressorAudioProcessor::~CompressorAudioProcessor()
{
}

//==============================================================================
const juce::String CompressorAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool CompressorAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool CompressorAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool CompressorAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double CompressorAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int CompressorAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int CompressorAudioProcessor::getCurrentProgram()
{
    return 0;
}

void CompressorAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String CompressorAudioProcessor::getProgramName (int index)
{
    return {};
}

void CompressorAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void CompressorAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    juce::dsp::ProcessSpec processSpec;
    processSpec.sampleRate = sampleRate;
    processSpec.maximumBlockSize = samplesPerBlock;
    processSpec.numChannels = getTotalNumOutputChannels();
    compressor.prepare(processSpec);
}

void CompressorAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool CompressorAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
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

void CompressorAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    int numSamples = buffer.getNumSamples();
    int numChannels = buffer.getNumChannels();

    counter = counter % 10;

    float maxLocalValue = 0;
    leftInputLevel = 0;
    rightInputLevel = 0;

    auto audioBlock = juce::dsp::AudioBlock<float>(buffer);

    auto processContext = juce::dsp::ProcessContextReplacing<float>(audioBlock);

    buffer.applyGain(0, numSamples, inputGain);
        
    for (int i = 0; i < numSamples; i++)
    {
        for (int j = 0; j < numChannels; j++)
        {
            float currentSample = std::abs(buffer.getSample(j, i));
            if (currentSample > maxLocalValue) maxLocalValue = currentSample;
            if (j == 0)
            {
                if (currentSample > leftInputLevel)
                {
                    leftInputLevel = currentSample;
                }
            }
            else if (currentSample > rightInputLevel) rightInputLevel = currentSample;
        }
        if (counter % waveFormAccuracy == 0)
        {
            history[writeMarker] = maxLocalValue;
            writeMarker++;
            writeMarker = writeMarker % historySize;
            maxLocalValue = 0.0f;
        }
        counter++;
    }
    compressor.process(processContext);
    buffer.applyGain(0,numSamples,outputGain);
    
    leftOutputLevel = buffer.getMagnitude(0, 0, numSamples);
    rightOutputLevel = buffer.getMagnitude(1, 0, numSamples);
}

//==============================================================================
bool CompressorAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* CompressorAudioProcessor::createEditor()
{
    return new CompressorAudioProcessorEditor (*this);
}

//==============================================================================
void CompressorAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void CompressorAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new CompressorAudioProcessor();
}

//==============================================================================
void CompressorAudioProcessor::setInputGain(double newGain) { inputGain = newGain; }

void CompressorAudioProcessor::setOutputGain(double newGain) { outputGain = newGain; }

void CompressorAudioProcessor::setThreshold(double newThreshold) { compressor.setThreshold(juce::Decibels::gainToDecibels(newThreshold)); }

void CompressorAudioProcessor::setRatio(double newRatio) { compressor.setRatio ((float)newRatio); }

void CompressorAudioProcessor::setKnee(double newKnee) { knee = newKnee; }

void CompressorAudioProcessor::setAttack(double newAttack) { compressor.setAttack(newAttack); }

void CompressorAudioProcessor::setRelease(double newRelease) { compressor.setRelease(newRelease); }

void CompressorAudioProcessor::setSustain(double newSustain) { sustain = newSustain; }

void CompressorAudioProcessor::toggleCompressorType() { compressorType = !compressorType; }