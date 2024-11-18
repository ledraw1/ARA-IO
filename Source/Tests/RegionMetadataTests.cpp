#include <juce_core/juce_core.h>
#include "../PluginARADocumentController.h"

class RegionMetadataTests : public juce::UnitTest
{
public:
    RegionMetadataTests() : juce::UnitTest("Region Metadata Tests") {}

    void runTest() override
    {
        beginTest("Test null sequence handling");
        {
            ARAIO_DocumentController controller(nullptr);
            auto metadata = controller.getRegionMetadata(nullptr);
            expect(metadata.isEmpty());
        }

        beginTest("Test fallback name handling");
        {
            ARAIO_DocumentController controller(nullptr);
            // Create a minimal mock playback region with no name
            struct MockPlaybackRegion : public ARA::PlugIn::PlaybackRegion {
                MockPlaybackRegion() : PlaybackRegion(nullptr, nullptr) {}
                const char* getName() const noexcept override { return nullptr; }
                ARA::PlugIn::AudioSource* getAudioSource() const noexcept override { return nullptr; }
                ARA::SamplePosition getStartInAudioModificationSamples() const noexcept override { return 0; }
                ARA::SampleCount getDurationInSamples() const noexcept override { return 1000; }
            } mockRegion;

            auto metadata = controller.getRegionMetadata(&mockRegion);
            expect(!metadata.isEmpty());
            expect(metadata.contains("name"));
            expect(metadata["name"] == "Unnamed Region");
        }

        beginTest("Test time validation");
        {
            ARAIO_DocumentController controller(nullptr);
            struct MockPlaybackRegion : public ARA::PlugIn::PlaybackRegion {
                MockPlaybackRegion(ARA::SamplePosition start) : PlaybackRegion(nullptr, nullptr), startPos(start) {}
                const char* getName() const noexcept override { return "Test Region"; }
                ARA::PlugIn::AudioSource* getAudioSource() const noexcept override { return nullptr; }
                ARA::SamplePosition getStartInAudioModificationSamples() const noexcept override { return startPos; }
                ARA::SampleCount getDurationInSamples() const noexcept override { return 1000; }
                ARA::SamplePosition startPos;
            };

            // Test negative start time
            MockPlaybackRegion negativeStartRegion(-100);
            auto metadata = controller.getRegionMetadata(&negativeStartRegion);
            expect(!metadata.isEmpty());
            expect(metadata.contains("startTime"));
            expect(static_cast<double>(metadata["startTime"]) >= 0.0);

            // Test valid start time
            MockPlaybackRegion validStartRegion(1000);
            metadata = controller.getRegionMetadata(&validStartRegion);
            expect(!metadata.isEmpty());
            expect(metadata.contains("startTime"));
            expect(static_cast<double>(metadata["startTime"]) == 1000.0);
        }

        beginTest("Test audio source validation");
        {
            ARAIO_DocumentController controller(nullptr);
            struct MockAudioSource : public ARA::PlugIn::AudioSource {
                MockAudioSource() : AudioSource(nullptr) {}
                const char* getName() const noexcept override { return "Test Source"; }
            } mockSource;

            struct MockPlaybackRegion : public ARA::PlugIn::PlaybackRegion {
                MockPlaybackRegion(ARA::PlugIn::AudioSource* source) 
                    : PlaybackRegion(nullptr, nullptr), audioSource(source) {}
                const char* getName() const noexcept override { return "Test Region"; }
                ARA::PlugIn::AudioSource* getAudioSource() const noexcept override { return audioSource; }
                ARA::SamplePosition getStartInAudioModificationSamples() const noexcept override { return 0; }
                ARA::SampleCount getDurationInSamples() const noexcept override { return 1000; }
                ARA::PlugIn::AudioSource* audioSource;
            };

            // Test with valid audio source
            MockPlaybackRegion regionWithSource(&mockSource);
            auto metadata = controller.getRegionMetadata(&regionWithSource);
            expect(!metadata.isEmpty());
            expect(metadata.contains("audioSourceName"));
            expect(metadata["audioSourceName"] == "Test Source");

            // Test with null audio source
            MockPlaybackRegion regionWithoutSource(nullptr);
            metadata = controller.getRegionMetadata(&regionWithoutSource);
            expect(!metadata.isEmpty());
            expect(metadata.contains("audioSourceName"));
            expect(metadata["audioSourceName"] == "Unknown Source");
        }

        // Note: Due to the nature of ARA objects, we're using minimal mock objects
        // that implement only the necessary interfaces for testing. In a production
        // environment, you might want to create more sophisticated mock objects
        // or use a mocking framework.
    }
};

static RegionMetadataTests regionMetadataTests;
