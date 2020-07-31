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
    g.drawFittedText ("Gain VST", 0, 0, getWidth(), 30, juce::Justification::centred, 1);
}

void Vst_cpp1AudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

void Vst_cpp1AudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
	
}
