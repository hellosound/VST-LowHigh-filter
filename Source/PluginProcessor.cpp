/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
LowPassHighPassFilterAudioProcessor::LowPassHighPassFilterAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
#else 
    :
#endif
    parameters(*this, nullptr, juce::Identifier("LowPassAndHighPassPlugin"), 
        
        {std::make_unique<juce::AudioParameterFloat>("cutoff_frequency", "Cutoff Frequency", 
            juce::NormalisableRange{20.f,20000.f,0.1f,0.2f,false}, 500.f), 
        std::make_unique<juce::AudioParameterBool>("highpass", "Highpass", false)})
{
        cutoffFrequencyParameter = parameters.getRawParameterValue("cutoff_frequency");
        highpassParameter = parameters.getRawParameterValue("highpass");
}

LowPassHighPassFilterAudioProcessor::~LowPassHighPassFilterAudioProcessor()
{
}

//==============================================================================
const juce::String LowPassHighPassFilterAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool LowPassHighPassFilterAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool LowPassHighPassFilterAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool LowPassHighPassFilterAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double LowPassHighPassFilterAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int LowPassHighPassFilterAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int LowPassHighPassFilterAudioProcessor::getCurrentProgram()
{
    return 0;
}

void LowPassHighPassFilterAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String LowPassHighPassFilterAudioProcessor::getProgramName (int index)
{
    return {};
}

void LowPassHighPassFilterAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void LowPassHighPassFilterAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    filter.setSamplingRate(static_cast<float>(sampleRate));
}

void LowPassHighPassFilterAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool LowPassHighPassFilterAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
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

void LowPassHighPassFilterAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    const auto cutoffFrequency = cutoffFrequencyParameter->load();
    const auto highpass = *highpassParameter < 0.5f ? false : true;

    filter.setCutoffFrequency(cutoffFrequency);
    filter.setHighpass(highpass);

    filter.processBlock(buffer, midiMessages);
}

//==============================================================================
bool LowPassHighPassFilterAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* LowPassHighPassFilterAudioProcessor::createEditor()
{
    return new LowPassHighPassFilterAudioProcessorEditor (*this, parameters);
}

//==============================================================================
void LowPassHighPassFilterAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void LowPassHighPassFilterAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new LowPassHighPassFilterAudioProcessor();
}
