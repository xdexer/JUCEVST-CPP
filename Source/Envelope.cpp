/*
  ==============================================================================

    Envelope.cpp
    Created: 20 Dec 2020 2:15:33am
    Author:  308167

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Envelope.h"

//==============================================================================
Envelope::Envelope(MySynthAudioProcessor& p): audioProcessor(p)
{
    setSize(200, 200);
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
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


    attackVal = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.tree, "attack", attackSlider);
    decayVal = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.tree, "decay", decaySlider);
    sustainVal = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.tree, "sustain", sustainSlider);
    releaseVal = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.tree, "release", releaseSlider);
}

Envelope::~Envelope()
{
}

void Envelope::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
}

void Envelope::resized()
{
    juce::Rectangle<int> area = getLocalBounds().reduced(40);

    // This method is where you should set the bounds of any child
    // components that your component contains.. 
    attackSlider.setBounds(10, 10, 40, 100);
    decaySlider.setBounds(60, 10, 40, 100);
    sustainSlider.setBounds(110, 10, 40, 100);
    releaseSlider.setBounds(160, 10, 40, 100);
}

void Envelope::sliderValueChanged(juce::Slider* slider)
{
    /*
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
    */
}