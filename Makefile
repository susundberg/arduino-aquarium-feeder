
SHELL:=/bin/bash


build:
	( \
	  source ../ENV//bin/activate; \
	  platformio run; \
	)


upload:
	( \
	  source ../ENV//bin/activate; \
	  platformio run --target upload; \
	)

build_tests:
	g++ -Wall -O0 -Isrc/ -Itests/fakes/ -o ./build/test_bin ./tests/test_main.cpp ./src/main.cpp