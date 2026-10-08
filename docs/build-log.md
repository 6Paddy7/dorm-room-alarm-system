# Build log

## 2026-10-08 (M0)

### What does `set-target` do?
It selects the chip the project is built for (here esp32s3). That choice decides
the compiler (`xtensa-esp32s3-elf-gcc`), the chip-specific drivers and startup
code, and the flash layout (the S3 bootloader goes at `0x0`, the original ESP32's
at `0x1000`). Because nothing built for one chip works on another, it runs a full
clean first: `build/` is deleted and a fresh `sdkconfig` is created. In this repo
the target is set in `sdkconfig.defaults`, so a fresh clone needs no `set-target`.

### Why three binaries, and where does each go?
- **Bootloader** (`0x0`): loaded first by the chip's ROM. Sets up flash, reads the
  partition table and starts the app.
- **Partition table** (`0x8000`): a map of the 16 MB flash: where the app lives,
  where NVS storage is (the disarm code will go there), and so on.
- **App** (`0x10000`): my code, compiled together with ESP-IDF and FreeRTOS.

They are separate because they change at different rates: the app changes on every
build, the partition table rarely and the bootloader almost never. That way the app
can be reflashed on its own.

### What are `sdkconfig`, `sdkconfig.defaults` and `menuconfig`?
- **`sdkconfig`**: the complete project configuration, thousands of options. It is
  generated, so it is gitignored.
- **`sdkconfig.defaults`**: only the options I deliberately changed (target and
  16 MB flash). Committed. It is read only when `sdkconfig` is created, so after
  changing it, delete `sdkconfig` and rebuild.
- **`menuconfig`**: the menu for browsing and changing `sdkconfig`
  (`idf.py menuconfig`, or the gear icon in the VS Code status bar).

### What happens between power-on and `app_main`?
1. The chip's ROM bootloader (factory code, can't change) loads the bootloader
   from flash at `0x0`.
2. The bootloader reads the partition table at `0x8000` and loads the app.
3. ESP-IDF's startup code sets up memory, starts both CPU cores and starts FreeRTOS.
4. FreeRTOS creates `main_task` on CPU0, which calls `app_main()`.

When `app_main` returns, only `main_task` ends; the system keeps running. Seen in
the monitor:

```
I (273) main_task: Calling app_main()
I (273) main: Dorm room alarm system: boot
I (273) main_task: Returned from app_main()
```

### Other findings
- Module marking confirmed: `ESP32-S3-N16R8` (16 MB flash, 8 MB octal PSRAM),
  matching what esptool detected.
- Every new project folder needs its own VS Code setup (CMake Tools disabled,
  ESP-IDF setup selected). The steps are in the README.