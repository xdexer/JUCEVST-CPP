/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
*/
class Vst_cpp1AudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    Vst_cpp1AudioProcessor();
    ~Vst_cpp1AudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
	
   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;
    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

	void initialiseGraph();
	void connectAudioNodes();
	void connectMidiNodes();
	using AudioGraphIOProcessor = juce::AudioProcessorGraph::AudioGraphIOProcessor;
	using Node = juce::AudioProcessorGraph::Node;
private:

	juce::AudioParameterFloat* gain;
	juce::AudioParameterBool* invertPhase;
	juce::AudioProcessorValueTreeState parameters;
	float previousGain;

	std::atomic<float>* phaseParameter = nullptr;
	std::atomic<float>* gainParameter = nullptr;

	std::unique_ptr<juce::AudioProcessorGraph> mainProcessor;
	Node::Ptr audioInputNode;
	Node::Ptr audioOutputNode;
	Node::Ptr midiInputNode;
	Node::Ptr midiOutputNode;

	//==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Vst_cpp1AudioProcessor)
};
