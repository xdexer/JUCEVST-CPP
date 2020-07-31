/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Vst_cpp1AudioProcessor::Vst_cpp1AudioProcessor()
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
	addParameter(gain = new juce::AudioParameterFloat("gain", "Gain", 0.0f, 1.0f, 0.5f));
	addParameter(invertPhase = new juce::AudioParameterBool("invertPhase", "Invert Phase", false));
}

Vst_cpp1AudioProcessor::~Vst_cpp1AudioProcessor()
{
}

//==============================================================================
const juce::String Vst_cpp1AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Vst_cpp1AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Vst_cpp1AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Vst_cpp1AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Vst_cpp1AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Vst_cpp1AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Vst_cpp1AudioProcessor::getCurrentProgram()
{
    return 0;
}

void Vst_cpp1AudioProcessor::setCurrentProgram (int index)
{
}

const juce::String Vst_cpp1AudioProcessor::getProgramName (int index)
{
    return {};
}

void Vst_cpp1AudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void Vst_cpp1AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
	auto phase = *invertPhase ? -1.0f : 1.0f;
	previousGain = *gain * phase;
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void Vst_cpp1AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Vst_cpp1AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void Vst_cpp1AudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
	auto phase = *invertPhase ? -1.0f : 1.0f;
	auto currentGain = *gain * phase;
	if (currentGain == previousGain)
	{
		buffer.applyGain(currentGain);
	}
	else
	{
		buffer.applyGainRamp(0, buffer.getNumSamples(), previousGain, currentGain);
		previousGain = currentGain;
	}

    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
    }
}

//==============================================================================
bool Vst_cpp1AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* Vst_cpp1AudioProcessor::createEditor()
{
    return new Vst_cpp1AudioProcessorEditor (*this);
}

//==============================================================================
void Vst_cpp1AudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
	//juce::MemoryOutputStream(destData, true).writeFloat(*gain);
	std::unique_ptr<juce::XmlElement> xml(new juce::XmlElement("ParamTutorial"));
	xml->setAttribute("gain", (double)* gain);
	xml->setAttribute("invertPhase", *invertPhase);
	copyXmlToBinary(*xml, destData);
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void Vst_cpp1AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
	//*gain = juce::MemoryInputStream(data, static_cast<size_t>(sizeInBytes), false).readFloat();
    
	std::unique_ptr<juce::XmlElement> xmlState (getXmlFromBinary(data, sizeInBytes));
	if (xmlState.get() != nullptr)
	{
		if (xmlState->hasTagName("ParamTutorial"))
		{
			*gain = (float)xmlState->getDoubleAttribute("gain", 1.0);
			*invertPhase = xmlState->getBoolAttribute("invertPhase", false);
		}
	}
	// You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Vst_cpp1AudioProcessor();
}
