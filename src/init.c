#include "init.h"

#include "api.h"
#include "gdexample.h"

void initialize_gdexample_module(void *p_userdata, GDExtensionInitializationLevel p_level)
{
    if (p_level != GDEXTENSION_INITIALIZATION_SCENE)
    {
        return;
    }

    // Get ClassDB methods here because the classes are all properly registered.
    // Check extension_api.json for hashes.
    StringName native_class_name;
    StringName method_name;

    constructors.string_name_new_with_utf8_chars(&native_class_name, "Object");
    constructors.string_name_new_with_utf8_chars(&method_name, "emit_signal");
    methods.object_emit_signal = api.classdb_get_method_bind(&native_class_name, &method_name, 4047867050);
    destructors.string_name_destructor(&native_class_name);
    destructors.string_name_destructor(&method_name);

    constructors.string_name_new_with_utf8_chars(&native_class_name, "Node2D");
    constructors.string_name_new_with_utf8_chars(&method_name, "set_position");
    methods.node2d_set_position = api.classdb_get_method_bind(&native_class_name, &method_name, 743155724);
    destructors.string_name_destructor(&native_class_name);
    destructors.string_name_destructor(&method_name);

    // Register class.
    StringName class_name;
    constructors.string_name_new_with_utf8_chars(&class_name, "GDExample");
    StringName parent_class_name;
    constructors.string_name_new_with_utf8_chars(&parent_class_name, "Sprite2D");

    GDExtensionClassCreationInfo2 class_info = {
        .is_virtual = false,
        .is_abstract = false,
        .is_exposed = true,
        .set_func = NULL,
        .get_func = NULL,
        .get_property_list_func = NULL,
        .free_property_list_func = NULL,
        .property_can_revert_func = NULL,
        .property_get_revert_func = NULL,
        .validate_property_func = NULL,
        .notification_func = NULL,
        .to_string_func = NULL,
        .reference_func = NULL,
        .unreference_func = NULL,
        .create_instance_func = gdexample_create_instance,
        .free_instance_func = gdexample_free_instance,
        .recreate_instance_func = NULL,
        .get_virtual_func = gdexample_get_virtual,
        .get_virtual_call_data_func = NULL,
        .call_virtual_with_data_func = NULL,
        .get_rid_func = NULL,
        .class_userdata = NULL,
    };

    api.classdb_register_extension_class2(class_library, &class_name, &parent_class_name, &class_info);

    // Bind methods.
    gdexample_bind_methods();

    // Destruct things.
    destructors.string_name_destructor(&class_name);
    destructors.string_name_destructor(&parent_class_name);
}

void deinitialize_gdexample_module(void *p_userdata, GDExtensionInitializationLevel p_level)
{
}

GDExtensionBool GDE_EXPORT gdexample_library_init(GDExtensionInterfaceGetProcAddress p_get_proc_address, GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization)
{
    class_library = p_library;
    load_api(p_get_proc_address);

    r_initialization->initialize = initialize_gdexample_module;
    r_initialization->deinitialize = deinitialize_gdexample_module;
    r_initialization->userdata = NULL;
    r_initialization->minimum_initialization_level = GDEXTENSION_INITIALIZATION_SCENE;

    return true;
}
