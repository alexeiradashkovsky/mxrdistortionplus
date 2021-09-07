/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "PedalComponent.h"


//==============================================================================
/**
*/
class MXRDistortionPlusAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    MXRDistortionPlusAudioProcessorEditor (MXRDistortionPlusAudioProcessor&);
    ~MXRDistortionPlusAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MXRDistortionPlusAudioProcessor& audioProcessor;

    juce::Rectangle<int> PedalSize = { 265,475 };
    juce::StringRef PedalName = "BrutalARAudio";
    juce::StringRef PedalShortName = "DS-PLUS";
    KnobNames PedalKnobNames = { "Distortion", "Level" };
    juce::Colour PedalColour = juce::Colour(0xFFFFFB67);

    PedalComponent pedal{ audioProcessor,PedalName,PedalShortName,PedalColour,PedalKnobNames };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MXRDistortionPlusAudioProcessorEditor)
};
