/*
  ==============================================================================

    OscillatorProcessor.h
    Created: 10 Nov 2020 11:02:44pm
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
class OscillatorProcessor  : public ProcessorBase
{
public:
    OscillatorProcessor();
	void prepareToPlay(double sampleRate, int samplesPerBlock) override;
	void processBlock(juce::AudioSampleBuffer& buffer, juce::MidiBuffer&) override;
	void reset() override;
	const juce::String getName() const override { return "Oscillator"; }


private:
	juce::dsp::Oscillator<float> oscillator;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscillatorProcessor)
};
