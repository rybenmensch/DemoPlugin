/*
  ==============================================================================

    AudioParams.h
    Created: 31 Mar 2021 2:12:29pm
    Author:  Manolo Müller

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class AudioParams {
public:
    AudioParams(juce::AudioProcessor *p){
        a = new AudioParameterFloat("Azimuth",      "Azimuth",      NormalisableRange<float>(0.0f, 360.0f), 0.0f);
        e = new AudioParameterFloat("Elevation",    "Elevation",    NormalisableRange<float>(-90.0f, 90.0f), 0.0f);
        d = new AudioParameterFloat("Distance",     "Distance",     NormalisableRange<float>(0.0f, 1.0f), 0.5f);
        
        //by adding the parameters to AudioProcessor we give the responsibility to AudioProcessor to destroy
        p->addParameter(a);
        p->addParameter(e);
        p->addParameter(d);
    }

    AudioParameterFloat *a;
    AudioParameterFloat *e;
    AudioParameterFloat *d;
};
