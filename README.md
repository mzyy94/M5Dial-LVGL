# M5Dial-LVGL
[![PlatformIO CI](https://github.com/mzyy94/M5Dial-LVGL/actions/workflows/ci.yml/badge.svg)](https://github.com/mzyy94/M5Dial-LVGL/actions/workflows/ci.yml)

LVGL porting for M5Dial

## Environments

- PlatformIO 6.1 with [espressif32@6.5.0]
- [ESP-IDF 5.1.2]

[espressif32@6.5.0]: https://github.com/platformio/platform-espressif32/releases/tag/v6.5.0
[ESP-IDF 5.1.2]: https://github.com/espressif/esp-idf/releases/tag/v5.1.2

## Setup

### PlatformIO

Specify M5Dial-LVGL git repo in [`lib_deps`] option.

```ini
lib_deps =
	M5Dial-LVGL=https://github.com/mzyy94/M5Dial-LVGL.git#v0.0.1
```

[`lib_deps`]: https://docs.platformio.org/en/latest/projectconf/sections/env/options/library/lib_deps.html

### ESP-IDF

Create [`idf_component.yml`] in **main** directory and put item in dependencies section.

```yaml
dependencies:
  mzyy94/M5Dial-LVGL:
    git: https://github.com/mzyy94/M5Dial-LVGL.git
    version: v0.0.1
```

[`idf_component.yml`]: https://espressif-docs.readthedocs-hosted.com/projects/idf-component-manager/en/v1.4.0/reference/manifest_file.html

## Usage

Call `m5dial_lvgl_init()` first, `m5dial_lvgl_next()` in a loop.
Please refer to examples for more details.

## Examples

| [hello_world]| [touch_button]| [dial_number]|
|:------------:|:-------------:|:------------:|
|![hello-world]|![touch-button]|![dial-number]|
|Simple drawing|  Touch input  | Encoder input|

[hello_world]: ./examples/hello_world
[touch_button]: ./examples/touch_button
[dial_number]: ./examples/dial_number

[hello-world]: ./docs/hello-world.png
[touch-button]: ./docs/touch-button.png
[dial-number]: ./docs/dial-number.png

## License

[MIT](LICENSE)
