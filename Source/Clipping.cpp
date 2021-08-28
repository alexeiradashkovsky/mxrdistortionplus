/*
  ==============================================================================

    Clipping.cpp
    Created: 27 Aug 2021 10:23:19am
    Author:  radal

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Clipping.h"

//==============================================================================
Clipping::Clipping(float levelKnob)
:Fs(44100.f),
 C1(1.e-9),
 x1(0.f),
 R5(10.e3),
 Vd(0.1f),
 thr(0.00000001f) {
    updateCoefficients();
    setKnob(levelKnob);
}


float Clipping::processSample(float Vi) {
    float b = 1.f; // for dampening
    float fd = -Vi / R1 + Is * sinh(Vd / (eta*Vt)) + G * Vd - x1;
    for (int i = 0; i < 50 && abs(fd) > thr; ++i) {
        float fdd = (Is / (eta*Vt)) * cosh(Vd / (eta*Vt)) + G;
        float Vnew = Vd - b * fd / fdd;
        float fn = -Vi / R1 + Is * sinh(Vnew / (eta*Vt)) + G * Vnew - x1;
        if (abs(fn) < abs(fd)) {
            Vd = Vnew;
            b = 1.f;
        }
        else {
            b *= 0.5f;
        }

        fd = -Vi / R1 + Is * sinh(Vd / (eta*Vt)) + G * Vd - x1;
    }
    
    x1 = 2 / (R1 * Vd) - x1;
    return Vd;
}

void Clipping::prepare(float newFs) {
    if (newFs != Fs) {
        Fs = newFs;
        updateCoefficients();
    }
}

void Clipping::setKnob(float levelKnob) {
    if (potLev != levelKnob) {
        potLev = 0.00001f + 0.99998f*levelKnob;
    }
}

void Clipping::updateCoefficients() {
    Ts = 1.f / Fs;
    R1 = Ts / (2.f*C1);
    updateGroupedResistances();
}

void Clipping::updateGroupedResistances() {
    G = (1 / R5 + 1 / R1);
}