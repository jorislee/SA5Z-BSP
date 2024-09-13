[English](./README_EN.md) | 简体中文

# SA5Z-BSP 开发框架

基于智多晶 Demo 代码组件开发构建的 SA5Z-BSP，用以更快速的构建项目和减少重复工作。

## 1.先决条件

- Keil 的安装或后续 GCC, Cmake。
- 使用 C99 编译器(C++11 可选)。

## 2. 快速入门

- 支持开发板
  - [AC201-SA5Z30D1](https://www.corecourse.cn/forum.php?mod=viewthread&tid=29172)
  - [AC201-SA5Z50D0](https://www.corecourse.cn/forum.php?mod=viewthread&tid=29651&highlight=AC201-SA5Z50D0) //TODO
- [Keil 配置说明](./docs/Keil.md)
- [FPGA 配置说明](./docs/fpga.md)

## 3. 外设驱动

- uart: 结合 FreeRTOS 构建中断与 Stream 的融和。
- flash：配置 DMA 以提高基于 FreeRTOS 的系统的读写性能。

## 4. 组件支持。

- 实时系统：FreeRTOS。
- 加密组件：GmSSL。
- LOG组件：ESP-IDF 中移植。

## 5. 待办事项

- LWIP 支持。
- 更多外设驱动支持。
- GCC 与 Cmake 支持。

## 许可证

本项目采用Apache-2.0开源协议，具体请阅读本项目中LICENSE文件内容。