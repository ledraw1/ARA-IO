# ARA-IO Development Plan

This document breaks down the implementation of the ARA Region Context Manager into discrete, testable stories using Behavior-Driven Development (BDD) with Gherkin syntax.

> **Status Legend**:
> - Completed
> - In Progress
> - Not Started
> - Blocked

## Epic 1: Region Discovery and Display 

> **Testing Note**: All test scenarios in this epic should be implemented using the JUCE Unit Test framework (`juce::UnitTest`). Each feature should have its corresponding test class inheriting from `juce::UnitTest`.

### Story 1.1: Basic Region Metadata Fetching 
```gherkin
Feature: Fetch Region Metadata
  As a plugin developer
  I want to fetch metadata for all regions in a track
  So that I can display them in the plugin GUI

  Background:
    Given the plugin is loaded in a DAW
    And the DAW has ARA support enabled

  Scenario: Fetch metadata for a single region
    Given there is one region in the track
    When the plugin queries for available regions
    Then it should receive the region's metadata including:
      | Property    | Type     |
      | Name/ID     | String   |
      | Start Time  | Double   |
      | End Time    | Double   |
      | Audio Source| String   |

  Scenario: Fetch metadata for multiple regions
    Given there are multiple regions in the track
    When the plugin queries for available regions
    Then it should receive metadata for all regions
    And the regions should be ordered by their start time

  Test Implementation:
    * Create RegionMetadataTest class inheriting from juce::UnitTest
    * Test metadata fetching for single and multiple regions
    * Verify metadata accuracy and ordering
```

#### Progress:
- Initial JUCE project setup completed
- ARA SDK integration completed
- Basic plugin build pipeline established
- VST3 and AU plugins building successfully
- Plugins installing to correct system locations

#### Remaining Work (Sub-stories):

##### Story 1.1.1: ARA Host Integration 
```gherkin
Feature: ARA Host Integration
  As a plugin
  I want to properly integrate with the ARA host
  So that I can access region data

  Scenario: Initialize ARA integration
    Given the plugin is loaded in an ARA-compatible host
    When the host initializes the plugin
    Then the plugin should register its ARA factory successfully
    And establish communication with the host

  Test Implementation:
    * Create ARAHostIntegrationTest class inheriting from juce::UnitTest
    * Mock ARA host interface for testing
    * Verify ARA factory registration
    * Test host-plugin communication initialization
```

##### Story 1.1.2: Region Data Structure Implementation 
```gherkin
Feature: Region Data Structure
  As a plugin developer
  I want to implement the region data structures
  So that I can store and manage region metadata efficiently

  Scenario: Create region data structure
    Given the need to store region metadata
    When implementing the data structure
    Then it should include all required fields
    And provide efficient access methods

  Test Implementation:
    * Create RegionDataStructureTest class inheriting from juce::UnitTest
    * Test data structure field access and modification
    * Verify memory management and efficiency
    * Test edge cases (empty regions, invalid data)
```

##### Story 1.1.3: Region Query Implementation 
> Blocked on: Story 1.1.1 (ARA Host Integration)
```gherkin
Feature: Region Query Implementation
  As a plugin
  I want to query region information from the host
  So that I can access region metadata

  Scenario: Query region metadata
    Given an ARA host connection
    When the plugin requests region information
    Then it should receive all available region metadata
    And parse it into the internal data structure

  Test Implementation:
    * Create RegionQueryTest class inheriting from juce::UnitTest
    * Mock host responses for region queries
    * Test metadata parsing accuracy
    * Verify error handling for failed queries
```

##### Story 1.1.4: Region Update Handling 
> Blocked on: Story 1.1.2 (Region Data Structure Implementation)
```gherkin
Feature: Region Update Handling
  As a plugin
  I want to handle region updates from the host
  So that I can maintain current region information

  Scenario: Handle region updates
    Given the plugin is monitoring region changes
    When the host sends a region update
    Then the plugin should update its internal data
    And prepare the data for GUI display

  Test Implementation:
    * Create RegionUpdateHandlingTest class inheriting from juce::UnitTest
    * Test update event handling
    * Verify data consistency after updates
    * Test concurrent update handling
```

### Story 1.2: Region List Display 
> Blocked on: Story 1.1 (Basic Region Metadata Fetching)
```gherkin
Feature: Display Region List
  As a user
  I want to see a list of all regions in my track
  So that I can understand their organization

  Background:
    Given the plugin is loaded in a DAW
    And there are regions in the track

  Scenario: Display region list in GUI
    When the plugin window is opened
    Then I should see a table containing all regions
    And each row should display:
      | Column      | Description          |
      | Name/ID     | Region identifier    |
      | Start Time  | In bars/beats        |
      | End Time    | In bars/beats        |
      | Controller  | Current controller   |

  Scenario: Update display when regions change
    When a new region is added to the track
    Then the table should update automatically
    And the new region should appear in the list

  Test Implementation:
    * Create RegionListDisplayTest class inheriting from juce::UnitTest
    * Test region list display and updates
    * Verify GUI accuracy and responsiveness
```

## Epic 2: Region Control Management 
> Blocked on: Epic 1 (Region Discovery and Display)

### Story 2.1: Query Region Control State 
```gherkin
Feature: Query Region Control State
  As a plugin
  I want to know who controls each region
  So that I can display accurate control information

  Scenario: Query control state of uncontrolled region
    Given a region exists in the track
    And no plugin has control of the region
    When I query the region's control state
    Then it should indicate the DAW is in control

  Scenario: Query control state of controlled region
    Given a region exists in the track
    And another plugin has control of the region
    When I query the region's control state
    Then it should indicate which plugin has control

  Test Implementation:
    * Create RegionControlStateTest class inheriting from juce::UnitTest
    * Test control state queries for uncontrolled and controlled regions
    * Verify accuracy of control state information
```

### Story 2.2: Request Region Control 
```gherkin
Feature: Request Region Control
  As a user
  I want to request control over regions
  So that I can manage their playback

  Scenario: Successfully request control
    Given a region is not controlled by any plugin
    When I click the "Request Control" button for that region
    Then the plugin should gain control of the region
    And the GUI should update to show my plugin as controller

  Scenario: Failed control request
    Given a region is controlled by another plugin
    When I click the "Request Control" button for that region
    Then the request should fail gracefully
    And the GUI should display an error message

  Test Implementation:
    * Create RegionControlRequestTest class inheriting from juce::UnitTest
    * Test successful and failed control requests
    * Verify GUI updates and error handling
```

### Story 2.3: Release Region Control 
```gherkin
Feature: Release Region Control
  As a user
  I want to release control of regions
  So that other plugins can control them

  Scenario: Release controlled region
    Given a region is controlled by my plugin
    When I click the "Release Control" button
    Then the plugin should release control
    And the GUI should update to show DAW as controller

  Scenario: Release uncontrolled region
    Given a region is not controlled by my plugin
    When I click the "Release Control" button
    Then nothing should happen
    And the GUI should not change

  Test Implementation:
    * Create RegionControlReleaseTest class inheriting from juce::UnitTest
    * Test releasing controlled and uncontrolled regions
    * Verify GUI updates and control state changes
```

## Epic 3: Dynamic Updates and State Management 
> Blocked on: Epic 2 (Region Control Management)

### Story 3.1: Region Change Notifications 
```gherkin
Feature: Region Change Notifications
  As a plugin
  I want to receive notifications about region changes
  So that I can keep the GUI in sync

  Scenario: New region added
    When a new region is added to the track
    Then the plugin should receive a notification
    And update the GUI with the new region

  Scenario: Region removed
    When a region is removed from the track
    Then the plugin should receive a notification
    And remove that region from the GUI

  Scenario: Region modified
    When a region's properties are changed
    Then the plugin should receive a notification
    And update the GUI with the new properties

  Test Implementation:
    * Create RegionChangeNotificationTest class inheriting from juce::UnitTest
    * Test notification handling for region additions, removals, and modifications
    * Verify GUI updates and accuracy
```

### Story 3.2: Control State Change Notifications 
```gherkin
Feature: Control State Change Notifications
  As a plugin
  I want to receive notifications about control state changes
  So that I can keep the GUI in sync

  Scenario: Another plugin takes control
    Given my plugin is displaying a region's state
    When another plugin takes control of the region
    Then my plugin should receive a notification
    And update the GUI to show the new controller

  Scenario: Plugin releases control
    Given my plugin is displaying a region's state
    When the controlling plugin releases control
    Then my plugin should receive a notification
    And update the GUI to show DAW control

  Test Implementation:
    * Create ControlStateChangeNotificationTest class inheriting from juce::UnitTest
    * Test notification handling for control state changes
    * Verify GUI updates and accuracy
```

## Implementation Notes

### Testing Strategy
1. Create mock ARA host for unit testing
2. Use JUCE's unit testing framework
3. Implement test doubles for:
   - ARA Playback Regions
   - ARA Model Update Controller
   - ARA Host Model
4. Test GUI components using JUCE's component testing utilities

### Dependencies
- JUCE Framework (Version 8)
- ARA SDK (Version 2.2.0)
- C++17 or later
- Unit Testing Framework: JUCE's built-in framework

### Development Order
1. Implement core ARA integration (Epic 1)
2. Build basic GUI components (Story 1.2)
3. Add control management features (Epic 2)
4. Implement dynamic updates (Epic 3)
5. Add comprehensive error handling
6. Polish GUI and user experience
