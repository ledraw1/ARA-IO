#include <JuceHeader.h>
#include "../Source/PluginARADocumentController.h"
#include "../Source/PluginARAPlaybackRenderer.h"

class TestDocumentController : public ARAIO_DocumentController 
{
public:
    TestDocumentController() 
        : ARAIO_DocumentController(nullptr, nullptr)
    {
    }

    using ARAIO_DocumentController::getProcessingLock;
};

class ARAPluginTests : public juce::UnitTest
{
public:
    ARAPluginTests() : juce::UnitTest("ARA Plugin Tests") {}

    void runTest() override
    {
        beginTest("ProcessingLock Test");
        {
            TestDocumentController controller;
            auto lock = controller.getProcessingLock();
            expect(lock.isLocked());
        }

        beginTest("PlaybackRenderer Creation Test");
        {
            TestDocumentController controller;
            std::unique_ptr<ARAIO_PlaybackRenderer> renderer(new ARAIO_PlaybackRenderer(controller.getDocumentController(), controller));
            expect(renderer != nullptr);
        }

        beginTest("PlaybackRenderer Processing Test");
        {
            TestDocumentController controller;
            ARAIO_PlaybackRenderer renderer(controller.getDocumentController(), controller);
            
            juce::AudioBuffer<float> buffer(2, 512);
            buffer.clear();
            
            // Test with playback disabled
            juce::AudioPlayHead::PositionInfo pos;
            pos.setIsPlaying(false);
            
            expect(renderer.processBlock(buffer, juce::AudioProcessor::Realtime::no, pos));
            
            // Verify buffer is silent when not playing
            for (int ch = 0; ch < buffer.getNumChannels(); ++ch)
                for (int s = 0; s < buffer.getNumSamples(); ++s)
                    expect(buffer.getSample(ch, s) == 0.0f);
        }
    }
};

static ARAPluginTests araPluginTests;
