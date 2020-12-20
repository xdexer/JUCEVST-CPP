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
    tree(*this, nullptr)
#endif
{
    //ADSR ENVELOPE
    juce::NormalisableRange<float> attackParam(0.1f, 5000.0f);
    juce::NormalisableRange<float> decayParam(0.1f, 1.0f);
    juce::NormalisableRange<float> sustainParam(0.1f, 5000.0f);
    juce::NormalisableRange<float> releaseParam(0.1f, 5000.0f);
    tree.createAndAddParameter("attack", "Attack", "attack", attackParam, 0.1f, nullptr, nullptr);
    tree.createAndAddParameter("decay", "Decay", "decay", decayParam, 0.1f, nullptr, nullptr);
    tree.createAndAddParameter("sustain", "Sustain", "sustain", sustainParam, 0.1f, nullptr, nullptr);
    tree.createAndAddParameter("release", "Release", "release", releaseParam, 0.1f, nullptr, nullptr);
    
    //TYPE OF WAVE SELECTION
    juce::NormalisableRange<float> wavetypeParam(0, 2); 
    tree.createAndAddParameter("wavetype", "WaveType", "wavetype", wavetypeParam, 0, nullptr, nullptr);

    //Filter settings
    juce::NormalisableRange<float> filterTypeVal(0, 2);
    juce::NormalisableRange<float> cutVal(20.0f, 9000.0f);
    juce::NormalisableRange<float> resVal(1, 5);
    tree.createAndAddParameter("filterType", "FilterType", "filterType", filterTypeVal, 0, nullptr, nullptr);
    tree.createAndAddParameter("filterCutoff", "FilterCutoff", "filterCutoff", cutVal, 400.0f, nullptr, nullptr);
    tree.createAndAddParameter("filterResonance", "FilterResonance", "filterResonance", resVal, 1, nullptr, nullptr);
    


    tree.state = juce::ValueTree("ParamTree");
    
    
    mySynth.clearVoices();
    for (int i = 0; i < 5; i++)
    {
        mySynth.addVoice(new SynthVoice());
    }
    mySynth.clearSounds();
    mySynth.addSound(new SynthSound());
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
    juce::ignoreUnused(samplesPerBlock);
    lastSampleRate = sampleRate;
    mySynth.setCurrentPlaybackSampleRate(lastSampleRate);
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
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
    for (int i = 0; i < mySynth.getNumVoices(); ++i)
    {
        if (myVoice = dynamic_cast<SynthVoice*>(mySynth.getVoice(i)))
        {
            myVoice->setEnvelopeParam(tree.getRawParameterValue("attack"), tree.getRawParameterValue("decay"), 
                tree.getRawParameterValue("sustain"), tree.getRawParameterValue("release"));
            
            myVoice->setOscType(tree.getRawParameterValue("wavetype"));

            myVoice->setFilterParams(tree.getRawParameterValue("filterType"), tree.getRawParameterValue("filterCutoff"),
                tree.getRawParameterValue("filterResonance"));
        }
    }


    buffer.clear();
    mySynth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());

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
