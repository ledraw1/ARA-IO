/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "PluginProcessor.h"

//==============================================================================
/**
*/
class ARAIO_AudioProcessorEditor  : public juce::AudioProcessorEditor
                                   #if JucePlugin_Enable_ARA
                                    , public juce::AudioProcessorEditorARAExtension
                                   #endif
{
public:
    explicit ARAIO_AudioProcessorEditor (ARAIO_AudioProcessor&);
    ~ARAIO_AudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    ARAIO_AudioProcessor& processorRef;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ARAIO_AudioProcessorEditor)
};
