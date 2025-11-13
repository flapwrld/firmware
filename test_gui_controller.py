#!/usr/bin/env python3
"""
Test script for the ESP Controller GUI
This script creates a mock serial device for testing the GUI controller
"""

import tkinter as tk
from tkinter import ttk
import threading
import time
import serial
import serial.tools.list_ports
import sys
import os

class MockSerialDevice:
    """Mock serial device for testing the GUI controller"""
    
    def __init__(self, port_name="TEST_PORT", baudrate=115200):
        self.port_name = port_name
        self.baudrate = baudrate
        self.is_open = False
        self.received_commands = []
        self.running = False
        self.thread = None
        self.display_data_requested = False
        
    def open(self):
        """Open the mock serial connection"""
        self.is_open = True
        self.running = True
        self.thread = threading.Thread(target=self._process_commands)
        self.thread.daemon = True
        self.thread.start()
        print(f"Mock serial device opened on {self.port_name}")
        
    def close(self):
        """Close the mock serial connection"""
        self.running = False
        self.is_open = False
        if self.thread:
            self.thread.join()
        print("Mock serial device closed")
        
    def write(self, data):
        """Write data to the mock serial device"""
        if self.is_open and self.running:
            command = data.decode('utf-8').strip()
            self.received_commands.append(command)
            print(f"Received command: {command}")
            
            # Check if this is a display data request
            if command == "GET_DISPLAY":
                self.display_data_requested = True
                
            return len(data)
        return 0
        
    def in_waiting(self):
        """Return number of bytes available to read"""
        # If display data was requested, return 1024 bytes (size of display data)
        if self.display_data_requested:
            return 1024
        return 0
        
    def read(self, size=1):
        """Read data from the mock serial device"""
        # If display data was requested, return mock display data
        if self.display_data_requested:
            self.display_data_requested = False
            # Return 1024 bytes of mock display data (128x64 pixels, 1 bit per pixel)
            # For simplicity, we'll create a pattern that shows some active pixels
            display_data = bytearray(1024)
            # Create a simple pattern - activate some pixels
            for i in range(0, 1024, 8):
                display_data[i] = 0xFF  # Set all bits in every 8th byte
            return bytes(display_data)
        return b''
        
    def _process_commands(self):
        """Process commands in a separate thread"""
        while self.running:
            time.sleep(0.1)
            
    @property
    def is_open(self):
        return self._is_open
        
    @is_open.setter
    def is_open(self, value):
        self._is_open = value

def test_gui_controller():
    """Test the GUI controller with a mock serial device"""
    print("Testing ESP Controller GUI with mock serial device")
    print("=" * 50)
    
    # Create mock serial device
    mock_device = MockSerialDevice()
    
    # Temporarily replace the serial.Serial class with our mock
    original_serial = serial.Serial
    serial.Serial = lambda port, baudrate, timeout=None: mock_device
    
    try:
        # Import the GUI controller
        sys.path.append(os.path.dirname(os.path.abspath(__file__)))
        from esp_controller_gui import ESPControllerGUI
        
        # Create root window
        root = tk.Tk()
        root.title("Test ESP Controller GUI")
        
        # Create the GUI controller
        app = ESPControllerGUI(root)
        
        # Simulate connecting to the mock device
        mock_device.open()
        
        # Simulate sending some commands
        def send_test_commands():
            time.sleep(1)  # Wait for GUI to initialize
            print("Sending test commands...")
            
            # Simulate button presses
            app.send_command("UP")
            time.sleep(0.5)
            
            app.send_command("DOWN")
            time.sleep(0.5)
            
            app.send_command("LEFT")
            time.sleep(0.5)
            
            app.send_command("RIGHT")
            time.sleep(0.5)
            
            app.send_command("OK")
            time.sleep(0.5)
            
            app.send_command("BACK")
            time.sleep(0.5)
            
            app.send_command("FUNCTION")
            time.sleep(0.5)
            
            app.send_command("BACK_LONG")
            time.sleep(0.5)
            
            # Test display data request
            print("Requesting display data...")
            app.request_display_update()
            time.sleep(0.5)
            
            print(f"Received commands: {mock_device.received_commands}")
            
            # Close after testing
            root.after(1000, root.destroy)
        
        # Start sending commands in a separate thread
        command_thread = threading.Thread(target=send_test_commands)
        command_thread.daemon = True
        command_thread.start()
        
        # Run the GUI
        root.mainloop()
        
        # Check if all commands were received
        expected_commands = ["UP", "DOWN", "LEFT", "RIGHT", "OK", "BACK", "FUNCTION", "BACK_LONG", "GET_DISPLAY"]
        received_commands = mock_device.received_commands
        
        print("\nTest Results:")
        print("-" * 20)
        if received_commands == expected_commands:
            print("✓ All commands received correctly")
        else:
            print("✗ Command mismatch")
            print(f"Expected: {expected_commands}")
            print(f"Received: {received_commands}")
            
        # Check if display data was requested
        if mock_device.display_data_requested:
            print("✓ Display data request handled")
        else:
            print("✗ Display data request not handled")
            
    except Exception as e:
        print(f"Error during testing: {e}")
    finally:
        # Restore original serial class
        serial.Serial = original_serial
        # Close mock device
        mock_device.close()

if __name__ == "__main__":
    test_gui_controller()