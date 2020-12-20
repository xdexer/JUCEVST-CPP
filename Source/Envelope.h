/*
  ==============================================================================

    Envelope.h
    Created: 20 Dec 2020 2:15:33am
    Author:  308167

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
//==============================================================================
/*
*/
class Envelope  : public juce::Component, private juce::Slider::Listener
{
public:
    Envelope(MySynthAudioProcessor&);
    ~Envelope() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    void sliderValueChanged(juce::Slider* slider) override;
private:

    MySynthAudioProcessor& audioProcessor;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attackVal;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> decayVal;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sustainVal;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> releaseVal;
    juce::Slider attackSlider;
    juce::Slider decaySlider;
    juce::Slider sustainSlider;
    juce::Slider releaseSlider;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Envelope)
};
