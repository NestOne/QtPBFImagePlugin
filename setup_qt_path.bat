# QtPBFImagePlugin VS2017 项目 - Qt路径配置脚本
# 将此文件保存为 setup_qt_path.bat 并运行以配置Qt路径

@echo off
echo QtPBFImagePlugin VS2017 项目 - Qt路径配置
setlocal enabledelayedexpansion

:CHECK_QT_PATH
if "%1"=="" (
    echo 请输入Qt安装路径，例如: C:\Qt\5.15.2\msvc2017_64
    echo 或者直接运行: setup_qt_path.bat C:\Qt\5.15.2\msvc2017_64
    set /p QT_PATH="Qt安装路径: "
) else (
    set QT_PATH=%1
)

:VALIDATE_PATH
if not exist "%QT_PATH%" (
    echo 错误: 路径 "%QT_PATH%" 不存在
    goto CHECK_QT_PATH
)

if not exist "%QT_PATH%\bin\qmake.exe" (
    echo 错误: 在 "%QT_PATH%\bin" 中找不到 qmake.exe
    echo 请确保这是有效的Qt安装路径
    goto CHECK_QT_PATH
)

if not exist "%QT_PATH%\bin\moc.exe" (
    echo 错误: 在 "%QT_PATH%\bin" 中找不到 moc.exe
    echo 请确保这是有效的Qt安装路径
    goto CHECK_QT_PATH
)

if not exist "%QT_PATH%\bin\rcc.exe" (
    echo 错误: 在 "%QT_PATH%\bin" 中找不到 rcc.exe
    echo 请确保这是有效的Qt安装路径
    goto CHECK_QT_PATH
)

:SET_ENVIRONMENT
setx QTDIR "%QT_PATH%"
echo.
echo 已设置 QTDIR 环境变量为: %QT_PATH%

setx PATH "%PATH%;%QT_PATH%\bin"
echo 已将 "%QT_PATH%\bin" 添加到 PATH

:CREATE_PROPS_FILE
echo ^<?xml version="1.0" encoding="utf-8"?^> > QtPath.props
echo ^<Project ToolsVersion="4.0" xmlns="http://schemas.microsoft.com/developer/msbuild/2003"^> >> QtPath.props
echo   ^<PropertyGroup Label="UserMacros"^> >> QtPath.props
echo     ^<QTDIR^>%QT_PATH%^</QTDIR^> >> QtPath.props
echo   ^</PropertyGroup^> >> QtPath.props
echo   ^<PropertyGroup^> >> QtPath.props
echo     ^<_PropertySheetDisplayName^>QtPath^</_PropertySheetDisplayName^> >> QtPath.props
echo   ^</PropertyGroup^> >> QtPath.props
echo ^</Project^> >> QtPath.props

echo.
echo 已创建 QtPath.props 文件，包含Qt路径配置

:FINISH
echo.
echo Qt路径配置完成！
echo 现在您可以打开 QtPBFImagePlugin.sln 并构建项目了
echo.
echo 注意: 您可能需要重启Visual Studio才能使环境变量生效
pause