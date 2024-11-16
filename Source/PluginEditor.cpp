/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ARAIO_AudioProcessorEditor::ARAIO_AudioProcessorEditor (ARAIO_AudioProcessor& p)
    : AudioProcessorEditor (&p)
    #if JucePlugin_Enable_ARA
    , AudioProcessorEditorARAExtension (&p)
    #endif
    , processorRef (p)
{
    juce::ignoreUnused (processorRef);

    setSize (400, 300);
}

ARAIO_AudioProcessorEditor::~ARAIO_AudioProcessorEditor()
{
}

//==============================================================================
void ARAIO_AudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("ARA-IO Plugin", getLocalBounds(), juce::Justification::centred, 1);
}

void ARAIO_AudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
