AUTOMAKE_OPTIONS = foreign
bin_PROGRAMS = series
series_SOURCES = main.cpp Series.cpp Series.h
dist_man_MANS = series.1
dist_pkgdata_DATA = data.txt

SUBDIRS = tests

# Add a 'deb' target to make debian package
.PHONY: deb debug
deb:
	mkdir -p $(CURDIR)/deb/DEBIAN
	echo "Package: $(PACKAGE)" > $(CTRL_DIR)/control
	echo "Version: $(VERSION)" >> $(CTRL_DIR)/control
	echo "Architecture: all" >> $(CTRL_DIR)/control
	echo "Maintainer: $(PACKAGE_BUGREPORT)" >> $(CTRL_DIR)/control
	echo -n "Description: " >> $(CTRL_DIR)/control
	cat series.1 >> $(CTRL_DIR)/control
	make DESTDIR=$(CURDIR)/deb install

CTRL_DIR=$(CURDIR)/deb/DEBIAN
CTRL_NAME=$(CTRL_DIR)/control

# Debug target to display variables
debug:
	$(foreach v,$(VARIABLES),$(info $(v)=$($(v))))
