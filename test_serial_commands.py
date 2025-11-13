#!/usr/bin/env python3
"""
Test script for serial commands
This script demonstrates how to send serial commands to the ESP device
"""

import serial
import time
import serial.tools.list_ports

def list_serial_ports():
    """List available serial ports"""
    ports = [port.device for port in serial.tools.list_ports.comports()]
    print("Available serial ports:")
    for i, port in enumerate(ports):
        print(f"  {i+1}. {port}")
    return ports

def test_serial_commands(port, baudrate=115200):
    """Test sending serial commands to the ESP device"""
    try:
        # Open serial connection
        ser = serial.Serial(port, baudrate, timeout=1)
        print(f"Connected to {port} at {baudrate} baud")
        
        # Wait for connection to establish
        time.sleep(2)
        
        # List of commands to test
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
        
        print("Testing serial commands...")
        print("Press Ctrl+C to stop")
        
        # Send each command with a delay
        for command in commands:
            print(f"Sending: {command}")
            ser.write(f"{command}\n".encode('utf-8'))
            time.sleep(1)  # Wait 1 second between commands
            
        # Continuous loop for manual testing
        print("\nEntering manual mode. Type commands or 'quit' to exit:")
        while True:
            user_input = input("> ").strip().upper()
            if user_input == 'QUIT':
                break
            elif user_input in commands:
                print(f"Sending: {user_input}")
                ser.write(f"{user_input}\n".encode('utf-8'))
            else:
                print(f"Unknown command. Supported: {', '.join(commands)}")
                
    except KeyboardInterrupt:
        print("\nTest interrupted by user")
    except Exception as e:
        print(f"Error: {e}")
    finally:
        if 'ser' in locals() and ser.is_open:
            ser.close()
            print("Serial connection closed")

def main():
    """Main function"""
    print("ESP Device Serial Command Test")
    print("=" * 30)
    
    # List available ports
    ports = list_serial_ports()
    
    if not ports:
        print("No serial ports found!")
        return
    
    # Get port selection from user
    try:
        choice = int(input(f"\nSelect port (1-{len(ports)}): ")) - 1
        if 0 <= choice < len(ports):
            selected_port = ports[choice]
            test_serial_commands(selected_port)
        else:
            print("Invalid selection!")
    except ValueError:
        print("Invalid input!")

if __name__ == "__main__":
    main()