#!/usr/bin/env python3
import tkinter as tk
from tkinter import ttk, messagebox
import serial
import serial.tools.list_ports
import threading
import time
import subprocess
import os
import requests
import tempfile
import zipfile

class ESPFlasher:
    def __init__(self, root):
        self.root = root
        self.root.title("ESP32 Flasher")
        self.root.geometry("600x700")
        self.root.resizable(False, False)
        
        self.ser = None
        self.connected = False
        self.display_data = None
        self.display_thread = None
        self.display_thread_running = False
        
        self.display_width = 128
        self.display_height = 64
        
        self.create_widgets()
        self.populate_com_ports()
        
    def create_widgets(self):
        # Flash section
        flash_frame = ttk.LabelFrame(self.root, text="Firmware", padding="10")
        flash_frame.pack(fill="x", padx=10, pady=5)
        
        ttk.Button(flash_frame, text="Flash Latest Release", 
                  command=self.flash_latest).pack(fill="x", pady=2)
        ttk.Button(flash_frame, text="Flash Local Build", 
                  command=self.flash_local).pack(fill="x", pady=2)
        
        self.flash_status = ttk.Label(flash_frame, text="Ready")
        self.flash_status.pack(pady=5)
        
        # Connection section
        conn_frame = ttk.LabelFrame(self.root, text="Connection", padding="10")
        conn_frame.pack(fill="x", padx=10, pady=5)
        
        port_frame = ttk.Frame(conn_frame)
        port_frame.pack(fill="x")
        
        ttk.Label(port_frame, text="Port:").pack(side="left")
        self.com_port_var = tk.StringVar()
        self.com_port_combo = ttk.Combobox(port_frame, textvariable=self.com_port_var, width=15)
        self.com_port_combo.pack(side="left", padx=5)
        
        ttk.Button(port_frame, text="Refresh", 
                  command=self.populate_com_ports).pack(side="left")
        
        self.connect_button = ttk.Button(conn_frame, text="Connect", 
                                        command=self.toggle_connection)
        self.connect_button.pack(pady=5)
        
        self.status_label = ttk.Label(conn_frame, text="Disconnected", foreground="red")
        self.status_label.pack()
        
        # Display section
        display_frame = ttk.LabelFrame(self.root, text="Display", padding="10")
        display_frame.pack(fill="both", expand=True, padx=10, pady=5)
        
        self.display_canvas = tk.Canvas(display_frame, width=self.display_width*2, 
                                       height=self.display_height*2, bg="black")
        self.display_canvas.pack()
        
        # Controls section
        ctrl_frame = ttk.LabelFrame(self.root, text="Controls", padding="10")
        ctrl_frame.pack(fill="x", padx=10, pady=5)
        
        # D-pad
        dpad = ttk.Frame(ctrl_frame)
        dpad.pack()
        
        ttk.Button(dpad, text="↑", width=5, 
                  command=lambda: self.send_cmd("UP")).grid(row=0, column=1, padx=2, pady=2)
        ttk.Button(dpad, text="←", width=5, 
                  command=lambda: self.send_cmd("LEFT")).grid(row=1, column=0, padx=2, pady=2)
        ttk.Button(dpad, text="OK", width=5, 
                  command=lambda: self.send_cmd("OK")).grid(row=1, column=1, padx=2, pady=2)
        ttk.Button(dpad, text="→", width=5, 
                  command=lambda: self.send_cmd("RIGHT")).grid(row=1, column=2, padx=2, pady=2)
        ttk.Button(dpad, text="↓", width=5, 
                  command=lambda: self.send_cmd("DOWN")).grid(row=2, column=1, padx=2, pady=2)
        
        # Function buttons
        func_frame = ttk.Frame(ctrl_frame)
        func_frame.pack(pady=10)
        
        ttk.Button(func_frame, text="FUNC", width=8, 
                  command=lambda: self.send_cmd("FUNCTION")).pack(side="left", padx=5)
        ttk.Button(func_frame, text="BACK", width=8, 
                  command=lambda: self.send_cmd("BACK")).pack(side="left", padx=5)
        
        # Keyboard bindings
        self.root.bind("<Up>", lambda e: self.send_cmd("UP"))
        self.root.bind("<Down>", lambda e: self.send_cmd("DOWN"))
        self.root.bind("<Left>", lambda e: self.send_cmd("LEFT"))
        self.root.bind("<Right>", lambda e: self.send_cmd("RIGHT"))
        self.root.bind("<Return>", lambda e: self.send_cmd("OK"))
        self.root.bind("<Escape>", lambda e: self.send_cmd("BACK"))
        
    def populate_com_ports(self):
        ports = [port.device for port in serial.tools.list_ports.comports()]
        self.com_port_combo['values'] = ports
        if ports:
            self.com_port_var.set(ports[0])
            
    def flash_latest(self):
        self.flash_status.config(text="Fetching latest release...")
        threading.Thread(target=self._flash_latest_thread, daemon=True).start()
        
    def _flash_latest_thread(self):
        try:
            # Get latest release from GitHub
            api_url = "https://api.github.com/repos/OWNER/REPO/releases/latest"
            response = requests.get(api_url)
            
            if response.status_code != 200:
                self.root.after(0, lambda: messagebox.showerror("Error", 
                    "Could not fetch latest release. Using local build instead."))
                self.root.after(0, self.flash_local)
                return
                
            release = response.json()
            
            # Find firmware asset
            firmware_url = None
            for asset in release.get('assets', []):
                if asset['name'].endswith('.bin'):
                    firmware_url = asset['browser_download_url']
                    break
                    
            if not firmware_url:
                self.root.after(0, lambda: messagebox.showerror("Error", 
                    "No firmware found in release"))
                return
                
            # Download firmware
            self.root.after(0, lambda: self.flash_status.config(text="Downloading..."))
            fw_response = requests.get(firmware_url)
            
            # Save to temp file
            with tempfile.NamedTemporaryFile(delete=False, suffix='.bin') as f:
                f.write(fw_response.content)
                temp_path = f.name
                
            # Flash
            self.root.after(0, lambda: self._flash_file(temp_path))
            
        except Exception as e:
            self.root.after(0, lambda: messagebox.showerror("Error", str(e)))
            self.root.after(0, lambda: self.flash_status.config(text="Flash failed"))
            
    def flash_local(self):
        firmware_path = ".pio/build/esp32dev/firmware.bin"
        if not os.path.exists(firmware_path):
            messagebox.showerror("Error", "Local firmware not found. Build first with: pio run")
            return
        self._flash_file(firmware_path)
        
    def _flash_file(self, firmware_path):
        port = self.com_port_var.get()
        if not port:
            messagebox.showerror("Error", "Select COM port")
            return
            
        self.flash_status.config(text="Flashing...")
        
        try:
            # Use esptool.py or platformio
            cmd = f"pio run --target upload --upload-port {port}"
            result = subprocess.run(cmd, shell=True, capture_output=True, text=True)
            
            if result.returncode == 0:
                self.flash_status.config(text="Flash successful!")
                messagebox.showinfo("Success", "Firmware flashed successfully")
            else:
                self.flash_status.config(text="Flash failed")
                messagebox.showerror("Error", f"Flash failed:\n{result.stderr}")
                
        except Exception as e:
            self.flash_status.config(text="Flash failed")
            messagebox.showerror("Error", str(e))
            
    def toggle_connection(self):
        if self.connected:
            self.disconnect()
        else:
            self.connect()
            
    def connect(self):
        try:
            port = self.com_port_var.get()
            if not port:
                messagebox.showerror("Error", "Select COM port")
                return
                
            self.ser = serial.Serial(port, 115200, timeout=1)
            time.sleep(2)
            
            self.connected = True
            self.connect_button.config(text="Disconnect")
            self.status_label.config(text="Connected", foreground="green")
            
            self.display_thread_running = True
            self.display_thread = threading.Thread(target=self.update_display_loop, daemon=True)
            self.display_thread.start()
            
        except Exception as e:
            messagebox.showerror("Error", f"Connection failed: {e}")
            
    def disconnect(self):
        self.display_thread_running = False
        if self.display_thread:
            self.display_thread.join(timeout=1)
            
        if self.ser and self.ser.is_open:
            self.ser.close()
            
        self.ser = None
        self.connected = False
        self.connect_button.config(text="Connect")
        self.status_label.config(text="Disconnected", foreground="red")
        
    def send_cmd(self, cmd):
        if not self.connected or not self.ser:
            return
        try:
            self.ser.write(f"{cmd}\n".encode())
        except:
            self.disconnect()
            
    def update_display_loop(self):
        while self.display_thread_running and self.connected:
            try:
                self.ser.write(b"GET_DISPLAY\n")
                data = self.ser.read(1024)
                if len(data) == 1024:
                    self.display_data = data
                    self.root.after(0, self.render_display)
            except:
                pass
            time.sleep(0.1)
            
    def render_display(self):
        if not self.display_data:
            return
            
        self.display_canvas.delete("all")
        
        for y in range(self.display_height):
            for x in range(self.display_width):
                byte_index = (y // 8) * self.display_width + x
                bit_index = y % 8
                
                if byte_index < len(self.display_data):
                    if self.display_data[byte_index] & (1 << bit_index):
                        self.display_canvas.create_rectangle(
                            x*2, y*2, x*2+2, y*2+2, 
                            fill="white", outline="")
                            
    def on_closing(self):
        self.disconnect()
        self.root.destroy()

if __name__ == "__main__":
    root = tk.Tk()
    app = ESPFlasher(root)
    root.protocol("WM_DELETE_WINDOW", app.on_closing)
    root.mainloop()
