#include "modmanager.h"

#define LISTENFORSETTING(type, setter, settingName) \
    geode::listenForSettingChanges(settingName, [](type val) { \
        ModManager::get().setter(val); \
    })

ModManager &ModManager::get() {
    if (!s_instance) {
        s_instance = new ModManager();
        s_instance->init();
    }
    return *s_instance;
}

bool ModManager::init() {
    auto mod = geode::Mod::get();

    m_enabled = mod->getSettingValue<bool>("enabled");

    m_offsetX = mod->getSettingValue<double>("offsetX");
    m_offsetY = mod->getSettingValue<double>("offsetY");
    m_scale = mod->getSettingValue<double>("scale");
    m_opacity = mod->getSettingValue<double>("opacity");

    return true;
}

$on_mod(Loaded) {
    auto &manager = ModManager::get();

    LISTENFORSETTING(bool, setEnabled, "enabled");

    LISTENFORSETTING(double, setOffsetX, "offsetX");
    LISTENFORSETTING(double, setOffsetY, "offsetY");
    LISTENFORSETTING(double, setScale, "scale");
    LISTENFORSETTING(double, setOpacity, "opacity");
}