# Master Makefile for game-dev-experiments
# Recursively builds all projects inside snippets/ and miniprojects/

SUBDIRS := $(wildcard snippets/*) $(wildcard miniprojects/*)

all:
	@for dir in $(SUBDIRS); do \
		if [ -f $$dir/Makefile ]; then \
			echo "==> Building $$dir"; \
			$(MAKE) -C $$dir; \
		fi \
	done

clean:
	@for dir in $(SUBDIRS); do \
		if [ -f $$dir/Makefile ]; then \
			echo "==> Cleaning $$dir"; \
			$(MAKE) -C $$dir clean; \
		fi \
	done
