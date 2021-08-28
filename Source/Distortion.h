/*
  ==============================================================================

    Distortion.h
    Created: 27 Aug 2021 10:22:33am
    Author:  radal

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class Distortion {
public:
    explicit Distortion(float disKnob);
    ~Distortion() = default;

    float processSample(float Vi);

    void prepare(float newFs);

    void setKnob(float disKnob);
private:
    void updateCoefficients();
    void updateGroupedResistances();

    float Fs;
    float Ts;

    float C1;
    float R1;
    float x1;

    float R3;
    float R4;

    float potDis;
    float Rp;

    // Grouped Resistances
    float G;
    float Gb;
    float Gi;
    float Gx1;
};
