#version 330

in vec2 in_position;
in vec4 in_color;

out vec4 color;

void main(void) {
    gl_Position = vec4(in_position, 0.5f, 1.0f);

    color = in_color;
}
