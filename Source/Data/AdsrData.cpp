/*
  ==============================================================================

    AdsrData.cpp
    Created: 15 Mar 2021 1:26:06pm
    Author:  Dominik Marcinkowski

  ==============================================================================
*/

#include "AdsrData.h"

//==============================================================================

void AdsrData::updateADSR(float attack,float decay, float sustain, float release)
{
    adsrParams.attack = attack;
    adsrParams.decay = decay;
    adsrParams.sustain = sustain;
    adsrParams.release = release;
    
    setParameters(adsrParams);
}
