/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class MySynthAudioProcessorEditor  : public juce::AudioProcessorEditor, public juce::Slider::Listener
{
public:
    MySynthAudioProcessorEditor (MySynthAudioProcessor&);
    ~MySynthAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    void sliderValueChanged(juce::Slider* slider) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MySynthAudioProcessor& audioProcessor;
    
    std::shared_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attackVal;
    std::shared_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> decayVal;
    std::shared_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sustainVal;
    std::shared_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> releaseVal;
    juce::Slider attackSlider;
    juce::Slider decaySlider;
    juce::Slider sustainSlider;
    juce::Slider releaseSlider;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MySynthAudioProcessorEditor)
};
