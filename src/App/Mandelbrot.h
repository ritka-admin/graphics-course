#include "Base/GLWindow.hpp"

#include <QApplication>
#include <QMouseEvent>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLWidget>
#include <QtMath>


class MandelbrotWindow : public fgl::GLWindow {

public:
	void init() override;
	void render() override;

	MandelbrotWindow(size_t max_iterations, int R)
		: max_iterations(max_iterations), R(R)
	{}

private:

	// Кол-во итерация, после которого будем проверять, ушли за границу или нет
	int max_iterations;

	// Граница, по которой проверяем
	int R;

	QPoint mouseStartPos_;
	bool dragged_ = false;
	QPointF shift_ = QPointF(0.5, 0.5);
	QPointF scale_ = QPointF(4, 4);

	GLint shiftUniform_ = -1;
	GLint scaleUniform_ = -1;
	GLint screenUniform_ = -1;
	GLint iterationsUniform_ = -1;
	GLint radiusUniform_ = -1;

	QOpenGLBuffer vbo_{QOpenGLBuffer::Type::VertexBuffer};
	QOpenGLBuffer ibo_{QOpenGLBuffer::Type::IndexBuffer};
	QOpenGLVertexArrayObject vao_;

	std::unique_ptr<QOpenGLShaderProgram> program_ = nullptr;

	size_t frame_ = 0;

	QVector2D mousePressPosition_{0., 0.};
	QVector3D rotationAxis_{0., 1., 0.};

	void mousePressEvent(QMouseEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;
	void mouseReleaseEvent(QMouseEvent *event) override;
	void wheelEvent ( QWheelEvent * event ) override;
};