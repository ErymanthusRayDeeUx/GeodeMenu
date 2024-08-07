#pragma once

#include <Geode/Geode.hpp>
#include "../Module.h"

using namespace geode::prelude;

class ColourModuleDelegate : public ColorPickPopupDelegate
{
    public:
        Module* mod;
        
        virtual void updateColor(cocos2d::ccColor4B const& color);
};

class ColourModule : public Module
{
    public:
        static inline ColourModule* selected = nullptr;

        ccColor3B colour = ccc3(255, 255, 255);
        ccColor3B def = ccc3(255, 255, 255);

        ColourModuleDelegate* delegate;

        CCSprite* btnSpr = nullptr;

        ColourModule(std::string name, std::string id, ccColor3B def);

        void save();
        void load();

        void onPickColourAndroid(cocos2d::CCObject* sender);

        void makeAndroid(CCNode* menu, CCPoint pos);
};