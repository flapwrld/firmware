#!/usr/bin/env python3
"""
pytest configuration file
"""

import sys
import os

# Add the src directory to the path so we can import the modules
sys.path.insert(0, os.path.join(os.path.dirname(__file__), 'src'))

# Add any pytest configuration here
def pytest_configure(config):
    """Configure pytest"""
    config.addinivalue_line(
        "markers", "serial: mark test as requiring serial communication"
    )
    config.addinivalue_line(
        "markers", "integration: mark test as integration test"
    )
    config.addinivalue_line(
        "markers", "unit: mark test as unit test"
    )