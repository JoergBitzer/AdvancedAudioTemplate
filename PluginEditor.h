#pragma once

#include "PluginProcessor.h"
// #include "JadeLookAndFeel.h"
#include "tools/PresetHandler.h"
#include "tools/MidiModPitchState.h"


#include "YourPluginName.h"

//==============================================================================
class YourPluginNameAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                            private juce::AudioProcessorParameter::Listener
{
public:
    
    explicit YourPluginNameAudioProcessorEditor (YourPluginNameAudioProcessor&);
    ~YourPluginNameAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // Turns the preset bar's Save button red once the user changes a parameter.
    // Listens to parameter GESTURES, which only user actions produce (slider drags,
    // typed values, double-click resets, buttons, combo boxes via the JUCE attachments)
    // -- not preset loading or host automation, which would otherwise mark a just-loaded
    // preset as changed. Gestures may arrive on any thread, hence the async hop.
    void parameterValueChanged(int, float) override {}
    void parameterGestureChanged(int parameterIndex, bool gestureIsStarting) override;

    // JadeLookAndFeel m_jadeLAF;
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    YourPluginNameAudioProcessor& m_processorRef;
    PresetComponent m_presetGUI;
#if WITH_MIDIKEYBOARD    
    MidiKeyboardComponent m_keyboard;
    MidiModPitchBendStateComponent m_wheels;    
#endif
    // plugin specific components
    YourPluginNameGUI m_editor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (YourPluginNameAudioProcessorEditor)
};
