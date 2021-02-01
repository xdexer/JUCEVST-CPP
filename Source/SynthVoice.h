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
    bool canPlaySound(juce::SynthesiserSound* sound) override;
    void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) override;
    void stopNote(float velocity, bool allowTailOff) override;
    void controllerMoved(int controllerNumber, int newControllerValue) override;
    void pitchWheelMoved(int newPitchWheelValue) override;
    void prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels);
    void renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override;
    
private:
    //changing from maximilian to juce dsp library
    //juce::dsp::Oscillator<float> osc{ [](float x) {return std::sin(x); } }; //sine wave
    //juce::dsp::Oscillator<float> osc{ [](float x) {return x / juce::MathConstants<float>::pi; } }; //Saw Wave

    juce::ADSR adsr;
    juce::ADSR::Parameters adsrParams;
    juce::AudioBuffer<float> synthBuffer;

    juce::dsp::Oscillator<float> osc{ [](float x) {return x < 0.0f ? -1.0f : 1.0f; }, 200 }; //Square Wave
    juce::dsp::Gain<float> gain;
    bool isPrepared{ false };
};