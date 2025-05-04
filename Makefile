FILES = $(filter-out %.bat, $(wildcard *))

.PHONY: prepare
prepare:
	brew install z3

.PHONY: build
build:
	clang++ g3tools.cpp -std=c++17 -lz3 -I/opt/homebrew/include -L/opt/homebrew/lib -o g3tools

.PHONY: changeSn
changeSn:
	./change_sn.sh

.PHONY: changeKey
changeKey:
	./change_key_to_default.sh

.PHONY: fixKey
fixKey:
	./fix_key.sh

.PHONY: exec
exec:
	@for file in $(wildcard *.sh); do \
		chmod +x $$file; \
		echo "Added +x to $$file"; \
	done
	chmod +x g3tools