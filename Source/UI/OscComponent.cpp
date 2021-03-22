/*
  ==============================================================================

    OscComponent.cpp
    Created: 15 Mar 2021 7:23:50pm
    Author:  Dominik Marcinkowski

  ==============================================================================
*/

#include <JuceHeader.h>
#include "OscComponent.h"

//==============================================================================
OscComponent::OscComponent(juce::AudioProcessorValueTreeState& tree, juce::String waveSelectorID)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    juce::StringArray choices {"Sine", "Saw", "Square", "Random"};
    oscWaveSelector.addItemList(choices, 1);
    addAndMakeVisible(oscWaveSelector);
    
    oscWaveSelectorAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(tree, waveSelectorID, oscWaveSelector);
}

OscComponent::~OscComponent()
{
}

void OscComponent::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::black);
}

void OscComponent::resized()
{
    oscWaveSelector.setBounds(0, 0, 90, 20);

}
