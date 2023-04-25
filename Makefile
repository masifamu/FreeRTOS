# this is how to search for library using arduino-cli "arduino-cli lib search adafruit SSD1306  --names"



BOARD?=arduino:avr:uno
PORT?=/dev/ttyACM0
PROJECT?=EnterValidProjectName

.PHONY: default build flash clean install_dependencies done distribute diff

default: install_dependencies diff build flash clean distribute done monitor

install_dependencies:
	@echo "\n*******************installing dependencies********************\n"
	@arduino-cli core install arduino:avr
	@arduino-cli core install arduino:mbed_nicla

	@arduino-cli lib install "Adafruit SSD1306"
	@arduino-cli lib install "FreeRTOS"
	@arduino-cli lib install "OneButton"

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

distribute:
	@echo "\n*********************generating distributable***********************\n"
	tar zcvf distributable.tgz *

diff:
	@echo "\n*******************files change statistics********************\n"
	@git status
	@git diff --stat