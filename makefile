#TARGET=arm
TARGET=pc

#BUILD=debug
BUILD=release


# build


compile:
	if [ ! -d build/$(TARGET)/$(BUILD) ]; then \
		mkdir -p build/$(TARGET)/$(BUILD) ; \
		cd build/$(TARGET)/$(BUILD) ; cmake ../../../ -DTARGET=$(TARGET) -DBUILD=$(BUILD) ; \
	fi
	cd build/$(TARGET)/$(BUILD) ; $(MAKE)

clean:
	- cd build/$(TARGET)/$(BUILD) ; $(MAKE) clean

distclean:
	- rm -rf build/$(TARGET)/$(BUILD)


# run


test: compile
	build/$(TARGET)/$(BUILD)/test/test
