/*
  ==============================================================================

    Oscillator.h
    Created: 20 Dec 2020 12:02:36am
    Author:  308167

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
//==============================================================================
/*
*/
class Oscillator : public juce::Component, private juce::ComboBox::Listener
{
public:
    Oscillator(MySynthAudioProcessor&);
    ~Oscillator() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void comboBoxChanged(juce::ComboBox*) override;

private:

    MySynthAudioProcessor& audioProcessor;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> waveSelection;
    juce::ComboBox oscMenu;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Oscillator)
};
