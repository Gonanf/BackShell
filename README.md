# BackShell

> Cliente malicioso, son herramientas de spyware para windows
> **Lenguaje principal (GitHub):** C++ · **URL:** https://github.com/Gonanf/BackShell

## Qué es

Este repositorio forma parte de la colección de **Gonanf / Gabriel Solotorevsky** clonada en `/run/media/chaos/terciario/proyectos/BackShell`.

- **Path absoluto:** `/run/media/chaos/terciario/proyectos/BackShell`
- **Estado git:** último commit `2024-08-06 CHANGELOG: Se simplifico la conexion con el server Se removio OpenCV a favor de stb Se añadio titulos a los sistemas`
- **Archivos (aprox):** 276
- **Stack detectado:** C++ (CMake)

## Stack

- C++ (CMake)

## Estructura

```
BackShell/
.vscode/
  .vscode/c_cpp_properties.json
  .vscode/settings.json
CMakeLists.txt
build/
  build/ALL_BUILD.vcxproj
  build/ALL_BUILD.vcxproj.filters
  build/BackShell.dir
  build/BackShell.sln
  build/BackShell.vcxproj
  build/BackShell.vcxproj.filters
  build/CMakeCache.txt
  build/CMakeFiles
src/
  src/connections.hpp
  src/errors.hpp
  src/key_logger.cpp
  src/main.cpp
  src/reverse_shell.cpp
  src/stb_image.h
```

## Cómo correr

> Instrucciones genéricas según el stack detectado. Ajustar según el repo.

```bash
cmake -B build && cmake --build build
./build/<binario>
```

## Estado

- **Último commit:** `2024-08-06 CHANGELOG: Se simplifico la conexion con el server Se removio OpenCV a favor de stb Se añadio titulos a los sistemas`
- **Clonado en:** `/run/media/chaos/terciario/proyectos/BackShell`
- **Exclusiones del lote:** Forks, Workmatch, el-hornero-digital, mali/meli, Sherut (no tocados por consigna)

## Docs

- `docs/overview.md` — descripción extendida y guía rápida (generado en este lote)


---
*README generado/mejorado automáticamente el 2026-09-04 con inspección de repo (opencode/agy pattern: lectura de estructura, lenguaje y entrypoints). No se modificó código, solo documentación.*
*Autor original: Gonanf — https://github.com/Gonanf/BackShell*
