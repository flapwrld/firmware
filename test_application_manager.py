#!/usr/bin/env python3
"""
Unit tests for the ApplicationManager class
"""

import sys
import os
import pytest

# Add the src directory to the path so we can import the ApplicationManager class
sys.path.insert(0, os.path.join(os.path.dirname(__file__), 'src'))

from core.ApplicationManager import ApplicationManager

def test_application_manager_initialization():
    """Test that the ApplicationManager class initializes correctly"""
    app_manager = ApplicationManager()
    assert app_manager is not None

def test_application_manager_get_application_count():
    """Test that the ApplicationManager returns correct application count"""
    app_manager = ApplicationManager()
    # Initially there should be no applications registered
    assert app_manager.getApplicationCount() == 0

def test_application_manager_get_current_application():
    """Test that the ApplicationManager returns None for current application when none is set"""
    app_manager = ApplicationManager()
    # Initially there should be no current application
    assert app_manager.getCurrentApplication() is None

# Note: Testing other methods would require mocking the Display and Navigation classes
# which is beyond the scope of this simple test file

if __name__ == "__main__":
    pytest.main([__file__])