﻿#include "stdafx.h"
#pragma hdrstop

#include "IGame_Persistent.h"
#if 1
#include "x_ray.h"
#include "IGame_Level.h"
#include "XR_IOConsole.h"
#include "Render.h"
#include "ps_instance.h"
#include "CustomHUD.h"
#endif

#ifdef INGAME_EDITOR
#include "editor_environment_manager.hpp"
#endif   // INGAME_EDITOR

IGame_Persistent::IGame_Persistent(bool bIsEditor)
{
    Device->seqAppStart.Add(this);
    Device->seqAppEnd.Add(this);
    Device->seqFrame.Add(this, REG_PRIORITY_HIGH + 1);
    Device->seqAppActivate.Add(this);
    Device->seqAppDeactivate.Add(this);

    m_pMainMenu = NULL;

#ifndef INGAME_EDITOR
    pEnvironment = xr_new<CEnvironment>();
#else   // #ifdef INGAME_EDITOR
    if (!bIsEditor)
    {
        if (Device->WeatherEditor())
            pEnvironment = xr_new<xrWeatherEditor::environment::manager>();
        else
            pEnvironment = xr_new<CEnvironment>();
    }

#endif   // #ifdef INGAME_EDITOR
}

IGame_Persistent::~IGame_Persistent()
{
    Device->seqFrame.Remove(this);
    Device->seqAppStart.Remove(this);
    Device->seqAppEnd.Remove(this);
    Device->seqAppActivate.Remove(this);
    Device->seqAppDeactivate.Remove(this);
    xr_delete(pEnvironment);
}

void IGame_Persistent::OnAppActivate() {}

void IGame_Persistent::OnAppDeactivate() {}

void IGame_Persistent::OnAppStart()
{
    Environment().load();
}

void IGame_Persistent::OnAppEnd()
{
    Environment().unload();
    OnGameEnd();

#if 1
    DEL_INSTANCE(g_hud);
#endif
}

void IGame_Persistent::PreStart(LPCSTR op)
{
    string256 prev_type;
    params    new_game_params;
    xr_strcpy(prev_type, m_game_params.m_game_type);
    new_game_params.parse_cmd_line(op);

    // change game type
    if (0 != xr_strcmp(prev_type, new_game_params.m_game_type))
    {
        OnGameEnd();
    }
}

void IGame_Persistent::Start(LPCSTR op)
{
    string256 prev_type;
    xr_strcpy(prev_type, m_game_params.m_game_type);
    m_game_params.parse_cmd_line(op);
    // change game type
    if ((0 != xr_strcmp(prev_type, m_game_params.m_game_type)))
    {
        if (*m_game_params.m_game_type)
            OnGameStart();
#if 1
        if (g_hud)
            DEL_INSTANCE(g_hud);
#endif
    }
    else
        UpdateGameType();

    VERIFY(ps_destroy.empty());
}

void IGame_Persistent::Disconnect()
{
#if 1
    // clear "need to play" particles
    destroy_particles(true);

    if (g_hud)
        DEL_INSTANCE(g_hud);
    // g_hud->OnDisconnected();
#endif
}

void IGame_Persistent::OnGameStart()
{
#if 1
    // LoadTitle("st_prefetching_objects");
    LoadTitle();
    if (strstr(Core.Params, "-noprefetch"))
        return;

    // prefetch game objects & models
    float p_time = 1000.f * Device->GetTimerGlobal()->GetElapsed_sec();
    u32   mem_0  = Memory.mem_usage();

    Log("Loading objects...");
    ObjectPool.prefetch();
    Log("Loading models...");
    Render->models_Prefetch();
    // Device->Resources->DeferredUpload();
    Device->m_pRender->ResourcesDeferredUpload();

    p_time    = 1000.f * Device->GetTimerGlobal()->GetElapsed_sec() - p_time;
    u32 p_mem = Memory.mem_usage() - mem_0;

    Msg("* [prefetch] time:    %d ms", iFloor(p_time));
    Msg("* [prefetch] memory:  %dKb", p_mem / 1024);
#endif
}

void IGame_Persistent::OnGameEnd()
{
#if 1
    ObjectPool.clear();
    Render->models_Clear(TRUE);
#endif
}

void IGame_Persistent::OnFrame()
{
    if (!Device->Paused() || Device->dwPrecacheFrame)
        Environment().OnFrame();

#if 1
    Device->Statistic->Particles_starting = ps_needtoplay.size();
    Device->Statistic->Particles_active   = ps_active.size();
    Device->Statistic->Particles_destroy  = ps_destroy.size();

    // Play req particle systems
    while (ps_needtoplay.size())
    {
        CPS_Instance* psi = ps_needtoplay.back();
        ps_needtoplay.pop_back();
        psi->Play(false);
    }
    // Destroy inactive particle systems
    while (ps_destroy.size())
    {
        // u32 cnt = ps_destroy.size();
        CPS_Instance* psi = ps_destroy.back();
        VERIFY(psi);
        if (psi->Locked())
        {
            Log("--locked");
            break;
        }
        ps_destroy.pop_back();
        psi->PSI_internal_delete();
    }
#endif
}

void IGame_Persistent::destroy_particles(const bool& all_particles)
{
#if 1
    ps_needtoplay.clear();

    while (ps_destroy.size())
    {
        CPS_Instance* psi = ps_destroy.back();
        VERIFY(psi);
        VERIFY(!psi->Locked());
        ps_destroy.pop_back();
        psi->PSI_internal_delete();
    }

    // delete active particles
    if (all_particles)
    {
        for (; !ps_active.empty();)
            (*ps_active.begin())->PSI_internal_delete();
    }
    else
    {
        u32            active_size = ps_active.size();
        CPS_Instance** I           = (CPS_Instance**)_alloca(active_size * sizeof(CPS_Instance*));
        std::copy(ps_active.begin(), ps_active.end(), I);

        struct destroy_on_game_load
        {
            static IC bool predicate(CPS_Instance* const& object)
            {
                return (!object->destroy_on_game_load());
            }
        };

        CPS_Instance** E = std::remove_if(I, I + active_size, &destroy_on_game_load::predicate);
        for (; I != E; ++I)
            (*I)->PSI_internal_delete();
    }

    VERIFY(ps_needtoplay.empty() && ps_destroy.empty() && (!all_particles || ps_active.empty()));
#endif
}

void IGame_Persistent::OnAssetsChanged()
{
#if 1
    Device->m_pRender->OnAssetsChanged();   // Resources->m_textures_description.Load();
#endif
}
