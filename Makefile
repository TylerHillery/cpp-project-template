# Familiar shortcuts around the CMake/Ninja build. Override with: make CXX=g++ test
CXX = clang++
.DEFAULT_GOAL := debug-build

.PHONY: setup debug-build release sanitize test test-sanitize run run-release run-sanitize debug format format-check tidy clean

setup:
	CXX=$(CXX) cmake --preset debug

debug-build:
	CXX=$(CXX) cmake --preset debug
	cmake --build build/debug

release:
	CXX=$(CXX) cmake --preset release
	cmake --build build/release

sanitize:
	CXX=$(CXX) cmake --preset sanitize
	cmake --build build/sanitize

test: debug-build
	ctest --test-dir build/debug --output-on-failure

test-sanitize: sanitize
	ctest --test-dir build/sanitize --output-on-failure

run: debug-build
	./build/debug/hello

run-release: release
	./build/release/hello

run-sanitize: sanitize
	./build/sanitize/hello

debug: debug-build
	lldb -- ./build/debug/hello

format:
	find src include tests -type f \( -name '*.cpp' -o -name '*.hpp' \) -exec clang-format -i {} +

format-check:
	find src include tests -type f \( -name '*.cpp' -o -name '*.hpp' \) -exec clang-format --dry-run --Werror {} +

tidy: setup
	find src tests -type f -name '*.cpp' -exec clang-tidy -p build/debug {} +

clean:
	cmake -E rm -rf build
