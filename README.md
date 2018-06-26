# Getting started with mbed-gapuino-sensorboard

This guide reviews the steps required to get ultra-compact sensor for relative humidity and temperature HTS221, to get a 3D digital accelerometer and a 3D digital gyroscope sensor LSM6DSL, to get Time-of-Flight (ToF) laser-ranging module VL53L0X, to get High Accuracy Ambient Light Sensor VEML6030, to get Barometric Pressure Sensor BMP280, to get an ultra-low-power high-performance three-axis magnetic sensor LIS3MDL working on an mbed OS platform.

Please install [mbed CLI](https://github.com/ARMmbed/mbed-cli#installing-mbed-cli).

## Import the example application

From the command-line, get the example:

```
mbed import https://github.com/GreenWaves-Technologies/mbed-gapuino-sensorboard.git
```
or
```
git clone https://github.com/GreenWaves-Technologies/mbed-example-sensorboard-bmp280.git
```

For problem of `hg` tool
```
sudo apt-get install mercurial
```
or
```
sudo yum install mercurial
```

For problem of `python missing module`, try following commands according to your python version :
```
sudo pip install mbed-cli
sudo pip install -r mbed-os/requirements.txt

sudo pip2 install mbed-cli
sudo pip2 install -r mbed-os/requirements.txt

sudo pip3 install mbed-cli
sudo pip3 install -r mbed-os/requirements.txt
```

## Get the source and export your compiler path, for example :
```
cd mbed-gapuino-sensorboard
mbed deploy
mbed config -G GCC_RISCV_PATH "/usr/lib/gap_riscv_toolchain/bin"
```
Then, please change `DEFAULT_SLAVE_ADDRESS` from `(0x77 << 1)` to `(0x76 << 1)` in ./BMP280/BMP280.h according to gapuino sensor board connection

### Now compile

Invoke `mbed compile`, and specify the name of your platform and your favorite toolchain (`GCC_ARM`, `ARM`, `IAR`, `GCC_RISCV`). For example, for the RISC-V GCC Compile :

```
mbed compile -m GAP8 -t GCC_RISCV
```

Your PC may take a few minutes to compile your code. At the end, you see the following result:

```
Elf2Bin: mbed-gapuino-sensorboard
+-----------------+-------+-------+------+
| Module          | .text | .data | .bss |
+-----------------+-------+-------+------+
| BUILD/GAP8      | 43182 |  1077 | 2655 |
| [fill]          |     2 |     7 |   17 |
| [lib]/c.a       |  7446 |  2096 |   60 |
| [lib]/gcc.a     | 12310 |     0 |    0 |
| [lib]/m.a       |  4460 |     0 |    0 |
| mbed-os/targets |   288 |     4 |   28 |
| Subtotals       | 67688 |  3184 | 2760 |
+-----------------+-------+-------+------+
Total Static RAM memory (data + bss): 5944 bytes
Total Flash memory (text + data): 70872 bytes

Image: ./BUILD/GAP8/GCC_RISCV/mbed-gapuino-sensorboard.bin
```

### Program your board

1. Connect your device (with sensor board) to the computer over USB.
1. Execute the script (make sure you have already install the [gap_sdk](https://github.com/GreenWaves-Technologies/gap_sdk)) :

```
source ./USER_PATH/gap_sdk/sourceme.sh
run_mbed ./BUILD/GAP8/GCC_RISCV/mbed-gapuino-sensorboard.elf
```

The informations of all sensors will be printed every 1 seconds (support soft float but do not support printf with float).

## Troubleshooting

If you have problems, you can review the [documentation](https://os.mbed.com/docs/latest/tutorials/debugging.html) for suggestions on what could be wrong and how to fix it.