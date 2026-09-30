# AdvancedAudioTemplate
A template for quick development of audio plugins on a semi-professional level.

Dependencies:
This template is based on JUCE. So you need to clone JUCE and you need one more CMakeLists.txt file from the repository AudioDevOrga.

Your directory structure should look like this

YourDevDir
    CMakeLists.txt (from AudioDevOrga)
    JUCE (directory)
    YourNewProjectDir (see Usage section of this ReadMe)
        CMakeLists.txt (from this template)
        tools (template dir)
        PluginEditor.cpp
        PluginEditor.h
        PluginProcessor.cpp
        PluginProcessor.h
        PluginSettings.h
        YourPluginName.cpp (keep this name for the file, it will be renamed later)
        YourPluginName.h (keep this name for the file, it will be renamed later)

## Purpose
This template provides some basic features for effects and synth, like:
* synchron block processing for arbitrary block sizes 
* preset handler 
* resizable GUI 
* saving/loading of plugin state (with GUI size) 
* keyboard  + pitch-wheel and modulation-wheel (midi insert and display)  
* Access to Version Number given in CMakeLists.txt
* a template plugin cpp and h for easy start (named YourPluginName.cpp and h). 

## History / Versioning
V1.0 basic usage is possible
V1.1 added access to AudioProcessor in the Algo and GUI (necessary for AudioPlayHead and to have getter function for the GUI)
V1.2 (lessons from StereoWidener, 2026-09-30): the Save button turns red when the user changes a parameter
(the editor listens to parameter gestures); factory presets are deployed one by one (missing ones are copied,
unmodified factory copies with a lower presetversion are updated, user-saved presets are never overwritten);
new tools/LogFrequencyRange.h; jassert warning with JUCE 9 fixed.

## Versioning of your plugin
The version is set in CMakeLists.txt: `project(${TARGET_NAME} VERSION 0.0.1)`. It is shown in the GUI
(Versioning.h, `PLUGIN_VERSION_MAJOR/MINOR/PATCH`) and in the plugin's metadata. For every change that you
build and commit:
* a new feature raises the second number and sets the third to zero (1.0.3 -> 1.1.0)
* a fix or other change raises the third number (1.1.0 -> 1.1.1)
* the first number is raised for a big step, e.g. the first public release (1.0.0) or a new version
  that is not compatible with old presets

## License of your plugin
The template contains two license files:
* `LICENSE`: the MIT License for your source code. Change the copyright line to your name.
* `LICENSE-AGPL-3.0.txt`: JUCE is free to use under the AGPLv3 (or with a commercial JUCE licence).
  If you give plugin binaries to others, the binaries as a whole are under the AGPLv3, so put both
  files next to your plugin and publish your source code (e.g. on GitHub). The note at the end of
  `LICENSE` explains this; keep it.

## Usage

1. Create a new directory (better create a new repository in GitHub)
2. (if Github): Checkout your new project
3. copy template files (https://github.com/JoergBitzer/AdvancedAudioTemplate)
4. rename all instances of "YourPluginName" in the Files with something appropriate 
    (use a renaming-tool like   
```console    
    sed -i 's/YourPluginName/YourNewProjectName/g' *.*
```    
for MacOS (https://stackoverflow.com/questions/4247068/sed-command-with-i-option-failing-on-mac-but-works-on-linux)
for Windows: (https://stackoverflow.com/questions/17144355/how-can-i-replace-every-occurrence-of-a-string-in-a-file-with-powershell)  

```console    
 Get-ChildItem '*.*' -Recurse | ForEach {
      (Get-Content $_ | ForEach  { $_ -replace 'YourPluginName', 'YourNewProjectName' }) |
      Set-Content $_ }
```    
or start the windows subsystem for linux

or use the tools given by visual studio code (Crtl + Shift + H (replace in files)) and use your new diretory./YOUR_PLuggIn_Folder as a filter in "files to include".

5. Rename YourPluginName.cpp and YourPluginName.h into YourNewProjectName.cpp and YourNewProjectName.h (e.g. Linux: 
```console    
    rename 's/YourPluginName/YourNewProjectName/' *.*     
```    
and Windows (cmd, not PS)
```console    
ren YourPluginName.* YourNewProjectName.*
```    

6. Add your new subdiretory to the main CMakeLists.txt (in main directory YourDevDir (e.g. AudioDev)) file
7. add or remove add_compile_definitions to your intention (Do you need a preset manager (default is yes), 
                                                            Do you need a midi-keyboard display (default is no)) 
8. Test if the template builds (should without error) and start coding your plugin

## AAT2: self-contained repository and releases built by GitHub

This branch (AAT2) adds two things to the template:
* **Self-contained repository:** JUCE is included as a git submodule (`JUCE/`, pinned to a JUCE release).
  `CMakeLists.txt` works on its own (`cmake -S . -B build`) and still works as a subdirectory of
  AudioDev: if the parent project has already added JUCE, the submodule is ignored.
* **Releases built by GitHub Actions** (`.github/workflows/release.yml`): pushing a tag `vX.Y.Z` builds
  the plugin for Windows, macOS (Universal binary for Apple Silicon and Intel, VST3 + AU) and Linux and
  creates a GitHub release with one zip per system. Each zip contains the plugins, the Standalone,
  `release/ReadMeFirst.txt`, both license files and, if present, the manual (`docs/*.pdf`).
  Before packaging, every build is tested with pluginval (tools/run_pluginval.*, see "Test your plugin
  with pluginval"); if the test fails, no release is created.

### Start a new plugin with AAT2
1. Create a new (empty) repository on GitHub and clone it.
2. Copy the files of this branch into it (without `.git` and `JUCE`), e.g.:
```console
git clone -b AAT2 --depth 1 https://github.com/JoergBitzer/AdvancedAudioTemplate.git aat2
rsync -a --exclude .git --exclude JUCE --exclude .gitmodules aat2/ YourNewRepository/
```
3. Add JUCE as a submodule (in your repository), pinned to a release:
```console
git submodule add https://github.com/juce-framework/JUCE.git JUCE
git -C JUCE checkout 9.0.3
```
4. Rename "YourPluginName" in **all** files, also in the subfolders `.github` and `release`
   (the command in "Usage" only covers the main folder), then rename the two files:
```console
grep -rl YourPluginName --exclude-dir=.git --exclude-dir=JUCE . | xargs sed -i 's/YourPluginName/YourNewProjectName/g'
rename 's/YourPluginName/YourNewProjectName/' *.*
```
   Also set `PLUGIN_CODE` (unique for every plugin) and `COMPANY_NAME` in CMakeLists.txt, and
   "YourName" / "YourGitHubName" in `release/ReadMeFirst.txt` and `LICENSE`.
5. Build (Release):
```console
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release --target YourNewProjectName_VST3 YourNewProjectName_Standalone
```

### Make a release
1. Optional: put the manual as a PDF into `docs/`.
2. Raise the version in CMakeLists.txt (see "Versioning of your plugin"), commit and push.
3. Tag the commit with the same version and push the tag:
```console
git tag v1.2.3
git push origin v1.2.3
```
4. After about 10 minutes the release with the three zips is on the "Releases" page of your repository.
   The tag must match the version in CMakeLists.txt, otherwise no release is created (the zips are then
   still attached to the workflow run on the "Actions" page).

"Run workflow" on the Actions page builds all three systems without creating a release, e.g. to test a
change. GitHub Actions are free for public repositories; private repositories have a limited number of
free minutes per month (macOS minutes count ten times).

Notes: the macOS binaries are only ad-hoc signed (no Apple Developer ID); users may have to remove the
quarantine flag (`xattr -cr ...`, see `release/ReadMeFirst.txt`). The Linux binaries are built on
Ubuntu 22.04, so they also run on older distributions.
## Test your plugin with pluginval
[pluginval](https://github.com/Tracktion/pluginval) loads your plugin like a DAW and tests it hard:
parameters, automation, different sample rates and block sizes, opening and closing the editor, and
more. Run it before every commit; it finds bugs that you would otherwise only notice in a DAW.

Linux/macOS:
```console
tools/run_pluginval.sh path/to/YourPluginName.vst3
```
Windows (PowerShell):
```console
powershell -ExecutionPolicy Bypass -File tools\run_pluginval.ps1 path\to\YourPluginName.vst3
```
The script downloads pluginval on the first run, tests at the highest strictness level (10) three times
(some bugs only show up now and then; give another number as second argument) and prints SUCCESS or
FAILED per run, with the path to the log of a failed run. In AudioDev the plugin is in
`build/YourPluginName/YourPluginName_artefacts/Debug/VST3/`. Test the Debug build: there, JUCE also
checks its assertions (`jassert`), and the Linux/macOS script counts every assertion as a failure.

## Important files to look for 

### PluginSettingsh
In this file you can set the block size of your internal synchronous (fixed size) data processor.
Furthermore all global graphic adjustments are defined here.

### YourPluginName.cpp and .h

After renaming the file you use these two files to implement the algorithm and the GUI. Always start with the definition of the parameters.

### Factory presets
Put your preset XML files (saved with the preset handler, then copied from the user preset
folder) into the project, add them with `juce_add_binary_data` in CMakeLists.txt and enable
`add_compile_definitions(FACTORY_PRESETS)`. At every start, `DeployFactoryPresets()` copies
each factory preset that is missing in the user folder. An existing file is only replaced if
it is an unmodified factory copy (`bank="Factory"`) and the embedded preset has a higher
`presetversion` attribute (add `presetversion="1"` to the root element of your XML files and
raise it when you change a preset). Presets the user saved (`bank="User"`) are never touched.
A factory preset the user deleted comes back at the next start.

### tools/LogFrequencyRange.h
`jade::makeLogFrequencyRange(minHz, maxHz)`: a logarithmic range for frequency parameters
(cutoffs, crossovers). Use it instead of writing your own: a custom range must clamp in its
snap function, or JUCE asserts (see the comment in the file).

## GUI rules
* No symbols outside Latin-1 in GUI text (no emoji, no ☀ ☾ ⚠ → etc.): some Windows fonts
  do not have them, and JUCE then shows a box or shortens the text to "...". Draw icons as a
  `juce::Path` instead (example: `drawThemeIcon()` in StereoWidener's PluginLookAndFeel.cpp,
  https://github.com/JoergBitzer/stereo_widening). The degree sign ° is fine.
* The Save button of the preset handler turns red after a user change. This works through
  parameter gestures, so connect your controls with the JUCE attachments
  (SliderAttachment, ButtonAttachment, ComboBoxAttachment) or `juce::ParameterAttachment`.

## Example to use the template

### Gain plugin (of course) 
[source code at](https://github.com/JoergBitzer/AAT_GainExample). I would use it only as a backup, if something goes wrong.

1. Think about a name: Here, GainPlugin

2. Apply Usage
for the 4th step: sed -i 's/YourPluginName/GainPlugin/g' *.*
for MacOS, see (https://stackoverflow.com/questions/4247068/sed-command-with-i-option-failing-on-mac-but-works-on-linux)
for Windows: (https://stackoverflow.com/questions/17144355/how-can-i-replace-every-occurrence-of-a-string-in-a-file-with-powershell) 
```console    
  Get-ChildItem '*.*' -Recurse | ForEach {
      (Get-Content $_ | ForEach  { $_ -replace 'YourPluginName', 'YourNewProjectName' }) |
      Set-Content $_ }
```    
or use the tools given by visual studio code (Crtl + Shift + H (replace in files)) and use your new diretory./YOUR_PLuggIn_Folder as a filter in "files to include".

for the 5th step: rename 's/YourPluginName/GainPlugin/' *.* or by hand (just 2 files)

for the 7th step switch off PresetHandlerGUI (for a simple gain not necessary) 

3. Change the size in PluginSettings.h to something useful for a gain plugin 
```cpp
const int g_minGuiSize_x(200);
const int g_maxGuiSize_x(500);
const int g_minGuiSize_y(400);
```

4. 
In GainPLugin.h add the parameter definition (delete the example)
```cpp
const struct
{
	const std::string ID = "gain";
	const std::string name = "Gain";
	const std::string unitName = "dB";
	const float minValue = -80.f;
	const float maxValue = 20.f;
	const float defaultValue = 0.f;
}g_paramGain;

```
5. Add the support for a smoothed parameter
```cpp
private:
    float m_gain = 1.f;
    std::atomic<float>* m_gainParam = nullptr; 
    float m_gainParamOld = std::numeric_limits<float>::min(); //smallest possible number, will change in the first block
    juce::SmoothedValue<float,juce::ValueSmoothingTypes::Multiplicative> m_smoothedGain;

```

6. change addParameter (delete the example code)
```cpp
    paramVector.push_back(std::make_unique<juce::AudioParameterFloat>(g_paramGain.ID,            // parameterID
                                                        g_paramGain.name,            // parameter name
                                                        g_paramGain.minValue,              // minimum value
                                                        g_paramGain.maxValue,              // maximum value
                                                        g_paramGain.defaultValue));
```
7. change prepareParameter (delete the ignore method)
```cpp
    m_gainParam = vts->getRawParameterValue(g_paramGain.ID);
```


7. change the smoothing time for the SmoothedValues in prepareToPlay
```cpp
    // here your code
    m_smoothedGain.reset(sampleRate,0.02); // 20ms is enough for a smooth gain, 
```

8. Change the processSynchronBlock method (delete ignore method)
```cpp
    // check parameter update
    if (*m_gainParam != m_gainParamOld)
    {
        m_gainParamOld = *m_gainParam;
        m_gain = powf(10.f,m_gainParamOld/20.f);
    }

    int NrOfSamples = buffer.getNumSamples();
    int chns = buffer.getNumChannels();

    //m_smoothedGain.setTargetValue(m_gain);
    m_smoothedGain.setTargetValue(m_gain);
    float curGain;
    for (int channel = 0; channel < chns; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);
        // ..do something to the data...
        for (int kk = 0; kk < NrOfSamples; ++kk)
        {
            if (channel == 0)
                curGain = m_smoothedGain.getNextValue();
            channelData[kk] *= curGain;
        }
    }
```

9. Component adjustment (add one slider)

In the header add the necessary variables it should read like this
```cpp
private:
    AudioProcessorValueTreeState& m_apvts; 
    juce::Slider m_GainSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> m_GainAttachment;
```

In the cpp file change the constructor
```cpp
    m_GainSlider.setRange (g_paramGain.minValue, g_paramGain.maxValue);         
    m_GainSlider.setTextValueSuffix (g_paramGain.unitName);    
    m_GainSlider.setSliderStyle(juce::Slider::LinearVertical);
    m_GainSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxAbove, true, 60, 20);
    m_GainSlider.setValue(g_paramGain.defaultValue);
	m_GainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, g_paramGain.ID, m_GainSlider);
	addAndMakeVisible(m_GainSlider);
```
and the setbounds method
```cpp
	auto r = getLocalBounds();
	m_GainSlider.setBounds(r);
```

10. compile and you have your gain plugin

Some remarks
For most parameter it is better to use small synchron blocks (e.g. 2ms) and smooth the update. If you need smoothing on a sample base (like for gains) use applyRamp from the buffer (it is linear, but faster compared to a sample-based smoothing). 

(a german video exist to build Gain PLugins)

## Second Example EQ (Peak, one band)

The description of this example is very short. You will find the source code on Github (AAT_EQ1)

1. Solve your math first. You will find the formulas for Equalizer by searching for the "RBJ cookbook".
2. Understand what a second order section filter is. (LTI System, with 3 transversal (b0,b1,b2) and 2 recursive coefficients (a1,a2))
3. Build the audio class (3 parameter (Gain, Freq, Q))
4. Build the GUI (3 rotary knobs)
5. Done

### Remarks
For a general solution with more possibilities for Equalizer (cut, shelf), use the given TGMLib / TGMStaticLib


