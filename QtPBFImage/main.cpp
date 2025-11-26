#include <iostream>

#include "QtGui/QImage"
#include "QtGui/QImageReader"
#include "QtCore/QFileInfo"
#include "QtCore/QDir"
#include "QtCore/QTextStream"
#include "QtConcurrent/QtConcurrent"
#include "QtCore/QRegularExpression"
//#include "QtWidgets/qapplication.h"

#include "../src/UGMvtRender.h"

#include <chrono>

//
//class App : public QGuiApplication
//{
//public:
//	App(int& argc, char** argv);
//
//	int run();
//
//private:
//	static void render(QFileInfo& fi);
//
//	static bool _hidpi;
//	static QRegularExpression _re;
//	static QDir _outdir;
//};
//
//bool App::_hidpi = false;
//QRegularExpression App::_re;
//QDir App::_outdir;
//
//void App::render(QFileInfo& fi)
//{
//	QImage image;
//	QRegularExpressionMatch match = _re.match(fi.baseName());
//	QByteArray zoom(match.captured(1).toLatin1());
//
//	QImageReader reader(fi.absoluteFilePath(), zoom);
//	if (_hidpi)
//		reader.setScaledSize(QSize(1024, 1024));
//
//	if (reader.read(&image)) {
//		QString outfile(_outdir.absoluteFilePath(fi.completeBaseName() + ".png"));
//		if (!image.save(outfile, "PNG")) {
//			QTextStream err(stderr);
//			err << outfile << ": error saving image\n";
//		}
//	}
//	else {
//		QTextStream err(stderr);
//		err << fi.absoluteFilePath() << ": " << reader.errorString() << "\n";
//	}
//}
//
//App::App(int& argc, char** argv) : QGuiApplication(argc, argv)
//{
//	setApplicationName("pbf2png");
//}
//
//int App::run()
//{
//	QCommandLineParser parser;
//	QCommandLineOption hidpi("H", "Create HIDPI images");
//	QCommandLineOption mask("M", "Tile name mask", "mask", "([0-9]+).*");
//	QCommandLineOption outdir("O", "Output directory", "dir");
//	parser.setApplicationDescription("Create PNG tiles from PBF(MVT) tiles");
//	parser.addHelpOption();
//	parser.addOption(hidpi);
//	parser.addOption(mask);
//	parser.addOption(outdir);
//	parser.addPositionalArgument("DIR", "PBF Tiles directory");
//	QTextStream err(stderr);
//
//	if (!parser.parse(arguments())) {
//		err << parser.errorText() << "\n";
//		return -1;
//	}
//
//	const QStringList args = parser.positionalArguments();
//	if (!args.size()) {
//		err << parser.helpText();
//		return -1;
//	}
//	QDir dir(args.at(0));
//	if (!dir.exists()) {
//		err << args.at(0) << ": No such directory\n";
//		return -1;
//	}
//	if (!parser.value(outdir).isNull()) {
//		_outdir = QDir(parser.value(outdir));
//		if (!_outdir.exists()) {
//			if (!_outdir.mkpath(".")) {
//				err << parser.value(outdir) << ": error creating directory\n";
//				return -1;
//			}
//		}
//	}
//	else
//		_outdir = dir;
//
//	QFileInfoList list(dir.entryInfoList(QDir::NoDotAndDotDot | QDir::Files));
//
//	_re.setPattern(parser.value(mask));
//	_hidpi = parser.isSet(hidpi);
//
//	QFuture<void> future = QtConcurrent::map(list, render);
//	future.waitForFinished();
//
//	return 0;
//}
//
//int main(int argc, char* argv[])
//{
//	App a(argc, argv);
//	return a.run();
//}



int main()
{
	//int argc = 0;
	//char** argv = nullptr;
	//if (qApp == nullptr)
	//{
	//	QCoreApplication::addLibraryPath("E:/GitHub/mvt2png/Debug/bin/platforms");
	//	new QApplication(argc, argv);
	//}


     // --- 1. 计时：加载样式 ---
    std::cout << "开始加载样式..." << std::endl;
    auto start_load = std::chrono::high_resolution_clock::now();

    UGMvtRender::loadStyles("E:/QtPBFImagePlugin/style");

    auto end_load = std::chrono::high_resolution_clock::now();
    auto duration_load = std::chrono::duration_cast<std::chrono::milliseconds>(end_load - start_load);
    std::cout << "样式加载完毕，耗时: " << duration_load.count() << " 毫秒" << std::endl << std::endl;


    // --- 2. 计时：渲染 MVT ---
    UGMvtRender render;
    std::cout << "开始渲染 MVT 文件..." << std::endl;
    auto start_render = std::chrono::high_resolution_clock::now();

    QImage* pImage = render.render("E:/GitHub/mvt2png/China/tiles/6/53/26.mvt", 1, 5, 0);

    auto end_render = std::chrono::high_resolution_clock::now();
    auto duration_render = std::chrono::duration_cast<std::chrono::milliseconds>(end_render - start_render);
    std::cout << "渲染完毕，耗时: " << duration_render.count() << " 毫秒" << std::endl << std::endl;


    // --- 3. 计时：保存图片 ---
    QString outfile("E:/GitHub/mvt2png/China/tiles/6/53/26.png");
    std::cout << "开始保存图片..." << std::endl;
    auto start_save = std::chrono::high_resolution_clock::now();

    if (pImage) {
        pImage->save(outfile, "PNG");
    }

    auto end_save = std::chrono::high_resolution_clock::now();
    auto duration_save = std::chrono::duration_cast<std::chrono::milliseconds>(end_save - start_save);
    std::cout << "图片保存完毕，耗时: " << duration_save.count() << " 毫秒" << std::endl << std::endl;


    std::cout << "Hello World!\n";

    // 重要提示：如果 render.render() 函数分配了内存 (返回一个 new QImage*)，
    // 您需要在使用后手动释放它以避免内存泄漏。
    if (pImage) {
        delete pImage;
        pImage = nullptr;
    }

    return 0;
}