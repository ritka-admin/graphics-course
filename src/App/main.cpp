#include <QApplication>
#include <QSurfaceFormat>
#include <QToolBar>
#include <QFormLayout>
#include <iostream>
#include <QLabel>
#include <QSlider>
#include <QString>
#include <QGroupBox>

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

	// TODO: add slider logic
	// TODO: change position and size of the slider
	auto slider_border = new QSlider();
	slider_border->setRange(1, 10);
	slider_border->setOrientation(Qt::Vertical);
//	slider_border->setStyleSheet("QSlider { height : 15px; width : 40px; }");
	slider_border->move(QPoint(10, 10));
	auto label1 = new QLabel("Border", slider_border);
	label1->setStyleSheet("QLabel { color : pink; }");

	auto slider_iterations = new QSlider();
	slider_iterations->setRange(1, 1000);
	slider_iterations->setOrientation(Qt::Vertical);
//	slider_iterations->setStyleSheet("QSlider { height : 15px; width : 40px;}");
	auto label2 = new QLabel("Iterations", slider_iterations);
	label2->setStyleSheet("QLabel { color : pink; }");

	auto layout = new QVBoxLayout();
	layout->addWidget(slider_border);
	layout->addWidget(label1);
	layout->addWidget(slider_iterations);
	layout->addWidget(label2);

	window.setLayout(layout);

	window.resize(1000, 800);
	window.show();

	return app.exec();
}