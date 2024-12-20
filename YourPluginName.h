#pragma once

#include <vector>
#include <juce_audio_processors/juce_audio_processors.h>

#include "tools/SynchronBlockProcessor.h"
#include "PluginSettings.h"

class YourPluginNameAudioProcessor;

// This is how we define our parameter as globals to use it in the audio processor as well as in the editor
const struct
{
	const std::string ID = "ExampleID";
	const std::string name = "Example";
	const std::string unitName = "xyz";
	const float minValue = 1.f;
	const float maxValue = 2.f;
	const float defaultValue = 1.2f;
}g_paramExample;


class YourPluginNameAudio : public SynchronBlockProcessor
{
public:
    YourPluginNameAudio(YourPluginNameAudioProcessor* processor);
    void prepareToPlay(double sampleRate, int max_samplesPerBlock, int max_channels);
    virtual int processSynchronBlock(juce::AudioBuffer<float>&, juce::MidiBuffer& midiMessages, int NrOfBlocksSinceLastProcessBlock);

    // parameter handling
  	void addParameter(std::vector < std::unique_ptr<juce::RangedAudioParameter>>& paramVector);
    void prepareParameter(std::unique_ptr<juce::AudioProcessorValueTreeState>&  vts);
    
    // some necessary info for the host
    int getLatency(){return m_Latency;};

private:
	YourPluginNameAudioProcessor* m_processor;
    int m_Latency = 0;
};

class YourPluginNameGUI : public juce::Component
{
public:
	YourPluginNameGUI(YourPluginNameAudioProcessor& p, juce::AudioProcessorValueTreeState& apvts);

	void paint(juce::Graphics& g) override;
	void resized() override;
private:
	YourPluginNameAudioProcessor& m_processor;
    juce::AudioProcessorValueTreeState& m_apvts; 

};
