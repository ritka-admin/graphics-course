#include "Mandelbrot.h"
#include "Base/GLWindow.hpp"
#include <iostream>

#include <QOpenGLShaderProgram>
#include <QtMath>
#include <QDrag>


namespace
{

// TODO: change to triangle_strip
constexpr std::array<GLfloat, 16u> vertices = {
	// first triangle
	-1.0, -1.0,
	1.0, -1.0,
	1.0, 1.0,

	//second
//	-1.0, -1.0,
	-1.0, 1.0,
//	1.0, 1.0,
};
constexpr std::array<GLuint, 6u> indices = {0, 1, 2, 0, 2, 3};

}

void MandelbrotWindow::init() {
		program_ = std::make_unique<QOpenGLShaderProgram>(this);
		program_->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/Shaders/mandelbrot.vs");
		program_->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/Shaders/mandelbrot.fs");

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
		shiftUniform_ = program_->uniformLocation("shift");
		screenUniform_ = program_->uniformLocation("screen");
		scaleUniform_ = program_->uniformLocation("scale");
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

void MandelbrotWindow::render() {
	// Configure viewport
	const auto retinaScale = devicePixelRatio();
	glViewport(0, 0, static_cast<GLint>(width() * retinaScale),
			   static_cast<GLint>(height() * retinaScale));

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	program_->bind();
	vao_.bind();

	QVector2D screen = QVector2D(width(), height());

	// TODO: parametrize scale
	program_->setUniformValue(scaleUniform_, 4);
	program_->setUniformValue(shiftUniform_, QVector2D(shift_.x(), shift_.y()));
	program_->setUniformValue(screenUniform_, screen);
	program_->setUniformValue(iterationsUniform_, max_iterations);
	program_->setUniformValue(radiusUniform_, R);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

	// Release VAO and shader program
	vao_.release();
	program_->release();
}

void MandelbrotWindow::mousePressEvent(QMouseEvent* got_event) {
	startPos_ = got_event->pos();
	dragged_ = true;
	std::cout << "dragged" << std::endl;
}

void MandelbrotWindow::mouseMoveEvent(QMouseEvent* got_event) {
	if (dragged_)
	{
		QPoint delta = got_event->pos() - startPos_;

		float prev_x = shift_.x();
		float prev_y = shift_.y();

		// константа 20 --- для не слишком быстрого перемещения по карте
		shift_.setX(prev_x + (float) delta.x() / (width() * 20));
		shift_.setY(prev_y - (float) delta.y() / (height() * 20));
	}
}

void MandelbrotWindow::mouseReleaseEvent(QMouseEvent* got_event) {
	got_event->pos();
	dragged_ = false;
	std::cout << "released" << std::endl;
}

