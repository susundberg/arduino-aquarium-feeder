
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

