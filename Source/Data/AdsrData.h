/*
  ==============================================================================

    AdsrData.h
    Created: 15 Mar 2021 1:26:06pm
    Author:  Dominik Marcinkowski

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class AdsrData  : public juce::ADSR
{
public:
    void updateADSR(float attack, float decay, float sustain, float release);

private:
    juce::ADSR::Parameters adsrParams;
};
