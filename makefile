OUTPUT_DIR=./bin
INPUT_DIR=./build-it

BOARD=arduino:avr:uno

CC=arduino-cli

COMPILE_FALGS=compile --output-dir $(OUTPUT_DIR) -b $(BOARD) $(INPUT_DIR)
UPLOAD_FLAGS=upload -v -b arduino:avr:uno --port /dev/ttyACM0 --input-dir $(OUTPUT_DIR) #-P "AVRISP mkll"

.PHONY=all

all: compile

build: compile upload

compile:
	$(CC) $(COMPILE_FALGS)

upload:
	$(CC) $(UPLOAD_FLAGS)