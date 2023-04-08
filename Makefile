BOARD?=arduino:avr:uno
PORT?=/dev/ttyACM0
PROJECT?=EnterValidProjectName
# SRC?=./1_profiler/1_profiler.ino
# TARGET_DIR?=./1_profiler/build

.PHONY: default build flash clean

default: install_dependencies build flash clean done monitor

install_dependencies:
	@echo "\n*******************installing dependencies********************\n"
	@arduino-cli core install arduino:avr
	@arduino-cli core install arduino:mbed_nicla

build:
	@echo "\n*******************building project********************\n"
	arduino-cli compile --fqbn $(BOARD) ./$(PROJECT)/$(PROJECT).ino --output-dir ./$(PROJECT)/build

flash:
	@echo "\n*******************uploading firmware********************\n"
	arduino-cli upload --fqbn $(BOARD) --port  $(PORT) --input-file ./$(PROJECT)/build/*.ino.hex

clean:
	@echo "\n*******************cleaning build directory********************\n"
	rm -rf ./$(PROJECT)/build

monitor:
	arduino-cli monitor --fqbn $(BOARD) --port $(PORT) -c baudrate=115200

done:
	@echo "\n*******************Done********************\n"
