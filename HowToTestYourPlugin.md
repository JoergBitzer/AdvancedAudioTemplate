# How to test your plugin

A plugin that works on your computer in your DAW can still crash in another DAW, at another
sample rate, or when the user moves a knob while the audio is running. Testing early saves you
from bug reports later. Start with these three steps; they need no extra knowledge.

## 1. Build and test the Debug version

While you develop, build the Debug version. It is slower, but JUCE checks many things there:
every `jassert(...)` in JUCE and in your code stops the program (in the debugger) or prints
"JUCE Assertion failure" if a condition is wrong. An assertion is always a hint to a real problem --
do not ignore it. Build the Release version for your users; it is faster and has no assertions.

## 2. Test with pluginval before every commit

[pluginval](https://github.com/Tracktion/pluginval) loads your plugin like a DAW and tests it hard:
parameters, automation, different sample rates and block sizes, opening and closing the editor, and
more. It finds bugs that you would otherwise only notice in a DAW, or that your users would find.

Linux/macOS:
```console
tools/run_pluginval.sh path/to/YourPluginName.vst3
```
Windows (PowerShell):
```console
powershell -ExecutionPolicy Bypass -File tools\run_pluginval.ps1 path\to\YourPluginName.vst3
```
In AudioDev the plugin is in `build/YourPluginName/YourPluginName_artefacts/Debug/VST3/`.

The script downloads pluginval on the first run, tests at the highest strictness level (10) three times
(some bugs only show up now and then; give another number as second argument) and prints SUCCESS or
FAILED per run, with the path to the log of a failed run. On Linux/macOS the script also counts every
JUCE assertion as a failure, and it uses a temporary home folder, so your real presets are not touched.

If a run fails, open the log and search for "FAILED" or "JUCE Assertion": the lines before it show
which test was running. Fix the problem and test again, until all runs pass.

## 3. Test in a DAW (and in JUCE's AudioPluginHost)

Automatic tests do not replace your ears and hands. Load the plugin in your DAW and:
* play audio through it and listen: clicks, dropouts, level jumps?
* move every control while the audio is running, also fast
* automate a parameter, save the project, close and open it again: is everything restored?
* load and save presets, switch between them
* close and open the plugin window, resize it
* use two instances of the plugin at the same time

No DAW at hand? JUCE comes with a simple host: build `JUCE/extras/AudioPluginHost`, then
"Options > Edit the list of available plug-ins" to scan your plugin. The Standalone version of your
plugin (built with the VST3) is also a quick way to test the GUI and the sound.
