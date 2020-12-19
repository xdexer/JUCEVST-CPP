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
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);

    attackSlider.setSliderStyle(juce::Slider::LinearVertical);
    attackSlider.setRange(0.1f, 5000.0f);
    attackSlider.setValue(0.1f);
    attackSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    attackSlider.addListener(this);
    addAndMakeVisible(&attackSlider);

    decaySlider.setSliderStyle(juce::Slider::LinearVertical);
    decaySlider.setRange(0.1f, 5000.0f);
    decaySlider.setValue(0.1f);
    decaySlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    decaySlider.addListener(this);
    addAndMakeVisible(&decaySlider);

    sustainSlider.setSliderStyle(juce::Slider::LinearVertical);
    sustainSlider.setRange(0.0f, 1.0f);
    sustainSlider.setValue(0.1f);
    sustainSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    sustainSlider.addListener(this);
    addAndMakeVisible(&sustainSlider);

    releaseSlider.setSliderStyle(juce::Slider::LinearVertical);
    releaseSlider.setRange(0.1f, 5000.0f);
    releaseSlider.setValue(0.1f);
    releaseSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    releaseSlider.addListener(this);
    addAndMakeVisible(&releaseSlider);

    
    
    
    attackVal = std::make_shared<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.tree, "attack", attackSlider);
    decayVal = std::make_shared<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.tree, "decay", decaySlider);
    sustainVal = std::make_shared<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.tree, "sustain", sustainSlider);
    releaseVal = std::make_shared<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.tree, "release", releaseSlider);
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
    attackSlider.setBounds(10, 10, 40, 100);
    decaySlider.setBounds(60, 10, 40, 100);
    sustainSlider.setBounds(110, 10, 40, 100);
    releaseSlider.setBounds(160, 10, 40, 100);
}

void MySynthAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &attackSlider)
    {
        audioProcessor.attackTime = attackSlider.getValue();
    }

    if (slider == &decaySlider)
    {
        audioProcessor.decayTime = decaySlider.getValue();
    }
    if (slider == &sustainSlider)
    {
        audioProcessor.sustainTime = sustainSlider.getValue();
    }
    if (slider == &releaseSlider)
    {
        audioProcessor.releaseTime = releaseSlider.getValue();
    }
}