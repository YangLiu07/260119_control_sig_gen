
# Auto Testing System (Qt + VISA)

## 📌 项目简介

本项目是基于 Qt6 + C++ 开发的自动测试系统平台，用于实现多仪器协同控制、设备自检、测试参数配置及日志记录功能。

系统支持通过 VISA 协议与多台仪器进行 TCPIP/串口通信，实现标准 SCPI 指令控制，并具备良好的模块化结构，便于后续扩展。

当前已实现：

- 设备自动连接检测（自检）
- SCPI 指令通信
- 多仪器管理
- 可视化界面参数配置
- 日志输出与状态提示
- 模块化驱动封装

---

## 🏗️ 系统架构

```

UI层 (Qt Widgets)
│
├── MainWindow（界面控制层）
│       ├── 参数读取
│       ├── 事件响应
│       ├── 日志管理
│
├── 驱动层（RigolDriver 等）
│       ├── connectDevice()
│       ├── write()
│       ├── read()
│       ├── query()
│
└── 硬件设备
├── 信号源
├── 数据采集仪
└── 滤波放大器

```

采用分层设计思想：

- UI层与设备驱动解耦
- 逻辑通过统一接口调用
- 可扩展更多仪器类型

---

## 🚀 已实现功能

### 1️⃣ 设备自检功能

点击「自检」按钮后：

- 自动读取VISA地址
- 尝试连接设备
- 发送 `*IDN?` 指令验证设备身份
- 输出连接状态及型号信息

示例日志：

```

========== 设备自检 ==========
检测 信号源...
信号源 连接成功
IDN: RIGOL,DS1054Z,...

检测 数据采集仪...
数据采集仪 连接成功
IDN: ...

自检完成

````

---

### 2️⃣ SCPI 指令封装

驱动层封装标准接口：

```cpp
bool connectDevice(const QString& addr);
bool write(const QString& cmd);
QString read();
QString query(const QString& cmd);
````

支持标准 SCPI 通信模式。

---

### 3️⃣ 日志系统

支持：

* 分级日志输出（Info / Warning / Error）
* 自动滚动到底部
* 时间戳显示
* UI实时更新

接口设计：

```cpp
void appendLog(const QString &msg, LogLevel level);
```

---

### 4️⃣ UI模块结构

* 仪器自检模块
* 信号源参数配置
* 数据采集仪配置
* 滤波放大器配置
* 日志显示区

使用 QGroupBox 分模块布局，支持后续功能扩展。

---

## 💻 开发环境

* Qt 6.2.3
* MinGW 64-bit
* C++17
* Windows 10/11
* NI VISA (如使用 USB/TCPIP 设备)

---

## 🔌 通信协议

* TCPIP::xxx::INSTR
* USB::xxx::INSTR
* 串口 COMx

支持标准 SCPI 协议设备。

---

## 🔄 后续规划

* [ ] 多线程异步设备检测（避免阻塞UI）
* [ ] 状态机控制测试流程
* [ ] 批量设备管理
* [ ] 自动化测试脚本配置
* [ ] 日志保存为文件
* [ ] 数据绘图模块
* [ ] 测试流程可配置化

---

## 📦 项目结构

```
.
├── main.cpp
├── mainwindow.h / .cpp
├── rigoldriver.h / .cpp
├── ui_mainwindow.ui
└── README.md
```

---

## 🧠 工程特点

* 模块化设计
* 逻辑与UI分离
* 可扩展驱动架构
* 面向自动测试系统的可扩展平台雏形

---

## 📬 联系

如需交流自动测试系统架构设计或仪器控制开发经验，可联系作者。
邮箱：liuyang20_edu@163.com
```

---
