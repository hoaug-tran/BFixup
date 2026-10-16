#include <Headers/kern_api.hpp>
#include <Headers/plugin_start.hpp>

#define UNLIKELY(x) __builtin_expect(!!(x), 0)
#define MODULE_SHORT "b1"


static const uint8_t kBigSurAddrLibGetBaseArrayModeReturnOriginal[] = {
    0x8B, 0x45, 0xE0, 0xB9, 0x01, 0x00, 0x04, 0x48,
    0x89, 0xC2, 0x21, 0xCA, 0x39, 0xCA, 0x75, 0x4E,
};

static const uint8_t kBigSurAddrLibGetBaseArrayModeReturnPatched[] = {
    0x8B, 0x45, 0xE0, 0xB9, 0x01, 0x00, 0x04, 0x48,
    0x89, 0xC2, 0x21, 0xCA, 0x39, 0xCA, 0xEB, 0x4E,
};

static const uint8_t kMontereyAddrLibGetBaseArrayModeReturnOriginal[] = {
    0xA9, 0x01, 0x00, 0x04, 0x48, 0x75, 0x79,
    0x8B, 0x4D, 0xE4, 0x89, 0xCA, 0xF7, 0xD2,
};

static const uint8_t kMontereyAddrLibGetBaseArrayModeReturnPatched[] = {
    0xA9, 0x01, 0x00, 0x04, 0x48, 0xEB, 0x79,
    0x8B, 0x4D, 0xE4, 0x89, 0xCA, 0xF7, 0xD2,
};

static const uint8_t kVentura133AddrLibGetBaseArrayModeReturnOriginal[] = {
    0x8B, 0x55, 0xE0, 0x89, 0xD0, 0xF7, 0xD0, 0xA9, 0x01,
    0x00, 0x04, 0x48, 0x0F, 0x85, 0xA0, 0x00, 0x00, 0x00,
};

static const uint8_t kVentura133AddrLibGetBaseArrayModeReturnPatched[] = {
    0x8B, 0x55, 0xE0, 0x89, 0xD0, 0xF7, 0xD0, 0xA9, 0x01,
    0x00, 0x04, 0x48, 0xE9, 0xA1, 0x00, 0x00, 0x00, 0x90,
};

static const uint8_t kVentura133AddrLibGetBaseArrayModeReturnOriginal2[] = {
    0xC6, 0x83, 0x46, 0xC6, 0x00, 0x00, 0x33,
    0xC6, 0x83, 0x48, 0xC6, 0x00, 0x00, 0x32,
};

static const uint8_t kVentura133AddrLibGetBaseArrayModeReturnPatched2[] = {
    0xC6, 0x83, 0x46, 0xC6, 0x00, 0x00, 0x33,
    0xC6, 0x83, 0x48, 0xC6, 0x00, 0x00, 0x32,
};

static const uint8_t kSonomaAddrLibGetBaseArrayModeReturnOriginal[] = {
    0x8B, 0x55, 0xE0, 0x89, 0xD0, 0xF7, 0xD0, 0xA9, 0x01,
    0x00, 0x04, 0x48, 0x0F, 0x85, 0xA1, 0x00, 0x00, 0x00,
};
static const uint8_t kSonomaAddrLibGetBaseArrayModeReturnPatched[] = {
    0x8B, 0x55, 0xE0, 0x89, 0xD0, 0xF7, 0xD0, 0xA9, 0x01,
    0x00, 0x04, 0x48, 0xE9, 0xA2, 0x00, 0x00, 0x00, 0x90,
};

static const uint8_t kSequoiaAddrLibGetBaseArrayModeReturnOriginal[] = {
    0x83, 0x48, 0xC6, 0x00, 0x00, 0x34, 0xEB, 0x60, 0x8B, 0x4D, 0xE0,
    0xF7, 0xD1, 0xF7, 0xC1, 0x01, 0x00, 0x04, 0x48, 0x75, 0x45,
};
static const uint8_t kSequoiaAddrLibGetBaseArrayModeReturnPatched[] = {
    0x83, 0x48, 0xC6, 0x00, 0x00, 0x34, 0xEB, 0x60, 0x8B, 0x4D, 0xE0,
    0xF7, 0xD1, 0xF7, 0xC1, 0x01, 0x00, 0x04, 0x48, 0xEB, 0x45};

static mach_vm_address_t orig_cs_validate{};

static void patched_cs_validate_page(vnode_t vp, memory_object_t pager,
                                     memory_object_offset_t page_offset,
                                     const void *data, int *validated,
                                     int *tainted, int *nx) {
  char path[1024];
  int pathlen = 1024;
  FunctionCast(patched_cs_validate_page, orig_cs_validate)(
      vp, pager, page_offset, data, validated, tainted, nx);
  if (!data || !vp)
    return;
  if (vn_getpath(vp, path, &pathlen) == 0 &&
      UserPatcher::matchSharedCachePath(path)) {

    if (getKernelVersion() == KernelVersion::Sequoia)
      if (UNLIKELY(KernelPatcher::findAndReplace(
              const_cast<void *>(data), PAGE_SIZE,
              kSequoiaAddrLibGetBaseArrayModeReturnOriginal,
              sizeof(kSequoiaAddrLibGetBaseArrayModeReturnOriginal),
              kSequoiaAddrLibGetBaseArrayModeReturnPatched,
              sizeof(kSequoiaAddrLibGetBaseArrayModeReturnPatched)))) {
        return;
      }

    if (getKernelVersion() == KernelVersion::Sonoma)
      if (UNLIKELY(KernelPatcher::findAndReplace(
              const_cast<void *>(data), PAGE_SIZE,
              kSonomaAddrLibGetBaseArrayModeReturnOriginal,
              sizeof(kSonomaAddrLibGetBaseArrayModeReturnOriginal),
              kSonomaAddrLibGetBaseArrayModeReturnPatched,
              sizeof(kSonomaAddrLibGetBaseArrayModeReturnPatched)))) {
        return;
      }

    if (getKernelVersion() == KernelVersion::Ventura)
      if (UNLIKELY(KernelPatcher::findAndReplace(
              const_cast<void *>(data), PAGE_SIZE,
              kVentura133AddrLibGetBaseArrayModeReturnOriginal,
              sizeof(kVentura133AddrLibGetBaseArrayModeReturnOriginal),
              kVentura133AddrLibGetBaseArrayModeReturnPatched,
              sizeof(kVentura133AddrLibGetBaseArrayModeReturnPatched)))) {
        KernelPatcher::findAndReplace(
            const_cast<void *>(data), PAGE_SIZE,
            kVentura133AddrLibGetBaseArrayModeReturnOriginal2,
            sizeof(kVentura133AddrLibGetBaseArrayModeReturnOriginal2),
            kVentura133AddrLibGetBaseArrayModeReturnPatched2,
            sizeof(kVentura133AddrLibGetBaseArrayModeReturnPatched2));
        return;
      }

    if (getKernelVersion() == KernelVersion::Monterey)
      if (UNLIKELY(KernelPatcher::findAndReplace(
              const_cast<void *>(data), PAGE_SIZE,
              kMontereyAddrLibGetBaseArrayModeReturnOriginal,
              sizeof(kMontereyAddrLibGetBaseArrayModeReturnOriginal),
              kMontereyAddrLibGetBaseArrayModeReturnPatched,
              sizeof(kMontereyAddrLibGetBaseArrayModeReturnPatched)))) {
        return;
      }

    if (getKernelVersion() <= KernelVersion::BigSur)
      if (UNLIKELY(KernelPatcher::findAndReplace(
              const_cast<void *>(data), PAGE_SIZE,
              kBigSurAddrLibGetBaseArrayModeReturnOriginal,
              sizeof(kBigSurAddrLibGetBaseArrayModeReturnOriginal),
              kBigSurAddrLibGetBaseArrayModeReturnPatched,
              sizeof(kBigSurAddrLibGetBaseArrayModeReturnPatched)))) {
        return;
      }
  }
}

static void pluginStart() {
  if (getKernelVersion() < KernelVersion::BigSur ||
      getKernelVersion() > KernelVersion::Sequoia)
    return;

  auto error = lilu.onPatcherLoad([](void *, KernelPatcher &patcher) {
    KernelPatcher::RouteRequest requests[]{
        {"_cs_validate_page", patched_cs_validate_page, orig_cs_validate}};
    if (!patcher.routeMultipleLong(KernelPatcher::KernelID, requests)) {
      SYSLOG("bfixup", "failed to route _cs_validate_page");
      return;
    }
    DBGLOG("bfixup", "installed _cs_validate_page hook");
  });
  if (error != LiluAPI::Error::NoError)
    SYSLOG("bfixup", "failed to register patcher callback: %d",
           static_cast<int>(error));
}

PluginConfiguration ADDPR(config){
    xStringify(PRODUCT_NAME),
    parseModuleVersion(xStringify(MODULE_VERSION)),
    LiluAPI::AllowNormal | LiluAPI::AllowInstallerRecovery |
        LiluAPI::AllowSafeMode,
    nullptr,
    0,
    nullptr,
    0,
    nullptr,
    0,
    KernelVersion::BigSur,
    KernelVersion::Sequoia,
    []() { pluginStart(); },
};
