#!/usr/bin/env python3
"""
Test script for verifying serial communication with the ESP device.
This script sends various commands to test the serial interface.
"""

import serial
import serial.tools.list_ports
import time
import sys

def list_ports():
    """List all available serial ports"""
    ports = [port.device for port in serial.tools.list_ports.comports()]
    print("Available ports:")
    for i, port in enumerate(ports):
        print(f"  {i+1}. {port}")
    return ports

def test_serial_connection(port, baudrate=115200):
    """Test serial connection by sending commands"""
    try:
        # Open serial connection
        ser = serial.Serial(port, baudrate, timeout=1)
        print(f"Connected to {port} at {baudrate} baud")
        
        # Wait for connection to establish
        time.sleep(2)
        
        # Flush input
        ser.flushInput()
        
        # Test commands
        commands = [
            "UP",
            "DOWN",
            "LEFT",
            "RIGHT",
            "OK",
            "BACK",
            "FUNCTION",
            "BACK_LONG"
        ]
        
        print("\nSending test commands...")
        for command in commands:
            # Send command with newline
            ser.write(f"{command}\n".encode())
            print(f"Sent: {command}")
            
            # Wait a bit between commands
            time.sleep(1)
        
        # Close connection
        ser.close()
        print("\nTest completed successfully!")
        return True
        
    except Exception as e:
        print(f"Error: {e}")
        return False

def main():
    """Main function"""
    print("ESP Device Serial Test Script")
    print("=" * 30)
    
    # List available ports
    ports = list_ports()
    
    if not ports:
        print("No serial ports found!")
        return
    
    # Get port selection
    try:
        choice = input(f"\nSelect port (1-{len(ports)}, or 'q' to quit): ").strip()
        if choice.lower() == 'q':
            return
            
        port_index = int(choice) - 1
        if port_index < 0 or port_index >= len(ports):
            print("Invalid port selection!")
            return
            
        port = ports[port_index]
        
    except ValueError:
        print("Invalid input!")
        return
    
    # Test the connection
    test_serial_connection(port)

if __name__ == "__main__":
    main()