﻿//----------------------------------------------------
// file: StaticMesh.cpp
//----------------------------------------------------

#include "stdafx.h"
#pragma hdrstop

#include "EditMesh.h"
#include "EditObject.h"
#include "Bone.h"

#include "face_smoth_flags.h"
#include "itterate_adjacents.h"
#include "itterate_adjacents_dynamic.h"
#include "UI_ToolsCustom.h"
#include "../xrETools/ETools.h"

extern ECORE_API BOOL g_extendedLog;

CEditableMesh::~CEditableMesh()
{
    Clear();
    R_ASSERT2(0 == m_RenderBuffers, "Render buffer still referenced.");
}

void CEditableMesh::Construct()
{
    m_Box.set(0, 0, 0, 0, 0, 0);
    m_Flags.assign(flVisible);
    m_Name          = "";
    m_CFModel       = 0;
    m_Vertices      = 0;
    m_SmoothGroups  = 0;
    m_Adjs          = 0;
    m_Faces         = 0;
    m_FaceNormals   = 0;
    m_VertexNormals = 0;
    m_Normals       = 0;
    m_SVertices     = 0;
    m_SVertInfl     = 0;
    m_RenderBuffers = 0;
    m_FNormalsRefs  = 0;
    m_VNormalsRefs  = 0;
    m_AdjsRefs      = 0;
    m_SVertRefs     = 0;
}

void CEditableMesh::Clear()
{
    UnloadRenderBuffers();
    UnloadAdjacency();
    UnloadCForm();
    UnloadFNormals();
    UnloadVNormals();
    UnloadSVertices();
    if (m_SmoothGroups)
        xr_free(m_SmoothGroups);
    m_SmoothGroups = 0;
    VERIFY(m_FNormalsRefs == 0 && m_VNormalsRefs == 0 && m_AdjsRefs == 0 && m_SVertRefs == 0);

    xr_free(m_Vertices);
    xr_free(m_Faces);

    if (m_Normals)
    {
        xr_free(m_Normals);
        m_Normals = 0;
    }

    for (VMapIt vm_it = m_VMaps.begin(); vm_it != m_VMaps.end(); vm_it++)
        xr_delete(*vm_it);
    m_VMaps.clear();
    m_SurfFaces.clear();
    for (VMRefsIt ref_it = m_VMRefs.begin(); ref_it != m_VMRefs.end(); ref_it++)
        xr_free(ref_it->pts);
    m_VMRefs.clear();
}

void CEditableMesh::UnloadCForm()
{
    ETOOLS::destroy_model(m_CFModel);
}

void CEditableMesh::UnloadFNormals(bool force)
{
    m_FNormalsRefs--;
    if (force || m_FNormalsRefs <= 0)
    {
        xr_free(m_FaceNormals);
        m_FNormalsRefs = 0;
    }
}
void CEditableMesh::UnloadVNormals(bool force)
{
    m_VNormalsRefs--;
    if (force || m_VNormalsRefs <= 0)
    {
        xr_free(m_VertexNormals);
        m_VNormalsRefs = 0;
    }
}
void CEditableMesh::UnloadSVertices(bool force)
{
    m_SVertRefs--;
    if (force || m_SVertRefs <= 0)
    {
        xr_free(m_SVertices);
        m_SVertRefs = 0;
    }
}
void CEditableMesh::UnloadAdjacency(bool force)
{
    m_AdjsRefs--;
    if (force || m_AdjsRefs <= 0)
    {
        xr_delete(m_Adjs);
        m_AdjsRefs = 0;
    }
}

void CEditableMesh::RecomputeBBox()
{
    if (0 == m_VertCount)
    {
        m_Box.set(0, 0, 0, 0, 0, 0);
        return;
    }
    m_Box.set(m_Vertices[0], m_Vertices[0]);
    for (u32 k = 1; k < m_VertCount; k++)
        m_Box.modify(m_Vertices[k]);
}

void CEditableMesh::GenerateFNormals()
{
    m_FNormalsRefs++;
    if (m_FaceNormals)
        return;
    m_FaceNormals = xr_alloc<Fvector>(m_FaceCount);

    // face normals
    for (u32 k = 0; k < m_FaceCount; k++)
        m_FaceNormals[k].mknormal(m_Vertices[m_Faces[k].pv[0].pindex], m_Vertices[m_Faces[k].pv[1].pindex], m_Vertices[m_Faces[k].pv[2].pindex]);
}
// BOOL CEditableMesh::m_bDraftMeshMode = FALSE;

void CEditableMesh::GenerateVNormals(bool force, bool silent, bool only_one_msg)
{
    m_VNormalsRefs++;
    if ((m_VertexNormals || (m_Normals && m_Parent->m_objectFlags.is(CEditableObject::eoNormals))) && !force)
        return;
    m_VertexNormals = xr_alloc<Fvector>(m_FaceCount * 3);

    // gen req
    GenerateFNormals();
    GenerateAdjacency();

    if (!m_Parent->m_objectFlags.is(CEditableObject::eoSoCSmooth))   // cop
    {
        if (!silent && (!only_one_msg || !m_Parent->m_SmoothMsgSended))
        {
            m_Parent->m_SmoothMsgSended = true;
            if (g_extendedLog)
                Msg("+ ..Generate CoP Smooth groups.");
        }
        for (u32 f_i = 0; f_i < m_FaceCount; f_i++)
        {
            for (int k = 0; k < 3; k++)
            {
                Fvector& N           = m_VertexNormals[f_i * 3 + k];
                IntVec&  a_lst       = (*m_Adjs)[m_Faces[f_i].pv[k].pindex];

                IntIt    face_adj_it = std::find(a_lst.begin(), a_lst.end(), f_i);
                VERIFY(face_adj_it != a_lst.end());
                //
                N.set(m_FaceNormals[a_lst.front()]);

                using iterate_adj = itterate_adjacents<itterate_adjacents_params_dynamic<st_FaceVert>>;
                iterate_adj::recurse_tri_params p(N, m_SmoothGroups, m_FaceNormals, a_lst, m_Faces, m_FaceCount);
                iterate_adj::RecurseTri(face_adj_it - a_lst.begin(), p);
                float len = N.magnitude();
                if (len > EPS_S)
                {
                    N.div(len);
                }
                else
                {
                    if (!silent)
                    {
                        Msg("! Invalid smooth group found (Maya type). Object: '%s'. Vertex: [%3.2f, %3.2f, %3.2f]", m_Parent->GetName(), VPUSH(m_Vertices[m_Faces[f_i].pv[k].pindex]));
                    }
                    N.set(m_FaceNormals[a_lst.front()]);
                }
            }
        }
    }
    else   // soc
    {
        if (!silent && (!only_one_msg || !m_Parent->m_SmoothMsgSended))
        {
            m_Parent->m_SmoothMsgSended = true;
            if (g_extendedLog)
                Msg("+ ..Generate SoC Smooth groups.");
        }
        if (m_Flags.is(flSGMask))
        {
            for (u32 f_i = 0; f_i < m_FaceCount; f_i++)
            {
                u32      sg = m_SmoothGroups[f_i];
                Fvector& FN = m_FaceNormals[f_i];
                for (int k = 0; k < 3; k++)
                {
                    Fvector& N = m_VertexNormals[f_i * 3 + k];
                    if (sg)
                    {
                        N.set(0, 0, 0);
                        IntVec& a_lst = (*m_Adjs)[m_Faces[f_i].pv[k].pindex];
                        VERIFY(a_lst.size());
                        for (IntIt i_it = a_lst.begin(); i_it != a_lst.end(); i_it++)
                            if (sg & m_SmoothGroups[*i_it])
                                N.add(m_FaceNormals[*i_it]);
                        float len = N.magnitude();
                        if (len > EPS_S)
                        {
                            N.div(len);
                        }
                        else
                        {
                            if (!silent)
                            {
                                Msg("! Invalid smooth group found (MAX type). Object: '%s'. Vertex: [%3.2f, %3.2f, %3.2f]", m_Parent->GetName(), VPUSH(m_Vertices[m_Faces[f_i].pv[k].pindex]));
                            }
                            N.set(m_FaceNormals[a_lst.front()]);
                        }
                    }
                    else
                    {
                        N.set(FN);
                    }
                }
            }
        }
        else
        {
            for (u32 f_i = 0; f_i < m_FaceCount; f_i++)
            {
                u32      sg = m_SmoothGroups[f_i];
                Fvector& FN = m_FaceNormals[f_i];
                for (int k = 0; k < 3; k++)
                {
                    Fvector& N = m_VertexNormals[f_i * 3 + k];
                    if (sg != -1)
                    {
                        N.set(0, 0, 0);
                        IntVec& a_lst = (*m_Adjs)[m_Faces[f_i].pv[k].pindex];
                        VERIFY(a_lst.size());
                        for (IntIt i_it = a_lst.begin(); i_it != a_lst.end(); i_it++)
                        {
                            if (sg != m_SmoothGroups[*i_it])
                                continue;
                            N.add(m_FaceNormals[*i_it]);
                        }
                        float len = N.magnitude();
                        if (len > EPS_S)
                        {
                            N.div(len);
                        }
                        else
                        {
                            if (!silent)
                            {
                                Msg("! Invalid smooth group found (Maya type). Object: '%s'. Vertex: [%3.2f, %3.2f, %3.2f]", m_Parent->GetName(), VPUSH(m_Vertices[m_Faces[f_i].pv[k].pindex]));
                            }
                            N.set(m_FaceNormals[a_lst.front()]);
                        }
                    }
                    else
                    {
                        N.set(FN);
                    }
                }
            }
        }
    }
    UnloadFNormals();
    UnloadAdjacency();
}

void CEditableMesh::GenerateSVertices(u32 influence)
{
    if (!m_Parent->IsSkeleton())
        return;

    m_SVertRefs++;
    if (m_SVertInfl != influence)
        UnloadSVertices(true);
    if (m_SVertices)
        return;
    m_SVertices = xr_alloc<st_SVert>(m_FaceCount * 3);
    m_SVertInfl = influence;

    //	CSMotion* active_motion=m_Parent->ResetSAnimation();
    m_Parent->CalculateAnimation(0);

    // generate normals
    GenerateFNormals();
    GenerateVNormals();

    if (m_Normals && m_Parent->m_objectFlags.is(CEditableObject::eoNormals))
        Log("& ..Export custom Normals");
    else
        Log("& ..Export Smooth groups.");

    for (u32 f_id = 0; f_id < m_FaceCount; f_id++)
    {
        st_Face& F = m_Faces[f_id];

        for (int k = 0; k < 3; ++k)
        {
            st_SVert&           SV       = m_SVertices[f_id * 3 + k];
            const Fvector&      N        = m_Normals && m_Parent->m_objectFlags.is(CEditableObject::eoNormals) ? m_Normals[f_id * 3 + k] : m_VertexNormals[f_id * 3 + k];
            const st_FaceVert&  fv       = F.pv[k];
            const Fvector&      P        = m_Vertices[fv.pindex];

            const st_VMapPtLst& vmpt_lst = m_VMRefs[fv.vmref];

            st_VertexWB         wb;
            for (u8 vmpt_id = 0; vmpt_id != vmpt_lst.count; ++vmpt_id)
            {
                const st_VMap& VM = *m_VMaps[vmpt_lst.pts[vmpt_id].vmap_index];
                if (VM.type == vmtWeight)
                {
                    wb.push_back(st_WB(m_Parent->GetBoneIndexByWMap(VM.name.c_str()), VM.getW(vmpt_lst.pts[vmpt_id].index)));

                    if (wb.back().bone == BI_NONE)
                    {
                        ELog.DlgMsg(mtError, "! Can't find bone assigned to weight map %s", *VM.name);
                        FATAL("Editor crashed.");
                        return;
                    }
                }
                else if (VM.type == vmtUV)
                    SV.uv.set(VM.getUV(vmpt_lst.pts[vmpt_id].index));
            }

            VERIFY(m_SVertInfl <= 4);

            wb.prepare_weights(m_SVertInfl);

            SV.offs = P;
            SV.norm = N;
            SV.bones.resize(wb.size());
            for (u8 k = 0; k < (u8)SV.bones.size(); k++)
            {
                SV.bones[k].id = wb[k].bone;
                SV.bones[k].w  = wb[k].weight;
            }
        }
    }

    // restore active motion
    UnloadFNormals();
    UnloadVNormals();
}

void CEditableMesh::GenerateSVerticesFast(u32 influence)
{
    if (!m_Parent->IsSkeleton())
        return;

    m_SVertRefs++;
    if (m_SVertInfl != influence)
        UnloadSVertices(true);
    if (m_SVertices)
        return;
    m_SVertices = xr_alloc<st_SVert>(m_FaceCount * 3);
    m_SVertInfl = influence;

    //	CSMotion* active_motion=m_Parent->ResetSAnimation();
    m_Parent->CalculateAnimation(0);

    // generate normals
    GenerateFNormals();
    GenerateVNormals();

    for (u32 f_id = 0; f_id < m_FaceCount; f_id++)
    {
        st_Face& F = m_Faces[f_id];

        for (int k = 0; k < 3; ++k)
        {
            st_SVert&           SV       = m_SVertices[f_id * 3 + k];
            const Fvector&      N        = m_Normals && m_Parent->m_objectFlags.is(CEditableObject::eoNormals) ? m_Normals[f_id * 3 + k] : m_VertexNormals[f_id * 3 + k];
            const st_FaceVert&  fv       = F.pv[k];
            const Fvector&      P        = m_Vertices[fv.pindex];

            const st_VMapPtLst& vmpt_lst = m_VMRefs[fv.vmref];

            st_VertexWB         wb;
            for (u8 vmpt_id = 0; vmpt_id != vmpt_lst.count; ++vmpt_id)
            {
                const st_VMap& VM = *m_VMaps[vmpt_lst.pts[vmpt_id].vmap_index];

                if (VM.type == vmtWeight)
                {
                    u16 bone = m_Parent->GetBoneIndexByWMap(VM.name.c_str());

                    wb.push_back(st_WB(bone, VM.getW(vmpt_lst.pts[vmpt_id].index)));

                    if (wb.back().bone == BI_NONE)
                    {
                        ELog.DlgMsg(mtError, "! ..Can't find bone assigned to weight map '%s'", *VM.name);
                        FATAL("Editor crashed.");
                        return;
                    }
                }
                else if (VM.type == vmtUV)
                    SV.uv.set(VM.getUV(vmpt_lst.pts[vmpt_id].index));
            }

            VERIFY(m_SVertInfl <= 4);

            wb.prepare_weights(m_SVertInfl);

            SV.offs = P;
            SV.norm = N;
            SV.bones.resize(wb.size());
            for (u8 k = 0; k < (u8)SV.bones.size(); k++)
            {
                SV.bones[k].id = wb[k].bone;
                SV.bones[k].w  = wb[k].weight;
            }
        }
    }

    // restore active motion
    UnloadFNormals();
    UnloadVNormals();
}

void CEditableMesh::GenerateAdjacency()
{
    m_AdjsRefs++;
    if (m_Adjs)
        return;
    m_Adjs = xr_new<AdjVec>();
    VERIFY(m_Faces);
    m_Adjs->resize(m_VertCount);
    // Log(".. Update adjacency");
    for (u32 f_id = 0; f_id < m_FaceCount; f_id++)
        for (int k = 0; k < 3; k++)
            (*m_Adjs)[m_Faces[f_id].pv[k].pindex].push_back(f_id);
}

CSurface* CEditableMesh::GetSurfaceByFaceID(u32 fid)
{
    R_ASSERT(fid < m_FaceCount);
    for (SurfFacesPairIt sp_it = m_SurfFaces.begin(); sp_it != m_SurfFaces.end(); sp_it++)
    {
        IntVec& face_lst = sp_it->second;
        IntIt   f_it     = std::lower_bound(face_lst.begin(), face_lst.end(), (int)fid);
        if ((f_it != face_lst.end()) && (*f_it == (int)fid))
            return sp_it->first;
        // if (std::find(face_lst.begin(),face_lst.end(),fid)!=face_lst.end()) return sp_it->first;
    }
    return 0;
}

void CEditableMesh::GetFaceTC(u32 fid, const Fvector2* tc[3])
{
    R_ASSERT(fid < m_FaceCount);
    st_Face& F = m_Faces[fid];
    for (int k = 0; k < 3; k++)
    {
        st_VMapPt& vmr = m_VMRefs[F.pv[k].vmref].pts[0];
        tc[k]          = &(m_VMaps[vmr.vmap_index]->getUV(vmr.index));
    }
}

void CEditableMesh::GetFacePT(u32 fid, const Fvector* pt[3])
{
    R_ASSERT(fid < m_FaceCount);
    st_Face& F = m_Faces[fid];

    for (int k = 0; k < 3; ++k)
        pt[k] = &m_Vertices[F.pv[k].pindex];
}

int CEditableMesh::GetFaceCount(bool bMatch2Sided, bool bIgnoreOCC)
{
    static shared_str occ_name = "materials\\occ";
    int               f_cnt    = 0;
    for (SurfFacesPairIt sp_it = m_SurfFaces.begin(); sp_it != m_SurfFaces.end(); sp_it++)
    {
        CSurface* S = sp_it->first;
        if (S->m_GameMtlName == occ_name && bIgnoreOCC)
            continue;

        if (bMatch2Sided)
        {
            if (S->m_Flags.is(CSurface::sf2Sided))
                f_cnt += sp_it->second.size() * 2;
            else
                f_cnt += sp_it->second.size();
        }
        else
        {
            f_cnt += sp_it->second.size();
        }
    }
    return f_cnt;
}

float CEditableMesh::CalculateSurfaceArea(CSurface* surf, bool bMatch2Sided)
{
    SurfFacesPairIt sp_it = m_SurfFaces.find(surf);
    if (sp_it == m_SurfFaces.end())
        return 0;
    float   area    = 0;
    IntVec& pol_lst = sp_it->second;
    for (int k = 0; k < int(pol_lst.size()); k++)
    {
        st_Face& F = m_Faces[pol_lst[k]];
        Fvector  c, e01, e02;
        e01.sub(m_Vertices[F.pv[1].pindex], m_Vertices[F.pv[0].pindex]);
        e02.sub(m_Vertices[F.pv[2].pindex], m_Vertices[F.pv[0].pindex]);
        area += c.crossproduct(e01, e02).magnitude() / 2.f;
    }
    if (bMatch2Sided && sp_it->first->m_Flags.is(CSurface::sf2Sided))
        area *= 2;
    return area;
}

float CEditableMesh::CalculateSurfacePixelArea(CSurface* surf, bool bMatch2Sided)
{
    SurfFacesPairIt sp_it = m_SurfFaces.find(surf);
    if (sp_it == m_SurfFaces.end())
        return 0;
    float   area    = 0;
    IntVec& pol_lst = sp_it->second;
    for (int k = 0; k < int(pol_lst.size()); k++)
    {
        // st_Face& F = m_Faces[pol_lst[k]];
        Fvector         c, e01, e02;
        const Fvector2* tc[3];
        GetFaceTC(pol_lst[k], tc);
        e01.sub(Fvector().set(tc[1]->x, tc[1]->y, 0), Fvector().set(tc[0]->x, tc[0]->y, 0));
        e02.sub(Fvector().set(tc[2]->x, tc[2]->y, 0), Fvector().set(tc[0]->x, tc[0]->y, 0));
        area += c.crossproduct(e01, e02).magnitude() / 2.f;
    }
    if (bMatch2Sided && sp_it->first->m_Flags.is(CSurface::sf2Sided))
        area *= 2;
    return area;
}

int CEditableMesh::GetSurfFaceCount(CSurface* surf, bool bMatch2Sided)
{
    SurfFacesPairIt sp_it = m_SurfFaces.find(surf);
    if (sp_it == m_SurfFaces.end())
        return 0;
    int f_cnt = sp_it->second.size();
    if (bMatch2Sided && sp_it->first->m_Flags.is(CSurface::sf2Sided))
        f_cnt *= 2;
    return f_cnt;
}

void CEditableMesh::DumpAdjacency()
{
    Log("& Adjacency dump.");
    Log("+ ------------------------------------------------------------------------");
    /*    for (u32 i=0; i<m_Adjs.size(); i++){
            IntVec& a_lst	= m_Adjs[i];
            xr_string s; s = "Point "; s+=xr_string(i); s+=":";
            xr_string s1;
            for (u32 j=0; j<a_lst.size(); j++){ s1=a_lst[j]; s+=" "+s1; }
            Log(s.c_str());
        }
    */
}
//----------------------------------------------------------------------------

int CEditableMesh::FindVMapByName(VMapVec& vmaps, const char* name, u8 t, bool polymap)
{
    for (VMapIt vm_it = vmaps.begin(); vm_it != vmaps.end(); vm_it++)
    {
        if (((*vm_it)->type == t) && (stricmp((*vm_it)->name.c_str(), name) == 0) && (polymap == (*vm_it)->polymap))
            return vm_it - vmaps.begin();
    }
    return -1;
}
//----------------------------------------------------------------------------

bool CEditableMesh::Validate()
{
    return true;
}
//----------------------------------------------------------------------------
