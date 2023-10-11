#include <QApplication>
#include <QSurfaceFormat>

#include "mondelbrot.h"

namespace
{
constexpr auto g_sampels = 16;
constexpr auto g_gl_major_version = 3;
constexpr auto g_gl_minor_version = 3;
}// namespace

int main(int argc, char ** argv)
{
	QApplication app(argc, argv);

	QSurfaceFormat format;
	format.setSamples(g_sampels);
	format.setVersion(g_gl_major_version, g_gl_minor_version);
	format.setProfile(QSurfaceFormat::CoreProfile);

	// c = p + iq
	double p_min = -1.5;
	double p_max = 1.5;
	double q_min = -1.5;
	double q_max = 1.5;

	// размеры окна?
	int a = 640;
	int b = 480;

	// Кол-во итерация, после которого будем проверять, ушли за границу или нет
	size_t max_iterations = 1000;

	// Граница, по которой проверяем
	size_t R = 10;

	MondelbrotWindow window(p_min, p_max, q_min, q_max, a, b, max_iterations, R);
	window.setFormat(format);
	window.resize(a, b);
	window.show();

	window.setAnimated(true);

	return app.exec();
}