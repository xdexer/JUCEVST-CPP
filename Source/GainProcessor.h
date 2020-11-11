/*
  ==============================================================================

    GainProcessor.h
    Created: 11 Nov 2020 12:48:49am
    Author:  Dominik

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include <juce_dsp/juce_dsp.h>
#include "ProcessorBase.h"

class GainProcessor : public ProcessorBase
{
public:
	GainProcessor();
	void prepareToPlay(double sampleRate, int samplesPerBlock) override;
	void processBlock(juce::AudioSampleBuffer& buffer, juce::MidiBuffer&) override;
	void reset() override;
	const juce::String getName() const override { return "Gain"; }

private:
	juce::dsp::Gain<float> gain;
};