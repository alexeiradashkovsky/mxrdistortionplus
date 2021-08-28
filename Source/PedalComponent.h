/*
  ==============================================================================

    PedalCompememt.h
    Created: 15 Jul 2021 4:51:47pm
    Author:  radal
    This class was created by Tony Lassandro. Check out
    his GitHub page for more resources: lassandroan
  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
//==============================================================================
/*
*/

using KnobNames = std::tuple<juce::StringRef, juce::StringRef>;


class PedalKnobLookAndFeel : public juce::LookAndFeel_V4 {
public:
    PedalKnobLookAndFeel() = default;
    ~PedalKnobLookAndFeel() = default;


    void drawRotarySlider(
        juce::Graphics&,
        int x,
        int y,
        int width,
        int height,
        float sliderPosProportional,
        float rotaryStartAngle,
        float rotaryEndAngle,
        juce::Slider&
    ) override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PedalKnobLookAndFeel)
};


class PedalComponent : public juce::Component, public juce::Slider::Listener
{
public:
    PedalComponent(MXRDistortionPlusAudioProcessor& p,
        const juce::StringRef    &name,
        const juce::StringRef    &shortName,
        const juce::Colour       &colour,
        const KnobNames    &knobs
    );

    ~PedalComponent();

    void sliderValueChanged(juce::Slider * slider) override;

private:
    void mouseUp(const juce::MouseEvent&) override;
    void paint(juce::Graphics&) override;
    void resized() override;

    // SharedResourcePointer acts as static storage and lets us use one shared
    // PedalKnobLookAndFeel object no matter how many PedalComponents we create
    juce::SharedResourcePointer<PedalKnobLookAndFeel> lookAndFeel;

    juce::Colour colour;
    juce::Slider knobs[2];

    MXRDistortionPlusAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PedalComponent)
};
