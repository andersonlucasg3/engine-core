# engine-core

The shared C++ foundation for this engine and for `CppMobileFramework`: type aliases, strings, containers, smart pointers, filesystem, process/environment, logging, threading, time and math types. It was extracted from `CppMobileFramework` (Core commit `deef9df`).

## It is a module, not a project

- There is no `*.Project.cs` here. `Core.Module.cs` is an `AModuleDefinition`; the parent engine repository's `Engine` project adds it with `AddModule<CoreModule>()` (`Engine/Engine.Project.cs:16`), and the `Editor` project gets it through its dependency on the `Engine` project.
- The repository root is the **module root**; `Sources/` is the compile root. The layout mirrors the other modules:

  ```text
  Core/
    Core.Module.cs
    Sources/
      **/*.cpp, *.h
  ```

- Platform-specific sources live under the path segments the build tool filters on (`Apple/`, `Google/`, `IOS/`, `Mac/`, `Microsoft/`, `Mobile/`), because inclusion is path-based; see the parent repository's `docs/architecture.md`.
- This directory is a git submodule. The parent repository pins a commit; changing Core without committing here does not change the parent's pin.

## Build role

- `ProjectTools` compiles `Core.Module.cs` and everything under `Sources/` into a dynamic library: `Core.dll` on Windows, `libCore.dylib` on Apple platforms (`Core.Module.cs:9`).
- The Windows toolchain injects `CORE_API` as `__declspec(dllexport)` when compiling Core and as `__declspec(dllimport)` for consumers (the Apple/Android toolchains define it empty). Anything a consumer must see from `Core.dll` has to be marked `CORE_API`, including the global instances (`GLogger`, `GTime`, `GResources`, `GMemory`, `GPath`, `GProcess`, `GEnvironment`).
- On Windows the module links `shell32.lib` and `ole32.lib` (`Core.Module.cs:13-17`); Android gets the `ANDROID_APPLICATION_PACKAGE` definition (`Core.Module.cs:19-23`).

## Rules for changing Core

- Change it minimally. It is shared lineage with `CppMobileFramework`; an API change here affects another codebase. Commit inside this submodule first, then update the parent pin.
- Missing-symbol policy: inspect the previous generation in the engine repository with `git show 62a0cbc^:Engine/Sources/Core/Sources/...`. If the old Core had the symbol, restore that shape here; otherwise adapt the engine to the new Core. Do not copy engine code into Core.
- Keep consumer-facing globals `CORE_API`. `GTime` and `GResources` once lacked it and were not exported from `Core.dll` (Core commit `10c64d7`).
- `GLogger.Fatal` throws `std::runtime_error` (`Sources/Logger/Logger.h:44-53`). Use `Log`/`Error` for recoverable conditions; `Fatal` is for unrecoverable programmer errors.
- `TMap::operator[]` fatals on a missing key and `Add` fatals on a duplicate; use `Find`/`Set` (`Sources/Templates/Map.h`).
- `TArray::Cast<T>()` is a raw byte reinterpretation, not a per-element conversion (`Sources/Templates/Array.h:338-355`).
- Smart-pointer headers are at `Sources/SmartPointer/`; `Templates/SharedPointers.h` and `Templates/SmartPointer/*` are gone. `TSharedPtr::Reset()` is private, so assign `nullptr`.
