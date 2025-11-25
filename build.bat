# QtPBFImagePlugin VS2017 项目 - 构建脚本
# 此脚本用于构建QtPBFImagePlugin项目

@echo off
echo QtPBFImagePlugin VS2017 项目构建脚本
setlocal enabledelayedexpansion

:CHECK_VS
where msbuild >nul 2>nul
if %errorlevel% neq 0 (
    echo 错误: 找不到 MSBuild，请确保已安装 Visual Studio 2017
    echo 或者使用 Visual Studio 2017 的开发人员命令提示符运行此脚本
    pause
    exit /b 1
)

:CHECK_QT
if "%QTDIR%"=="" (
    echo 错误: QTDIR 环境变量未设置
    echo 请先运行 setup_qt_path.bat 来配置Qt路径
    pause
    exit /b 1
)

if not exist "%QTDIR%\bin\moc.exe" (
    echo 错误: 在 "%QTDIR%\bin" 中找不到 moc.exe
    echo 请检查 QTDIR 设置是否正确
    pause
    exit /b 1
)

if not exist "%QTDIR%\bin\rcc.exe" (
    echo 错误: 在 "%QTDIR%\bin" 中找不到 rcc.exe
    echo 请检查 QTDIR 设置是否正确
    pause
    exit /b 1
)

:BUILD_OPTIONS
echo.
echo 请选择构建配置:
echo 1. Debug x86
echo 2. Debug x64
echo 3. Release x86
echo 4. Release x64
echo 5. 全部构建
set /p choice="请选择 (1-5): "

set CONFIGS=
if "%choice%"=="1" set CONFIGS="Debug|Win32"
if "%choice%"=="2" set CONFIGS="Debug|x64"
if "%choice%"=="3" set CONFIGS="Release|Win32"
if "%choice%"=="4" set CONFIGS="Release|x64"
if "%choice%"=="5" set CONFIGS="Debug|Win32" "Debug|x64" "Release|Win32" "Release|x64"

if "%CONFIGS%"=="" (
    echo 无效的选择
    goto BUILD_OPTIONS
)

:BUILD
echo.
echo 开始构建项目...

for %%C in (%CONFIGS%) do (
    echo.
    echo 正在构建 %%C...
    msbuild QtPBFImagePlugin.sln /p:Configuration=%%~C /p:Platform=%%~D /m
    if %errorlevel% neq 0 (
        echo 错误: 构建 %%C 失败
        pause
        exit /b 1
    )
    echo 构建 %%C 完成
)

:SUCCESS
echo.
echo 所有构建任务完成！
echo 输出文件位于:
echo - Debug x86: x86\Debug\pbf.dll
echo - Debug x64: x64\Debug\pbf.dll
echo - Release x86: x86\Release\pbf.dll
echo - Release x64: x64\Release\pbf.dll
pause