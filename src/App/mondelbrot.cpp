#include "Base/GLWindow.hpp"

#include <QOpenGLShaderProgram>
#include <QtMath>

class MondelbrotWindow : public fgl::GLWindow {
	// c = p + iq
	double p_min = -1.5;
	double p_max = 1.5;
	double q_min = -1.5;
	double q_max = 1.5;

	// размеры окна?
	size_t a = 640;
	size_t b = 480;

	// Кол-во итерация, после которого будем проверять, ушли за границу или нет
	size_t max_iterations = 1000;

	// Граница, по которой проверяем
	size_t R = 10;
	std::unique_ptr<QOpenGLShaderProgram> program_ = nullptr;

	void init() {
		program_ = std::make_unique<QOpenGLShaderProgram>(this);
		program_->addShaderFromSourceCode(QOpenGLShader::Fragment, ":/Shaders/diffuse.fs");
	}

	void render() {
		// TODO: вынести логику в отдельную функцию или это должно быть на шейдере??
		double x_step = (p_max - p_min) / a;
		double y_step = (q_max - q_min) / b;

		for (size_t i = 0; i < a; ++i) {
			for (size_t j = 0; j < b; ++j) {
				// вычисляем координаты текущей `c` на декартовой плоскости
				double p = p_min + i * x_step;
				double q = q_min + j * y_step;

				double z_x = 0;
				double z_y = 0;
				// смотрим, что произойдёт с точкой через k итераций
				for (size_t k = 0; k < max_iterations; ++k) {
					// x_{k+1} = x_k^2 - y_k^2 + p
					z_x = z_x * z_x - z_y * z_y + p;

					// y_{k+1} = 2 * x_k * y_k + q
					z_y = 2 * z_x * z_y + q;

					// вышла за границу --- перекрашиваем в цвет итерации
					if (qSqrt(z_x * z_x + z_y * z_y) > R) {
						// TODO: ставим ей не чёрный цвет
					}
				}
			}
		}
	}
};