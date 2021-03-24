/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "MainGui.h"

//==============================================================================
/**
*/
class DemoPluginAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    DemoPluginAudioProcessorEditor (DemoPluginAudioProcessor&);
    ~DemoPluginAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    DemoPluginAudioProcessor& audioProcessor;
    MainGui* mainGui;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DemoPluginAudioProcessorEditor)
};
