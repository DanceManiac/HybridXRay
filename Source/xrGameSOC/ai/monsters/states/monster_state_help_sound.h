﻿#pragma once

#include "../state.h"

template<typename _Object> class CStateMonsterHearHelpSound: public CState<_Object>
{
protected:
    typedef CState<_Object>  inherited;
    typedef CState<_Object>* state_ptr;

public:
    CStateMonsterHearHelpSound(_Object* obj);
    virtual ~CStateMonsterHearHelpSound() {}

    virtual void reselect_state();
    virtual void setup_substates();

    virtual bool check_start_conditions();
    virtual bool check_completion();
};

#include "monster_state_help_sound_inline.h"
