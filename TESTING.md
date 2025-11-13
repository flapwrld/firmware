# Testing Plan

## Initial Display Test
1. Power on the device
2. Verify the startup screen with "HAKLESMY" logo displays correctly
3. Press OK button to proceed to main menu

## Menu Navigation Test
1. Verify carousel-style menu displays correctly with all applications
2. Test navigation using UP/DOWN buttons
3. Verify selected item is highlighted
4. Test OK button to launch applications
5. Test BACK button to return to menu

## Application Tests

### DOOM Application
1. Launch DOOM from menu
2. Verify 3D view renders correctly
3. Test movement controls (UP/DOWN)
4. Test turning controls (LEFT/RIGHT)
5. Verify HUD displays correctly
6. Test menu access with UP button
7. Test BACK button to return to 3D view
8. Test BACK button to return to main menu

### WiFi Scanner
1. Launch WiFi Scanner from menu
2. Verify scanning interface displays
3. Check that available networks are listed
4. Test network selection
5. Verify connection simulation works
6. Test BACK button functionality

### Explorer
1. Launch Explorer from menu
2. Verify SD card root directory displays
3. Test navigation through directories
4. Test file selection
5. Verify file content display
6. Test BACK button functionality

### Tamagotchi
1. Launch Tamagotchi from menu
2. Verify pet display
3. Test feeding functionality
4. Test playing functionality
5. Test cleaning functionality
6. Verify status changes
7. Test BACK button functionality

### Stopwatch
1. Launch Stopwatch from menu
2. Verify initial display (00:00:00)
3. Test START/STOP functionality
4. Test LAP functionality
5. Test RESET functionality
6. Test BACK button functionality

### Calculator
1. Launch Calculator from menu
2. Test basic operations (+, -, *, /)
3. Verify display updates correctly
4. Test multi-digit numbers
5. Test decimal point functionality
6. Test CLEAR button
7. Test BACK button functionality

## Bitmap Verification
1. Verify all application icons display correctly in menu
2. Check DOOM icon (skull)
3. Check WiFi icon
4. Check file/folder icons
5. Check settings icon
6. Check Tamagotchi icon
7. Check Stopwatch icon
8. Check Calculator icon

## Button Response Test
1. Verify all buttons respond correctly
2. UP - Navigation/Menu access
3. DOWN - Navigation
4. LEFT - Turn left (DOOM)
5. RIGHT - Turn right (DOOM)
6. OK - Select/Confirm
7. BACK - Return/Cancel

## Display Quality Test
1. Verify all text is visible and readable
2. Check contrast of bitmaps
3. Verify no display artifacts
4. Check refresh rate during animations

## Serial Communication Test

### Manual Testing
1. Connect the device to a computer via USB
2. Open a serial monitor (115200 baud rate)
3. Send each supported command followed by a newline:
   - `UP`
   - `DOWN`
   - `LEFT`
   - `RIGHT`
   - `OK`
   - `BACK`
   - `FUNCTION`
   - `BACK_LONG`
4. Verify that each command is received and processed correctly
5. Check that the device responds as if the corresponding button was pressed
6. Verify that the device sends an "OK" response for valid commands
7. Verify that the device sends an "ERROR" response for invalid commands

### Command-Line Interface Testing
1. Run the command-line test script: `python test_serial_commands.py`
2. Select the appropriate serial port
3. Verify that all commands are sent successfully
4. Check that the device responds correctly to each command
5. Test sending invalid commands and verify error responses

### Unit Testing
1. Run the serial command parser unit tests: `python test_serial_command_parser.py`
2. Verify that all test cases pass:
   - Valid command parsing
   - Invalid command handling
   - Case sensitivity
   - Whitespace handling
3. Run the navigation system unit tests: `python test_navigation.py`
4. Verify that external event handling works correctly
5. Run the application manager unit tests: `python test_application_manager.py`
6. Verify that serial command processing works correctly

### ESP Controller Application Test
1. Run the controller application: `python esp_controller_gui.py`
2. Select the appropriate serial port
3. Connect to the device
4. Test each button in the GUI
5. Verify that keyboard shortcuts work correctly
6. Check that status updates are displayed correctly
7. Test the connection indicator (red/green circle)
8. Verify automatic port detection works correctly

### GUI Controller Unit Testing
1. Run the GUI controller unit tests: `python test_gui_controller.py`
2. Verify that all test cases pass:
   - Button click handling
   - Keyboard shortcut handling
   - Serial communication with mock device
   - Connection management
   - UI updates

### Pytest Suite
1. Run the complete test suite: `python -m pytest`
2. Verify that all tests pass:
   - Serial command parser tests
   - Navigation system tests
   - Application manager tests
   - GUI controller tests
3. Check test coverage reports if available

For detailed information about the serial command protocol, see [SERIAL_COMMANDS.md](SERIAL_COMMANDS.md).