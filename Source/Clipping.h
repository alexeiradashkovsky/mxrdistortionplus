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
    const float eta = 1.f;
    const float Is = 1.e-15;
    const float Vt = 26.e-6;

    float Fs;
    float Ts;

    float C1;
    float R1;
    float x1;

    float R5;
    
    float potLev;

    float Vd;
    float thr;

    // Grouped Resistances
    float G;
};