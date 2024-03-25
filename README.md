# Sudoku
这是 宋星霖 的自制的参赛作品，是一个数独游戏。

项目结构如下（去除了不重要的文件）：
```
.
├── button.cpp ────── 按钮类实现
├── button.h ──────── 按钮类定义
├── ico.rc ────────── .exe图标的配置文件
├── img ───────────── 图片文件夹
│   ├── has0.png ─┐
│   ├── has1.png ─┤
│   ├── has2.png ─┤
│   ├── has3.png ─┤
│   ├── has4.png ─┼── 取数板0-9个的图片
│   ├── has5.png ─┤
│   ├── has6.png ─┤
│   ├── has7.png ─┤
│   ├── has8.png ─┤
│   ├── has9.png ─┘
│   ├── ico.ico ───── .exe图标
│   ├── ico.png ───── 程序图标
│   ├── pic1.png ─┐
│   ├── pic2.png ─┤
│   ├── pic3.png ─┤
│   ├── pic4.png ─┤
│   ├── pic5.png ─┼── 数字1-9图片
│   ├── pic6.png ─┤
│   ├── pic7.png ─┤
│   ├── pic8.png ─┤
│   └── pic9.png ─┘
├── main.cpp ──────── 主文件
├── mainwindow.cpp ── 主窗口实现
├── mainwindow.h ──── 主窗口定义
├── mainwindow.ui ─── 主窗口样式
├── pic.qrc ───────── 资源文件
├── questions.json ── 题库
├── sudoku.cpp ────── 数独棋盘实现
├── sudoku.h ──────── 数独棋盘定义
├── var.cpp ──────┐
└── var.h ────────┴── 公用锁
```
