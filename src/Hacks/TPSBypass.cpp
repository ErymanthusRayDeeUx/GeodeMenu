#include <Geode/Geode.hpp>
#include <Geode/modify/GJBaseGameLayer.hpp>
#include "../Client/Client.h"

using namespace geode::prelude;

template <typename T>
inline std::vector<uint8_t> getBytes(T value) {
    return std::vector<uint8_t>((uint8_t *) &value, (uint8_t *) &value + sizeof(T));
    //std::vector<uint8_t> out(sizeof(T));
    //T in = value;
    //std::memcpy(out.data(), &in, out.size());

    //return out;
}

std::vector<Patch*> patches = {};

void updateTPSPatches(bool tpsEnabled)
{    
    if (patches.size() > 0)
    {
        for (auto catgirl : patches)
        {
            Mod::get()->disownPatch(catgirl); // goodbye cutie you will be very missed :3c
        }

        patches.clear();
    }

    float tps = 240;

    auto x = numFromString<float>(as<InputModule*>(Client::GetModule("tps-bypass")->options[0])->text);

    if (x.isOk())
    {
        tps = x.value();
    }

    if (tpsEnabled)
    {
        #ifdef GEODE_IS_WINDOWS
        //patches.push_back(Mod::get()->patch(reinterpret_cast<void*>(geode::base::get() + 0x5ec6d0), geode::toByteArray<double>(1.0f / tps)).unwrap());
        #endif

        #ifdef GEODE_IS_ANDROID32
        patches.push_back(Mod::get()->patch(reinterpret_cast<void*>(geode::base::get() + (0x46ce38 - 0x10000)), getBytes<double>(1.0f / tps)).unwrap());
        #endif

        #ifdef GEODE_IS_ANDROID64
        patches.push_back(Mod::get()->patch(reinterpret_cast<void*>(geode::base::get() + (0x9384b8 - 0x100000)), getBytes<double>(1.0f / tps)).unwrap());
        #endif

        #ifdef GEODE_IS_INTEL_MAC
        patches.push_back(Mod::get()->patch(reinterpret_cast<void*>(geode::base::get() + 0x823b00), getBytes<double>(1.0f / tps)).unwrap());
        #endif

        #ifdef GEODE_IS_ARM_MAC
        
        #endif

        //patches.push_back(Mod::get()->patch(reinterpret_cast<void*>(geode::base::get() + 0x823b00), getBytes<double>(1.0f / tps)).unwrap());

        #ifdef GEODE_IS_MACOS
        //patches.push_back(Mod::get()->patch(reinterpret_cast<void*>(geode::base::get() + 0x7e9c60), getBytes<double>(1.0f / tps)).unwrap());
        #endif

        #ifdef GEODE_IS_IOS
        patches.push_back(Mod::get()->patch(reinterpret_cast<void*>(geode::base::get() + 0x642b60), getBytes<double>(1.0f / tps)).unwrap());
        #endif
    }
}

class TPSChangedDelegate : public ModuleChangeDelegate
{
    virtual void onModuleChanged(bool enabled)
    {
        updateTPSPatches(Client::GetModuleEnabled("tps-bypass"));
    }
};

$execute
{
    Loader::get()->queueInMainThread([] {
        auto del = new TPSChangedDelegate();

        Client::GetModule("tps-bypass")->delegate = del;
        Client::GetModule("tps-bypass")->options[0]->delegate = del;

        updateTPSPatches(Client::GetModuleEnabled("tps-bypass"));
    });
}