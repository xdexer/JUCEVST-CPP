/*
  ==============================================================================

    OscData.h
    Created: 15 Mar 2021 5:54:11pm
    Author:  Dominik Marcinkowski

  ==============================================================================
*/


#pragma once
#include <JuceHeader.h>

class OscData : public juce::dsp::Oscillator<float>
{
public:
    void prepareToPlay (juce::dsp::ProcessSpec& spec);
    void setWaveType(int choice);
    void setWaveFrequency(int midiNoteNumber);
    void getNextAudioBlock(juce::dsp::AudioBlock<float>& block);

};
