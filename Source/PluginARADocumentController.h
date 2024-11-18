/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for an ARA document controller implementation.

  ==============================================================================
*/

#pragma once

#include <juce_audio_processors/juce_audio_processors.h>

//==============================================================================
/**
    Interface for thread-safe processing lock.
*/
class ProcessingLockInterface
{
public:
    virtual ~ProcessingLockInterface() = default;
    virtual juce::ScopedTryReadLock getProcessingLock() = 0;
};

//==============================================================================
/**
    Main document controller for ARA plugin.
    Handles document state, playback regions, and audio modifications.
*/
class ARAIO_DocumentController  : public juce::ARADocumentControllerSpecialisation,
                                public ProcessingLockInterface
{
public:
    //==============================================================================
    using juce::ARADocumentControllerSpecialisation::ARADocumentControllerSpecialisation;

    // Add any public methods that you need here
    const juce::Array<ARA::PlugIn::RegionSequence*>& getRegionSequences() const { return regionSequences; }

    // Get metadata for all regions in a sequence
    struct RegionMetadata {
        juce::String name;
        double startTime;
        double endTime;
        juce::String audioSource;
    };

    juce::Array<RegionMetadata> getRegionMetadata(ARA::PlugIn::RegionSequence* sequence) const
    {
        juce::Array<RegionMetadata> metadata;
        if (sequence == nullptr)
            return metadata;

        for (auto playbackRegion : sequence->getPlaybackRegions())
        {
            if (playbackRegion == nullptr)
                continue;

            RegionMetadata region;
            
            // Get name with fallback
            auto name = playbackRegion->getName();
            region.name = name != nullptr ? juce::String(name) : juce::String("Unnamed Region");

            // Get timing info with validation
            region.startTime = juce::jmax(0.0, playbackRegion->getStartInPlaybackTime());
            region.endTime = juce::jmax(region.startTime, playbackRegion->getEndInPlaybackTime());

            // Get audio source with validation
            auto modification = playbackRegion->getAudioModification();
            auto audioSource = modification != nullptr ? modification->getAudioSource() : nullptr;
            region.audioSource = (audioSource != nullptr && audioSource->getName() != nullptr) 
                               ? juce::String(audioSource->getName()) 
                               : juce::String("Unknown Source");

            metadata.add(region);
        }
        return metadata;
    }

protected:
    //==============================================================================
    // Override document controller customization methods here
    juce::ARAPlaybackRenderer* doCreatePlaybackRenderer() noexcept override;

    bool doRestoreObjectsFromStream (juce::ARAInputStream& input, const juce::ARARestoreObjectsFilter* filter) noexcept override;
    bool doStoreObjectsToStream (juce::ARAOutputStream& output, const juce::ARAStoreObjectsFilter* filter) noexcept override;

    juce::ScopedTryReadLock getProcessingLock() override { return juce::ScopedTryReadLock(processLock); }

private:
    //==============================================================================
    juce::ReadWriteLock processLock;
    juce::Array<ARA::PlugIn::RegionSequence*> regionSequences;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ARAIO_DocumentController)
};
