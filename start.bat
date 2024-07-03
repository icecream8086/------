@echo off
:: 获取当前批处理文件的目录
set "programDir=%~dp0"
:: 切换到程序所在目录
cd /d "%programDir%"
:: 打开新的命令行窗口，并保持在当前目录
start cmd /k cd /d "%programDir%"