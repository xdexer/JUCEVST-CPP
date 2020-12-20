/*
  ==============================================================================

    Filter.h
    Created: 20 Dec 2020 2:30:50pm
    Author:  308167

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
//==============================================================================
/*
*/
class Filter  : public juce::Component
{
public:
    Filter(MySynthAudioProcessor&);
    ~Filter() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    MySynthAudioProcessor& audioProcessor;
    juce::Slider filterCutoff;
    juce::Slider filterResonance;
    juce::ComboBox filterMenu;

    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> filterTypeVal;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> filCut;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> filRes;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Filter)
};
