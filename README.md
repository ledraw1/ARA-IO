# ARA-IO Plugin

## Overview
This is an Audio Random Access (ARA) plugin built using the JUCE framework. The plugin enables DAWs (Digital Audio Workstations) that support ARA to access and process audio content in more sophisticated ways than traditional VST/AU plugins.

## Current Features
- **Time Range Analysis**: The plugin can access and process audio content based on playback regions in your DAW
- **Region-Based Processing**: Ability to read start and end times from playback regions
- **ARA Integration**: Full ARA host integration for enhanced audio analysis capabilities

## Supported Formats
- VST3
- Audio Unit (AU)
- Standalone Plugin

## Technical Requirements
- Compatible DAW with ARA support (like Logic Pro, PreSonus Studio One)
- macOS operating system
- ARA SDK
- JUCE framework

## Build Instructions
1. Open the Xcode project
2. Select desired build scheme:
   - ARA-IO - All
   - ARA-IO - VST3
   - ARA-IO - AU
   - ARA-IO - Standalone Plugin
3. Build the project using Xcode

## Current Status
This plugin is under active development. It currently implements basic ARA functionality with a focus on time range processing and playback region handling.

## Development Notes
- The plugin uses JUCE's native array handling methods
- Implements proper null checking for ARA objects
- Handles playback region time information through ARA's dedicated methods

For developers interested in contributing or understanding the codebase, the main processing logic can be found in `PluginProcessor.cpp`.
