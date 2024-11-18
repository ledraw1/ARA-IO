#!/bin/bash

# Default values
CLEAN=true
CONFIG="Debug"
RUN_TESTS=false  # Changed default to false since plugins can't be executed directly

# Parse command line arguments
while [[ $# -gt 0 ]]; do
    case $1 in
        --no-clean)
            CLEAN=false
            shift
            ;;
        --release)
            CONFIG="Release"
            shift
            ;;
        --run-tests)  # Changed from --no-tests to --run-tests since default is now false
            RUN_TESTS=true
            shift
            ;;
        -h|--help)
            echo "Usage: $0 [options]"
            echo "Options:"
            echo "  --no-clean    Skip clean build (default: clean build)"
            echo "  --release     Build release configuration (default: debug)"
            echo "  --run-tests   Run tests if available (default: skip tests)"
            echo "  -h, --help    Show this help message"
            exit 0
            ;;
        *)
            echo "Unknown option: $1"
            exit 1
            ;;
    esac
done

# Project paths
PROJECT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
XCODE_PROJECT="$PROJECT_DIR/Builds/MacOSX/ARA-IO.xcodeproj"
SCHEME="ARA-IO - All"

# Build command construction
BUILD_CMD=(xcodebuild -project "$XCODE_PROJECT" -scheme "$SCHEME" -configuration "$CONFIG")

# Clean if requested
if [ "$CLEAN" = true ]; then
    echo "Cleaning build..."
    "${BUILD_CMD[@]}" clean
fi

# Build
echo "Building $CONFIG configuration..."
"${BUILD_CMD[@]}" build

BUILD_RESULT=$?
if [ $BUILD_RESULT -ne 0 ]; then
    echo "Build failed with exit code $BUILD_RESULT"
    exit $BUILD_RESULT
fi

# Run tests if requested and available
if [ "$RUN_TESTS" = true ]; then
    echo "Note: Tests are currently not supported for VST3/AU plugins as they require a host application."
    echo "To test the plugin, please load it in a compatible DAW or plugin host application."
fi

echo "Build completed successfully!"
