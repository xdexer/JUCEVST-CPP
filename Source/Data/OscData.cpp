/*
  ==============================================================================

    OscData.cpp
    Created: 15 Mar 2021 5:54:11pm
    Author:  Dominik Marcinkowski

  ==============================================================================
*/

#include "OscData.h"
#include <random>
// (-1.0f + (((float) rand()) / (float) RAND_MAX * 2.0f))
void OscData::prepareToPlay(juce::dsp::ProcessSpec& spec)
{
    srand(0);
    prepare(spec);
}

void OscData::setWaveType(int choice)
{
    
    switch (choice) {
        case 0:
            //Sine
            initialise([](float x){return std::sin(x);});
            break;
            
        case 1:
            //Saw
            initialise([](float x){return x / juce::MathConstants<float>::pi;});
            break;
            
        case 2:
            //Square
            initialise([](float x){return x < 0.0f ? -1.0f : 1.0f;}, 200);
            break;
        
        case 3:
            //Random
            initialise([](float x){return (-1.0f + (((float) rand()) / (float) RAND_MAX * 2.0f));});
            break;
        default:
            jassertfalse;
            break;
    }
}

void OscData::setWaveFrequency(int midiNoteNumber)
{
    setFrequency(juce::MidiMessage::getMidiNoteInHertz (midiNoteNumber));
}

void OscData::getNextAudioBlock(juce::dsp::AudioBlock<float>& block)
{
    process(juce::dsp::ProcessContextReplacing<float>(block));
}
