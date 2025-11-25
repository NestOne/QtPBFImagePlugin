> [!CAUTION]
> 此项目现已废弃。

# QtPBFImagePlugin
用于显示Mapbox矢量瓦片的Qt图像插件

## 描述
QtPBFImagePlugin是一个Qt图像插件，使能够显示栅格MBTiles地图或栅格XYZ在线地图的应用程序也能够显示PBF(MVT)矢量瓦片，而几乎不需要对应用程序进行任何修改（请参阅使用说明）。

使用标准的Mapbox GL样式来设置地图样式。支持[Maputnik](https://maputnik.github.io/editor)使用的大多数相关样式特性。插件附带了一组针对OpenMapTiles、Mapbox、Protomaps和Versatiles瓦片方案的默认样式。

默认瓦片大小为512px。

## 使用
由于Mapbox矢量瓦片规范中的一个主要设计缺陷——缩放级别不是PBF数据的一部分——插件不能"直接"使用，而是需要传递缩放级别。这是通过利用QImage构造函数的可选*format*参数或*QImage::loadFromData()*、*QPixmap::loadFromData()*函数来实现的。缩放级别以ASCII字符串形式传递给这些函数：

```cpp
QImage img;
img.loadFromData(data, QByteArray::number(zoom));
```

有关完整代码示例，请参阅[pbf2png](https://github.com/tumic0/pbf2png)转换工具。

### HiDPI支持
插件支持使用*QImageReader::setScaledSize()*方法进行矢量缩放，因此当像以下示例这样使用时：

```cpp
QImage img;
QImageReader reader(file, QByteArray::number(zoom));
reader.setScaledSize(QSize(1024, 1024));
reader.read(&img);
```

您将获得1024x1024px的瓦片，像素比为2（= HiDPI瓦片）。最大瓦片大小为4096x4096px。

### 过缩放
从插件版本3开始支持瓦片过缩放。如果您将*format*设置为`$zoom;$overzoom`：

```cpp
QImage img;
QByteArray fmt(QByteArray::number(zoom) + ';' + QByteArray::number(overzoom));
img.loadFromData(data, fmt);
```

您将获得(512<<overzoom)x(512<<overzoom)px的瓦片，像素比为1。当过缩放与*setScaledSize()*结合使用时，基础大小是过缩放后的瓦片大小。

### 样式选择
从插件版本5开始支持样式选择。如果您将*format*设置为`$zoom;$overzoom;$style`：

```cpp
QImage img;
QByteArray fmt(QByteArray::number(zoom) + ';' + QByteArray::number(overzoom) \
  + ';' + QByteArray::number(style));
img.loadFromData(data, fmt);
```

将使用第style个可用样式来渲染瓦片。

要获取可用样式列表，请使用"Description"键调用*QImageReader::text()*：

```cpp
QImageReader reader(&imageData);
QString info(reader.text("Description"));
```

这将用类似以下的JSON数组填充*info*：

```json
[
  {
    "layers": [
      "aerodrome_label",
      "aeroway",
      "boundary",
      "building",
      "landcover",
      "landuse",
      "park",
      "place",
      "poi",
      "transportation",
      "transportation_name",
      "water",
      "water_name",
      "waterway"
    ],
    "name": "OpenMapTiles"
  },
  {
    "layers": [
      "boundaries",
      "buildings",
      "earth",
      "landcover",
      "landuse",
      "places",
      "pois",
      "roads",
      "water"
    ],
    "name": "Protomaps"
  }
]
```

## 样式
地图样式在插件加载时从[$AppDataLocation](http://doc.qt.io/qt-5/qstandardpaths.html)/style目录的子目录中加载，每个子目录对应一个样式。如果样式使用精灵图，精灵图JSON文件必须命名为`sprite.json`，精灵图像必须命名为`sprite.png`，并且这两个文件必须与样式本身放在同一目录中。

有关各种不同瓦片方案的兼容样式集，请参阅[QtPBFImagePlugin-styles](https://github.com/tumic0/QtPBFImagePlugin-styles)仓库。

## 构建
### 先决条件
* Qt5 >= 5.15 或 Qt6（Android构建需要Qt6）

### 步骤
#### Linux、OS X和Android
```shell
qmake pbfplugin.pro
make
```
#### Windows
```shell
qmake pbfplugin.pro
nmake
```

## 安装
将插件复制到系统Qt图像插件路径以使其工作。您也可以在启动应用程序之前设置QT_PLUGIN_PATH系统变量。对于Linux，在OBS上有适用于大多数常见发行版的RPM和DEB[包](https://build.opensuse.org/project/show/home:tumic:QtPBFImagePlugin)。

## 限制
* 仅显示PBF文件中的数据。样式中定义的外部图层将被忽略。
* 文本PBF要素必须具有唯一ID（OpenMapTiles >= v3.7），文本布局算法才能正常工作。此外，瓦片缓冲区必须足够大以包含所有与瓦片边界重叠的相邻文本要素（只有瓦片本身的数据才能绘制到结果图像中）。
* 样式中不支持表达式，仅实现了原始的GL缩放函数。

## 更新日志
[更新日志](https://build.opensuse.org/projects/home:tumic:QtPBFImagePlugin/packages/QtPBFImagePlugin/files/qt6-qtpbfimageformat.changes)

## 状态
一图胜千言。
#### OpenMapTiles

* 数据：[MapTiler](https://github.com/tumic0/GPXSee-maps/blob/master/World/MapTiler-OpenMapTiles.tpl)
* 样式：[OSM-liberty](https://github.com/tumic0/QtPBFImagePlugin-styles/blob/master/OpenMapTiles/osm-liberty/style.json)

![osm-liberty 5](https://tumic0.github.io/QtPBFImagePlugin/images/osm-liberty-5.png)
![osm-liberty 8](https://tumic0.github.io/QtPBFImagePlugin/images/osm-liberty-8.png)
![osm-liberty 12](https://tumic0.github.io/QtPBFImagePlugin/images/osm-liberty-12.png)
![osm-liberty 14](https://tumic0.github.io/QtPBFImagePlugin/images/osm-liberty-14.png)
![osm-liberty 15](https://tumic0.github.io/QtPBFImagePlugin/images/osm-liberty-15.png)

#### Mapbox

* 数据：[Mapbox](https://github.com/tumic0/GPXSee-maps/blob/master/World/Mapbox.tpl)
* 样式：[Bright](https://github.com/tumic0/QtPBFImagePlugin-styles/blob/master/Mapbox/bright/style.json)

![bright 4](https://tumic0.github.io/QtPBFImagePlugin/images/bright-4.png)
![bright 6](https://tumic0.github.io/QtPBFImagePlugin/images/bright-6.png)
![bright 13](https://tumic0.github.io/QtPBFImagePlugin/images/bright-13.png)
![bright 15](https://tumic0.github.io/QtPBFImagePlugin/images/bright-15.png)
![bright 17](https://tumic0.github.io/QtPBFImagePlugin/images/bright-17.png)

#### Tilezen

* 数据：[HERE](https://github.com/tumic0/GPXSee-maps/blob/master/World/here-vector.tpl)
* 样式：[Apollo-Bright](https://github.com/tumic0/QtPBFImagePlugin-styles/blob/master/Tilezen/apollo-bright/style.json)

![apollo-bright 4](https://tumic0.github.io/QtPBFImagePlugin/images/apollo-bright-4.png)
![apollo-bright 6](https://tumic0.github.io/QtPBFImagePlugin/images/apollo-bright-6.png)
![apollo-bright 12](https://tumic0.github.io/QtPBFImagePlugin/images/apollo-bright-12.png)
![apollo-bright 15](https://tumic0.github.io/QtPBFImagePlugin/images/apollo-bright-15.png)
![apollo-bright 16](https://tumic0.github.io/QtPBFImagePlugin/images/apollo-bright-16.png)

## 使用QtPBFImagePlugin的应用程序
* ~~[GPXSee](https://www.gpxsee.org)~~（在版本 < 15.0中）