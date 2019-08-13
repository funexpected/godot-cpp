#ifndef GODOT_GLOBAL_HPP
#define GODOT_GLOBAL_HPP

#include "Array.hpp"
#include "String.hpp"
#include <gdnative_api_struct.gen.h>

#ifndef GDNLIB_PREFIX
#define GDNLIB_PREFIX
#endif
#define GDNLIB_PASTER(x,y) x ## y
#define GDNLIB_EVALUATOR(x,y)  GDNLIB_PASTER(x,y)
#define GDNLIB_NAME(fun) GDNLIB_EVALUATOR(GDNLIB_PREFIX, fun)

namespace godot {

extern "C" const godot_gdnative_core_api_struct *api;
extern "C" const godot_gdnative_core_1_1_api_struct *core_1_1_api;
extern "C" const godot_gdnative_ext_nativescript_api_struct *nativescript_api;
extern "C" const godot_gdnative_ext_nativescript_1_1_api_struct *nativescript_1_1_api;

extern "C" const void *GDNLIB_NAME(gdnlib);
extern "C" void *GDNLIB_NAME(nativescript_handle);

class Godot {

public:
	static void print(const String &message);
	static void print_warning(const String &description, const String &function, const String &file, int line);
	static void print_error(const String &description, const String &function, const String &file, int line);

	static void gdnative_init(godot_gdnative_init_options *o);
	static void gdnative_terminate(godot_gdnative_terminate_options *o);
	static void nativescript_init(void *handle);
	static void nativescript_terminate(void *handle);

	static void gdnative_profiling_add_data(const char *p_signature, uint64_t p_time);

	template <class... Args>
	static void print(const String &fmt, Args... values) {
		print(fmt.format(Array::make(values...)));
	}
};

struct _RegisterState {
	static int language_index;
};

} // namespace godot

#endif
