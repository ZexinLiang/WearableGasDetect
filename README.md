# WearableGasDetect

**English** | [简体中文](#wearablegasdetect-可穿戴气体检测系统)

WearableGasDetect is a wearable gas-detection system built around a WCH CH32V307 main controller, CH582 wireless/sensor sub-device firmware, LVGL/GUI Guider user interface assets, a remote monitoring server, PCB design files, and enclosure/mechanical models. The repository keeps the embedded firmware, UI source, server-side web application, PCB deliverables, and historical backup snapshots in one place.

## Table of Contents

- [System Overview](#system-overview)
- [Repository Layout](#repository-layout)
- [Firmware Projects](#firmware-projects)
- [Remote Server](#remote-server)
- [Hardware & Mechanical Assets](#hardware--mechanical-assets)
- [Toolchain](#toolchain)
- [Build & Deployment](#build--deployment)
- [Notes on Backups](#notes-on-backups)
- [License](#license)

## System Overview

```text
Gas / environment sensors
          |
          v
+--------------------------+      wireless / serial link      +--------------------------+
| Sub device               | <------------------------------> | Main body controller     |
| CH582 firmware           |                                  | CH32V307 + LVGL UI       |
| sensor acquisition / BLE |                                  | display / alarm / logic  |
+--------------------------+                                  +------------+-------------+
                                                                            |
                                                                            | network / local service
                                                                            v
                                                               +------------+-------------+
                                                               | RemoteServer              |
                                                               | Backend + Frontend        |
                                                               | monitoring / visualization|
                                                               +--------------------------+
```

The current main firmware is the LVGL v7 CH32V307 project. LVGL v8 and earlier experiments are kept under `Backups/` for reference.

## Repository Layout

| Path | Description |
|---|---|
| [`MainBody_CH32V307_lvglv7/`](MainBody_CH32V307_lvglv7) | Current CH32V307 main-body firmware with LVGL v7 UI integration |
| [`GUIGuiderUI/`](GUIGuiderUI) | NXP GUI Guider UI design projects and generated UI resources |
| [`RemoteServer/`](RemoteServer) | Monitoring / service-side application, split into backend and frontend |
| [`PCB/`](PCB) | PCB project files and Gerber deliverables for main board and sub board |
| [`Backups/`](Backups) | Historical firmware/UI/LVGL snapshots retained for traceability |
| [`models/`](models) | Enclosure and mechanical models (`.SLDPRT`, `.SLDASM`, `.STL`, `.SLDDRW`) |
| `主板设备以及IO占用.xlsx` | Main-board device and IO allocation sheet |
| `关于GUI Guider...docx` | GUI Guider / LVGL page-scroll workaround notes |

## Firmware Projects

| Path | Platform | Role |
|---|---|---|
| [`MainBody_CH32V307_lvglv7/MainBody_CH32V307`](MainBody_CH32V307_lvglv7/MainBody_CH32V307) | WCH CH32V307, MounRiver Studio | Main wearable controller: LVGL UI, alarm/buzzer, CH582 link, CH9142 communication, sensor/status logic |
| [`Backups/CH582F_Peri_Err`](Backups/CH582F_Peri_Err) | WCH CH582F, MounRiver Studio | CH582 peripheral/sub-device firmware snapshot for wireless or sensor-side experiments |
| [`Backups/MainBody_CH32V307_lvglv8`](Backups/MainBody_CH32V307_lvglv8) | CH32V307 + LVGL v8 | Historical LVGL v8 main-body experiment |
| [`Backups/MainBody_CH32V307_lvglv7`](Backups/MainBody_CH32V307_lvglv7) | CH32V307 + LVGL v7 | Historical LVGL v7 main-body snapshot |
| [`Backups/MainBody_CH32V307Backup`](Backups/MainBody_CH32V307Backup) | CH32V307 | Additional backup snapshot of the main-body firmware |
| [`Backups/lvgl8.3.10`](Backups/lvgl8.3.10) / [`Backups/temp`](Backups/temp) | LVGL source/examples | LVGL source, examples and generated UI experiments kept for comparison |

## Remote Server

`RemoteServer/` contains a web-based monitoring/service application:

| Path | Description |
|---|---|
| [`RemoteServer/Backend`](RemoteServer/Backend) | Backend service project with `CMakeLists.txt`, `requirements.txt`, and `MainServer/` notes |
| [`RemoteServer/Frontend`](RemoteServer/Frontend) | Vite/Vue frontend (`package.json`, `src/App.vue`, `src/main.js`) |

The backend/frontend are kept as source projects rather than prebuilt artifacts.

## Hardware & Mechanical Assets

- **Main controller:** WCH CH32V307 RISC-V MCU.
- **Sub device:** WCH CH582/CH582F wireless or sensor-side MCU firmware snapshots.
- **UI:** LVGL integrated with NXP GUI Guider generated resources.
- **PCB:**
  - `PCB/PCB-WearableGasDetect.epro` — main EasyEDA Professional PCB project.
  - `PCB/PCB-WirelessCharging.eprj` — wireless-charging related PCB project.
  - `PCB/Gerber_MainBoard.zip` and `PCB/Gerber_SubBoard.zip` — Gerber deliverables retained intentionally.
- **Mechanical models:** `models/` keeps SolidWorks and STL enclosure/assembly files.

Large CAD/PCB deliverables are intentionally retained in git as project assets.

## Toolchain

- **MounRiver Studio** for WCH CH32V307 / CH582 embedded projects (`.wvproj`, `.launch`).
- **WCH SDK / peripheral libraries** included in the firmware project tree.
- **LVGL + GUI Guider** for embedded UI design and generated UI source.
- **Node.js + pnpm/npm** for the Vite/Vue frontend.
- **Python/CMake toolchain** as required by `RemoteServer/Backend`.
- **EasyEDA Professional** for `.epro`/`.eprj` PCB files.
- **SolidWorks** or compatible CAD software for the mechanical model files.

## Build & Deployment

### CH32V307 main firmware

1. Install MounRiver Studio and the CH32V307 device support package.
2. Open `MainBody_CH32V307_lvglv7/MainBody_CH32V307/MainBody_CH32V307.wvproj`.
3. Build the project in MounRiver Studio.
4. Flash/debug through a WCH-Link compatible probe.
5. Regenerated files under `obj/`, `*.elf`, `*.hex`, `*.map`, etc. are excluded by `.gitignore`.

### GUI assets

Open the projects under `GUIGuiderUI/WearableGasUI/` in GUI Guider, regenerate LVGL resources if the screen layout changes, then integrate generated source into the CH32V307 firmware tree.

### Remote frontend

```bash
cd RemoteServer/Frontend
pnpm install
pnpm dev
```

Use `npm` if pnpm is not available; the lock file is kept for reproducible frontend installation.

### Remote backend

```bash
cd RemoteServer/Backend
python -m pip install -r requirements.txt
```

Then follow the backend project notes under `RemoteServer/Backend/README.md` and `RemoteServer/Backend/MainServer/README.md` for the actual service entrypoint and runtime parameters.

## Notes on Backups

- Backup folders are **kept intentionally**. They preserve LVGL v7/v8 migration history, CH582 experiments, and main-firmware snapshots.
- Self-contained archives such as `WearableGasDetect.rar` and `GUIGuiderUI/WearableGasUI_bak.zip` were removed from git tracking because their contents already exist in the repository tree.
- Gerber ZIP files under `PCB/` are retained because they are fabrication deliverables.
- Chinese file names and existing project paths are kept unchanged to avoid breaking local IDE and document references.

## License

Released under the MIT License. See [LICENSE](LICENSE).

---

# WearableGasDetect 可穿戴气体检测系统

[English](#wearablegasdetect) | **简体中文**

WearableGasDetect 是一个可穿戴气体检测系统，包含 WCH CH32V307 主控固件、CH582 无线/传感子机固件、LVGL/GUI Guider 界面工程、远程监控服务、PCB 设计文件以及外壳/结构模型。本仓库集中保存嵌入式代码、UI 源文件、服务端/前端代码、PCB 交付物和历史备份快照。

## 目录

- [系统概览](#系统概览)
- [仓库结构](#仓库结构)
- [固件工程](#固件工程)
- [远程服务](#远程服务)
- [硬件与结构资料](#硬件与结构资料)
- [开发工具](#开发工具)
- [编译与部署](#编译与部署)
- [关于备份](#关于备份)
- [许可协议](#许可协议)

## 系统概览

```text
气体 / 环境传感器
          |
          v
+--------------------------+      无线 / 串口链路       +--------------------------+
| 子设备                   | <-------------------------> | 主机控制器               |
| CH582 固件               |                            | CH32V307 + LVGL UI       |
| 传感采集 / BLE           |                            | 显示 / 报警 / 业务逻辑   |
+--------------------------+                            +------------+-------------+
                                                                      |
                                                                      | 网络 / 本地服务
                                                                      v
                                                         +------------+-------------+
                                                         | RemoteServer              |
                                                         | Backend + Frontend        |
                                                         | 监控 / 可视化             |
                                                         +--------------------------+
```

当前主线固件为 LVGL v7 版本 CH32V307 工程。LVGL v8 及早期实验保留在 `Backups/` 中用于追溯。

## 仓库结构

| 路径 | 说明 |
|---|---|
| [`MainBody_CH32V307_lvglv7/`](MainBody_CH32V307_lvglv7) | 当前 CH32V307 主机固件，集成 LVGL v7 UI |
| [`GUIGuiderUI/`](GUIGuiderUI) | NXP GUI Guider 界面工程和生成资源 |
| [`RemoteServer/`](RemoteServer) | 监控/服务端应用，分为后端与前端 |
| [`PCB/`](PCB) | 主板、子板 PCB 工程与 Gerber 交付物 |
| [`Backups/`](Backups) | 历史固件/UI/LVGL 快照，按用户确认保留 |
| [`models/`](models) | 外壳和结构模型（`.SLDPRT`、`.SLDASM`、`.STL`、`.SLDDRW`） |
| `主板设备以及IO占用.xlsx` | 主板设备与 IO 占用表 |
| `关于GUI Guider...docx` | GUI Guider / LVGL 页面滑动问题处理记录 |

## 固件工程

| 路径 | 平台 | 作用 |
|---|---|---|
| [`MainBody_CH32V307_lvglv7/MainBody_CH32V307`](MainBody_CH32V307_lvglv7/MainBody_CH32V307) | WCH CH32V307，MounRiver Studio | 主机控制器：LVGL UI、蜂鸣器/报警、CH582 链路、CH9142 通信、传感/状态逻辑 |
| [`Backups/CH582F_Peri_Err`](Backups/CH582F_Peri_Err) | WCH CH582F，MounRiver Studio | CH582 外设/子机固件快照，用于无线或传感端实验 |
| [`Backups/MainBody_CH32V307_lvglv8`](Backups/MainBody_CH32V307_lvglv8) | CH32V307 + LVGL v8 | LVGL v8 主机方案历史实验 |
| [`Backups/MainBody_CH32V307_lvglv7`](Backups/MainBody_CH32V307_lvglv7) | CH32V307 + LVGL v7 | LVGL v7 主机方案历史快照 |
| [`Backups/MainBody_CH32V307Backup`](Backups/MainBody_CH32V307Backup) | CH32V307 | 主机固件额外备份快照 |
| [`Backups/lvgl8.3.10`](Backups/lvgl8.3.10) / [`Backups/temp`](Backups/temp) | LVGL 源码/示例 | LVGL 源码、示例与生成界面实验，用于对比参考 |

## 远程服务

`RemoteServer/` 保存 Web 监控/服务端应用：

| 路径 | 说明 |
|---|---|
| [`RemoteServer/Backend`](RemoteServer/Backend) | 后端服务工程，含 `CMakeLists.txt`、`requirements.txt` 和 `MainServer/` 说明 |
| [`RemoteServer/Frontend`](RemoteServer/Frontend) | Vite/Vue 前端，含 `package.json`、`src/App.vue`、`src/main.js` |

后端和前端均以源码形式保留，不提交预构建产物。

## 硬件与结构资料

- **主控：** WCH CH32V307 RISC-V MCU。
- **子设备：** WCH CH582/CH582F 无线或传感端固件快照。
- **UI：** LVGL 与 NXP GUI Guider 生成资源集成。
- **PCB：**
  - `PCB/PCB-WearableGasDetect.epro` —— 主工程（立创 EDA 专业版）。
  - `PCB/PCB-WirelessCharging.eprj` —— 无线充电相关 PCB 工程。
  - `PCB/Gerber_MainBoard.zip`、`PCB/Gerber_SubBoard.zip` —— 主板/子板 Gerber 交付物，按用户确认保留。
- **结构模型：** `models/` 保存 SolidWorks 与 STL 外壳/装配文件。

大体积 CAD/PCB 交付文件按用户要求保留在仓库中。

## 开发工具

- **MounRiver Studio**：用于 WCH CH32V307 / CH582 嵌入式工程（`.wvproj`、`.launch`）。
- **WCH SDK / 外设库**：随固件工程保存。
- **LVGL + GUI Guider**：用于嵌入式 UI 设计与代码生成。
- **Node.js + pnpm/npm**：用于 Vite/Vue 前端。
- **Python/CMake 工具链**：按 `RemoteServer/Backend` 需求配置。
- **立创 EDA 专业版**：打开 `.epro` / `.eprj` PCB 文件。
- **SolidWorks** 或兼容 CAD 软件：打开结构模型。

## 编译与部署

### CH32V307 主机固件

1. 安装 MounRiver Studio 及 CH32V307 器件支持。
2. 打开 `MainBody_CH32V307_lvglv7/MainBody_CH32V307/MainBody_CH32V307.wvproj`。
3. 在 MounRiver Studio 中编译。
4. 使用 WCH-Link 兼容调试器烧录/调试。
5. `obj/`、`*.elf`、`*.hex`、`*.map` 等再生文件已写入 `.gitignore`。

### GUI 资源

用 GUI Guider 打开 `GUIGuiderUI/WearableGasUI/` 下的工程；修改界面后重新生成 LVGL 资源，再集成到 CH32V307 固件目录。

### 远程前端

```bash
cd RemoteServer/Frontend
pnpm install
pnpm dev
```

如无 pnpm 可改用 npm；仓库保留 lock 文件用于复现依赖安装。

### 远程后端

```bash
cd RemoteServer/Backend
python -m pip install -r requirements.txt
```

随后按 `RemoteServer/Backend/README.md` 与 `RemoteServer/Backend/MainServer/README.md` 中的入口和运行参数启动服务。

## 关于备份

- `Backups/` 按用户确认**保留**，用于追溯 LVGL v7/v8 迁移、CH582 实验以及主机固件版本演进。
- `WearableGasDetect.rar`、`GUIGuiderUI/WearableGasUI_bak.zip` 等自包含归档已移出 git 跟踪，因为内容已在仓库树中存在。
- `PCB/` 下 Gerber ZIP 是制板交付物，按用户确认保留。
- 中文文件名和既有工程路径保持不变，避免破坏本地 IDE 与文档引用。

## 许可协议

本仓库基于 MIT 许可证开源，详见 [LICENSE](LICENSE)。
