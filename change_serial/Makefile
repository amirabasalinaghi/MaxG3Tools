APP_NAME := change_sn
SRC := change_sn.go
BUILD_DIR := build

.PHONY: build clean

build: \
  $(BUILD_DIR)/$(APP_NAME)_darwin_amd64 \
  $(BUILD_DIR)/$(APP_NAME)_darwin_arm64 \
  $(BUILD_DIR)/$(APP_NAME)_windows_amd64.exe \
  $(BUILD_DIR)/$(APP_NAME)_linux_amd64 \
  $(BUILD_DIR)/$(APP_NAME)_linux_arm64

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/$(APP_NAME)_darwin_amd64: $(SRC) | $(BUILD_DIR)
	CGO_ENABLED=0 GOOS=darwin GOARCH=amd64 go build -o $@ $<

$(BUILD_DIR)/$(APP_NAME)_darwin_arm64: $(SRC) | $(BUILD_DIR)
	CGO_ENABLED=0 GOOS=darwin GOARCH=arm64 go build -o $@ $<

$(BUILD_DIR)/$(APP_NAME)_windows_amd64.exe: $(SRC) | $(BUILD_DIR)
	CGO_ENABLED=0 GOOS=windows GOARCH=amd64 go build -o $@ $<

$(BUILD_DIR)/$(APP_NAME)_linux_amd64: $(SRC) | $(BUILD_DIR)
	CGO_ENABLED=0 GOOS=linux GOARCH=amd64 go build -o $@ $<

$(BUILD_DIR)/$(APP_NAME)_linux_arm64: $(SRC) | $(BUILD_DIR)
	CGO_ENABLED=0 GOOS=linux GOARCH=arm64 go build -o $@ $<

clean:
	rm -rf $(BUILD_DIR)
