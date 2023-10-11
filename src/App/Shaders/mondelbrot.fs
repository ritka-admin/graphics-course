#version 330 core

uniform vec4 pqs;
uniform vec4 steps;
uniform size_t max_iterations;

out vec4 fragment_color;


void main() {
    float cur_x = gl_FragCoord.x;
    float cur_y = gl_FragCoord.y;

    float p_min = pqs.x;
    float p_max = pqs.y;
    float q_min = pqs.z;
    float q_max = pqs.w;

    float p = p_min + cur_x * steps.x;
    float q = q_min + cur_y * steps.y;

    float z_x = 0;
    float z_y = 0;
    for (int k = 0; k < max_iterations; ++k) {
        z_x = z_x * z_x - z_y * z_y + p;

        z_y = 2 * z_x * z_y + q;

        if (qSqrt(z_x * z_x + z_y * z_y) > R) {
            fragment_color = (k % 255., k % 255., k % 255., 1.);
            break;
        }
    }
    fragment_color = (0., 0., 0., 1.);
}
