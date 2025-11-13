#!/usr/bin/env python3
"""
Unit tests for the SerialCommandParser class
"""

import sys
import os
import pytest

# Add the src directory to the path so we can import the SerialCommandParser
sys.path.insert(0, os.path.join(os.path.dirname(__file__), 'src'))

from utils.SerialCommandParser import SerialCommandParser

def test_serial_command_parser_initialization():
    """Test that the SerialCommandParser initializes correctly"""
    parser = SerialCommandParser()
    assert parser is not None

def test_serial_command_parser_initialize():
    """Test that the SerialCommandParser initialize method works"""
    parser = SerialCommandParser()
    parser.initialize()
    # No exception should be raised

def test_serial_command_parser_is_command_available():
    """Test that the SerialCommandParser isCommandAvailable method works"""
    parser = SerialCommandParser()
    # Since we're not actually connecting to a serial port, this should return False
    assert parser.isCommandAvailable() == False

# Note: Testing the parseCommand method would require mocking the Serial class
# which is beyond the scope of this simple test file

if __name__ == "__main__":
    pytest.main([__file__])