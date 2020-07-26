/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Vst_cpp1AudioProcessorEditor::Vst_cpp1AudioProcessorEditor (Vst_cpp1AudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (200, 200);
	midiVolume.setSliderStyle(juce::Slider::LinearBarVertical);
	midiVolume.setRange(0.0, 127.0, 1.0);
	midiVolume.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
	midiVolume.setPopupDisplayEnabled(true, false, this);
	midiVolume.setTextValueSuffix(" Volume");
	midiVolume.setValue(1.0);

	midiVolume.addListener(this);
	addAndMakeVisible(&midiVolume);
}

Vst_cpp1AudioProcessorEditor::~Vst_cpp1AudioProcessorEditor()
{
}

//==============================================================================
void Vst_cpp1AudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Midi Volume", 0, 0, getWidth(), 30, juce::Justification::centred, 1);
}

void Vst_cpp1AudioProcessorEditor::resized()
{
	midiVolume.setBounds(40, 30, 20, getHeight() - 60);
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

void Vst_cpp1AudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
	audioProcessor.noteOnVel = midiVolume.getValue();
}
