# GDExtension C example

This is a very basic example on how to create a GDExtension using C without any
language bindings. It replicates the [C++ example](https://docs.godotengine.org/en/4.2/tutorials/scripting/gdextension/gdextension_cpp_example.html)
from the official documentation but without the C++ bindings.

The intention is to showcase how the GDExtension API works so other bindings can
use this as a reference.

Note that while it's possible to develop your extensions in C like this, it is not
the recommended workflow. The API was not designed to be used without some sort of
code generation to create helper functions. Doing all this manually can become tedious
quite fast.

The `api.c` (and its corresponding header) are a small set of such helper functions, made so the interaction with the GDExtension API and the extension logic in itself are separate. This makes it easier to understand each part of the example.

## Compiling

The `SConstruct` file is a very simple one that compiles a debug build targeting
the platform where you're running [`scons`](https://scons.org/) on. After compiling, the Godot project in
the `demo` folder can be opened in the editor.
