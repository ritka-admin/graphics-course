#version 330 core

uniform vec2 screen;
uniform int max_iterations;
uniform int R;
uniform vec2 scale;
uniform vec2 center;

out vec4 frag_color;


void main() {
    float cur_x = scale.x * (gl_FragCoord.x/screen.x - 0.5) - center.x;
    float cur_y = scale.y * (gl_FragCoord.y/screen.y - 0.5) - center.y;

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

    vec3 colors = k == max_iterations ? vec3(0., 0., 0.) : vec3((float(k) / 50.));
    frag_color = vec4(colors.rgb, 1);
}
