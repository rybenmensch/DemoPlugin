/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DemoPluginAudioProcessorEditor::DemoPluginAudioProcessorEditor (DemoPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    mainGui = new MainGui();
    
    addAndMakeVisible(mainGui);
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
}

DemoPluginAudioProcessorEditor::~DemoPluginAudioProcessorEditor()
{
    delete mainGui;
}

//==============================================================================
void DemoPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("SALI MITENAND!", getLocalBounds(), juce::Justification::centred, 1);
}

void DemoPluginAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    mainGui->setBounds(getBounds());
}
