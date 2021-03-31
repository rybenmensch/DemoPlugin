/*
  ==============================================================================

    PositionDisplay.h
    Created: 11 Mar 2021 11:38:43pm
    Author:  Schweizer Christian

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class PositionDisplay  : public juce::Component
{
public:
    PositionDisplay(AudioParams* pAudioParams)
    {
        // keep a reference to our audio params
        pParams = pAudioParams;
    }

    ~PositionDisplay() override
    {
        // nothing to do since we only keep a reference to an object that was created by "someone" else
    }

    void paint (juce::Graphics& g) override
    {
        // get snapshot of our AED coordinates and transform them to XYZ coordinates (our screen operates in XY-space)
        float a = pParams->a->get() * MathConstants<float>::pi / 180.0f;
        float e = pParams->e->get() * MathConstants<float>::pi / 180.0f;
        float d = pParams->d->get();
        float x = d * cos(e) * sin(a);
        float y = d * cos(e) * cos(a);
        float z = d * sin(e);
        
        int radarSize = jmin(getWidth(), getHeight());
        
        // draw rectangular background
        g.setColour(juce::Colour (0xff664444));
        g.fillRect(0, 0, radarSize, radarSize);
        
        // draw radar circles
        g.setColour(juce::Colours::white);
        juce::Point<float> center(radarSize / 2.0, radarSize / 2.0);
        for(int i = 1; i <= 10; i++)
        {
            juce::Rectangle<float> rect;
            rect.setSize(i / 10.0 * radarSize, i / 10.0 * radarSize);
            rect.setCentre(center);
            g.drawEllipse(rect, 1.0f);
        }
        
        // draw position
        g.setColour(juce::Colours::limegreen);
        juce::Point<float> coordinates;
        coordinates.setX((x + 1) / 2.0 * radarSize);
        coordinates.setY((-y + 1) / 2.0 * radarSize); // inverted Y (screen Y is top->bottom, mathematical Y is bottom->top)
        int pointSize = (z + 1.0) * 20.0; // Z is simply visualized by point size (small = far, large = near)
        
        juce::Rectangle<float> bounds;
        bounds.setSize(pointSize, pointSize);
        bounds.setCentre(coordinates);
        g.fillEllipse(bounds);
    }

    void resized() override
    {
        // nothing special to do because the paint() function is automatically called from the base class
    }

private:
    AudioParams* pParams;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PositionDisplay)
};
