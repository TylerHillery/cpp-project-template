# C++ project template

A small C++17 starter based on the sibling `c-project-template`: Clang, CMake/Ninja,
clangd, clang-format, clang-tidy, LLDB, CTest, and ASan/UBSan. It uses ordinary
standard-library C++; **it is not a no-libc++/libstdc++ build**. Add a separate,
audited C-facing core only if you actually need one.

## Requirements

CMake >= 3.21, Ninja, Clang (or GCC), clang-format, clang-tidy, LLDB, and CTest
(shipped with CMake). `make` provides the familiar shortcuts.

## Start a new project

Copy this directory without `build/`. Rename the project, executable, and
`example` namespace; replace the sample parser and tests. Keep public headers
in `include/`, implementations in `src/`, and tests in `tests/`.

## Build and run

```sh
make setup          # configure debug; generates build/debug/compile_commands.json
make                # build debug (same as make debug-build)
make debug-build    # -O0 -g (CMake Debug)
make run            # run the debug executable
make release        # optimized build
make sanitize       # ASan + UBSan, -O1 -g
make run-sanitize
make test           # debug tests through CTest
make test-sanitize  # sanitizer tests through CTest
make debug          # open the debug executable in LLDB
make format
make format-check
make tidy           # uses build/debug/compile_commands.json
```

To use GCC in a fresh build, run `make CXX=g++ test`. Each mode has its own
CMake cache: to change compilers for an existing mode, remove **that mode's**
`build/` subdirectory first. `make clean` removes all generated builds.
For clangd, point it at `build/debug/compile_commands.json` (for example, set
`--compile-commands-dir=build/debug` in your editor). If you don't want Make,
use `cmake --preset debug`, `cmake --build build/debug`, and
`ctest --test-dir build/debug --output-on-failure` directly.

For optional git hooks: `prek install` and `prek run --all-files` (or use
`pre-commit`). Format/check targets touch only project source, not dependencies.

## Tests in C++

The sample test is a normal executable returning nonzero on failure; CTest runs
it and reports failures. Checks remain active in optimized builds (unlike
`assert`, which disappears with `NDEBUG`). Add more tests with `add_executable`
and `add_test` in `CMakeLists.txt`.

Common external choices: **Catch2** and **doctest** for concise assertions;
**GoogleTest** (often with GoogleMock) for larger suites/mocks. CTest is a
*runner*, not an assertion framework: any of these can be registered with it.
Keep the zero-dependency tests until their simplicity stops helping; if you
adopt a framework, pin its version rather than requiring developers to have
an arbitrary version installed.

## Conventions

Use braces, four spaces, snake_case functions/files, RAII and explicit
ownership (`std::unique_ptr` for exclusive ownership). Prefer return values
for expected errors, including parse failures; test edge cases and invalid
inputs. Avoid premature manual allocation and clever templates. Use a stable C
API only when cross-language or cross-compiler binary interoperability matters.
