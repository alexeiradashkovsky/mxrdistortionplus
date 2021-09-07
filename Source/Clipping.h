/*
  ==============================================================================

    Clipping.h
    Created: 27 Aug 2021 10:23:19am
    Author:  radal

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class Clipping {
public:
    explicit Clipping(float levelKnob);
    ~Clipping() = default;

    float processSample(float Vi);

    void prepare(float newFs);

    void setKnob(float levelKnob);

private:
    void updateCoefficients();
    void updateGroupedResistances();
    const float eta = 2.f;
    const float Is = 1.e-6;
    const float Vt = 26.e-3;

    float Fs;
    float Ts;

    float C2;
    float R2;
    float x2;

    float R5;
    
    float potLev;

    float Vd;
    float thr;

    // Grouped Resistances
    float G;
};
