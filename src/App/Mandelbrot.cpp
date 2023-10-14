#include "Mandelbrot.h"
#include <QtMath>
#include <QLabel>
#include <QSlider>
#include <QVBoxLayout>

#include <array>
#include <string>


namespace
{

constexpr std::array<GLfloat, 8u> vertices = {
	-1.0, -1.0,
	1.0, -1.0,
	1.0, 1.0,
	-1.0, 1.0
};
constexpr std::array<GLuint, 6u> indices = {0, 1, 3, 2};

}

MandelbrotWindow::MandelbrotWindow() {
	auto slider_border = new QSlider();
	slider_border->setRange(MandelbrotWindow::MIN_BORDER, MandelbrotWindow::MAX_BORDER);
	slider_border->setSingleStep(1);
	slider_border->setOrientation(Qt::Vertical);
	auto border_name = new QLabel("Border", slider_border);
	auto border_lower = new QLabel(std::to_string(MandelbrotWindow::MIN_BORDER).c_str(), slider_border);
	auto border_higher = new QLabel(std::to_string(MandelbrotWindow::MAX_BORDER).c_str(), slider_border);
	border_name->setStyleSheet("QLabel { color : pink; }");
	border_lower->setStyleSheet("QLabel { color : pink; }");
	border_higher->setStyleSheet("QLabel { color : pink; }");

	auto slider_iterations = new QSlider();
	slider_iterations->setRange(MandelbrotWindow::MIN_ITERATIONS, MandelbrotWindow::MAX_ITERATIONS);
	slider_iterations->setSingleStep(10);
	slider_iterations->setOrientation(Qt::Vertical);
	auto iterations_name = new QLabel("Iterations", slider_iterations);
	auto it_lower = new QLabel(std::to_string(MandelbrotWindow::MIN_ITERATIONS).c_str(), slider_border);
	auto it_higher = new QLabel(std::to_string(MandelbrotWindow::MAX_ITERATIONS).c_str(), slider_border);
	iterations_name->setStyleSheet("QLabel { color : pink; }");
	it_lower->setStyleSheet("QLabel { color : pink; }");
	it_higher->setStyleSheet("QLabel { color : pink; }");

	auto layout = new QVBoxLayout();
	layout->addWidget(border_name, 2);
	layout->addWidget(border_higher, 1);
	layout->addWidget(slider_border, 10);
	layout->addWidget(border_lower, 3);
	layout->addWidget(it_higher, 3);
	layout->addWidget(slider_iterations, 10);
	layout->addWidget(it_lower, 1);
	layout->addWidget(iterations_name, 2);

	setLayout(layout);

	connect(slider_border, &QSlider::valueChanged, this, &MandelbrotWindow::change_borders);
	connect(slider_iterations, &QSlider::valueChanged, this, &MandelbrotWindow::change_iterations);
}

void MandelbrotWindow::initializeGL() {
		opengl_funcs.initializeOpenGLFunctions();

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

		// 3 аргумент --- смещение относительно начала в VBO
		// 5 аргумент --- stride, расстояние между вершинами
		program_->enableAttributeArray(0);
		program_->setAttributeBuffer(0, GL_FLOAT, 0, 2, static_cast<int>(2 * sizeof(GLfloat)));

		centerUniform_ = program_->uniformLocation("center");
		screenUniform_ = program_->uniformLocation("screen");
		scaleUniform_ = program_->uniformLocation("scale");
		iterationsUniform_ = program_->uniformLocation("max_iterations");
		radiusUniform_ = program_->uniformLocation("R");

		program_->release();

		vao_.release();

		ibo_.release();
		vbo_.release();

		// Clear all FBO buffers
		opengl_funcs.glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void MandelbrotWindow::paintGL() {
	// Configure viewport
	const auto retinaScale = devicePixelRatio();
	opengl_funcs.glViewport(0, 0, static_cast<GLint>(width() * retinaScale),
			   static_cast<GLint>(height() * retinaScale));

	opengl_funcs.glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	program_->bind();
	vao_.bind();

	QVector2D screen = QVector2D(width(), height());
	program_->setUniformValue(centerUniform_, center_);
	program_->setUniformValue(scaleUniform_, scale_);
	program_->setUniformValue(screenUniform_, screen);
	program_->setUniformValue(iterationsUniform_, max_iterations);
	program_->setUniformValue(radiusUniform_, R);

	opengl_funcs.glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, nullptr);

	// Release VAO and shader program
	vao_.release();
	program_->release();
}

void MandelbrotWindow::mousePressEvent(QMouseEvent* got_event) {
	mouseStartPos_ = got_event->pos();
	dragged_ = true;
}

void MandelbrotWindow::mouseMoveEvent(QMouseEvent* got_event) {
	if (dragged_)
	{
		QPoint delta = got_event->pos() - mouseStartPos_;

		float prev_x = center_.x();
		float prev_y = center_.y();

		auto speed = scale_.x();

		center_.setX(prev_x + (float) delta.x() / width() * speed);
		center_.setY(prev_y - (float) delta.y() / height() * speed);

		mouseStartPos_ = got_event->pos();

		update();
	}
}

void MandelbrotWindow::mouseReleaseEvent([[maybe_unused]] QMouseEvent* got_event) {
	dragged_ = false;
}


void MandelbrotWindow::wheelEvent(QWheelEvent * got_event) {
	QPoint delta = got_event->angleDelta() / 8;

	float prev_x = scale_.x();
	float prev_y = scale_.y();

	float speed = scale_.x();

	scale_.setX(prev_x - delta.y() / (float) height() * speed);
	scale_.setY(prev_y - delta.y() / (float) height() * speed);

	update();
}

void MandelbrotWindow::change_iterations(int it) {
	max_iterations = it;
	update();
}

void MandelbrotWindow::change_borders(int r) {
	R = r;
	update();
}
