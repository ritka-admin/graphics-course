#version 330 core

// uniform vec4 pqs;
uniform vec2 steps;
uniform int max_iterations;
uniform int R;

// out vec4 fragment_color;

void main() {
    // от -2 до 2
    float cur_x = 3*(gl_FragCoord.x/steps.x - 0.5);
    float cur_y = 3*(gl_FragCoord.y/steps.y - 0.5);

    float p = cur_x;
    float q = cur_y;

    vec2 z;
    z.x = p;
    z.y = q;
    int k;
    for (k = 0; k < max_iterations; ++k) {
        float x = z.x * z.x - z.y * z.y + p;
        float y = (z.y * z.x + z.x * z.y) + q;

        float res = sqrt(x * x + y * y);
        if (res > R) {
            break;
        }

        z.x = x;
        z.y = y;
    }

//     gl_FragColor = vec4(0, 0, 0, 1.);
    gl_FragColor = vec4(vec3((k == max_iterations ? 0.0 : float(k) / 100.)), 1);
}
