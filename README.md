# ARA-IO Plugin

## Overview
This is an Audio Random Access (ARA) plugin built using the JUCE framework. The plugin enables DAWs (Digital Audio Workstations) that support ARA to access and process audio content in more sophisticated ways than traditional VST/AU plugins.

## Current Features
- **Time Range Analysis**: The plugin can access and process audio content based on playback regions in your DAW
- **Region-Based Processing**: Ability to read start and end times from playback regions
- **ARA Integration**: Full ARA host integration for enhanced audio analysis capabilities
- **Comprehensive Testing**: Built-in unit testing infrastructure for robust code quality

## Supported Formats
- VST3
- Audio Unit (AU)
- Standalone Plugin (with integrated unit tests)

## Technical Requirements
- Compatible DAW with ARA support (like Logic Pro, PreSonus Studio One)
- macOS operating system (x86_64 or arm64)
- ARA SDK
- JUCE framework (version 8.x)
- Xcode for building

## Build Instructions
1. Open the Xcode project
2. Select desired build scheme:
   - ARA-IO - All
   - ARA-IO - VST3
   - ARA-IO - AU
   - ARA-IO - Standalone Plugin
3. Build the project using Xcode

## Testing
The plugin includes a comprehensive unit testing infrastructure:

### Running Tests
1. Build and run the Standalone Plugin target
2. Tests will automatically execute on startup
3. Results are displayed in the console
4. The application will exit with status code 0 if all tests pass, or 1 if any tests fail

### Test Implementation
- Tests are implemented using JUCE's built-in UnitTest framework
- Test files are located in the `/Tests` directory
- Main test runner is in `TestRunner.cpp`
- Plugin-specific tests are in `PluginTests.cpp`

### Adding New Tests
1. Create a new test class inheriting from `juce::UnitTest`
2. Implement the `runTest()` method
3. Use `beginTest()` to start a test section
4. Use `expect()` for assertions
5. Create a static instance of your test class

Example:
```cpp
class MyPluginTest : public juce::UnitTest
{
public:
    MyPluginTest() : UnitTest("My Plugin Tests") {}
    
    void runTest() override
    {
        beginTest("Feature Test");
        expect(myFeature.doesWork());
    }
};

static MyPluginTest test;
```

## Current Status
- Core ARA functionality implemented
- Comprehensive unit testing infrastructure in place
- Cross-platform support for macOS (x86_64, arm64)
- All unit tests passing
- Active development ongoing

## Development Notes
- The plugin uses JUCE's native array handling methods
- Implements proper null checking for ARA objects
- Handles playback region time information through ARA's dedicated methods
- Uses modern C++17 features
- Follows defensive programming practices
- Includes comprehensive unit testing

### Key Files
- `PluginProcessor.cpp`: Main processing logic
- `PluginARADocumentController.cpp`: ARA document handling
- `PluginARAPlaybackRenderer.cpp`: ARA playback rendering
- `Tests/TestRunner.cpp`: Unit test infrastructure
- `Tests/PluginTests.cpp`: Plugin-specific tests

## Contributing
1. Fork the repository
2. Create a feature branch
3. Add appropriate unit tests for new features
4. Ensure all tests pass
5. Submit a pull request

For developers interested in contributing or understanding the codebase, start with the test files to understand the expected behavior of each component.
