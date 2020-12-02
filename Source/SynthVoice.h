/*
  ==============================================================================

    SynthVoice.h
    Created: 1 Dec 2020 9:13:08pm
    Author:  308167

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "SynthSound.h"

class SynthVoice : public juce::SynthesiserVoice
{
public:

    bool canPlaySound(juce::SynthesiserSound* sound)
    {
        return dynamic_cast<SynthSound*>(sound) != nullptr;
    }

    //====================================================================
    void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition)
    {
        frequency = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
        DBG(midiNoteNumber);
    }

    //====================================================================
    
    void stopNote(float velocity, bool allowTailOff)
    {
        clearCurrentNote();
    }
    //====================================================================

    void pitchWheelMoved(int newPitchWheelValue)
    {

    }
    //====================================================================
    void controllerMoved(int controllerNumber, int newControllerValue)
    {

    }
    //====================================================================
    void renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
    {

    }
    //====================================================================
private:
    double level;
    double frequency;
};