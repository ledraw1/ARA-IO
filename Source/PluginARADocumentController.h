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
