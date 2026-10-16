# C++ project template

A small C++17 starter based on the sibling `c-project-template`: Clang, CMake/Ninja,
clangd, clang-format, clang-tidy, LLDB, CTest, and ASan/UBSan. It uses ordinary
standard-library C++; **it is not a no-libc++/libstdc++ build**. Add a separate,
audited C-facing core only if you actually need one.

## Requirements

Install [mise](https://mise.jdx.dev/) and, from this directory, run:

```sh
mise install
mise exec -- make test
mise exec -- make test-sanitize
```

The project-local `mise.toml` pins CMake, Ninja, Make, Clang/clangd/clang-format/
clang-tidy, LLDB, and prek. CTest comes with CMake. You don't need a global mise
config or shell activation: `mise exec -- ...` runs commands with these tools on
`PATH`. If mise is already activated in your shell, just use `make test`.
You'll still need the usual OS runtime/development libraries for your platform;
mise doesn't replace an operating-system SDK. The pinned Clang and LLDB
packages are distributed by conda-forge and may take a while to download.
For a different platform where those packages aren't available, install the
compiler/debugger through your OS and adapt `mise.toml` accordingly.

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
The checked-in `.clangd` points clangd at `build/debug/compile_commands.json`.
Run `make setup` once before opening source files in the editor, and restart
clangd after switching compilers. Unlike a C `compile_flags.txt`, the C++
compilation database supplies per-file includes, `-std=c++17`, and the actual
compiler used by each target. If you don't want Make,
use `cmake --preset debug`, `cmake --build build/debug`, and
`ctest --test-dir build/debug --output-on-failure` directly.

For optional git hooks: `prek install` and `prek run --all-files` (or use
`pre-commit`). Format/check targets touch only project source, not dependencies.

## VS Code

Open the template folder in VS Code and accept its workspace extension
recommendations (`.vscode/extensions.json`): the C++ extension pack, clangd,
CMake Tools, CodeLLDB, and clang-format. `make setup` generates the compilation
database used by clangd. Workspace settings choose clangd rather than the
extension pack's separate C++ IntelliSense and format C++ with the project's
`.clang-format` on save. The included launch configuration uses CodeLLDB.
If VS Code cannot find the mise-installed binaries, start it from an activated
mise shell or use your existing mise VS Code integration. Install the extensions
in the remote environment too when using WSL, SSH, or a container.

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
