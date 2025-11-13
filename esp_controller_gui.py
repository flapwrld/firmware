import tkinter as tk
from tkinter import ttk, messagebox
import serial
import serial.tools.list_ports
import threading
import time

class ESPControllerGUI:
    def __init__(self, root):
        self.root = root
        self.root.title("ESP Device Controller")
        self.root.geometry("500x600")
        self.root.resizable(False, False)
        
        # Serial connection
        self.ser = None
        self.connected = False
        self.display_data = None
        self.display_thread = None
        self.display_thread_running = False
        
        # Display dimensions
        self.display_width = 128
        self.display_height = 64
        
        # Create GUI elements
        self.create_widgets()
        
        # Populate COM ports
        self.populate_com_ports()
        
    def create_widgets(self):
        # Main frame
        main_frame = ttk.Frame(self.root, padding="10")
        main_frame.grid(row=0, column=0, sticky=(tk.W, tk.E, tk.N, tk.S))
        
        # Connection frame
        connection_frame = ttk.LabelFrame(main_frame, text="Serial Connection", padding="10")
        connection_frame.grid(row=0, column=0, columnspan=3, sticky=(tk.W, tk.E), pady=(0, 10))
        
        ttk.Label(connection_frame, text="COM Port:").grid(row=0, column=0, sticky=tk.W)
        self.com_port_var = tk.StringVar()
        self.com_port_combo = ttk.Combobox(connection_frame, textvariable=self.com_port_var, width=15)
        self.com_port_combo.grid(row=0, column=1, padx=(5, 10))
        
        ttk.Label(connection_frame, text="Baud Rate:").grid(row=0, column=2, sticky=tk.W)
        self.baud_rate_var = tk.StringVar(value="115200")
        baud_combo = ttk.Combobox(connection_frame, textvariable=self.baud_rate_var, width=10)
        baud_combo['values'] = ('9600', '19200', '38400', '57600', '115200')
        baud_combo.grid(row=0, column=3, padx=(5, 0))
        
        self.connect_button = ttk.Button(connection_frame, text="Connect", command=self.toggle_connection)
        self.connect_button.grid(row=1, column=0, columnspan=4, pady=(10, 0))
        
        # Status label
        self.status_label = ttk.Label(main_frame, text="Disconnected", foreground="red")
        self.status_label.grid(row=1, column=0, columnspan=3, pady=(0, 10))
        
        # Display frame
        display_frame = ttk.LabelFrame(main_frame, text="Device Display", padding="10")
        display_frame.grid(row=2, column=0, columnspan=3, sticky=(tk.W, tk.E, tk.N, tk.S), pady=(0, 10))
        
        # Create a canvas for the display
        self.display_canvas = tk.Canvas(display_frame, width=self.display_width, height=self.display_height, bg="black")
        self.display_canvas.grid(row=0, column=0, padx=5, pady=5)
        
        # Control buttons frame
        control_frame = ttk.LabelFrame(main_frame, text="Controls", padding="20")
        control_frame.grid(row=3, column=0, columnspan=3, sticky=(tk.W, tk.E, tk.N, tk.S), pady=(0, 10))
        
        # D-pad buttons
        btn_width = 10
        btn_padx = 5
        btn_pady = 5
        
        # UP button
        self.up_button = ttk.Button(control_frame, text="UP", width=btn_width, command=lambda: self.send_command("UP"))
        self.up_button.grid(row=0, column=1, padx=btn_padx, pady=btn_pady)
        
        # LEFT button
        self.left_button = ttk.Button(control_frame, text="LEFT", width=btn_width, command=lambda: self.send_command("LEFT"))
        self.left_button.grid(row=1, column=0, padx=btn_padx, pady=btn_pady)
        
        # OK button (center)
        self.ok_button = ttk.Button(control_frame, text="OK", width=btn_width, command=lambda: self.send_command("OK"))
        self.ok_button.grid(row=1, column=1, padx=btn_padx, pady=btn_pady)
        
        # RIGHT button
        self.right_button = ttk.Button(control_frame, text="RIGHT", width=btn_width, command=lambda: self.send_command("RIGHT"))
        self.right_button.grid(row=1, column=2, padx=btn_padx, pady=btn_pady)
        
        # DOWN button
        self.down_button = ttk.Button(control_frame, text="DOWN", width=btn_width, command=lambda: self.send_command("DOWN"))
        self.down_button.grid(row=2, column=1, padx=btn_padx, pady=btn_pady)
        
        # Function buttons
        self.function_button = ttk.Button(control_frame, text="FUNCTION", width=btn_width, command=lambda: self.send_command("FUNCTION"))
        self.function_button.grid(row=3, column=0, padx=btn_padx, pady=(20, btn_pady))
        
        self.back_button = ttk.Button(control_frame, text="BACK", width=btn_width, command=lambda: self.send_command("BACK"))
        self.back_button.grid(row=3, column=2, padx=btn_padx, pady=(20, btn_pady))
        
        # BACK LONG button
        self.back_long_button = ttk.Button(control_frame, text="BACK LONG", width=btn_width, command=lambda: self.send_command("BACK_LONG"))
        self.back_long_button.grid(row=4, column=1, padx=btn_padx, pady=btn_pady)
        
        # Disable control buttons initially
        self.set_control_buttons_state("disabled")
        
        # Bind keyboard shortcuts
        self.root.bind("<Up>", lambda e: self.send_command("UP"))
        self.root.bind("<Down>", lambda e: self.send_command("DOWN"))
        self.root.bind("<Left>", lambda e: self.send_command("LEFT"))
        self.root.bind("<Right>", lambda e: self.send_command("RIGHT"))
        self.root.bind("<Return>", lambda e: self.send_command("OK"))
        self.root.bind("<Escape>", lambda e: self.send_command("BACK"))
        self.root.bind("<F1>", lambda e: self.send_command("FUNCTION"))
        
    def populate_com_ports(self):
        ports = [port.device for port in serial.tools.list_ports.comports()]
        self.com_port_combo['values'] = ports
        if ports:
            self.com_port_var.set(ports[0])
            
    def toggle_connection(self):
        if self.connected:
            self.disconnect()
        else:
            self.connect()
            
    def connect(self):
        try:
            port = self.com_port_var.get()
            baud = int(self.baud_rate_var.get())
            
            if not port:
                messagebox.showerror("Error", "Please select a COM port")
                return
                
            self.ser = serial.Serial(port, baud, timeout=1)
            time.sleep(2)  # Wait for connection to establish
            
            self.connected = True
            self.connect_button.config(text="Disconnect")
            self.status_label.config(text="Connected", foreground="green")
            self.set_control_buttons_state("normal")
            
            # Start display update thread
            self.display_thread_running = True
            self.display_thread = threading.Thread(target=self.update_display_loop, daemon=True)
            self.display_thread.start()
            
        except Exception as e:
            messagebox.showerror("Connection Error", f"Failed to connect: {str(e)}")
            
    def disconnect(self):
        try:
            # Stop display update thread
            self.display_thread_running = False
            if self.display_thread:
                self.display_thread.join(timeout=1)
            
            if self.ser and self.ser.is_open:
                self.ser.close()
        except:
            pass
        finally:
            self.ser = None
            self.connected = False
            self.connect_button.config(text="Connect")
            self.status_label.config(text="Disconnected", foreground="red")
            self.set_control_buttons_state("disabled")
            
    def set_control_buttons_state(self, state):
        self.up_button.config(state=state)
        self.down_button.config(state=state)
        self.left_button.config(state=state)
        self.right_button.config(state=state)
        self.ok_button.config(state=state)
        self.function_button.config(state=state)
        self.back_button.config(state=state)
        self.back_long_button.config(state=state)
        
    def send_command(self, command):
        if not self.connected or not self.ser:
            messagebox.showwarning("Not Connected", "Please connect to a serial port first")
            return
            
        try:
            # Send command followed by newline
            self.ser.write(f"{command}\n".encode('utf-8'))
            print(f"Sent: {command}")
        except Exception as e:
            messagebox.showerror("Send Error", f"Failed to send command: {str(e)}")
            self.disconnect()
            
    def request_display_data(self):
        """Request display data from the device"""
        if not self.connected or not self.ser:
            return
            
        try:
            # Send GET_DISPLAY command
            self.ser.write(b"GET_DISPLAY\n")
            
            # Read 1024 bytes of display data
            data = self.ser.read(1024)
            if len(data) == 1024:
                self.display_data = data
                # Update the display on the main thread
                self.root.after(0, self.update_display)
        except Exception as e:
            print(f"Error requesting display data: {str(e)}")
            
    def update_display(self):
        """Update the display canvas with the received data"""
        if self.display_data is None:
            return
            
        # Clear the canvas
        self.display_canvas.delete("all")
        
        # Draw the display data
        for y in range(self.display_height):
            for x in range(self.display_width):
                # Calculate which byte and bit we're looking at
                byte_index = (y // 8) * self.display_width + x
                bit_index = y % 8
                
                # Check if the bit is set
                if byte_index < len(self.display_data):
                    byte_value = self.display_data[byte_index]
                    if byte_value & (1 << bit_index):
                        # Draw a white pixel
                        self.display_canvas.create_rectangle(x, y, x+1, y+1, fill="white", outline="")
                        
    def update_display_loop(self):
        """Periodically request display data"""
        while self.display_thread_running and self.connected:
            self.request_display_data()
            time.sleep(0.1)  # Update display 10 times per second
            
    def on_closing(self):
        self.disconnect()
        self.root.destroy()

def main():
    root = tk.Tk()
    app = ESPControllerGUI(root)
    root.protocol("WM_DELETE_WINDOW", app.on_closing)
    root.mainloop()

if __name__ == "__main__":
    main()