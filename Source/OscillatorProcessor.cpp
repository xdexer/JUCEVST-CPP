/*
  ==============================================================================

    OscillatorProcessor.cpp
    Created: 10 Nov 2020 11:02:44pm
    Author:  Dominik

  ==============================================================================
*/

#include <JuceHeader.h>
#include "OscillatorProcessor.h"

//==============================================================================
OscillatorProcessor::OscillatorProcessor()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
	oscillator.setFrequency(440.0f);
	oscillator.initialise([](float x) {return std::sin(x); });

}

void OscillatorProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
	juce::dsp::ProcessSpec spec{ sampleRate, static_cast<juce::uint32>(samplesPerBlock) };
	oscillator.prepare(spec);
}

void OscillatorProcessor::processBlock(juce::AudioSampleBuffer& buffer, juce::MidiBuffer&)
{
	juce::dsp::AudioBlock<float> block(buffer);
	juce::dsp::ProcessContextReplacing<float> context(block);
	oscillator.process(context);
}

void OscillatorProcessor::reset()
{
	oscillator.reset();
}
