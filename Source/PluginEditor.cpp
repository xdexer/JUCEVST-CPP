/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Vst_cpp1AudioProcessorEditor::Vst_cpp1AudioProcessorEditor (Vst_cpp1AudioProcessor& p, juce::AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), audioProcessor (p), valueTreeState(vts)
{
	setSize(400, 400);
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
	gainLabel.setText("Gain", juce::dontSendNotification);
	gainSlider.setSliderStyle(juce::Slider::LinearBarVertical);
	gainSlider.setRange(0.0, 127.0, 1.0);
	gainSlider.setValue(1.0);
	gainAttachment.reset(new SliderAttachment(valueTreeState, "gain", gainSlider));
	//invertButton.setButtonText("Invert Phase");
	//invertAttachment.reset(new ButtonAttachment(valueTreeState, "invertPhase", invertButton));
    
	//addAndMakeVisible(&gainLabel);
	addAndMakeVisible(&gainSlider);
	//addAndMakeVisible(&invertButton);
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
	gainSlider.setBounds(40, 30, 20, getHeight() - 60);
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

void Vst_cpp1AudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
	//audioProcessor.noteOnVel = gainSlider.getValue();
}
