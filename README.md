# Cmake Project for STM32WB
Minimal C++ project that builds for STM32F4xx devices. Tested with Nucleo Board P-NUCLEO-WB55.

## Adapted 

This project is an adapted version from [Marcus Forte](https://github.com/Marcus-Forte/learning-uc/). He described everything on [YouTube](https://youtu.be/Zdid7PgY75U).

## Debug 

- Connect ST-Link V2 on your host machine. Make sure 
- install `stlink` tools. 
- On the host, start session with `st-util`. This serves as a gdb server. Check launch.json for the host address from within the docker container.
- Start Lauch Vscode target.
