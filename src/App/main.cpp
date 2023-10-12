#include <QApplication>
#include <QSurfaceFormat>

#include "Mandelbrot.h"

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
//	double p_min = -2;
//	double p_max = 2;
//	double q_min = -2;
//	double q_max = 2;

	// Кол-во итерация, после которого будем проверять, ушли за границу или нет
	int max_iterations = 1000;

	// Граница, по которой проверяем
	size_t R = 10;

	MandelbrotWindow window(max_iterations, R, 1000, 800);
	window.setFormat(format);
	window.resize(1000, 800);
	window.show();

	window.setAnimated(false);

	return app.exec();
}