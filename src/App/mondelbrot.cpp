#include "Base/GLWindow.hpp"
#include "mondelbrot.h"

#include <QOpenGLShaderProgram>
#include <QtMath>

void MondelbrotWindow::init() {
		program_ = std::make_unique<QOpenGLShaderProgram>(this);
//		program_->addShaderFromSourceCode(QOpenGLShader::Vertex, ":/Shaders/mondelbrot.vs");
//		program_->addShaderFromSourceCode(QOpenGLShader::Fragment, ":/Shaders/mondelbrot.fs");

		program_->link();

		program_->bind();

		pqUniform_ = program_->uniformLocation("pqs");
		stepsUniform_ = program_->uniformLocation("steps");
		iterationsUniform_ = program_->uniformLocation("max_iterations");

		program_.release();
	}

void MondelbrotWindow::render() {
	// ------- TODO: do i need it? ---------
	// Configure viewport
	const auto retinaScale = devicePixelRatio();
	glViewport(0, 0, static_cast<GLint>(width() * retinaScale),
			   static_cast<GLint>(height() * retinaScale));

	// ---------------------------------------
	program_->bind();
	QVector4D pqs = QVector4D(p_min, p_max, q_min, q_max);

	double x_step = (p_max - p_min) / a;
	double y_step = (q_max - q_min) / b;;
	QVector2D steps = QVector2D(x_step, y_step);

	program_->setUniformValue(pqUniform_, pqs);
	program_->setUniformValue(stepsUniform_, steps);
	// TODO: pass max iters as parameter
	program_->setUniformValue(iterationsUniform_, 1000);

	program_.release();
}

// double x_step = (p_max - p_min) / a;
// double y_step = (q_max - q_min) / b;
//
// for (size_t i = 0; i < a; ++i) {
//     for (size_t j = 0; j < b; ++j) {
//         // вычисляем координаты текущей `c` на декартовой плоскости
//         double p = p_min + i * x_step;
//         double q = q_min + j * y_step;
//
//         double z_x = 0;
//         double z_y = 0;
//         // смотрим, что произойдёт с точкой через k итераций
//         for (size_t k = 0; k < max_iterations; ++k) {
//             // x_{k+1} = x_k^2 - y_k^2 + p
//             z_x = z_x * z_x - z_y * z_y + p;
//
//             // y_{k+1} = 2 * x_k * y_k + q
//             z_y = 2 * z_x * z_y + q;
//
//             // вышла за границу --- перекрашиваем в цвет итерации
//             if (qSqrt(z_x * z_x + z_y * z_y) > R) {
//                 // TODO: ставим ей не чёрный цвет
//             }
//         }
//     }
// }