#version 330 core

uniform vec2 screen;
uniform int max_iterations;
uniform int R;
uniform int scale;
uniform vec2 shift;


void main() {
    float cur_x = scale * (gl_FragCoord.x/screen.x - shift.x);
    float cur_y = scale * (gl_FragCoord.y/screen.y - shift.y);

    float p = cur_x;
    float q = cur_y;

    vec2 z;
    z.x = 0;
    z.y = 0;
    int k;
    for (k = 0; k < max_iterations; ++k) {
        float x = z.x * z.x - z.y * z.y + p;
        float y = z.y * z.x + z.x * z.y + q;

        float res = sqrt(x * x + y * y);
        if (res > R) {
            break;
        }

        z.x = x;
        z.y = y;
    }

    gl_FragColor = vec4(vec3((k == max_iterations ? 0.0 : float(k) / 100.)), 1);
}
