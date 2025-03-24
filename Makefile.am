AUTOMAKE_OPTIONS = foreign
bin_PROGRAMS = series
series_SOURCES = main.cpp Series.cpp Series.h
dist_man_MANS = series.1
nobase_dist_pkgdata_DATA = data.txt

CTRLF_DIR=$(CURDIR)/deb/DEBIAN
CTRLF_NAME=$(CTRLF_DIR)/control

.PHONY: deb debug
deb:
	mkdir -p $(CTRLF_DIR)
	echo "Package: $(PACKAGE)" > $(CTRLF_NAME)
	echo "Version: $(VERSION)" >> $(CTRLF_NAME)
	echo "Architecture: all" >> $(CTRLF_NAME)
	echo "Maintainer: $(PACKAGE_BUGREPORT)" >> $(CTRLF_NAME)
	echo "Description:" >> $(CTRLF_NAME)
	cat series.1 >> $(CTRLF_NAME)
	make DESTDIR=$(CURDIR)/deb install
	
debug:
	$(foreach v, $(.VARIABLES), $(info $(v)=$($(v))))
