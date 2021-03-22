/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MySynthAudioProcessor::MySynthAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
        .withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
        .withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
    ),
    tree(*this, nullptr, "Parameters", createParams())
#endif
{

    synth.addSound(new SynthSound());
    synth.addVoice(new SynthVoice());
}

MySynthAudioProcessor::~MySynthAudioProcessor()
{
    
}

//==============================================================================
const juce::String MySynthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool MySynthAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool MySynthAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool MySynthAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double MySynthAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MySynthAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int MySynthAudioProcessor::getCurrentProgram()
{
    return 0;
}

void MySynthAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String MySynthAudioProcessor::getProgramName (int index)
{
    return {};
}

void MySynthAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void MySynthAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    //specify oscillator 
    //changing from maximilian to juce dsp library
    synth.setCurrentPlaybackSampleRate(sampleRate);
    
    for (int i = 0; i < synth.getNumVoices(); ++i)
    {
        if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
        {
            voice->prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());
        }
    }

    //juce::ignoreUnused(samplesPerBlock);
    //lastSampleRate = sampleRate;
    //mySynth.setCurrentPlaybackSampleRate(lastSampleRate);

}

void MySynthAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MySynthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void MySynthAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    //changing from maximilian to juce dsp library
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumInputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());


    for (int i = 0; i < synth.getNumVoices(); ++i)
    {
        if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
        {
            //Osc controls
            //ADSR
            //LFO
            
            auto& attack = *tree.getRawParameterValue("ATTACK");
            auto& decay = *tree.getRawParameterValue("DECAY");
            auto& sustain = *tree.getRawParameterValue("SUSTAIN");
            auto& release = *tree.getRawParameterValue("RELEASE");
            
            auto& oscWaveChoice = *tree.getRawParameterValue("OSC1WAVETYPE");
            
            voice->update(attack.load(), decay.load(), sustain.load(), release.load());
            voice->getOscillator().setWaveType(oscWaveChoice);
        }
    }

//    for (const juce::MidiMessageMetadata metadata : midiMessages)
//    {
//        if (metadata.numBytes == 3)
//            juce::Logger::writeToLog("TimeStamp: " + juce::String(metadata.getMessage().getTimeStamp()));
//    }

    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());

}

//==============================================================================
bool MySynthAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* MySynthAudioProcessor::createEditor()
{
    return new MySynthAudioProcessorEditor (*this);
}

//==============================================================================
void MySynthAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void MySynthAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MySynthAudioProcessor();
}

//Value Tree
juce::AudioProcessorValueTreeState::ParameterLayout MySynthAudioProcessor::createParams()
{
    //Combobox: switch oscillators
    // ADSR - 4x float
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    //OSC select
    params.push_back(std::make_unique<juce::AudioParameterChoice>("OSC", "Oscillator",
        juce::StringArray{"Sine", "Saw", "Square", "Random"}, 0));

    //ADSR
    params.push_back(std::make_unique<juce::AudioParameterFloat>("ATTACK","Attack",
        juce::NormalisableRange<float>{0.1f, 1.0f, }, 0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("DECAY", "Decay",
        juce::NormalisableRange<float>{0.1f, 1.0f, }, 0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("SUSTAIN", "Sustain",
        juce::NormalisableRange<float>{0.1f, 1.0f, }, 1.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("RELEASE", "Release",
        juce::NormalisableRange<float>{0.1f, 3.0f, }, 0.4f));
    
    
    params.push_back(std::make_unique<juce::AudioParameterChoice>("OSC1WAVETYPE", "Osc 1 Wave Type", juce::StringArray{"Sine", "Saw", "Square", "Random"}, 0));
    return { params.begin(), params.end() };
}
