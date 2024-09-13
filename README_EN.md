English | [简体中文](./README.md)

# SA5Z-BSP Development Framework

SA5Z-BSP is developed based on the Zhiduojing Demo code component, which can build projects more quickly and reduce duplication of work.

## 1.Prerequisites

- Keil or gcc installed.
- Use a C99 compiler(C++11 is optional).

## 2. Quick Start

- Supported Development Boards
  - [AC201-SA5Z30D1](https://www.corecourse.cn/forum.php?mod=viewthread&tid=29172)
  - [AC201-SA5Z50D0](https://www.corecourse.cn/forum.php?mod=viewthread&tid=29651&highlight=AC201-SA5Z50D0) //TODO
- [Keil Config](./docs/Keil.md)
- [FPGA Config](./docs/fpga.md)

## 3. Peripheral Drivers

- uart: Combine FreeRTOS to build an integration of interrupts and Streams.。
- flash：Configure DMA to improve read and write performance on FreeRTOS-based systems.

## 4. Component support

- Real-time systems: FreeRTOS
- Encryption Components: GmSSL
- LOG component: ported from ESP-IDF.

## 5. TODO List

- LWIP support.
- More peripheral driver support.
- GCC and Cmake support.

## License

The project uses the Apache-2.0 open source protocol. For details, please read the contents of the LICENSE file in the project.