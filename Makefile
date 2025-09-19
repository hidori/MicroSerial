TARGETS = DebugSerial HelloSerial
BUILD_CONFIG ?= ./arduino-cli.yaml
CORES ?= arduino:avr
LIBS ?=

DEPLOY_DIR ?= ~/Documents/Arduino/libraries/MicroSerial
BUILD_DIR ?= ./build
TEMP_DIR ?= ./tmp

define build-targets
	$(foreach TARGET,$(TARGETS), \
		$(call build-target,$(1),$(TARGET)))
endef

define build-target
	arduino-cli compile \
		$(if $(filter-out undefined,$(origin DEBUG)),--build-property "build.extra_flags=-DDEBUG") \
		--fqbn $(1) \
		--library ./src \
		--export-binaries \
		./examples/$(2)/$(2).ino;
endef

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) $(TEMP_DIR)
	find . -type f -exec chmod -x {} +
	$(foreach TARGET,$(TARGETS),rm -fr ./examples/$(TARGET)/build/;)
	$(foreach TARGET,$(TARGETS),rm -f ./examples/$(TARGET)/*.lst;)

.PHONY: build
build: build/uno

.PHONY: build/uno
build/uno:
	$(call build-targets,arduino:avr:uno)

.PHONY: deploy
deploy:
	mkdir -p $(DEPLOY_DIR)
	cp ./src/* $(DEPLOY_DIR)

.PHONY: install
install: core/install lib/install

.PHONY: core/update-index
core/update-index:
	arduino-cli core update-index

.PHONY: core/install
core/install: core/update-index
	@if [ ! -f ~/.arduino15/arduino-cli.yaml ]; then arduino-cli config init; fi
	arduino-cli --config-file $(BUILD_CONFIG) core update-index
	arduino-cli --config-file $(BUILD_CONFIG) core install $(CORES)

.PHONY: lib/install
lib/install:
#	arduino-cli --config-file $(BUILD_CONFIG) lib install $(LIBS)
