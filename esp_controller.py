import tkinter as tk
from tkinter import ttk, messagebox
import serial
import serial.tools.list_ports
import threading
import time

class ESPController:
    def __init__(self, root):
        self.root = root
        self.root.title("ESP Device Controller")
        self.root.geometry("400x500")
        self.root.resizable(False, False)
        
        # Configure styles
        self.setup_styles()
        
        # Serial connection
        self.ser = None
        self.serial_thread = None
        self.running = False
        
        # Create UI
        self.create_widgets()
        
        # Update available ports
        self.update_ports()
        
    def setup_styles(self):
        """Configure the application styles"""
        self.root.configure(bg='#2c3e50')
        
        # Create style object
        style = ttk.Style()
        
        # Configure button styles
        style.configure(
            "DPad.TButton",
            font=('Arial', 12, 'bold'),
            padding=10,
            background='#3498db',
            foreground='white'
        )
        
        style.configure(
            "Control.TButton",
            font=('Arial', 10, 'bold'),
            padding=8,
            background='#27ae60',
            foreground='white'
        )
        
        style.configure(
            "Connect.TButton",
            font=('Arial', 10, 'bold'),
            padding=6,
            background='#e74c3c',
            foreground='white'
        )
        
        style.configure(
            "TLabel",
            background='#2c3e50',
            foreground='white',
            font=('Arial', 10)
        )
        
        style.configure(
            "Title.TLabel",
            font=('Arial', 16, 'bold'),
            foreground='#ecf0f1'
        )
        
        style.configure(
            "Status.TLabel",
            font=('Arial', 9),
            foreground='#bdc3c7'
        )
        
    def create_widgets(self):
        """Create all UI widgets"""
        # Main frame
        main_frame = tk.Frame(self.root, bg='#2c3e50')
        main_frame.pack(fill=tk.BOTH, expand=True, padx=20, pady=20)
        
        # Title
        title_label = ttk.Label(main_frame, text="ESP Device Controller", style="Title.TLabel")
        title_label.pack(pady=(0, 20))
        
        # Serial connection frame
        serial_frame = tk.Frame(main_frame, bg='#34495e', relief=tk.RAISED, bd=2)
        serial_frame.pack(fill=tk.X, pady=(0, 20))
        
        # Port selection
        port_frame = tk.Frame(serial_frame, bg='#34495e')
        port_frame.pack(side=tk.LEFT, padx=10, pady=10)
        
        ttk.Label(port_frame, text="Port:").pack(anchor=tk.W)
        self.port_var = tk.StringVar()
        self.port_combo = ttk.Combobox(port_frame, textvariable=self.port_var, width=15, state="readonly")
        self.port_combo.pack()
        
        # Baud rate
        baud_frame = tk.Frame(serial_frame, bg='#34495e')
        baud_frame.pack(side=tk.LEFT, padx=10, pady=10)
        
        ttk.Label(baud_frame, text="Baud Rate:").pack(anchor=tk.W)
        self.baud_var = tk.StringVar(value="115200")
        baud_combo = ttk.Combobox(baud_frame, textvariable=self.baud_var, width=10, state="readonly")
        baud_combo['values'] = ("9600", "19200", "38400", "57600", "115200")
        baud_combo.pack()
        
        # Connect button
        self.connect_btn = ttk.Button(
            serial_frame, 
            text="Connect", 
            style="Connect.TButton",
            command=self.toggle_connection
        )
        self.connect_btn.pack(side=tk.RIGHT, padx=10, pady=10)
        
        # Status label
        self.status_var = tk.StringVar(value="Disconnected")
        self.status_label = ttk.Label(main_frame, textvariable=self.status_var, style="Status.TLabel")
        self.status_label.pack(pady=(0, 20))
        
        # D-Pad frame
        dpad_frame = tk.Frame(main_frame, bg='#2c3e50')
        dpad_frame.pack(expand=True)
        
        # UP button
        self.up_btn = ttk.Button(
            dpad_frame, 
            text="UP", 
            style="DPad.TButton",
            command=lambda: self.send_command("UP")
        )
        self.up_btn.grid(row=0, column=1, padx=5, pady=5, sticky="ew")
        
        # LEFT button
        self.left_btn = ttk.Button(
            dpad_frame, 
            text="LEFT", 
            style="DPad.TButton",
            command=lambda: self.send_command("LEFT")
        )
        self.left_btn.grid(row=1, column=0, padx=5, pady=5, sticky="ew")
        
        # OK button (center)
        self.ok_btn = ttk.Button(
            dpad_frame, 
            text="OK", 
            style="DPad.TButton",
            command=lambda: self.send_command("OK")
        )
        self.ok_btn.grid(row=1, column=1, padx=5, pady=5, sticky="ew")
        
        # RIGHT button
        self.right_btn = ttk.Button(
            dpad_frame, 
            text="RIGHT", 
            style="DPad.TButton",
            command=lambda: self.send_command("RIGHT")
        )
        self.right_btn.grid(row=1, column=2, padx=5, pady=5, sticky="ew")
        
        # DOWN button
        self.down_btn = ttk.Button(
            dpad_frame, 
            text="DOWN", 
            style="DPad.TButton",
            command=lambda: self.send_command("DOWN")
        )
        self.down_btn.grid(row=2, column=1, padx=5, pady=5, sticky="ew")
        
        # Configure grid weights for proper resizing
        dpad_frame.columnconfigure(0, weight=1)
        dpad_frame.columnconfigure(1, weight=1)
        dpad_frame.columnconfigure(2, weight=1)
        
        # Control buttons frame
        control_frame = tk.Frame(main_frame, bg='#2c3e50')
        control_frame.pack(pady=20)
        
        # FUNCTION button
        self.function_btn = ttk.Button(
            control_frame, 
            text="FUNCTION", 
            style="Control.TButton",
            command=lambda: self.send_command("FUNCTION")
        )
        self.function_btn.pack(side=tk.LEFT, padx=10)
        
        # BACK button
        self.back_btn = ttk.Button(
            control_frame, 
            text="BACK", 
            style="Control.TButton",
            command=lambda: self.send_command("BACK")
        )
        self.back_btn.pack(side=tk.LEFT, padx=10)
        
        # BACK LONG button
        self.back_long_btn = ttk.Button(
            control_frame, 
            text="BACK LONG", 
            style="Control.TButton",
            command=lambda: self.send_command("BACK_LONG")
        )
        self.back_long_btn.pack(side=tk.LEFT, padx=10)
        
        # Bind keyboard events
        self.bind_keyboard_events()
        
        # Disable buttons initially
        self.set_button_states(False)
        
    def bind_keyboard_events(self):
        """Bind keyboard events to buttons"""
        self.root.bind('<Up>', lambda e: self.send_command("UP"))
        self.root.bind('<Down>', lambda e: self.send_command("DOWN"))
        self.root.bind('<Left>', lambda e: self.send_command("LEFT"))
        self.root.bind('<Right>', lambda e: self.send_command("RIGHT"))
        self.root.bind('<Return>', lambda e: self.send_command("OK"))
        self.root.bind('<Escape>', lambda e: self.send_command("BACK"))
        self.root.bind('<F1>', lambda e: self.send_command("FUNCTION"))
        
    def update_ports(self):
        """Update the list of available serial ports"""
        ports = [port.device for port in serial.tools.list_ports.comports()]
        self.port_combo['values'] = ports
        if ports:
            self.port_combo.current(0)
            
    def toggle_connection(self):
        """Toggle serial connection"""
        if self.ser and self.ser.is_open:
            self.disconnect()
        else:
            self.connect()
            
    def connect(self):
        """Connect to the selected serial port"""
        port = self.port_var.get()
        baud = int(self.baud_var.get())
        
        if not port:
            messagebox.showerror("Error", "Please select a port")
            return
            
        try:
            self.ser = serial.Serial(port, baud, timeout=1)
            time.sleep(2)  # Wait for connection to establish
            
            self.status_var.set(f"Connected to {port}")
            self.connect_btn.configure(text="Disconnect")
            self.set_button_states(True)
            
        except Exception as e:
            messagebox.showerror("Connection Error", f"Failed to connect: {str(e)}")
            self.status_var.set("Connection failed")
            
    def disconnect(self):
        """Disconnect from the serial port"""
        if self.ser and self.ser.is_open:
            self.ser.close()
            
        self.status_var.set("Disconnected")
        self.connect_btn.configure(text="Connect")
        self.set_button_states(False)
        
    def set_button_states(self, state):
        """Enable or disable control buttons"""
        state_str = "normal" if state else "disabled"
        
        self.up_btn.configure(state=state_str)
        self.down_btn.configure(state=state_str)
        self.left_btn.configure(state=state_str)
        self.right_btn.configure(state=state_str)
        self.ok_btn.configure(state=state_str)
        self.function_btn.configure(state=state_str)
        self.back_btn.configure(state=state_str)
        self.back_long_btn.configure(state=state_str)
        
    def send_command(self, command):
        """Send a command to the ESP device"""
        if not self.ser or not self.ser.is_open:
            messagebox.showwarning("Not Connected", "Please connect to a serial port first")
            return
            
        try:
            # Send command with newline
            self.ser.write(f"{command}\n".encode())
            print(f"Sent: {command}")
            
            # Update status
            self.status_var.set(f"Sent: {command}")
            
        except Exception as e:
            messagebox.showerror("Send Error", f"Failed to send command: {str(e)}")
            self.status_var.set("Send failed")
            
    def on_closing(self):
        """Handle application closing"""
        if self.ser and self.ser.is_open:
            self.ser.close()
        self.root.destroy()

def main():
    root = tk.Tk()
    app = ESPController(root)
    root.protocol("WM_DELETE_WINDOW", app.on_closing)
    root.mainloop()

if __name__ == "__main__":
    main()