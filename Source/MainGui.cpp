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

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "MainGui.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
MainGui::MainGui (AudioParams* pAudioParams)
{
    //[Constructor_pre] You can add your own custom stuff here..
    pParams = pAudioParams;
    pParams->a->addListener(this);
    pParams->e->addListener(this);
    pParams->d->addListener(this);

    //[/Constructor_pre]

    buttonAction.reset (new juce::TextButton ("buttonAction"));
    addAndMakeVisible (buttonAction.get());
    buttonAction->setTooltip (TRANS("What the fuck did you just fucking say about me, you little bitch? I\'ll have you know I graduated top of my class in the Navy Seals, and I\'ve been involved in numerous secret raids on Al-Quaeda, and I have over 300 confirmed kills. I am trained in gorilla warfare and I\'m the top sniper in the entire US armed forces. You are nothing to me but just another target. I will wipe you the fuck out with precision the likes of which has never been seen before on this Earth, mark my fucking words. You think you can get away with saying that shit to me over the Internet? Think again, fucker. As we speak I am contacting my secret network of spies across the USA and your IP is being traced right now so you better prepare for the storm, maggot. The storm that wipes out the pathetic little thing you call your life. You\'re fucking dead, kid. I can be anywhere, anytime, and I can kill you in over seven hundred ways, and that\'s just with my bare hands. Not only am I extensively trained in unarmed combat, but I have access to t"));
    buttonAction->setButtonText (TRANS("Sali!"));
    buttonAction->addListener (this);

    display.reset (new PositionDisplay (pParams));
    addAndMakeVisible (display.get());
    display->setName ("new component");


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

MainGui::~MainGui()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    pParams->a->removeListener(this);
    pParams->e->removeListener(this);
    pParams->d->removeListener(this);
    //[/Destructor_pre]

    buttonAction = nullptr;
    display = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void MainGui::paint (juce::Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (juce::Colour (0xff323e44));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void MainGui::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    buttonAction->setBounds (8, 8, getWidth() - 23, 24);
    display->setBounds (8, 40, getWidth() - 23, getHeight() - 50);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void MainGui::buttonClicked (juce::Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == buttonAction.get())
    {
        //[UserButtonCode_buttonAction] -- add your button handler code here..
        AlertWindow::showMessageBoxAsync(AlertWindow::AlertIconType::WarningIcon, "Gratuliere", "Du hesch die ewige.");
        Random rnd;
        *pParams->a = rnd.nextInt(360);
        *pParams->e = rnd.nextInt(90) - 90;
        *pParams->d = rnd.nextInt(10) / 10.0f;

        //[/UserButtonCode_buttonAction]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void MainGui::updatePosition(){
    display->repaint();
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="MainGui" componentName=""
                 parentClasses="public juce::Component, public AudioProcessorParameter::Listener, public AsyncUpdater"
                 constructorParams="AudioParams* pAudioParams" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ff323e44"/>
  <TEXTBUTTON name="buttonAction" id="66d2a3a4fcca44ed" memberName="buttonAction"
              virtualName="" explicitFocusOrder="0" pos="8 8 23M 24" tooltip="What the fuck did you just fucking say about me, you little bitch? I'll have you know I graduated top of my class in the Navy Seals, and I've been involved in numerous secret raids on Al-Quaeda, and I have over 300 confirmed kills. I am trained in gorilla warfare and I'm the top sniper in the entire US armed forces. You are nothing to me but just another target. I will wipe you the fuck out with precision the likes of which has never been seen before on this Earth, mark my fucking words. You think you can get away with saying that shit to me over the Internet? Think again, fucker. As we speak I am contacting my secret network of spies across the USA and your IP is being traced right now so you better prepare for the storm, maggot. The storm that wipes out the pathetic little thing you call your life. You're fucking dead, kid. I can be anywhere, anytime, and I can kill you in over seven hundred ways, and that's just with my bare hands. Not only am I extensively trained in unarmed combat, but I have access to t"
              buttonText="Sali!" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <GENERICCOMPONENT name="new component" id="e8246abff378226" memberName="display"
                    virtualName="" explicitFocusOrder="0" pos="8 40 23M 50M" class="PositionDisplay"
                    params="pParams"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

