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
#include "maximilian.h"

class SynthVoice : public juce::SynthesiserVoice
{
public:

    bool canPlaySound(juce::SynthesiserSound* sound)
    {
        return dynamic_cast<SynthSound*>(sound) != nullptr;
    }

    //====================================================================
    void setEnvelopeParam(std::atomic<float>* attack, std::atomic<float>* decay, std::atomic<float>* sustain, std::atomic<float>* release)
    {
        //DBG(*attack);
        //DBG(*release);
        env1.setAttack(static_cast<double>(*attack));
        env1.setDecay(static_cast<double>(*decay));
        env1.setSustain(static_cast<double>(*sustain));
        env1.setRelease(static_cast<double>(*release));
    }   

    //====================================================================
    void setOscType(std::atomic<float>* selection)
    {
        //DBG(*selection);
        theWave = *selection;
    }

    //====================================================================
    void setFilterParams(std::atomic<float>* filterType, std::atomic<float>* filterCutoff, std::atomic<float>* filterResonance)
    {
        DBG(*filterCutoff);
        filterChoice = *filterType;
        cutoffFreq = *filterCutoff;
        resonance = *filterResonance;
    }

    //====================================================================
    double getOscType()
    {
        if (theWave == 0)
        {
            return osc1.sinewave(frequency);
        }
        if (theWave == 1)
        {
            return osc1.saw(frequency);
        }
        if (theWave == 2)
        {
            return osc1.square(frequency);
        }
        return osc1.sinewave(frequency);
    }

    //====================================================================
    double getEnvelope()
    {
        return env1.adsr(getOscType(), env1.trigger);
    }

    //====================================================================
    double getFilterParams()
    {
        if (filterChoice == 0)
        {
            return filter1.lores(getEnvelope(), cutoffFreq, resonance);
        }
        if (filterChoice == 1)
        {
            return filter1.hires(getEnvelope(), cutoffFreq, resonance);
        }
        if (filterChoice == 2)
        {
            return filter1.bandpass(getEnvelope(), cutoffFreq, resonance);
        }
        return filter1.lores(getEnvelope(), cutoffFreq, resonance);
    }

    //====================================================================
    void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition)
    {
        env1.trigger = 1;
        level = velocity;
        frequency = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
        DBG(midiNoteNumber);
    }

    //====================================================================
    
    void stopNote(float velocity, bool allowTailOff)
    {
        env1.trigger = 0;
        allowTailOff = true;
        
        if(velocity == 0)
            clearCurrentNote();

    }
    
    //====================================================================
    void renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
    {
        for (int sample = 0; sample < numSamples; ++sample)
        {
            for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
            {
                outputBuffer.addSample(channel, startSample, getFilterParams()*0.3f);
            }
            ++startSample;
        }
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
private:
    double level;
    double frequency;
    int theWave;

    int filterChoice;
    float cutoffFreq;
    float resonance;

    maxiOsc osc1;
    maxiEnv env1;
    maxiFilter filter1;
};