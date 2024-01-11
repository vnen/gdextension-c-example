#include "gdexample.h"
#include "api.h"

#include <math.h>

void gdexample_init(GDExample *self)
{
    self->time_passed = 0.0;
    self->time_emit = 0.0;
    self->amplitude = 10.0;
    self->speed = 1.0;

    // Construct the StringName for the signal.
    constructors.string_name_new_with_utf8_chars(&self->position_changed, "position_changed");
}

void gdexample_terminate(GDExample *self)
{
    // Destruct the StringName for the signal.
    destructors.string_name_destructor(&self->position_changed);
}

void example_destructor(GDExample *self)
{
    // Destruct the StringName for the signal.
    destructors.string_name_destructor(&self->position_changed);
}

void gdexample_set_amplitude(GDExample *self, double amplitude)
{
    self->amplitude = amplitude;
}

double gdexample_get_amplitude(const GDExample *self)
{
    return self->amplitude;
}

void gdexample_set_speed(GDExample *self, double speed)
{
    self->speed = speed;
}

double gdexample_get_speed(const GDExample *self)
{
    return self->speed;
}

void gdexample_process(GDExample *self, double delta)
{
    self->time_passed += self->speed * delta;

    Vector2 new_position;

    // Set up the arguments for the Vector2 constructor.
    double x = self->amplitude + (self->amplitude * sin(self->time_passed * 2.0));
    double y = self->amplitude + (self->amplitude * cos(self->time_passed * 1.5));
    GDExtensionConstTypePtr args[] = {&x, &y};
    // Call the Vector2 constructor.
    constructors.vector2_constructor_x_y(&new_position, args);

    // Set up the arguments for the set_position method.
    GDExtensionConstTypePtr args2[] = {&new_position};
    // Call the set_position method.
    api.object_method_bind_ptrcall(methods.node2d_set_position, self->object, args2, NULL);

    self->time_emit += delta;
    if (self->time_emit >= 1.0)
    {
        // Call the emit_signal method.
        call_2_args_stringname_vector2_no_ret_variant(methods.object_emit_signal, self->object, &self->position_changed, &new_position);
        self->time_emit = 0.0;
    }
}

void gdexample_call_get_amplitude(void *method_userdata, GDExtensionClassInstancePtr p_instance, const GDExtensionConstVariantPtr *p_args, GDExtensionInt p_argument_count, GDExtensionVariantPtr r_return, GDExtensionCallError *r_error);

void gdexample_bind_methods()
{
    bind_method_0_r("GDExample", "get_amplitude", gdexample_get_amplitude, GDEXTENSION_VARIANT_TYPE_FLOAT);
    bind_method_1("GDExample", "set_amplitude", gdexample_set_amplitude, "amplitude", GDEXTENSION_VARIANT_TYPE_FLOAT);
    bind_property("GDExample", "amplitude", GDEXTENSION_VARIANT_TYPE_FLOAT, "get_amplitude", "set_amplitude");

    bind_method_0_r("GDExample", "get_speed", gdexample_get_speed, GDEXTENSION_VARIANT_TYPE_FLOAT);
    bind_method_1("GDExample", "set_speed", gdexample_set_speed, "speed", GDEXTENSION_VARIANT_TYPE_FLOAT);
    bind_property("GDExample", "speed", GDEXTENSION_VARIANT_TYPE_FLOAT, "get_speed", "set_speed");

    bind_signal_1("GDExample", "position_changed", "new_position", GDEXTENSION_VARIANT_TYPE_VECTOR2);
}

GDExtensionObjectPtr gdexample_create_instance(void *p_class_userdata)
{
    // Create native Godot object;
    StringName class_name;
    constructors.string_name_new_with_utf8_chars(&class_name, "Sprite2D");
    GDExtensionObjectPtr object = api.classdb_construct_object(&class_name);
    destructors.string_name_destructor(&class_name);

    // Create extension object.
    GDExample *self = (GDExample *)api.mem_alloc(sizeof(GDExample));
    gdexample_init(self);
    self->object = object;

    // Set the extension instance in the native Godot object.
    constructors.string_name_new_with_utf8_chars(&class_name, "GDExample");
    api.object_set_instance(object, &class_name, self);
    destructors.string_name_destructor(&class_name);

    return object;
}

void gdexample_free_instance(void *p_class_userdata, GDExtensionClassInstancePtr p_instance)
{
    if (p_instance == NULL)
    {
        return;
    }
    GDExample *self = (GDExample *)p_instance;
    gdexample_terminate(self);
    api.mem_free(self);
}

void *gdexample_get_virtual_with_data(void *p_class_userdata, GDExtensionConstStringNamePtr p_name)
{
    // If it is the "_process" method, return a pointer to the gdexample_process function.
    if (is_string_name_equal(p_name, "_process"))
    {
        return (void *)gdexample_process;
    }
    // Otherwise, return NULL.
    return NULL;
}

void gdexample_call_virtual_with_data(GDExtensionClassInstancePtr p_instance, GDExtensionConstStringNamePtr p_name, void *p_virtual_call_userdata, const GDExtensionConstTypePtr *p_args, GDExtensionTypePtr r_ret)
{
    // If it is the "_process" method, call it with a helper.
    if (is_string_name_equal(p_name, "_process"))
    {
        ptrcall_1_float_arg_no_ret(p_virtual_call_userdata, p_instance, p_args, r_ret);
    }
}
