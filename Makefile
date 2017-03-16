
SHELL:=/bin/bash


build:
	( \
	  source ../ENV//bin/activate; \
	  platformio run; \
	)


upload:
	( \
	  source ../ENV//bin/activate; \
	  platformio run --verbose --target upload; \
	)


test_build:
	scons -Y tests/tools/

