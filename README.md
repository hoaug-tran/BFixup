# BFixup

A Lilu plugin that works around OpenGL crashes and performance issues in Chromium-based browsers (Google Chrome, Microsoft Edge, Electron apps) on macOS.

Originally created by **jalavoui** on InsanelyMac. This fork updates the plugin to use modern Lilu routing APIs and extends support to newer macOS versions.

## What's Changed in This Fork

- Switched from deprecated `routeFunctionLong` to `routeMultipleLong` (`RouteRequest`) to prevent race conditions and kernel panics when chaining hooks with other Lilu plugins.
- Hardened page validation hook with null-pointer checks.
- Added error logging when Lilu callback registration or route installation fails.
- Updated minimum Lilu dependency requirement to 1.7.2.

## Supported macOS Versions

- macOS Big Sur (11.x / Darwin 20)
- macOS Monterey (12.x / Darwin 21)
- macOS Ventura (13.x / Darwin 22)
- macOS Sonoma (14.x / Darwin 23)
- macOS Sequoia (15.x / Darwin 24)

## Installation

1. Copy `BFixup.kext` to `EFI/OC/Kexts/`.
2. Add `BFixup.kext` into your OpenCore `config.plist` under `Kernel -> Add`.
   Make sure it loads **after** `Lilu.kext`.
3. Restart your system.

## Building from Source

### Requirements

- macOS with Xcode and Command Line Tools
- [MacKernelSDK](https://github.com/acidanthera/MacKernelSDK)
- [Lilu](https://github.com/acidanthera/Lilu) headers (in `Lilu.kext/Contents/Resources/Headers`)

### Build Command

```sh
xcodebuild -project BFixup.xcodeproj -scheme BFixup -configuration Release
```

The output kext will be at `build/Build/Products/Release/BFixup.kext`.

## Credits

- [jalavoui](https://www.insanelymac.com/forum/topic/358160-howto-avoid-opengl-crash-and-speed-up-chrome-ms-edge-browsers/) for creating BFixup and discovering the original OpenGL workaround.
- **hoping** for the Sonoma and Sequoia patch byte patterns.
- [Acidanthera](https://github.com/acidanthera) for Lilu and MacKernelSDK.
- [osy](https://github.com/osy) for the original plugin base.

## License

This project is licensed under the [MIT License](LICENSE).
