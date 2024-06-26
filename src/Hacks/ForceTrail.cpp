#include <Geode/Geode.hpp>
#include <Geode/modify/CCMotionStreak.hpp>
#include "../Client/Client.h"

using namespace geode::prelude;

Module* on = nullptr;
Module* off = nullptr;

class $modify (CCMotionStreak)
{
    virtual void update(float delta)
    {
        if (!on)
            on = Client::GetModule("trail-on");

        if (!off)
            off = Client::GetModule("trail-off");

        if (on->enabled)
        {
            m_bStroke = true;
            this->setOpacity(255);
        }

        if (off->enabled)
        {
            m_bStroke = false;
            this->setOpacity(0);
        }

        CCMotionStreak::update(delta);
    }
};