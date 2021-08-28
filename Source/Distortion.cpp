/*
  ==============================================================================

    Distortion.cpp
    Created: 27 Aug 2021 10:22:33am
    Author:  radal

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Distortion.h"

//==============================================================================
Distortion::Distortion(float disKnob)
:Fs(44100.f),
 Ts(1.f / Fs),
 C1(47.e-9),
 x1(0.f),
 R1(Ts / (2.f*C1)),
 R3(4.7e3),
 R4(1.e6),
 potDis(0.f),
 Rp(0.f) {
    setKnob(disKnob);
    updateCoefficients();
}


float Distortion::processSample(float Vi) {
    float Vb = Gb * Vi - R1 * Gb*x1;
    float Vr1 = Vi - Vb;
    float Vo = Gi * Vi - Gx1 * x1;
    if (Vo > 4.5f) {
        Vo = 4.5f;
    } else if (Vo < -4.5f) {
        Vo = -4.5f;
    }
    x1 = (2.f * Vr1 / R1) - x1;
    return Vo;
}

void Distortion::prepare(float newFs) {
    if (newFs != Fs) {
        Fs = newFs;
        updateCoefficients();
    }
}

void Distortion::setKnob(float disKnob) {
    if (disKnob != potDis) {
        potDis = disKnob;
        Rp = 1.e6 * (1.f - potDis);
        updateGroupedResistances();
    }
}

void Distortion::updateCoefficients() {
    Ts = 1.f / Fs;
    R1 = Ts / (2.f*C1);
    updateGroupedResistances();
}

void Distortion::updateGroupedResistances() {
    G = 1.f / (R1 + R3 + Rp);
    Gb = (R3 + Rp) * G;
    Gi = 1.f + R4 * G;
    Gx1 = R1 * R4 * G;
}