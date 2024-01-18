#include "api.h"

GDExtensionClassLibraryPtr class_library = NULL;

struct Constructors constructors;
struct Destructors destructors;
struct Operators operators;
struct Methods methods;
struct API api;

GDExtensionPropertyInfo make_property_full(
    GDExtensionVariantType type,
    const char *name,
    uint32_t hint,
    const char *hint_string,
    const char *class_name,
    uint32_t usage_flags)
{

    StringName *prop_name = api.mem_alloc(sizeof(StringName));
    constructors.string_name_new_with_utf8_chars(prop_name, name);
    String *prop_hint_string = api.mem_alloc(sizeof(String));
    constructors.string_new_with_utf8_chars(prop_hint_string, hint_string);
    StringName *prop_class_name = api.mem_alloc(sizeof(StringName));
    constructors.string_name_new_with_utf8_chars(prop_class_name, class_name);

    GDExtensionPropertyInfo info = {
        .name = prop_name,
        .type = type,
        .hint = hint,
        .hint_string = prop_hint_string,
        .class_name = prop_class_name,
        .usage = usage_flags,
    };

    return info;
}

bool is_string_name_equal(GDExtensionConstStringNamePtr p_a, const char *p_b)
{
    // Create a StringName for the C string.
    StringName string_name;
    constructors.string_name_new_with_utf8_chars(&string_name, p_b);

    // Compare both StringNames.
    bool is_equal = false;
    operators.string_name_equal(p_a, &string_name, &is_equal);

    // Destroy the created StringName.
    destructors.string_name_destructor(&string_name);

    // Return the result.
    return is_equal;
}

GDExtensionPropertyInfo make_property(
    GDExtensionVariantType type,
    const char *name)
{

    return make_property_full(type, name, PROPERTY_HINT_NONE, "", "", PROPERTY_USAGE_DEFAULT);
}

void destruct_property(GDExtensionPropertyInfo *info)
{
    destructors.string_name_destructor(info->name);
    destructors.string_destructor(info->hint_string);
    destructors.string_name_destructor(info->class_name);
    api.mem_free(info->name);
    api.mem_free(info->hint_string);
    api.mem_free(info->class_name);
}

// Version for 0 arguments, no return.
void bind_method_0(
    const char *class_name,
    const char *method_name,
    void *function)
{

    StringName method_name_string;
    constructors.string_name_new_with_utf8_chars(&method_name_string, method_name);

    GDExtensionClassMethodCall call_func = call_0_args_no_ret;
    GDExtensionClassMethodPtrCall ptrcall_func = ptrcall_0_args_no_ret;

    GDExtensionClassMethodInfo method_info = {
        .name = &method_name_string,
        .method_userdata = function,
        .call_func = call_func,
        .ptrcall_func = ptrcall_func,
        .method_flags = GDEXTENSION_METHOD_FLAGS_DEFAULT,
        .has_return_value = false,
        .argument_count = 0,
    };

    StringName class_name_string;
    constructors.string_name_new_with_utf8_chars(&class_name_string, class_name);

    api.classdb_register_extension_class_method(class_library, &class_name_string, &method_info);

    // Destruct strings.
    destructors.string_name_destructor(&method_name_string);
    destructors.string_name_destructor(&class_name_string);
}

// Version for 0 arguments, with return.
void bind_method_0_r(
    const char *class_name,
    const char *method_name,
    void *function,
    GDExtensionVariantType return_type)
{
    StringName method_name_string;
    constructors.string_name_new_with_utf8_chars(&method_name_string, method_name);

    GDExtensionClassMethodCall call_func = call_0_args_ret_float;
    GDExtensionClassMethodPtrCall ptrcall_func = ptrcall_0_args_ret_float;

    GDExtensionPropertyInfo return_info = make_property(return_type, "");

    GDExtensionClassMethodInfo method_info = {
        .name = &method_name_string,
        .method_userdata = function,
        .call_func = call_func,
        .ptrcall_func = ptrcall_func,
        .method_flags = GDEXTENSION_METHOD_FLAGS_DEFAULT,
        .has_return_value = true,
        .return_value_info = &return_info,
        .return_value_metadata = GDEXTENSION_METHOD_ARGUMENT_METADATA_NONE,
        .argument_count = 0,
    };

    StringName class_name_string;
    constructors.string_name_new_with_utf8_chars(&class_name_string, class_name);

    api.classdb_register_extension_class_method(class_library, &class_name_string, &method_info);

    // Destruct things.
    destructors.string_name_destructor(&method_name_string);
    destructors.string_name_destructor(&class_name_string);
    destruct_property(&return_info);
}

// Version for 1 argument, no return.
void bind_method_1(
    const char *class_name,
    const char *method_name,
    void *function,
    const char *arg1_name,
    GDExtensionVariantType arg1_type)
{

    StringName method_name_string;
    constructors.string_name_new_with_utf8_chars(&method_name_string, method_name);

    GDExtensionClassMethodCall call_func = call_1_float_arg_no_ret;
    GDExtensionClassMethodPtrCall ptrcall_func = ptrcall_1_float_arg_no_ret;

    GDExtensionPropertyInfo args_info[] = {
        make_property(arg1_type, arg1_name),
    };
    GDExtensionClassMethodArgumentMetadata args_metadata[] = {
        GDEXTENSION_METHOD_ARGUMENT_METADATA_NONE,
    };

    GDExtensionClassMethodInfo method_info = {
        .name = &method_name_string,
        .method_userdata = function,
        .call_func = call_func,
        .ptrcall_func = ptrcall_func,
        .method_flags = GDEXTENSION_METHOD_FLAGS_DEFAULT,
        .has_return_value = false,
        .argument_count = 1,
        .arguments_info = args_info,
        .arguments_metadata = args_metadata,
    };

    StringName class_name_string;
    constructors.string_name_new_with_utf8_chars(&class_name_string, class_name);

    api.classdb_register_extension_class_method(class_library, &class_name_string, &method_info);

    // Destruct things.
    destructors.string_name_destructor(&method_name_string);
    destructors.string_name_destructor(&class_name_string);
    destruct_property(&args_info[0]);
}

void bind_property(
    const char *class_name,
    const char *name,
    GDExtensionVariantType type,
    const char *getter,
    const char *setter)
{
    StringName class_string_name;
    constructors.string_name_new_with_utf8_chars(&class_string_name, class_name);
    GDExtensionPropertyInfo info = make_property(type, name);
    StringName getter_name;
    constructors.string_name_new_with_utf8_chars(&getter_name, getter);
    StringName setter_name;
    constructors.string_name_new_with_utf8_chars(&setter_name, setter);

    api.classdb_register_extension_class_property(class_library, &class_string_name, &info, &setter_name, &getter_name);

    // Destruct things.
    destructors.string_name_destructor(&class_string_name);
    destruct_property(&info);
    destructors.string_name_destructor(&getter_name);
    destructors.string_name_destructor(&setter_name);
}

// Version for 1 argument.
void bind_signal_1(
    const char *class_name,
    const char *signal_name,
    const char *arg1_name,
    GDExtensionVariantType arg1_type)
{
    StringName class_string_name;
    constructors.string_name_new_with_utf8_chars(&class_string_name, class_name);
    StringName signal_string_name;
    constructors.string_name_new_with_utf8_chars(&signal_string_name, signal_name);

    GDExtensionPropertyInfo args_info[] = {
        make_property(arg1_type, arg1_name),
    };

    api.classdb_register_extension_class_signal(class_library, &class_string_name, &signal_string_name, args_info, 1);

    // Destruct things.
    destructors.string_name_destructor(&class_string_name);
    destructors.string_name_destructor(&signal_string_name);
    destruct_property(&args_info[0]);
}

void ptrcall_0_args_no_ret(void *method_userdata, GDExtensionClassInstancePtr p_instance, const GDExtensionConstTypePtr *p_args, GDExtensionTypePtr r_ret)
{
    // Call the function.
    void (*function)(void *) = method_userdata;
    function(p_instance);
}

void ptrcall_0_args_ret_float(void *method_userdata, GDExtensionClassInstancePtr p_instance, const GDExtensionConstTypePtr *p_args, GDExtensionTypePtr r_ret)
{
    // Call the function.
    double (*function)(void *) = method_userdata;
    *((double *)r_ret) = function(p_instance);
}

void ptrcall_1_float_arg_no_ret(void *method_userdata, GDExtensionClassInstancePtr p_instance, const GDExtensionConstTypePtr *p_args, GDExtensionTypePtr r_ret)
{
    // Call the function.
    void (*function)(void *, double) = method_userdata;
    function(p_instance, *((double *)p_args[0]));
}

void call_0_args_no_ret(void *method_userdata, GDExtensionClassInstancePtr p_instance, const GDExtensionConstVariantPtr *p_args, GDExtensionInt p_argument_count, GDExtensionVariantPtr r_return, GDExtensionCallError *r_error)
{
    // Call the function.
    void (*function)(void *) = method_userdata;
    function(p_instance);
}

void call_0_args_ret_float(void *method_userdata, GDExtensionClassInstancePtr p_instance, const GDExtensionConstVariantPtr *p_args, GDExtensionInt p_argument_count, GDExtensionVariantPtr r_return, GDExtensionCallError *r_error)
{
    // Check argument count.
    if (p_argument_count != 0)
    {
        r_error->error = GDEXTENSION_CALL_ERROR_TOO_MANY_ARGUMENTS;
        r_error->expected = 0;
        return;
    }

    // Call the function.
    double (*function)(void *) = method_userdata;
    double result = function(p_instance);
    // Set resulting Variant.
    constructors.variant_from_float_constructor(r_return, &result);
}

void call_1_float_arg_no_ret(void *method_userdata, GDExtensionClassInstancePtr p_instance, const GDExtensionConstVariantPtr *p_args, GDExtensionInt p_argument_count, GDExtensionVariantPtr r_return, GDExtensionCallError *r_error)
{
    // Check argument count.
    if (p_argument_count < 1)
    {
        r_error->error = GDEXTENSION_CALL_ERROR_TOO_FEW_ARGUMENTS;
        r_error->expected = 1;
        return;
    }
    else if (p_argument_count > 1)
    {
        r_error->error = GDEXTENSION_CALL_ERROR_TOO_MANY_ARGUMENTS;
        r_error->expected = 1;
        return;
    }

    // Check the argument type.
    GDExtensionVariantType type = api.variant_get_type(p_args[0]);
    if (type != GDEXTENSION_VARIANT_TYPE_FLOAT)
    {
        r_error->error = GDEXTENSION_CALL_ERROR_INVALID_ARGUMENT;
        r_error->expected = GDEXTENSION_VARIANT_TYPE_FLOAT;
        r_error->argument = 0;
        return;
    }

    // Extract the argument.
    double arg1;
    constructors.float_from_variant_constructor(&arg1, (GDExtensionVariantPtr)p_args[0]);

    // Call the function.
    void (*function)(void *, double) = method_userdata;
    function(p_instance, arg1);
}

void call_2_args_stringname_vector2_no_ret_variant(GDExtensionMethodBindPtr p_method_bind, GDExtensionObjectPtr p_instance, const GDExtensionTypePtr p_arg1, const GDExtensionTypePtr p_arg2)
{
    // Set up the arguments for the call.
    Variant arg1;
    constructors.variant_from_string_name_constructor(&arg1, p_arg1);
    Variant arg2;
    constructors.variant_from_vector2_constructor(&arg2, p_arg2);
    GDExtensionConstVariantPtr args[] = {&arg1, &arg2};

    // Add dummy return value storage.
    Variant ret;

    // Call the function.
    api.object_method_bind_call(p_method_bind, p_instance, args, 2, &ret, NULL);

    // Destroy the arguments that need it.
    destructors.variant_destroy(&arg1);
    destructors.variant_destroy(&ret);
}

void load_api(GDExtensionInterfaceGetProcAddress p_get_proc_address)
{
    // Get helper functions first.
    GDExtensionInterfaceVariantGetPtrConstructor variant_get_ptr_constructor = (GDExtensionInterfaceVariantGetPtrConstructor)p_get_proc_address("variant_get_ptr_constructor");
    GDExtensionInterfaceVariantGetPtrDestructor variant_get_ptr_destructor = (GDExtensionInterfaceVariantGetPtrDestructor)p_get_proc_address("variant_get_ptr_destructor");
    GDExtensionInterfaceVariantGetPtrOperatorEvaluator variant_get_ptr_operator_evaluator = (GDExtensionInterfaceVariantGetPtrOperatorEvaluator)p_get_proc_address("variant_get_ptr_operator_evaluator");

    // API.
    api.classdb_get_method_bind = (GDExtensionInterfaceClassdbGetMethodBind)p_get_proc_address("classdb_get_method_bind");
    api.object_method_bind_call = p_get_proc_address("object_method_bind_call");
    api.object_method_bind_ptrcall = p_get_proc_address("object_method_bind_ptrcall");
    api.classdb_register_extension_class2 = p_get_proc_address("classdb_register_extension_class2");
    api.classdb_register_extension_class_property = p_get_proc_address("classdb_register_extension_class_property");
    api.classdb_register_extension_class_method = p_get_proc_address("classdb_register_extension_class_method");
    api.classdb_register_extension_class_signal = p_get_proc_address("classdb_register_extension_class_signal");
    api.classdb_construct_object = (GDExtensionInterfaceClassdbConstructObject)p_get_proc_address("classdb_construct_object");
    api.object_set_instance = p_get_proc_address("object_set_instance");
    api.get_variant_from_type_constructor = (GDExtensionInterfaceGetVariantFromTypeConstructor)p_get_proc_address("get_variant_from_type_constructor");
    api.get_variant_to_type_constructor = (GDExtensionInterfaceGetVariantToTypeConstructor)p_get_proc_address("get_variant_to_type_constructor");
    api.variant_get_type = (GDExtensionInterfaceVariantGetType)p_get_proc_address("variant_get_type");
    api.mem_alloc = (GDExtensionInterfaceMemAlloc)p_get_proc_address("mem_alloc");
    api.mem_free = (GDExtensionInterfaceMemFree)p_get_proc_address("mem_free");

    // Constructors.
    constructors.vector2_constructor_x_y = variant_get_ptr_constructor(GDEXTENSION_VARIANT_TYPE_VECTOR2, 3); // See extension_api.json for indices.
    constructors.string_new_with_utf8_chars = p_get_proc_address("string_new_with_utf8_chars");
    constructors.string_name_new_with_utf8_chars = p_get_proc_address("string_name_new_with_utf8_chars");
    constructors.variant_from_float_constructor = api.get_variant_from_type_constructor(GDEXTENSION_VARIANT_TYPE_FLOAT);
    constructors.float_from_variant_constructor = api.get_variant_to_type_constructor(GDEXTENSION_VARIANT_TYPE_FLOAT);
    constructors.variant_from_string_name_constructor = api.get_variant_from_type_constructor(GDEXTENSION_VARIANT_TYPE_STRING_NAME);
    constructors.variant_from_vector2_constructor = api.get_variant_from_type_constructor(GDEXTENSION_VARIANT_TYPE_VECTOR2);

    // Destructors.
    destructors.string_destructor = variant_get_ptr_destructor(GDEXTENSION_VARIANT_TYPE_STRING);
    destructors.string_name_destructor = variant_get_ptr_destructor(GDEXTENSION_VARIANT_TYPE_STRING_NAME);
    destructors.variant_destroy = p_get_proc_address("variant_destroy");

    // Operators.
    operators.string_name_equal = variant_get_ptr_operator_evaluator(GDEXTENSION_VARIANT_OP_EQUAL, GDEXTENSION_VARIANT_TYPE_STRING_NAME, GDEXTENSION_VARIANT_TYPE_STRING_NAME);
}
