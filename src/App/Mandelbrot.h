#include <QMouseEvent>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>


class MandelbrotWindow : public QOpenGLWidget {

public:

	int MIN_BORDER = 2;
	int MAX_BORDER = 10;

	int MIN_ITERATIONS = 10;
	int MAX_ITERATIONS = 200;

	void initializeGL() override;
	void paintGL() override;

	void change_iterations(int it);
	void change_borders(int r);

	MandelbrotWindow();

private:

	// fractal params
	int max_iterations = MandelbrotWindow::MIN_ITERATIONS;
	int R = MandelbrotWindow::MIN_BORDER;

	// Coordinate plane params
	QPointF scale_ = QPointF(4, 4);
	QPointF center_ = QPointF(0, 0);

	// uniforms' locations
	GLint centerUniform_ = -1;
	GLint scaleUniform_ = -1;
	GLint screenUniform_ = -1;
	GLint iterationsUniform_ = -1;
	GLint radiusUniform_ = -1;

	// buffers
	QOpenGLBuffer vbo_{QOpenGLBuffer::Type::VertexBuffer};
	QOpenGLBuffer ibo_{QOpenGLBuffer::Type::IndexBuffer};
	QOpenGLVertexArrayObject vao_;

	// shader program
	std::unique_ptr<QOpenGLShaderProgram> program_ = nullptr;

	// opengl interface provider
	QOpenGLFunctions opengl_funcs;

	// events
	void mousePressEvent(QMouseEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;
	void mouseReleaseEvent(QMouseEvent *event) override;
	void wheelEvent ( QWheelEvent * event) override;

	// mouse events supplementary info
	QPoint mouseStartPos_;
	bool dragged_ = false;
};