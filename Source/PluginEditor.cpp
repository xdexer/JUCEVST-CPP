/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MySynthAudioProcessorEditor::MySynthAudioProcessorEditor (MySynthAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize (600, 200);
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    attackAttachment = std::make_unique<SliderAttachment>(audioProcessor.tree, "ATTACK", attackSlider);
    decayAttachment = std::make_unique<SliderAttachment>(audioProcessor.tree, "DECAY", decaySlider);
    sustainAttachment = std::make_unique<SliderAttachment>(audioProcessor.tree, "SUSTAIN", sustainSlider);
    releaseAttachment = std::make_unique<SliderAttachment>(audioProcessor.tree, "RELEASE", releaseSlider);
    oscSelAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.tree,"OSC", oscSelector);
}

MySynthAudioProcessorEditor::~MySynthAudioProcessorEditor()
{
}

//==============================================================================
void MySynthAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
}

void MySynthAudioProcessorEditor::resized()
{
    juce::Rectangle<int> area = getLocalBounds();
    
    const int componentWidth = 200;
    const int componentHeight = 200;
}

