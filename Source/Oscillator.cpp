/*
  ==============================================================================

    Oscillator.cpp
    Created: 20 Dec 2020 12:02:36am
    Author:  308167

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Oscillator.h"

//==============================================================================
Oscillator::Oscillator(MySynthAudioProcessor& p): audioProcessor(p)
{
    setSize(200, 200);

    oscMenu.addItem("Sine", 1);
    oscMenu.addItem("Saw", 2);
    oscMenu.addItem("Square", 3);
    addAndMakeVisible(&oscMenu);
    oscMenu.addListener(this);

    oscMenu.setJustificationType(juce::Justification::centred);

    waveSelection = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.tree,"wavetype", oscMenu);
}

Oscillator::~Oscillator()
{
}

void Oscillator::paint (juce::Graphics& g)
{

}

void Oscillator::resized()
{
    juce::Rectangle<int> area = getLocalBounds().reduced(40);

    oscMenu.setBounds(area.removeFromTop(20));

}

void Oscillator::comboBoxChanged(juce::ComboBox* box)
{

}
