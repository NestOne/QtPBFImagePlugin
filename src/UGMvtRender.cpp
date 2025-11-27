#include "UGMvtRender.h"
#include "data.h"
#include "tile.h"

#include "QtGui/QImage.h"
#include "QtCore/qfile.h"
#include "QtCore/QDir.h"
#include "QtCore/QDebug"

#define TILE_SIZE 512

QList<Style*> UGMvtRender::_styles;

QImage* UGMvtRender::render(const QString& filePath,unsigned int zoom, unsigned int overzoom, unsigned int style)
{
	// 1. 创建 QFile 对象
	QFile file(filePath);

	// 2. 以只读模式打开文件
	if (!file.open(QIODevice::ReadOnly)) {
		qWarning() << "Could not open file for reading:" << file.errorString();
		return nullptr; // 返回一个空的  表示失败
	}

	// 3. 读取文件的全部内容
	QByteArray ba = file.readAll();

	// 4. 关闭文件
	file.close();


	Data data;
	if (!data.load(ba)) {
		qCritical() << "Invalid PBF data";
		return false;
	}

	QSize scaledSize(_scaledSize.isValid()
		? _scaledSize : QSize(TILE_SIZE, TILE_SIZE));
	QSize size(qMin(scaledSize.width() << overzoom, 4096),
		qMin(scaledSize.height() << overzoom, 4096));
	QPointF scale((qreal)scaledSize.width() / TILE_SIZE,
		(qreal)scaledSize.height() / TILE_SIZE);

	QImage* image = new QImage(size, QImage::Format_ARGB32_Premultiplied);
	Tile tile(image, zoom, scale);

	if (style < _styles.size())
		_styles.at(style)->render(data, tile);

    return image;
}

void UGMvtRender::loadStyles(const QString& path)
{
	QDir dir(path);
	QFileInfoList styles(dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot));

	for (int i = 0; i < styles.size(); i++) {
		QDir d(styles.at(i).absoluteFilePath());
		Style* style = new Style(d.filePath("style.json"));
		if (style->isValid())
			_styles.append(style);
		else
			delete style;
	}
}
