/*
  ==============================================================================

    SynthSound.h
    Created: 1 Dec 2020 9:12:59pm
    Author:  308167

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class SynthSound : public juce::SynthesiserSound
{
public:
    bool appliesToNote(int midiNoteNumber) override
    {
        return true;
    }

    bool appliesToChannel(int midiChannel) override
    {
        return true;
    }
};
