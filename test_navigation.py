#!/usr/bin/env python3
"""
Unit tests for the Navigation class
"""

import sys
import os
import pytest

# Add the src directory to the path so we can import the Navigation class
sys.path.insert(0, os.path.join(os.path.dirname(__file__), 'src'))

from core.Navigation import Navigation, NavigationEvent

def test_navigation_initialization():
    """Test that the Navigation class initializes correctly"""
    # Create mock buttons array
    mock_buttons = [None] * 7  # 7 buttons
    
    navigation = Navigation(mock_buttons)
    assert navigation is not None

def test_navigation_set_external_event():
    """Test that the Navigation class can set external events"""
    # Create mock buttons array
    mock_buttons = [None] * 7  # 7 buttons
    
    navigation = Navigation(mock_buttons)
    navigation.setExternalEvent(NavigationEvent.NAV_UP)
    
    # Check that the external event was set
    assert navigation.getExternalEvent() == NavigationEvent.NAV_UP

def test_navigation_clear_external_event():
    """Test that the Navigation class can clear external events"""
    # Create mock buttons array
    mock_buttons = [None] * 7  # 7 buttons
    
    navigation = Navigation(mock_buttons)
    navigation.setExternalEvent(NavigationEvent.NAV_UP)
    navigation.clearExternalEvent()
    
    # Check that the external event was cleared
    assert navigation.getExternalEvent() == NavigationEvent.NAV_NONE

# Note: Testing the getEvent method would require mocking the Button class
# which is beyond the scope of this simple test file

if __name__ == "__main__":
    pytest.main([__file__])