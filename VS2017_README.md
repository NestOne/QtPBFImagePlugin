# QtPBFImagePlugin Visual Studio 2017 项目配置

## 项目说明
这是一个将Qt PBF图像插件项目转换为Visual Studio 2017项目的配置文件集合。

## 依赖项
- Qt5 (>= 5.15) 或 Qt6
- Visual Studio 2017
- Windows SDK

## 配置要求
在构建项目之前，需要设置以下环境变量：
- `QTDIR`: Qt安装目录，例如 `C:\Qt\5.15.2\msvc2017_64`

## 项目设置
项目已经配置为：
- 生成DLL文件 (pbf.dll)
- 支持Debug和Release配置
- 支持x86和x64平台
- 包含Qt头文件和库文件依赖
- 配置了moc和rcc自定义构建步骤

## 构建步骤
1. 打开 QtPBFImagePlugin.sln 文件
2. 确保QTDIR环境变量已设置
3. 选择所需的配置和平台
4. 构建项目

## 输出文件
构建完成后，输出文件为：
- Debug: pbf.dll (调试版本)
- Release: pbf.dll (发布版本)

## 注意事项
- 需要安装Qt并正确设置QTDIR环境变量
- 项目使用Qt5作为默认版本，如需Qt6请修改项目文件中的库名称
- 确保Qt的bin目录在PATH环境变量中，以便moc和rcc工具可用