# Makefile for building ESP Controller GUI executables

# Default target
.PHONY: all
all: help

# Help target
.PHONY: help
help:
	@echo "ESP Controller GUI Build System"
	@echo "=============================="
	@echo "Available targets:"
	@echo "  help          - Show this help message"
	@echo "  install       - Install dependencies"
	@echo "  install-dev   - Install development dependencies"
	@echo "  run           - Run the application"
	@echo "  build-pyinstaller - Build executable with PyInstaller"
	@echo "  build-cxfreeze - Build executable with cx_Freeze"
	@echo "  clean         - Clean build artifacts"

# Install dependencies
.PHONY: install
install:
	pip3 install -r requirements.txt

# Install development dependencies
.PHONY: install-dev
install-dev:
	pip3 install -r requirements-dev.txt

# Run the application
.PHONY: run
run:
	python3 esp_controller_gui.py

# Build with PyInstaller
.PHONY: build-pyinstaller
build-pyinstaller:
	pyinstaller --onefile esp_controller_gui.spec

# Build with cx_Freeze
.PHONY: build-cxfreeze
build-cxfreeze:
	python3 setup.py build

# Clean build artifacts
.PHONY: clean
clean:
	rm -rf build/
	rm -rf dist/
	rm -rf *.spec.bak
	find . -name "*.pyc" -delete
	find . -name "__pycache__" -type d -exec rm -rf {} +