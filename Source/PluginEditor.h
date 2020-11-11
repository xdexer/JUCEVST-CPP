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
class Vst_cpp1AudioProcessorEditor  : public juce::AudioProcessorEditor, private juce::Slider::Listener
{
	typedef juce::AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
	typedef juce::AudioProcessorValueTreeState::ButtonAttachment ButtonAttachment;
public:
    Vst_cpp1AudioProcessorEditor (Vst_cpp1AudioProcessor&, juce::AudioProcessorValueTreeState&);
    ~Vst_cpp1AudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
	void sliderValueChanged(juce::Slider* slider) override;
    Vst_cpp1AudioProcessor& audioProcessor;


	juce::AudioProcessorValueTreeState& valueTreeState;
	juce::Label gainLabel;
	juce::Slider gainSlider;
	std::unique_ptr<SliderAttachment> gainAttachment;
	juce::ToggleButton invertButton;
	std::unique_ptr<ButtonAttachment> invertAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Vst_cpp1AudioProcessorEditor)
};
