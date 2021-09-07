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
 C2(1.e-9),
 x2(0.f),
 R5(10.e3),
 Vd(0.0f),
 thr(0.00000001f) {
    updateCoefficients();
    setKnob(levelKnob);
}


float Clipping::processSample(float Vi) {
    float b = 1.f; // for dampening
    float fd = -Vi / R2 + Is * sinh(Vd / (eta*Vt)) + G * Vd - x2;
    for (int i = 0; i < 50 && abs(fd) > thr; ++i) {
        float fdd = (Is / (eta*Vt)) * cosh(Vd / (eta*Vt)) + G;
        float Vnew = Vd - b * fd / fdd;
        float fn = -Vi / R2 + Is * sinh(Vnew / (eta*Vt)) + G * Vnew - x2;
        if (abs(fn) < abs(fd)) {
            Vd = Vnew;
            b = 1.f;
        }
        else {
            b *= 0.5f;
        }

        fd = -Vi / R2 + Is * sinh(Vd / (eta*Vt)) + G * Vd - x2;
    }
    
    x2 = 2 * Vd / R2 - x2;
    return  potLev * Vd;
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
    R2 = Ts / (2.f*C2);
    updateGroupedResistances();
}

void Clipping::updateGroupedResistances() {
    G = (1 / R5 + 1 / R2);
}