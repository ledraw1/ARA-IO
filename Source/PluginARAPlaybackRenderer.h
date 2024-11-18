/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for an ARA playback renderer implementation.

  ==============================================================================
*/

#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include "PluginARADocumentController.h"

//==============================================================================
/**
*/
class ARAIO_PlaybackRenderer  : public juce::ARAPlaybackRenderer
{
public:
    //==============================================================================
    ARAIO_PlaybackRenderer(ARA::PlugIn::DocumentController* documentController,
                          ProcessingLockInterface& lockInterface)
        : juce::ARAPlaybackRenderer(documentController)
        , processingLock(lockInterface)
    {}

    //==============================================================================
    void prepareToPlay (double sampleRate,
                        int maximumSamplesPerBlock,
                        int numChannels,
                        juce::AudioProcessor::ProcessingPrecision,
                        AlwaysNonRealtime alwaysNonRealtime) override;
    void releaseResources() override;

    //==============================================================================
    bool processBlock (juce::AudioBuffer<float>& buffer,
                       juce::AudioProcessor::Realtime realtime,
                       const juce::AudioPlayHead::PositionInfo& positionInfo) noexcept override;

private:
    //==============================================================================
    ProcessingLockInterface& processingLock;
    double sampleRate = 44100.0;
    int maximumSamplesPerBlock = 4096;
    int numChannels = 1;
    bool useBufferedAudioSourceReader = true;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ARAIO_PlaybackRenderer)
};
