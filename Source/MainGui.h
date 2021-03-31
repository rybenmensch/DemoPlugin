/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 6.0.7

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2020 - Raw Material Software Limited.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include <JuceHeader.h>
#include "AudioParams.h"
#include "PositionDisplay.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class MainGui  : public juce::Component,
                 public AudioProcessorParameter::Listener,
                 public AsyncUpdater,
                 public juce::Button::Listener
{
public:
    //==============================================================================
    MainGui (AudioParams* pAudioParams);
    ~MainGui() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void parameterValueChanged(int parameterIndex, float newValue) override
    {
        triggerAsyncUpdate();
    }

    void parameterGestureChanged(int parameterIndex, bool gestureIsStarting) override
    {
        //nothing to do.
        //overriding just because we need to
    }

    void handleAsyncUpdate() override
    {
        updatePosition();
    }

    //[/UserMethods]

    void paint (juce::Graphics& g) override;
    void resized() override;
    void buttonClicked (juce::Button* buttonThatWasClicked) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    void updatePosition();
    AudioParams* pParams;
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<juce::TextButton> buttonAction;
    std::unique_ptr<PositionDisplay> display;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainGui)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

