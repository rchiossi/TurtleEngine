#version 330

precision highp float;

in vec4 color;

void main(void)
{
    gl_FragColor = vec4(color);
}

