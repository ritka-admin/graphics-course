#version 330 core

uniform vec4 pqs;
uniform vec2 steps;
uniform int max_iterations;
uniform int R;

out vec4 fragment_color;


void main() {
    // от -2 до 2
    float cur_x = 4*(gl_FragCoord.x/steps.x - 0.5);
    float cur_y = 4*(gl_FragCoord.y/steps.y - 0.5);

    float p = cur_x;
    float q = cur_y;

    float z_x = 0;
    float z_y = 0;
    for (int k = 0; k < max_iterations; ++k) {
        z_x = z_x * z_x - z_y * z_y + p;
        z_y = 2 * z_x * z_y + q;

        float res = sqrt(z_x * z_x + z_y * z_y);
        if (res > R) {
            fragment_color = vec4(k, 0, 0, 1.);
            return;
        }
    }
    fragment_color = vec4(0., 0., 0., 1.);
}
