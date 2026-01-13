```ANSI Shadow
███████╗███╗   ███╗    ███████╗██╗  ██╗███████╗██╗     ██╗     
██╔════╝████╗ ████║    ██╔════╝██║  ██║██╔════╝██║     ██║     
█████╗  ██╔████╔██║    ███████╗███████║█████╗  ██║     ██║     
██╔══╝  ██║╚██╔╝██║    ╚════██║██╔══██║██╔══╝  ██║     ██║     
███████╗██║ ╚═╝ ██║    ███████║██║  ██║███████╗███████╗███████╗
╚══════╝╚═╝     ╚═╝    ╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝
```
[![EmShell CI-workflow](https://github.com/CYK-dot/EmShell/actions/workflows/ci.yml/badge.svg?branch=main)](https://github.com/CYK-dot/EmShell/actions/workflows/ci.yml)  [![codecov](https://codecov.io/gh/CYK-dot/EmShell/graph/badge.svg?token=GWYXCW02R7)](https://codecov.io/gh/CYK-dot/EmShell)  [![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

# 简介
轻量级嵌入式Shell，旨在为MCU提供高可用的命令行接口。优势：
1. Shell为前后端分离设计，支持多后端/多前端，例如物理前端（例如UART）/逻辑前端（例如RTOS任务）
2. 视图切换逻辑开放可定制。可通过依赖注入支持文件系统，或定制自己的切换逻辑。
3. 代码组件化，支持异步回显、命令行历史、用户管理等功能。支持定制新组件，亦可依组件进行功能裁剪。
