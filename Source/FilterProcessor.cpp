/*
  ==============================================================================

    FilterProcessor.cpp
    Created: 11 Nov 2020 10:02:28pm
    Author:  Dominik

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FilterProcessor.h"

//==============================================================================

void FilterProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
	*filter.state = *juce::dsp::IIR::Coefficients<float>::makeHighPass(sampleRate, 1000.0f);
	juce::dsp::ProcessSpec spec{ sampleRate, static_cast<juce::uint32>(samplesPerBlock,2) };
	filter.prepare(spec);
}

void FilterProcessor::processBlock(juce::AudioSampleBuffer& buffer, juce::MidiBuffer&)
{
	juce::dsp::AudioBlock<float> block(buffer);
	juce::dsp::ProcessContextReplacing<float> context(block);
	filter.process(context);
}

void FilterProcessor::reset()
{
	filter.reset();
}

