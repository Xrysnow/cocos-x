#pragma once

// Private bridge compiled into the pinned GLFW target. Calls are on GLFW's window thread.
#ifdef __cplusplus
extern "C" {
#endif

struct GLFWwindow;
typedef struct CcGlfwX11TextInput CcGlfwX11TextInput;

CcGlfwX11TextInput* cc_glfw_x11_text_input_create(struct GLFWwindow* window);
void cc_glfw_x11_text_input_destroy(CcGlfwX11TextInput* input);
void cc_glfw_x11_text_input_begin(CcGlfwX11TextInput* input);
void cc_glfw_x11_text_input_end(CcGlfwX11TextInput* input);
int cc_glfw_x11_text_input_has_anchor(CcGlfwX11TextInput* input);
void cc_glfw_x11_text_input_set_spot(CcGlfwX11TextInput* input, int hasSpot, short x, short y);
void cc_glfw_x11_text_input_refresh(CcGlfwX11TextInput* input);

int cc_glfw_x11_text_input_key_consumed(struct GLFWwindow* window);
void cc_glfw_x11_text_input_finish_poll(void);

#ifdef __cplusplus
}
#endif
