#pragma once

#include "QtGui/QImage.h"
#include "Style.h"

class UGMvtRender
{
public:
	QImage* render(const QString& filePath, unsigned int zoom, unsigned int overzoom, unsigned int style);

	static void loadStyles(const QString& path);

private:
	QSize _scaledSize;

	static QList<Style*> _styles;
};

