#include <JuceHeader.h>

// This is the main entry point for the test runner
int main (int argc, char* argv[])
{
    // Initialize the test environment
    juce::UnitTestRunner testRunner;
    
    // Run all registered tests
    testRunner.runAllTests();
    
    // Return 0 if all tests passed, or a non-zero value if any tests failed
    return testRunner.getNumResults() > 0 && testRunner.getResult(testRunner.getNumResults() - 1)->failures > 0 ? 1 : 0;
}
