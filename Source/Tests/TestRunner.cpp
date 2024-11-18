#include <juce_core/juce_core.h>

// This is called by JUCE to run the unit tests
int runUnitTests()
{
    // Run all registered unit tests
    juce::UnitTestRunner testRunner;
    testRunner.runAllTests();

    // Return 0 if all tests passed, 1 if any failed
    return testRunner.getNumFailures();
}
