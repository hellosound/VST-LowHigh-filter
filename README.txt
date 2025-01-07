LowPassHighPass Audio Plugin

Overview

The LowPassHighPass Audio Plugin is a JUCE-based audio plugin that provides users with basic filtering capabilities. 
This plugin features a cutoff frequency slider and a high-pass toggle button to manipulate audio signals in real-time.
It supports both low-pass and high-pass filter modes.
---------------------------------------------------------------------------------------------

Features

Cutoff Frequency Control: Adjust the filter's cutoff frequency between 20 Hz and 20,000 Hz.

High-Pass Toggle: Switch between low-pass and high-pass filter modes.

GUI: Simple and intuitive user interface.

Host Compatibility: Designed to work with most modern DAWs that support VST3 or AU plugins.

---------------------------------------------------------------------------------------------
Installation

Clone or download the repository.
Open the project in your IDE (e.g., Visual Studio, Xcode) using the Projucer file.
Build the project for your target platform (Windows, macOS, etc.).
Copy the generated plugin file (.vst3, .component, etc.) to your DAW's plugin folder.
Rescan plugins in your DAW.

---------------------------------------------------------------------------------------------

Usage

Load the plugin in your DAW.
Adjust the Cutoff Frequency Slider to set the desired cutoff frequency.
Toggle the High-Pass Button to switch between high-pass and low-pass filtering.
Listen to the processed audio output in real-time.
---------------------------------------------------------------------------------------------

Parameters

1. Cutoff Frequency
ID: cutoff_frequency
Range: 20 Hz - 20,000 Hz
Default Value: 500 Hz

2. High-Pass Toggle
ID: highpass
Type: Boolean (On/Off)
Default Value: Off (Low-Pass mode)
---------------------------------------------------------------------------------------------

Development
Requirements
JUCE Framework
C++17 or later
Supported IDE (Visual Studio, Xcode, etc.)
---------------------------------------------------------------------------------------------

File Structure

PluginProcessor.cpp: Contains the audio processing logic.
PluginEditor.cpp: Manages the graphical user interface.
PluginProcessor.h / PluginEditor.h: Header files for the processor and editor classes.
---------------------------------------------------------------------------------------------

Building the Project

Open LowPassHighPass.jucer in Projucer.
Configure your export targets (VST3, AU, etc.).
Save the project and open it in your IDE.
Build and compile.
---------------------------------------------------------------------------------------------
Known Issues

GUI layout may appear misaligned in some hosts with unusual scaling settings.
Parameter interpolation might introduce minor audio artifacts during rapid changes.

---------------------------------------------------------------------------------------------
Future Improvements

Add visual representation of the filter's frequency response.
Smooth parameter automation to eliminate audio artifacts.
Expand compatibility for additional plugin formats.
---------------------------------------------------------------------------------------------

License

This project is licensed under the MIT License. See the LICENSE file for details.
---------------------------------------------------------------------------------------------
Acknowledgements

Built using the JUCE Framework.
Inspired by fundamental audio filtering techniques.
