from cx_Freeze import setup, Executable

# Dependencies are automatically detected, but it might need fine tuning.
build_options = {
    'packages': [],
    'excludes': [],
    'include_files': []
}

# GUI applications require a different base on Windows
import sys
base = 'Win32GUI' if sys.platform == 'win32' else None

executables = [
    Executable(
        'esp_controller_gui.py',
        base=base,
        target_name='esp_controller'
    )
]

setup(
    name='ESP_Controller',
    version='1.0',
    description='ESP Device Controller GUI',
    options={'build_exe': build_options},
    executables=executables
)