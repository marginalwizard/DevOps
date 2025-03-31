AUTOMAKE_OPTIONS = foreign subdir-objects
bin_PROGRAMS = series
series_SOURCES = main.cpp Series.cpp Series.h HTTP_Server.cpp
dist_man_MANS = series.1
nobase_dist_pkgdata_DATA = data.txt

SUBDIRS = tests

CTRLF_DIR=$(CURDIR)/deb/DEBIAN
CTRLF_NAME=$(CTRLF_DIR)/control

.PHONY: deb debug
deb:
	mkdir -p $(CTRLF_DIR)
	echo "Package: $(PACKAGE)" > $(CTRLF_NAME)
	echo "Version: $(VERSION)" >> $(CTRLF_NAME)
	echo "Architecture: all" >> $(CTRLF_NAME)
	echo "Maintainer: $(PACKAGE_BUGREPORT)" >> $(CTRLF_NAME)
	echo "Description: Program for calculating the values of series" >> $(CTRLF_NAME)
	echo " A program for calculating number series by variant." >> $(CTRLF_NAME)
	echo " ." >> $(CTRLF_NAME)
	echo " The program implements the calculation of series values with a given accuracy" >> $(CTRLF_NAME)
	echo " and the number of row members." >> $(CTRLF_NAME)
	make DESTDIR=$(CURDIR)/deb install
        
debug:
	$(foreach v, $(.VARIABLES), $(info $(v)=$($(v))))
