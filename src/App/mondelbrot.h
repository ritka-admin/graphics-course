#include "Base/GLWindow.hpp"

#include <QOpenGLShaderProgram>
#include <QtMath>

class MondelbrotWindow : public fgl::GLWindow {

public:
	void init() override;
	void render() override;

	MondelbrotWindow(double p_min, double p_max, double q_min, double q_max, size_t a, size_t b, size_t max_iterations, size_t R)
		: p_min(p_min), p_max(p_max), q_min(q_min), q_max(q_max), a(a), b(b), max_iterations(max_iterations), R(R)
	{}

private:
	// c = p + iq
	double p_min;
	double p_max;
	double q_min;
	double q_max;

	// размеры окна?
	int a;
	int b;

	// Кол-во итерация, после которого будем проверять, ушли за границу или нет
	size_t max_iterations;

	// Граница, по которой проверяем
	size_t R;
	std::unique_ptr<QOpenGLShaderProgram> program_ = nullptr;

	GLint pqUniform_ = -1;
	GLint stepsUniform_ = -1;
	GLint iterationsUniform_ = -1;
};