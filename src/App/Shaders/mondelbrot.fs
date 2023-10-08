#version 330 core

int int iteration;
out vec4 fragment_color;

void main() {
    // choose color depending on iteration
	out_col = vec4(iteration % 255, iteration % 255, iteration % 255, 1.0);
}