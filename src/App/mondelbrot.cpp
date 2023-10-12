#include "Base/GLWindow.hpp"
#include "mondelbrot.h"
#include <iostream>

#include <QOpenGLShaderProgram>
#include <QtMath>

namespace
{

constexpr std::array<GLfloat, 15u> vertices = {
	// first triangle
	-1.0, -1.0,
	1.0, -1.0,
	1.0, 1.0,

	//second
	-1.0, -1.0,
	-1.0, 1.0,
	1.0, 1.0,
};
constexpr std::array<GLuint, 6u> indices = {0, 1, 2, 3, 4, 5};

}

void MondelbrotWindow::init() {
		program_ = std::make_unique<QOpenGLShaderProgram>(this);
		program_->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/Shaders/mondelbrot.vs");
		program_->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/Shaders/mondelbrot.fs");

		program_->link();

		// Create VAO object
		vao_.create();
		vao_.bind();

		// Create VBO
		vbo_.create();
		vbo_.bind();
		vbo_.setUsagePattern(QOpenGLBuffer::StaticDraw);
		vbo_.allocate(vertices.data(), static_cast<int>(vertices.size() * sizeof(GLfloat)));

		// Create IBO
		ibo_.create();
		ibo_.bind();
		ibo_.setUsagePattern(QOpenGLBuffer::StaticDraw);
		ibo_.allocate(indices.data(), static_cast<int>(indices.size() * sizeof(GLuint)));

		// Bind attributes
		program_->bind();

		program_->enableAttributeArray(0);
		program_->setAttributeBuffer(0, GL_FLOAT, 0, 2, static_cast<int>(2 * sizeof(GLfloat)));

		// 3 аргумент --- смещение относительно начала в VBO
		// 5 аргумент --- stride, расстояние между вершинами
//		program_->enableAttributeArray(1);
//		program_->setAttributeBuffer(1, GL_FLOAT, static_cast<int>(2 * sizeof(GLfloat)), 3,
//									 static_cast<int>(5 * sizeof(GLfloat)));

		pqUniform_ = program_->uniformLocation("pqs");
		stepsUniform_ = program_->uniformLocation("steps");
		iterationsUniform_ = program_->uniformLocation("max_iterations");
		radiusUniform_ = program_->uniformLocation("R");

		program_->release();

		vao_.release();

		ibo_.release();
		vbo_.release();

		// Uncomment to enable depth test and face culling
		// glEnable(GL_DEPTH_TEST);
		// glEnable(GL_CULL_FACE);

		// Clear all FBO buffers
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void MondelbrotWindow::render() {
	// Configure viewport
	const auto retinaScale = devicePixelRatio();
	glViewport(0, 0, static_cast<GLint>(width() * retinaScale),
			   static_cast<GLint>(height() * retinaScale));

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	program_->bind();
	vao_.bind();

	QVector4D pqs = QVector4D(p_min, p_max, q_min, q_max);

//	double x_step = (p_max - p_min) / a;
//	double y_step = (q_max - q_min) / b;
	QVector2D steps = QVector2D(a, b);

	program_->setUniformValue(pqUniform_, pqs);
	program_->setUniformValue(stepsUniform_, steps);
	// TODO: pass max iters as parameter
	program_->setUniformValue(iterationsUniform_, 100);
	program_->setUniformValue(radiusUniform_, 10);

	// TODO: change parameters
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

	// Release VAO and shader program
	vao_.release();
	program_->release();
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