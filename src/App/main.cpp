#include <QApplication>
#include <QSurfaceFormat>
#include <QToolBar>
#include <QFormLayout>


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

	MandelbrotWindow window;
	window.setFormat(format);

	window.resize(1000, 800);
	window.show();

	return app.exec();
}