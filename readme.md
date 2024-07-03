## 程序清单:
```bash
Project
│  rand.exe [主程序]
│  outa.txt [所有地图]
│  outb.txt [已选地图]
│  readme.txt [文档]
│  start.bat [启动脚本]
│
└─src
        rand_map.c [源码]
```

使用方法:
1. 确保所有文件都在同一个目录下。
2. 通过双击 start.bat 或在命令行中输入相应命令来运行程序。

命令行参数:
- '-list': 列出所有已经选择过的地图。
- '-rand': 从 outa.txt 中随机选择一个未被选择过的地图，并记录到 outb.txt 中。
- '-search <keyword>': 搜索包含指定关键字的地图。已选择的地图会以红色高亮显示，未选择的地图会以绿色高亮显示。
- '-now': 显示当前时间。这个参数可以附加在任何其他参数后面使用。

例如:
- 要随机选择一个地图，可以在命令行中输入: out.exe -rand
- 要查看所有已选择的地图，可以输入: out.exe -list
- 要搜索地图，可以输入: out.exe -search 地图名 已使用地图使用红色表示，未使用使用绿色表示
- 要查看帮助信息，直接运行: out.exe
- 允许附加任意时间参数，例如: out.exe -rand -now 
可以用于重定向输出作为日志功能使用rand -list -now > ./result.txt
可以生成一个result.txt文件用于管理信息

> CRC SHA256


```bash
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
PS C:\Users\zzbsn\Downloads\随机选图工具> certutil -hashfile '.\rand.exe' SHA256
SHA256 hash of .\rand.exe:
dfb41792545678b9b30b48297e72fcee55656580ef7a5b70981c49eb4d25e9ea
CertUtil: -hashfile command completed successfully.
PS C:\Users\zzbsn\Downloads\随机选图工具>

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
```