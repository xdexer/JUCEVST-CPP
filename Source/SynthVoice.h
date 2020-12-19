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
    void setParam(std::atomic<float>* attack, std::atomic<float>* decay, std::atomic<float>* sustain, std::atomic<float>* release)
    {
        DBG(*attack);
        DBG(*release);
        env1.setAttack(static_cast<double>(*attack));
        env1.setDecay(static_cast<double>(*decay));
        env1.setSustain(static_cast<double>(*sustain));
        env1.setRelease(static_cast<double>(*release));
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
            double theWave = osc1.sinewave(frequency);
            double theSound = env1.adsr(theWave, env1.trigger) * level;
            double filteredSound = filter1.lores(theSound, 100, 0.1);

            for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
            {
                outputBuffer.addSample(channel, startSample, filteredSound);
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

    maxiOsc osc1;
    maxiEnv env1;
    maxiFilter filter1;
};