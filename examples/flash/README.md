[English](./README_EN.md) | 简体中文

# flash 例程

读写 flash 数据并打印输出。

## log output

```
[0;32mI (0) xs.main: flash id = 0xef4017[0m
[0;32mI (1) xs.main: ==============flash read================[0m
[0;32mI (1) xs.main: ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff[0m
[0;32mI (2) xs.main: ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff[0m
[0;32mI (3) xs.main: ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff[0m
[0;32mI (3) xs.main: ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff[0m
[0;32mI (4) xs.main: ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff[0m
[0;32mI (5) xs.main: ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff[0m
[0;32mI (5) xs.main: ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff[0m
[0;32mI (6) xs.main: ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff[0m
[0;32mI (6) xs.main: ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff[0m
[0;32mI (7) xs.main: ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff[0m
[0;32mI (8) xs.main: ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff[0m
[0;32mI (8) xs.main: ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff[0m
[0;32mI (9) xs.main: ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff[0m
[0;32mI (10) xs.main: ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff[0m
[0;32mI (10) xs.main: ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff[0m
[0;32mI (11) xs.main: ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff[0m
[0;32mI (1074) xs.main: ==============flash write================[0m
[0;32mI (1075) xs.main: ==============flash read back================[0m
[0;32mI (1075) xs.main: 00 01 02 03 04 05 06 07 08 09 0a 0b 0c 0d 0e 0f[0m
[0;32mI (1076) xs.main: 10 11 12 13 14 15 16 17 18 19 1a 1b 1c 1d 1e 1f[0m
[0;32mI (1076) xs.main: 20 21 22 23 24 25 26 27 28 29 2a 2b 2c 2d 2e 2f[0m
[0;32mI (1077) xs.main: 30 31 32 33 34 35 36 37 38 39 3a 3b 3c 3d 3e 3f[0m
[0;32mI (1078) xs.main: 40 41 42 43 44 45 46 47 48 49 4a 4b 4c 4d 4e 4f[0m
[0;32mI (1079) xs.main: 50 51 52 53 54 55 56 57 58 59 5a 5b 5c 5d 5e 5f[0m
[0;32mI (1079) xs.main: 60 61 62 63 64 65 66 67 68 69 6a 6b 6c 6d 6e 6f[0m
[0;32mI (1080) xs.main: 70 71 72 73 74 75 76 77 78 79 7a 7b 7c 7d 7e 7f[0m
[0;32mI (1081) xs.main: 80 81 82 83 84 85 86 87 88 89 8a 8b 8c 8d 8e 8f[0m
[0;32mI (1081) xs.main: 90 91 92 93 94 95 96 97 98 99 9a 9b 9c 9d 9e 9f[0m
[0;32mI (1082) xs.main: a0 a1 a2 a3 a4 a5 a6 a7 a8 a9 aa ab ac ad ae af[0m
[0;32mI (1083) xs.main: b0 b1 b2 b3 b4 b5 b6 b7 b8 b9 ba bb bc bd be bf[0m
[0;32mI (1083) xs.main: c0 c1 c2 c3 c4 c5 c6 c7 c8 c9 ca cb cc cd ce cf[0m
[0;32mI (1084) xs.main: d0 d1 d2 d3 d4 d5 d6 d7 d8 d9 da db dc dd de df[0m
[0;32mI (1085) xs.main: e0 e1 e2 e3 e4 e5 e6 e7 e8 e9 ea eb ec ed ee ef[0m
[0;32mI (1085) xs.main: f0 f1 f2 f3 f4 f5 f6 f7 f8 f9 fa fb fc fd fe ff[0m
[0;32mI (2086) xs.main: ==============flash dma read================[0m
[0;32mI (2086) xs.main: ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff[0m
[0;32mI (2087) xs.main: ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff[0m
[0;32mI (2087) xs.main: ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff[0m
[0;32mI (2088) xs.main: ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff[0m
[0;32mI (2089) xs.main: ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff[0m
[0;32mI (2090) xs.main: ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff[0m
[0;32mI (2090) xs.main: ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff[0m
[0;32mI (2091) xs.main: ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff[0m
[0;32mI (2092) xs.main: ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff[0m
[0;32mI (2092) xs.main: ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff[0m
[0;32mI (2093) xs.main: ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff[0m
[0;32mI (2094) xs.main: ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff[0m
[0;32mI (2094) xs.main: ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff[0m
[0;32mI (2095) xs.main: ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff[0m
[0;32mI (2096) xs.main: ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff[0m
[0;32mI (2097) xs.main: ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff ff[0m
[0;32mI (3174) xs.main: ==============flash dma write================[0m
[0;32mI (3174) xs.main: ==============flash dma read back================[0m
[0;32mI (3174) xs.main: 00 01 02 03 04 05 06 07 08 09 0a 0b 0c 0d 0e 0f[0m
[0;32mI (3175) xs.main: 10 11 12 13 14 15 16 17 18 19 1a 1b 1c 1d 1e 1f[0m
[0;32mI (3176) xs.main: 20 21 22 23 24 25 26 27 28 29 2a 2b 2c 2d 2e 2f[0m
[0;32mI (3176) xs.main: 30 31 32 33 34 35 36 37 38 39 3a 3b 3c 3d 3e 3f[0m
[0;32mI (3177) xs.main: 40 41 42 43 44 45 46 47 48 49 4a 4b 4c 4d 4e 4f[0m
[0;32mI (3178) xs.main: 50 51 52 53 54 55 56 57 58 59 5a 5b 5c 5d 5e 5f[0m
[0;32mI (3178) xs.main: 60 61 62 63 64 65 66 67 68 69 6a 6b 6c 6d 6e 6f[0m
[0;32mI (3179) xs.main: 70 71 72 73 74 75 76 77 78 79 7a 7b 7c 7d 7e 7f[0m
[0;32mI (3180) xs.main: 80 81 82 83 84 85 86 87 88 89 8a 8b 8c 8d 8e 8f[0m
[0;32mI (3180) xs.main: 90 91 92 93 94 95 96 97 98 99 9a 9b 9c 9d 9e 9f[0m
[0;32mI (3181) xs.main: a0 a1 a2 a3 a4 a5 a6 a7 a8 a9 aa ab ac ad ae af[0m
[0;32mI (3182) xs.main: b0 b1 b2 b3 b4 b5 b6 b7 b8 b9 ba bb bc bd be bf[0m
[0;32mI (3183) xs.main: c0 c1 c2 c3 c4 c5 c6 c7 c8 c9 ca cb cc cd ce cf[0m
[0;32mI (3183) xs.main: d0 d1 d2 d3 d4 d5 d6 d7 d8 d9 da db dc dd de df[0m
[0;32mI (3184) xs.main: e0 e1 e2 e3 e4 e5 e6 e7 e8 e9 ea eb ec ed ee ef[0m
[0;32mI (3185) xs.main: f0 f1 f2 f3 f4 f5 f6 f7 f8 f9 fa fb fc fd fe ff[0m
```

