#ifndef API_H
#define API_H

/*
This file works as a collection of helpers to call the GDExtension API
in a less verbose way, as well as a cache for methods from the discovery API,
just so we don't have to keep loading the same methods again.
*/

#include "gdextension_interface.h"

#include "defs.h"

extern GDExtensionClassLibraryPtr class_library;

// API methods.

struct Constructors
{
    GDExtensionPtrConstructor vector2_constructor_x_y;
    GDExtensionInterfaceStringNewWithUtf8Chars string_new_with_utf8_chars;
    GDExtensionInterfaceStringNameNewWithUtf8Chars string_name_new_with_utf8_chars;
    GDExtensionVariantFromTypeConstructorFunc variant_from_float_constructor;
    GDExtensionTypeFromVariantConstructorFunc float_from_variant_constructor;
    GDExtensionVariantFromTypeConstructorFunc variant_from_string_name_constructor;
    GDExtensionVariantFromTypeConstructorFunc variant_from_vector2_constructor;
} constructors;

struct Destructors
{
    GDExtensionPtrDestructor string_destructor;
    GDExtensionPtrDestructor string_name_destructor;
    GDExtensionInterfaceVariantDestroy variant_destroy;
} destructors;

struct Operators
{
    GDExtensionPtrOperatorEvaluator string_name_equal;
} operators;

struct Methods
{
    GDExtensionMethodBindPtr object_emit_signal;
    GDExtensionMethodBindPtr node2d_set_position;
} methods;

struct API
{
    GDExtensionInterfaceObjectMethodBindCall object_method_bind_call;
    GDExtensionInterfaceClassdbRegisterExtensionClass2 classdb_register_extension_class2;
    GDExtensionInterfaceClassdbConstructObject classdb_construct_object;
    GDExtensionInterfaceObjectSetInstance object_set_instance;
    GDExtensionInterfaceMemAlloc mem_alloc;
    GDExtensionInterfaceMemFree mem_free;
    GDExtensionInterfaceGetVariantFromTypeConstructor get_variant_from_type_constructor;
    GDExtensionInterfaceGetVariantToTypeConstructor get_variant_to_type_constructor;
    GDExtensionInterfaceVariantGetType variant_get_type;
    GDExtensionInterfaceClassdbRegisterExtensionClassMethod classdb_register_extension_class_method;
    GDExtensionInterfaceClassdbRegisterExtensionClassProperty classdb_register_extension_class_property;
    GDExtensionInterfaceClassdbGetMethodBind classdb_get_method_bind;
    GDExtensionInterfaceObjectMethodBindPtrcall object_method_bind_ptrcall;
    GDExtensionInterfaceClassdbRegisterExtensionClassSignal classdb_register_extension_class_signal;
} api;

// Helpers.
// The methods here are tailored for this specific example and aren't meant
// for general usage, but they show how to use the API.

// Compare a StringName with a C string.
bool is_string_name_equal(GDExtensionConstStringNamePtr p_a, const char *p_b);

// Create a PropertyInfo struct.
GDExtensionPropertyInfo make_property(
    GDExtensionVariantType type,
    const char *name);

GDExtensionPropertyInfo make_property_full(
    GDExtensionVariantType type,
    const char *name,
    uint32_t hint,
    const char *hint_string,
    const char *class_name,
    uint32_t usage_flags);

void destruct_property(GDExtensionPropertyInfo *info);

// Version for 0 arguments, no return.
void bind_method_0(
    const char *class_name,
    const char *method_name,
    void *function);

// Version for 0 arguments, with return.
void bind_method_0_r(
    const char *class_name,
    const char *method_name,
    void *function,
    GDExtensionVariantType return_type);

// Version for 1 argument, no return.
void bind_method_1(
    const char *class_name,
    const char *method_name,
    void *function,
    const char *arg1_name,
    GDExtensionVariantType arg1_type);

void bind_property(
    const char *class_name,
    const char *name,
    GDExtensionVariantType type,
    const char *getter,
    const char *setter);

// Version for 1 argument.
void bind_signal_1(
    const char *class_name,
    const char *signal_name,
    const char *arg1_name,
    GDExtensionVariantType arg1_type);

// Helpers for calling functions.
void call_0_args_no_ret(void *method_userdata, GDExtensionClassInstancePtr p_instance, const GDExtensionConstVariantPtr *p_args, GDExtensionInt p_argument_count, GDExtensionVariantPtr r_return, GDExtensionCallError *r_error);
void call_0_args_ret_float(void *method_userdata, GDExtensionClassInstancePtr p_instance, const GDExtensionConstVariantPtr *p_args, GDExtensionInt p_argument_count, GDExtensionVariantPtr r_return, GDExtensionCallError *r_error);
void call_1_float_arg_no_ret(void *method_userdata, GDExtensionClassInstancePtr p_instance, const GDExtensionConstVariantPtr *p_args, GDExtensionInt p_argument_count, GDExtensionVariantPtr r_return, GDExtensionCallError *r_error);

// Helpers for ptrcall functions.
void ptrcall_0_args_no_ret(void *method_userdata, GDExtensionClassInstancePtr p_instance, const GDExtensionConstTypePtr *p_args, GDExtensionTypePtr r_ret);
void ptrcall_0_args_ret_float(void *method_userdata, GDExtensionClassInstancePtr p_instance, const GDExtensionConstTypePtr *p_args, GDExtensionTypePtr r_ret);
void ptrcall_1_float_arg_no_ret(void *method_userdata, GDExtensionClassInstancePtr p_instance, const GDExtensionConstTypePtr *p_args, GDExtensionTypePtr r_ret);

// Helpers for virtual functions.
void ptrcall_1_float_arg_no_ret_virtual(GDExtensionClassInstancePtr p_instance, const GDExtensionConstTypePtr *p_args, GDExtensionTypePtr r_ret);

// Helper to call with Variant arguments.
void call_2_args_stringname_vector2_no_ret_variant(GDExtensionMethodBindPtr p_method_bind, GDExtensionObjectPtr p_instance, const GDExtensionTypePtr p_arg1, const GDExtensionTypePtr p_arg2);

void load_api(GDExtensionInterfaceGetProcAddress p_get_proc_address);

#endif // API_H
