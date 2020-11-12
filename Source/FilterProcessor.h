/*
  ==============================================================================

    FilterProcessor.h
    Created: 11 Nov 2020 10:02:28pm
    Author:  Dominik

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <juce_dsp/juce_dsp.h>
#include "ProcessorBase.h"
//==============================================================================
/*
*/
class FilterProcessor  : public ProcessorBase
{
public:
    FilterProcessor() {}
	void prepareToPlay(double sampleRate, int samplesPerBlock) override;
	void processBlock(juce::AudioSampleBuffer& buffer, juce::MidiBuffer&) override;
	void reset() override;
	const juce::String getName() const override { return "Filter"; }

private:
	juce::dsp::ProcessorDuplicator<juce::dsp::IIR::Filter<float>, juce::dsp::IIR::Coefficients<float>> filter;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterProcessor)
};
