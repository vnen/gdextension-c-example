# GDExtension C example

## Introduction

This is a simple example on how to work with GDExtension directly with C code. Note
that the API is not meant to be used directly, so this will definitely be quite verbose
and require a lot of small steps even for a small example. However, it serves as
a reference for creating bindings for a different language. It is still possible
to use the API directly if you prefer, which might be convenient when only binding
a third-party library.

## Setting up the project

There are a few things you'll need:

- a Godot 4.x executable,
- a C compiler,
- SCons as a build tool.

Since this is using the API directly, there's no need to use the [godot-cpp](https://github.com/godotengine/godot-cpp)
repository.

## File structure

To organize our files, we're gonna split in mainly two folders:

gdextension_c_example/
|
+--demo/                  # game example/demo to test the extension
|
+--src/                   # source code of the extension we are building
