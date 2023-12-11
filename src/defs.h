#ifndef DEFS_H
#define DEFS_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#if !defined(GDE_EXPORT)
#if defined(_WIN32)
#define GDE_EXPORT __declspec(dllexport)
#elif defined(__GNUC__)
#define GDE_EXPORT __attribute__((visibility("default")))
#else
#define GDE_EXPORT
#endif
#endif

// The sizes can be obtained from the extension_api.json file.
#ifdef REAL_T_IS_DOUBLE
#define VARIANT_SIZE 40
#define VECTOR2_SIZE 16
#else
#define VARIANT_SIZE 24
#define VECTOR2_SIZE 8
#endif

#ifdef BUILD_32
#define STRING_SIZE 4
#define STRING_NAME_SIZE 4
#else
#define STRING_SIZE 8
#define STRING_NAME_SIZE 8
#endif

// Types.

typedef struct
{
    uint8_t data[VARIANT_SIZE];
} Variant;

typedef struct
{
    uint8_t data[VECTOR2_SIZE];
} Vector2;

typedef struct
{
    uint8_t data[STRING_SIZE];
} String;

typedef struct
{
    uint8_t data[STRING_NAME_SIZE];
} StringName;

// Enums.

typedef enum
{
    PROPERTY_HINT_NONE = 0,
} PropertyHint;

typedef enum
{
    PROPERTY_USAGE_NONE = 0,
    PROPERTY_USAGE_STORAGE = 2,
    PROPERTY_USAGE_EDITOR = 4,
    PROPERTY_USAGE_DEFAULT = PROPERTY_USAGE_STORAGE | PROPERTY_USAGE_EDITOR,
} PropertyUsageFlags;

#endif // DEFS_H
