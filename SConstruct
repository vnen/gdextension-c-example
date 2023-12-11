#!/bin/env python
from SCons.Script import Environment
from os import path
import sys

env = Environment()

# Set the target path and name.
target_path = "demo/bin/"
target_name = "libgdexample"

# Set the compiler and flags.
env.Append(CPPPATH=["src"])  # Add the src directory to the include path.
env.Append(CFLAGS=["-O0", "-g"])  # Make a debug build.

# Use Clang on macOS.
if sys.platform == "darwin":
    env["CC"] = "clang"

# Add all C files in "src" folder as sources.
sources = env.Glob("src/*.c")

# Create a shared library.
library = env.SharedLibrary(
    target=path.join(target_path, target_name),
    source=sources,
)

# Set the library as the default target.
env.Default(library)
