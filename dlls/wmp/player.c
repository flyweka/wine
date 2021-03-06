/*
 * Copyright 2014 Jacek Caban for CodeWeavers
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */

#include "wmp_private.h"

#include "wine/debug.h"

WINE_DEFAULT_DEBUG_CHANNEL(wmp);

static inline WMPMedia *impl_from_IWMPMedia(IWMPMedia *iface)
{
    return CONTAINING_RECORD(iface, WMPMedia, IWMPMedia_iface);
}

static inline WindowsMediaPlayer *impl_from_IWMPNetwork(IWMPNetwork *iface)
{
    return CONTAINING_RECORD(iface, WindowsMediaPlayer, IWMPNetwork_iface);
}

static inline WindowsMediaPlayer *impl_from_IWMPPlayer4(IWMPPlayer4 *iface)
{
    return CONTAINING_RECORD(iface, WindowsMediaPlayer, IWMPPlayer4_iface);
}

static inline WindowsMediaPlayer *impl_from_IWMPPlayer(IWMPPlayer *iface)
{
    return CONTAINING_RECORD(iface, WindowsMediaPlayer, IWMPPlayer_iface);
}

static inline WindowsMediaPlayer *impl_from_IWMPControls(IWMPControls *iface)
{
    return CONTAINING_RECORD(iface, WindowsMediaPlayer, IWMPControls_iface);
}

static HRESULT WINAPI WMPPlayer4_QueryInterface(IWMPPlayer4 *iface, REFIID riid, void **ppv)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer4(iface);
    return IOleObject_QueryInterface(&This->IOleObject_iface, riid, ppv);
}

static ULONG WINAPI WMPPlayer4_AddRef(IWMPPlayer4 *iface)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer4(iface);
    return IOleObject_AddRef(&This->IOleObject_iface);
}

static ULONG WINAPI WMPPlayer4_Release(IWMPPlayer4 *iface)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer4(iface);
    return IOleObject_Release(&This->IOleObject_iface);
}

static HRESULT WINAPI WMPPlayer4_GetTypeInfoCount(IWMPPlayer4 *iface, UINT *pctinfo)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer4(iface);
    FIXME("(%p)->(%p)\n", This, pctinfo);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPPlayer4_GetTypeInfo(IWMPPlayer4 *iface, UINT iTInfo,
        LCID lcid, ITypeInfo **ppTInfo)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer4(iface);
    FIXME("(%p)->(%u %d %p)\n", This, iTInfo, lcid, ppTInfo);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPPlayer4_GetIDsOfNames(IWMPPlayer4 *iface, REFIID riid,
        LPOLESTR *rgszNames, UINT cNames, LCID lcid, DISPID *rgDispId)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer4(iface);
    FIXME("(%p)->(%s %p %u %d %p)\n", This, debugstr_guid(riid), rgszNames, cNames, lcid, rgDispId);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPPlayer4_Invoke(IWMPPlayer4 *iface, DISPID dispIdMember,
        REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS *pDispParams, VARIANT *pVarResult,
        EXCEPINFO *pExcepInfo, UINT *puArgErr)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer4(iface);
    FIXME("(%p)->(%d %s %d %x %p %p %p %p)\n", This, dispIdMember, debugstr_guid(riid), lcid,
          wFlags, pDispParams, pVarResult, pExcepInfo, puArgErr);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPPlayer4_close(IWMPPlayer4 *iface)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer4(iface);
    FIXME("(%p)\n", This);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPPlayer4_get_URL(IWMPPlayer4 *iface, BSTR *pbstrURL)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer4(iface);
    TRACE("(%p)->(%p)\n", This, pbstrURL);
    if(This->wmpmedia == NULL) {
        return S_FALSE;
    }
    return IWMPMedia_get_sourceURL(This->wmpmedia, pbstrURL);
}

static HRESULT WINAPI WMPPlayer4_put_URL(IWMPPlayer4 *iface, BSTR url)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer4(iface);
    IWMPMedia *media;
    TRACE("(%p)->(%s)\n", This, debugstr_w(url));
    if(url == NULL) {
        return E_POINTER;
    }
    media = create_media_from_url(url);
    return IWMPPlayer4_put_currentMedia(iface, media);
}

static HRESULT WINAPI WMPPlayer4_get_openState(IWMPPlayer4 *iface, WMPOpenState *pwmpos)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer4(iface);
    FIXME("(%p)->(%p)\n", This, pwmpos);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPPlayer4_get_playState(IWMPPlayer4 *iface, WMPPlayState *pwmpps)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer4(iface);
    FIXME("(%p)->(%p)\n", This, pwmpps);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPPlayer4_get_controls(IWMPPlayer4 *iface, IWMPControls **ppControl)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer4(iface);

    TRACE("(%p)->(%p)\n", This, ppControl);

    IWMPControls_AddRef(&This->IWMPControls_iface);
    *ppControl = &This->IWMPControls_iface;
    return S_OK;
}

static HRESULT WINAPI WMPPlayer4_get_settings(IWMPPlayer4 *iface, IWMPSettings **ppSettings)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer4(iface);

    TRACE("(%p)->(%p)\n", This, ppSettings);

    IWMPSettings_AddRef(&This->IWMPSettings_iface);
    *ppSettings = &This->IWMPSettings_iface;
    return S_OK;
}

static HRESULT WINAPI WMPPlayer4_get_currentMedia(IWMPPlayer4 *iface, IWMPMedia **ppMedia)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer4(iface);
    TRACE("(%p)->(%p)\n", This, ppMedia);
    if(This->wmpmedia == NULL) {
        return S_FALSE;
    }
    IWMPMedia_AddRef(This->wmpmedia);
    *ppMedia = This->wmpmedia;
    return S_OK;
}

static HRESULT WINAPI WMPPlayer4_put_currentMedia(IWMPPlayer4 *iface, IWMPMedia *pMedia)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer4(iface);
    TRACE("(%p)->(%p)\n", This, pMedia);
    if(pMedia == NULL) {
        return E_POINTER;
    }
    if(This->wmpmedia != NULL) {
        IWMPMedia_Release(This->wmpmedia);
    }
    This->wmpmedia = pMedia;
    IWMPMedia_AddRef(This->wmpmedia);
    return S_OK;
}

static HRESULT WINAPI WMPPlayer4_get_mediaCollection(IWMPPlayer4 *iface, IWMPMediaCollection **ppMediaCollection)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer4(iface);
    FIXME("(%p)->(%p)\n", This, ppMediaCollection);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPPlayer4_get_playlistCollection(IWMPPlayer4 *iface, IWMPPlaylistCollection **ppPlaylistCollection)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer4(iface);
    FIXME("(%p)->(%p)\n", This, ppPlaylistCollection);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPPlayer4_get_versionInfo(IWMPPlayer4 *iface, BSTR *version)
{
    static const WCHAR versionW[] = {'1','2','.','0','.','7','6','0','1','.','1','6','9','8','2',0};
    WindowsMediaPlayer *This = impl_from_IWMPPlayer4(iface);

    TRACE("(%p)->(%p)\n", This, version);

    if (!version)
        return E_POINTER;

    *version = SysAllocString(versionW);
    return *version ? S_OK : E_OUTOFMEMORY;
}

static HRESULT WINAPI WMPPlayer4_launchURL(IWMPPlayer4 *iface, BSTR url)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer4(iface);
    FIXME("(%p)->(%s)\n", This, debugstr_w(url));
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPPlayer4_get_network(IWMPPlayer4 *iface, IWMPNetwork **ppQNI)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer4(iface);
    TRACE("(%p)->(%p)\n", This, ppQNI);

    IWMPNetwork_AddRef(&This->IWMPNetwork_iface);
    *ppQNI = &This->IWMPNetwork_iface;
    return S_OK;
}

static HRESULT WINAPI WMPPlayer4_get_currentPlaylist(IWMPPlayer4 *iface, IWMPPlaylist **ppPL)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer4(iface);
    FIXME("(%p)->(%p)\n", This, ppPL);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPPlayer4_put_currentPlaylist(IWMPPlayer4 *iface, IWMPPlaylist *pPL)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer4(iface);
    FIXME("(%p)->(%p)\n", This, pPL);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPPlayer4_get_cdromCollection(IWMPPlayer4 *iface, IWMPCdromCollection **ppCdromCollection)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer4(iface);
    FIXME("(%p)->(%p)\n", This, ppCdromCollection);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPPlayer4_get_closedCaption(IWMPPlayer4 *iface, IWMPClosedCaption **ppClosedCaption)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer4(iface);
    FIXME("(%p)->(%p)\n", This, ppClosedCaption);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPPlayer4_get_isOnline(IWMPPlayer4 *iface, VARIANT_BOOL *pfOnline)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer4(iface);
    FIXME("(%p)->(%p)\n", This, pfOnline);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPPlayer4_get_Error(IWMPPlayer4 *iface, IWMPError **ppError)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer4(iface);
    FIXME("(%p)->(%p)\n", This, ppError);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPPlayer4_get_Status(IWMPPlayer4 *iface, BSTR *pbstrStatus)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer4(iface);
    FIXME("(%p)->(%p)\n", This, pbstrStatus);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPPlayer4_get_dvd(IWMPPlayer4 *iface, IWMPDVD **ppDVD)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer4(iface);
    FIXME("(%p)->(%p)\n", This, ppDVD);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPPlayer4_newPlaylist(IWMPPlayer4 *iface, BSTR name, BSTR url, IWMPPlaylist **ppPlaylist)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer4(iface);
    FIXME("(%p)->(%s %s %p)\n", This, debugstr_w(name), debugstr_w(url), ppPlaylist);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPPlayer4_newMedia(IWMPPlayer4 *iface, BSTR url, IWMPMedia **ppMedia)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer4(iface);
    FIXME("(%p)->(%p)\n", This, ppMedia);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPPlayer4_get_enabled(IWMPPlayer4 *iface, VARIANT_BOOL *pbEnabled)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer4(iface);
    FIXME("(%p)->(%p)\n", This, pbEnabled);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPPlayer4_put_enabled(IWMPPlayer4 *iface, VARIANT_BOOL enabled)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer4(iface);
    FIXME("(%p)->(%x)\n", This, enabled);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPPlayer4_get_fullScreen(IWMPPlayer4 *iface, VARIANT_BOOL *pbFullScreen)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer4(iface);
    FIXME("(%p)->(%p)\n", This, pbFullScreen);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPPlayer4_put_fullScreen(IWMPPlayer4 *iface, VARIANT_BOOL fullscreen)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer4(iface);
    FIXME("(%p)->(%x)\n", This, fullscreen);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPPlayer4_get_enableContextMenu(IWMPPlayer4 *iface, VARIANT_BOOL *pbEnableContextMenu)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer4(iface);
    FIXME("(%p)->(%p)\n", This, pbEnableContextMenu);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPPlayer4_put_enableContextMenu(IWMPPlayer4 *iface, VARIANT_BOOL enable)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer4(iface);
    FIXME("(%p)->(%x)\n", This, enable);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPPlayer4_put_uiMode(IWMPPlayer4 *iface, BSTR mode)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer4(iface);
    FIXME("(%p)->(%s)\n", This, debugstr_w(mode));
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPPlayer4_get_uiMode(IWMPPlayer4 *iface, BSTR *pbstrMode)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer4(iface);
    FIXME("(%p)->(%p)\n", This, pbstrMode);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPPlayer4_get_stretchToFit(IWMPPlayer4 *iface, VARIANT_BOOL *enabled)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer4(iface);
    FIXME("(%p)->(%p)\n", This, enabled);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPPlayer4_put_stretchToFit(IWMPPlayer4 *iface, VARIANT_BOOL enabled)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer4(iface);
    FIXME("(%p)->(%x)\n", This, enabled);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPPlayer4_get_windowlessVideo(IWMPPlayer4 *iface, VARIANT_BOOL *enabled)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer4(iface);
    FIXME("(%p)->(%p)\n", This, enabled);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPPlayer4_put_windowlessVideo(IWMPPlayer4 *iface, VARIANT_BOOL enabled)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer4(iface);
    FIXME("(%p)->(%x)\n", This, enabled);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPPlayer4_get_isRemote(IWMPPlayer4 *iface, VARIANT_BOOL *pvarfIsRemote)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer4(iface);
    FIXME("(%p)->(%p)\n", This, pvarfIsRemote);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPPlayer4_get_playerApplication(IWMPPlayer4 *iface, IWMPPlayerApplication **ppIWMPPlayerApplication)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer4(iface);
    FIXME("(%p)->(%p)\n", This, ppIWMPPlayerApplication);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPPlayer4_openPlayer(IWMPPlayer4 *iface, BSTR url)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer4(iface);
    FIXME("(%p)->(%s)\n", This, debugstr_w(url));
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPPlayer_QueryInterface(IWMPPlayer *iface, REFIID riid, void **ppv)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer(iface);
    return WMPPlayer4_QueryInterface(&This->IWMPPlayer4_iface, riid, ppv);
}

static ULONG WINAPI WMPPlayer_AddRef(IWMPPlayer *iface)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer(iface);
    return WMPPlayer4_AddRef(&This->IWMPPlayer4_iface);
}

static ULONG WINAPI WMPPlayer_Release(IWMPPlayer *iface)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer(iface);
    return WMPPlayer4_Release(&This->IWMPPlayer4_iface);
}

static HRESULT WINAPI WMPPlayer_GetTypeInfoCount(IWMPPlayer *iface, UINT *pctinfo)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer(iface);
    return WMPPlayer4_GetTypeInfoCount(&This->IWMPPlayer4_iface, pctinfo);
}

static HRESULT WINAPI WMPPlayer_GetTypeInfo(IWMPPlayer *iface, UINT iTInfo,
        LCID lcid, ITypeInfo **ppTInfo)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer(iface);

    return WMPPlayer4_GetTypeInfo(&This->IWMPPlayer4_iface, iTInfo,
        lcid, ppTInfo);
}

static HRESULT WINAPI WMPPlayer_GetIDsOfNames(IWMPPlayer *iface, REFIID riid,
        LPOLESTR *rgszNames, UINT cNames, LCID lcid, DISPID *rgDispId)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer(iface);
    return WMPPlayer4_GetIDsOfNames(&This->IWMPPlayer4_iface, riid,
        rgszNames, cNames, lcid, rgDispId);
}

static HRESULT WINAPI WMPPlayer_Invoke(IWMPPlayer *iface, DISPID dispIdMember,
        REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS *pDispParams, VARIANT *pVarResult,
        EXCEPINFO *pExcepInfo, UINT *puArgErr)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer(iface);
    return WMPPlayer4_Invoke(&This->IWMPPlayer4_iface, dispIdMember,
        riid, lcid, wFlags, pDispParams, pVarResult,
        pExcepInfo, puArgErr);
}

static HRESULT WINAPI WMPPlayer_close(IWMPPlayer *iface)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer(iface);
    return WMPPlayer4_close(&This->IWMPPlayer4_iface);
}

static HRESULT WINAPI WMPPlayer_get_URL(IWMPPlayer *iface, BSTR *pbstrURL)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer(iface);
    return WMPPlayer4_get_URL(&This->IWMPPlayer4_iface, pbstrURL);
}

static HRESULT WINAPI WMPPlayer_put_URL(IWMPPlayer *iface, BSTR url)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer(iface);
    return WMPPlayer4_put_URL(&This->IWMPPlayer4_iface, url);
}

static HRESULT WINAPI WMPPlayer_get_openState(IWMPPlayer *iface, WMPOpenState *pwmpos)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer(iface);
    return WMPPlayer4_get_openState(&This->IWMPPlayer4_iface, pwmpos);
}

static HRESULT WINAPI WMPPlayer_get_playState(IWMPPlayer *iface, WMPPlayState *pwmpps)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer(iface);
    return WMPPlayer4_get_playState(&This->IWMPPlayer4_iface, pwmpps);
}

static HRESULT WINAPI WMPPlayer_get_controls(IWMPPlayer *iface, IWMPControls **ppControl)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer(iface);
    return WMPPlayer4_get_controls(&This->IWMPPlayer4_iface, ppControl);
}

static HRESULT WINAPI WMPPlayer_get_settings(IWMPPlayer *iface, IWMPSettings **ppSettings)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer(iface);
    return WMPPlayer4_get_settings(&This->IWMPPlayer4_iface, ppSettings);
}

static HRESULT WINAPI WMPPlayer_get_currentMedia(IWMPPlayer *iface, IWMPMedia **ppMedia)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer(iface);
    return WMPPlayer4_get_currentMedia(&This->IWMPPlayer4_iface, ppMedia);
}

static HRESULT WINAPI WMPPlayer_put_currentMedia(IWMPPlayer *iface, IWMPMedia *pMedia)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer(iface);
    return WMPPlayer4_put_currentMedia(&This->IWMPPlayer4_iface, pMedia);
}

static HRESULT WINAPI WMPPlayer_get_mediaCollection(IWMPPlayer *iface, IWMPMediaCollection **ppMediaCollection)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer(iface);
    return WMPPlayer4_get_mediaCollection(&This->IWMPPlayer4_iface, ppMediaCollection);
}

static HRESULT WINAPI WMPPlayer_get_playlistCollection(IWMPPlayer *iface, IWMPPlaylistCollection **ppPlaylistCollection)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer(iface);
    return WMPPlayer4_get_playlistCollection(&This->IWMPPlayer4_iface, ppPlaylistCollection);
}

static HRESULT WINAPI WMPPlayer_get_versionInfo(IWMPPlayer *iface, BSTR *version)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer(iface);
    return WMPPlayer4_get_versionInfo(&This->IWMPPlayer4_iface, version);
}

static HRESULT WINAPI WMPPlayer_launchURL(IWMPPlayer *iface, BSTR url)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer(iface);
    return WMPPlayer4_launchURL(&This->IWMPPlayer4_iface, url);
}

static HRESULT WINAPI WMPPlayer_get_network(IWMPPlayer *iface, IWMPNetwork **ppQNI)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer(iface);
    return WMPPlayer4_get_network(&This->IWMPPlayer4_iface, ppQNI);
}

static HRESULT WINAPI WMPPlayer_get_currentPlaylist(IWMPPlayer *iface, IWMPPlaylist **ppPL)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer(iface);
    return WMPPlayer4_get_currentPlaylist(&This->IWMPPlayer4_iface, ppPL);
}

static HRESULT WINAPI WMPPlayer_put_currentPlaylist(IWMPPlayer *iface, IWMPPlaylist *pPL)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer(iface);
    return WMPPlayer4_put_currentPlaylist(&This->IWMPPlayer4_iface, pPL);
}

static HRESULT WINAPI WMPPlayer_get_cdromCollection(IWMPPlayer *iface, IWMPCdromCollection **ppCdromCollection)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer(iface);
    return WMPPlayer4_get_cdromCollection(&This->IWMPPlayer4_iface, ppCdromCollection);
}

static HRESULT WINAPI WMPPlayer_get_closedCaption(IWMPPlayer *iface, IWMPClosedCaption **ppClosedCaption)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer(iface);
    return WMPPlayer4_get_closedCaption(&This->IWMPPlayer4_iface, ppClosedCaption);
}

static HRESULT WINAPI WMPPlayer_get_isOnline(IWMPPlayer *iface, VARIANT_BOOL *pfOnline)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer(iface);
    return WMPPlayer4_get_isOnline(&This->IWMPPlayer4_iface, pfOnline);
}

static HRESULT WINAPI WMPPlayer_get_Error(IWMPPlayer *iface, IWMPError **ppError)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer(iface);
    return WMPPlayer4_get_Error(&This->IWMPPlayer4_iface, ppError);
}

static HRESULT WINAPI WMPPlayer_get_Status(IWMPPlayer *iface, BSTR *pbstrStatus)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer(iface);
    return WMPPlayer4_get_Status(&This->IWMPPlayer4_iface, pbstrStatus);
}

static HRESULT WINAPI WMPPlayer_get_enabled(IWMPPlayer *iface, VARIANT_BOOL *pbEnabled)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer(iface);
    return WMPPlayer4_get_enabled(&This->IWMPPlayer4_iface, pbEnabled);
}

static HRESULT WINAPI WMPPlayer_put_enabled(IWMPPlayer *iface, VARIANT_BOOL enabled)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer(iface);
    return WMPPlayer4_put_enabled(&This->IWMPPlayer4_iface, enabled);
}

static HRESULT WINAPI WMPPlayer_get_fullScreen(IWMPPlayer *iface, VARIANT_BOOL *pbFullScreen)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer(iface);
    return WMPPlayer4_get_fullScreen(&This->IWMPPlayer4_iface, pbFullScreen);
}

static HRESULT WINAPI WMPPlayer_put_fullScreen(IWMPPlayer *iface, VARIANT_BOOL fullscreen)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer(iface);
    return WMPPlayer4_put_fullScreen(&This->IWMPPlayer4_iface, fullscreen);
}

static HRESULT WINAPI WMPPlayer_get_enableContextMenu(IWMPPlayer *iface, VARIANT_BOOL *pbEnableContextMenu)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer(iface);
    return WMPPlayer4_get_enableContextMenu(&This->IWMPPlayer4_iface, pbEnableContextMenu);
}

static HRESULT WINAPI WMPPlayer_put_enableContextMenu(IWMPPlayer *iface, VARIANT_BOOL enable)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer(iface);
    return WMPPlayer4_put_enableContextMenu(&This->IWMPPlayer4_iface, enable);
}

static HRESULT WINAPI WMPPlayer_put_uiMode(IWMPPlayer *iface, BSTR mode)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer(iface);
    return WMPPlayer4_put_uiMode(&This->IWMPPlayer4_iface, mode);
}

static HRESULT WINAPI WMPPlayer_get_uiMode(IWMPPlayer *iface, BSTR *pbstrMode)
{
    WindowsMediaPlayer *This = impl_from_IWMPPlayer(iface);
    return WMPPlayer4_get_uiMode(&This->IWMPPlayer4_iface, pbstrMode);
}

static IWMPPlayerVtbl WMPPlayerVtbl = {
    WMPPlayer_QueryInterface,
    WMPPlayer_AddRef,
    WMPPlayer_Release,
    WMPPlayer_GetTypeInfoCount,
    WMPPlayer_GetTypeInfo,
    WMPPlayer_GetIDsOfNames,
    WMPPlayer_Invoke,
    WMPPlayer_close,
    WMPPlayer_get_URL,
    WMPPlayer_put_URL,
    WMPPlayer_get_openState,
    WMPPlayer_get_playState,
    WMPPlayer_get_controls,
    WMPPlayer_get_settings,
    WMPPlayer_get_currentMedia,
    WMPPlayer_put_currentMedia,
    WMPPlayer_get_mediaCollection,
    WMPPlayer_get_playlistCollection,
    WMPPlayer_get_versionInfo,
    WMPPlayer_launchURL,
    WMPPlayer_get_network,
    WMPPlayer_get_currentPlaylist,
    WMPPlayer_put_currentPlaylist,
    WMPPlayer_get_cdromCollection,
    WMPPlayer_get_closedCaption,
    WMPPlayer_get_isOnline,
    WMPPlayer_get_Error,
    WMPPlayer_get_Status,
    WMPPlayer_get_enabled,
    WMPPlayer_put_enabled,
    WMPPlayer_get_fullScreen,
    WMPPlayer_put_fullScreen,
    WMPPlayer_get_enableContextMenu,
    WMPPlayer_put_enableContextMenu,
    WMPPlayer_put_uiMode,
    WMPPlayer_get_uiMode,
};


static IWMPPlayer4Vtbl WMPPlayer4Vtbl = {
    WMPPlayer4_QueryInterface,
    WMPPlayer4_AddRef,
    WMPPlayer4_Release,
    WMPPlayer4_GetTypeInfoCount,
    WMPPlayer4_GetTypeInfo,
    WMPPlayer4_GetIDsOfNames,
    WMPPlayer4_Invoke,
    WMPPlayer4_close,
    WMPPlayer4_get_URL,
    WMPPlayer4_put_URL,
    WMPPlayer4_get_openState,
    WMPPlayer4_get_playState,
    WMPPlayer4_get_controls,
    WMPPlayer4_get_settings,
    WMPPlayer4_get_currentMedia,
    WMPPlayer4_put_currentMedia,
    WMPPlayer4_get_mediaCollection,
    WMPPlayer4_get_playlistCollection,
    WMPPlayer4_get_versionInfo,
    WMPPlayer4_launchURL,
    WMPPlayer4_get_network,
    WMPPlayer4_get_currentPlaylist,
    WMPPlayer4_put_currentPlaylist,
    WMPPlayer4_get_cdromCollection,
    WMPPlayer4_get_closedCaption,
    WMPPlayer4_get_isOnline,
    WMPPlayer4_get_Error,
    WMPPlayer4_get_Status,
    WMPPlayer4_get_dvd,
    WMPPlayer4_newPlaylist,
    WMPPlayer4_newMedia,
    WMPPlayer4_get_enabled,
    WMPPlayer4_put_enabled,
    WMPPlayer4_get_fullScreen,
    WMPPlayer4_put_fullScreen,
    WMPPlayer4_get_enableContextMenu,
    WMPPlayer4_put_enableContextMenu,
    WMPPlayer4_put_uiMode,
    WMPPlayer4_get_uiMode,
    WMPPlayer4_get_stretchToFit,
    WMPPlayer4_put_stretchToFit,
    WMPPlayer4_get_windowlessVideo,
    WMPPlayer4_put_windowlessVideo,
    WMPPlayer4_get_isRemote,
    WMPPlayer4_get_playerApplication,
    WMPPlayer4_openPlayer
};

static inline WindowsMediaPlayer *impl_from_IWMPSettings(IWMPSettings *iface)
{
    return CONTAINING_RECORD(iface, WindowsMediaPlayer, IWMPSettings_iface);
}

static HRESULT WINAPI WMPSettings_QueryInterface(IWMPSettings *iface, REFIID riid, void **ppv)
{
    WindowsMediaPlayer *This = impl_from_IWMPSettings(iface);
    return IOleObject_QueryInterface(&This->IOleObject_iface, riid, ppv);
}

static ULONG WINAPI WMPSettings_AddRef(IWMPSettings *iface)
{
    WindowsMediaPlayer *This = impl_from_IWMPSettings(iface);
    return IOleObject_AddRef(&This->IOleObject_iface);
}

static ULONG WINAPI WMPSettings_Release(IWMPSettings *iface)
{
    WindowsMediaPlayer *This = impl_from_IWMPSettings(iface);
    return IOleObject_Release(&This->IOleObject_iface);
}

static HRESULT WINAPI WMPSettings_GetTypeInfoCount(IWMPSettings *iface, UINT *pctinfo)
{
    WindowsMediaPlayer *This = impl_from_IWMPSettings(iface);
    FIXME("(%p)->(%p)\n", This, pctinfo);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPSettings_GetTypeInfo(IWMPSettings *iface, UINT iTInfo,
        LCID lcid, ITypeInfo **ppTInfo)
{
    WindowsMediaPlayer *This = impl_from_IWMPSettings(iface);
    FIXME("(%p)->(%u %d %p)\n", This, iTInfo, lcid, ppTInfo);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPSettings_GetIDsOfNames(IWMPSettings *iface, REFIID riid,
        LPOLESTR *rgszNames, UINT cNames, LCID lcid, DISPID *rgDispId)
{
    WindowsMediaPlayer *This = impl_from_IWMPSettings(iface);
    FIXME("(%p)->(%s %p %u %d %p)\n", This, debugstr_guid(riid), rgszNames, cNames, lcid, rgDispId);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPSettings_Invoke(IWMPSettings *iface, DISPID dispIdMember,
        REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS *pDispParams, VARIANT *pVarResult,
        EXCEPINFO *pExcepInfo, UINT *puArgErr)
{
    WindowsMediaPlayer *This = impl_from_IWMPSettings(iface);
    FIXME("(%p)->(%d %s %d %x %p %p %p %p)\n", This, dispIdMember, debugstr_guid(riid), lcid,
          wFlags, pDispParams, pVarResult, pExcepInfo, puArgErr);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPSettings_get_isAvailable(IWMPSettings *iface, BSTR item, VARIANT_BOOL *p)
{
    WindowsMediaPlayer *This = impl_from_IWMPSettings(iface);
    FIXME("(%p)->(%s %p)\n", This, debugstr_w(item), p);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPSettings_get_autoStart(IWMPSettings *iface, VARIANT_BOOL *p)
{
    WindowsMediaPlayer *This = impl_from_IWMPSettings(iface);
    TRACE("(%p)->(%p)\n", This, p);
    if (!p)
        return E_POINTER;
    *p = This->auto_start;
    return S_OK;
}

static HRESULT WINAPI WMPSettings_put_autoStart(IWMPSettings *iface, VARIANT_BOOL v)
{
    WindowsMediaPlayer *This = impl_from_IWMPSettings(iface);
    TRACE("(%p)->(%x)\n", This, v);
    This->auto_start = v;
    return S_OK;
}

static HRESULT WINAPI WMPSettings_get_baseURL(IWMPSettings *iface, BSTR *p)
{
    WindowsMediaPlayer *This = impl_from_IWMPSettings(iface);
    FIXME("(%p)->(%p)\n", This, p);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPSettings_put_baseURL(IWMPSettings *iface, BSTR v)
{
    WindowsMediaPlayer *This = impl_from_IWMPSettings(iface);
    FIXME("(%p)->(%s)\n", This, debugstr_w(v));
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPSettings_get_defaultFrame(IWMPSettings *iface, BSTR *p)
{
    WindowsMediaPlayer *This = impl_from_IWMPSettings(iface);
    FIXME("(%p)->(%p)\n", This, p);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPSettings_put_defaultFrame(IWMPSettings *iface, BSTR v)
{
    WindowsMediaPlayer *This = impl_from_IWMPSettings(iface);
    FIXME("(%p)->(%s)\n", This, debugstr_w(v));
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPSettings_get_invokeURLs(IWMPSettings *iface, VARIANT_BOOL *p)
{
    WindowsMediaPlayer *This = impl_from_IWMPSettings(iface);

    TRACE("(%p)->(%p)\n", This, p);

    if (!p)
        return E_POINTER;
    *p = This->invoke_urls;
    return S_OK;
}

static HRESULT WINAPI WMPSettings_put_invokeURLs(IWMPSettings *iface, VARIANT_BOOL v)
{
    WindowsMediaPlayer *This = impl_from_IWMPSettings(iface);
    /* Leaving as FIXME as we don't currently use this */
    FIXME("(%p)->(%x)\n", This, v);
    This->invoke_urls = v;
    return S_OK;
}

static HRESULT WINAPI WMPSettings_get_mute(IWMPSettings *iface, VARIANT_BOOL *p)
{
    WindowsMediaPlayer *This = impl_from_IWMPSettings(iface);
    FIXME("(%p)->(%p)\n", This, p);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPSettings_put_mute(IWMPSettings *iface, VARIANT_BOOL v)
{
    WindowsMediaPlayer *This = impl_from_IWMPSettings(iface);
    FIXME("(%p)->(%x)\n", This, v);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPSettings_get_playCount(IWMPSettings *iface, LONG *p)
{
    WindowsMediaPlayer *This = impl_from_IWMPSettings(iface);
    FIXME("(%p)->(%p)\n", This, p);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPSettings_put_playCount(IWMPSettings *iface, LONG v)
{
    WindowsMediaPlayer *This = impl_from_IWMPSettings(iface);
    FIXME("(%p)->(%d)\n", This, v);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPSettings_get_rate(IWMPSettings *iface, double *p)
{
    WindowsMediaPlayer *This = impl_from_IWMPSettings(iface);
    FIXME("(%p)->(%p)\n", This, p);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPSettings_put_rate(IWMPSettings *iface, double v)
{
    WindowsMediaPlayer *This = impl_from_IWMPSettings(iface);
    FIXME("(%p)->(%lf)\n", This, v);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPSettings_get_balance(IWMPSettings *iface, LONG *p)
{
    WindowsMediaPlayer *This = impl_from_IWMPSettings(iface);
    FIXME("(%p)->(%p)\n", This, p);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPSettings_put_balance(IWMPSettings *iface, LONG v)
{
    WindowsMediaPlayer *This = impl_from_IWMPSettings(iface);
    FIXME("(%p)->(%d)\n", This, v);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPSettings_get_volume(IWMPSettings *iface, LONG *p)
{
    WindowsMediaPlayer *This = impl_from_IWMPSettings(iface);
    FIXME("(%p)->(%p)\n", This, p);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPSettings_put_volume(IWMPSettings *iface, LONG v)
{
    WindowsMediaPlayer *This = impl_from_IWMPSettings(iface);
    FIXME("(%p)->(%d)\n", This, v);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPSettings_getMode(IWMPSettings *iface, BSTR mode, VARIANT_BOOL *p)
{
    WindowsMediaPlayer *This = impl_from_IWMPSettings(iface);
    FIXME("(%p)->(%s %p)\n", This, debugstr_w(mode), p);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPSettings_setMode(IWMPSettings *iface, BSTR mode, VARIANT_BOOL v)
{
    WindowsMediaPlayer *This = impl_from_IWMPSettings(iface);
    FIXME("(%p)->(%s %x)\n", This, debugstr_w(mode), v);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPSettings_get_enableErrorDialogs(IWMPSettings *iface, VARIANT_BOOL *p)
{
    WindowsMediaPlayer *This = impl_from_IWMPSettings(iface);

    TRACE("(%p)->(%p)\n", This, p);

    if (!p)
        return E_POINTER;
    *p = This->enable_error_dialogs;
    return S_OK;
}

static HRESULT WINAPI WMPSettings_put_enableErrorDialogs(IWMPSettings *iface, VARIANT_BOOL v)
{
    WindowsMediaPlayer *This = impl_from_IWMPSettings(iface);
    /* Leaving as FIXME as we don't currently use this */
    FIXME("(%p)->(%x)\n", This, v);
    This->enable_error_dialogs = v;
    return S_OK;
}

static const IWMPSettingsVtbl WMPSettingsVtbl = {
    WMPSettings_QueryInterface,
    WMPSettings_AddRef,
    WMPSettings_Release,
    WMPSettings_GetTypeInfoCount,
    WMPSettings_GetTypeInfo,
    WMPSettings_GetIDsOfNames,
    WMPSettings_Invoke,
    WMPSettings_get_isAvailable,
    WMPSettings_get_autoStart,
    WMPSettings_put_autoStart,
    WMPSettings_get_baseURL,
    WMPSettings_put_baseURL,
    WMPSettings_get_defaultFrame,
    WMPSettings_put_defaultFrame,
    WMPSettings_get_invokeURLs,
    WMPSettings_put_invokeURLs,
    WMPSettings_get_mute,
    WMPSettings_put_mute,
    WMPSettings_get_playCount,
    WMPSettings_put_playCount,
    WMPSettings_get_rate,
    WMPSettings_put_rate,
    WMPSettings_get_balance,
    WMPSettings_put_balance,
    WMPSettings_get_volume,
    WMPSettings_put_volume,
    WMPSettings_getMode,
    WMPSettings_setMode,
    WMPSettings_get_enableErrorDialogs,
    WMPSettings_put_enableErrorDialogs
};

static HRESULT WINAPI WMPNetwork_QueryInterface(IWMPNetwork *iface, REFIID riid, void **ppv)
{
    if(IsEqualGUID(riid, &IID_IDispatch)) {
        *ppv = iface;
    }else if(IsEqualGUID(riid, &IID_IWMPNetwork)) {
        *ppv = iface;
    }else {
        WARN("Unsupported interface (%s)\n", wine_dbgstr_guid(riid));
        *ppv = NULL;
        return E_NOINTERFACE;
    }

    IUnknown_AddRef((IUnknown*)*ppv);
    return S_OK;
}

static ULONG WINAPI WMPNetwork_AddRef(IWMPNetwork *iface)
{
    WindowsMediaPlayer *This = impl_from_IWMPNetwork(iface);
    return IOleObject_AddRef(&This->IOleObject_iface);
}

static ULONG WINAPI WMPNetwork_Release(IWMPNetwork *iface)
{
    WindowsMediaPlayer *This = impl_from_IWMPNetwork(iface);
    return IOleObject_Release(&This->IOleObject_iface);
}

static HRESULT WINAPI WMPNetwork_GetTypeInfoCount(IWMPNetwork *iface, UINT *pctinfo)
{
    WindowsMediaPlayer *This = impl_from_IWMPNetwork(iface);
    FIXME("(%p)->(%p)\n", This, pctinfo);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPNetwork_GetTypeInfo(IWMPNetwork *iface, UINT iTInfo,
        LCID lcid, ITypeInfo **ppTInfo)
{
    WindowsMediaPlayer *This = impl_from_IWMPNetwork(iface);
    FIXME("(%p)->(%u %d %p)\n", This, iTInfo, lcid, ppTInfo);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPNetwork_GetIDsOfNames(IWMPNetwork *iface, REFIID riid,
        LPOLESTR *rgszNames, UINT cNames, LCID lcid, DISPID *rgDispId)
{
    WindowsMediaPlayer *This = impl_from_IWMPNetwork(iface);
    FIXME("(%p)->(%s %p %u %d %p)\n", This, debugstr_guid(riid), rgszNames, cNames, lcid, rgDispId);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPNetwork_Invoke(IWMPNetwork *iface, DISPID dispIdMember,
        REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS *pDispParams, VARIANT *pVarResult,
        EXCEPINFO *pExcepInfo, UINT *puArgErr)
{
    WindowsMediaPlayer *This = impl_from_IWMPNetwork(iface);
    FIXME("(%p)->(%d %s %d %x %p %p %p %p)\n", This, dispIdMember, debugstr_guid(riid), lcid,
          wFlags, pDispParams, pVarResult, pExcepInfo, puArgErr);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPNetwork_get_bandWidth(IWMPNetwork *iface, LONG *plBandwidth)
{
    WindowsMediaPlayer *This = impl_from_IWMPNetwork(iface);
    FIXME("(%p)->(%p)\n", This, plBandwidth);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPNetwork_get_recoveredPackets(IWMPNetwork *iface, LONG *plRecoveredPackets)
{
    WindowsMediaPlayer *This = impl_from_IWMPNetwork(iface);
    FIXME("(%p)->(%p)\n", This, plRecoveredPackets);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPNetwork_get_sourceProtocol(IWMPNetwork *iface, BSTR *pbstrSourceProtocol)
{
    WindowsMediaPlayer *This = impl_from_IWMPNetwork(iface);
    FIXME("(%p)->(%p)\n", This, pbstrSourceProtocol);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPNetwork_get_receivedPackets(IWMPNetwork *iface, LONG *plReceivedPackets)
{
    WindowsMediaPlayer *This = impl_from_IWMPNetwork(iface);
    FIXME("(%p)->(%p)\n", This, plReceivedPackets);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPNetwork_get_lostPackets(IWMPNetwork *iface, LONG *plLostPackets)
{
    WindowsMediaPlayer *This = impl_from_IWMPNetwork(iface);
    FIXME("(%p)->(%p)\n", This, plLostPackets);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPNetwork_get_receptionQuality(IWMPNetwork *iface, LONG *plReceptionQuality)
{
    WindowsMediaPlayer *This = impl_from_IWMPNetwork(iface);
    FIXME("(%p)->(%p)\n", This, plReceptionQuality);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPNetwork_get_bufferingCount(IWMPNetwork *iface, LONG *plBufferingCount)
{
    WindowsMediaPlayer *This = impl_from_IWMPNetwork(iface);
    FIXME("(%p)->(%p)\n", This, plBufferingCount);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPNetwork_get_bufferingProgress(IWMPNetwork *iface, LONG *plBufferingProgress)
{
    WindowsMediaPlayer *This = impl_from_IWMPNetwork(iface);
    FIXME("(%p)->(%p)\n", This, plBufferingProgress);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPNetwork_get_bufferingTime(IWMPNetwork *iface, LONG *plBufferingTime)
{
    WindowsMediaPlayer *This = impl_from_IWMPNetwork(iface);
    FIXME("(%p)->(%p)\n", This, plBufferingTime);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPNetwork_put_bufferingTime(IWMPNetwork *iface, LONG lBufferingTime)
{
    WindowsMediaPlayer *This = impl_from_IWMPNetwork(iface);
    FIXME("(%p)->(%d)\n", This, lBufferingTime);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPNetwork_get_frameRate(IWMPNetwork *iface, LONG *plFrameRate)
{
    WindowsMediaPlayer *This = impl_from_IWMPNetwork(iface);
    FIXME("(%p)->(%p)\n", This, plFrameRate);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPNetwork_get_maxBitRate(IWMPNetwork *iface, LONG *plBitRate)
{
    WindowsMediaPlayer *This = impl_from_IWMPNetwork(iface);
    FIXME("(%p)->(%p)\n", This, plBitRate);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPNetwork_get_bitRate(IWMPNetwork *iface, LONG *plBitRate)
{
    WindowsMediaPlayer *This = impl_from_IWMPNetwork(iface);
    FIXME("(%p)->(%p)\n", This, plBitRate);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPNetwork_getProxySettings(IWMPNetwork *iface, BSTR bstrProtocol, LONG *plProxySetting)
{
    WindowsMediaPlayer *This = impl_from_IWMPNetwork(iface);
    FIXME("(%p)->(%s, %p)\n", This, debugstr_w(bstrProtocol), plProxySetting);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPNetwork_setProxySettings(IWMPNetwork *iface, BSTR bstrProtocol, LONG lProxySetting)
{
    WindowsMediaPlayer *This = impl_from_IWMPNetwork(iface);
    FIXME("(%p)->(%s, %d)\n", This, debugstr_w(bstrProtocol), lProxySetting);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPNetwork_getProxyName(IWMPNetwork *iface, BSTR bstrProtocol, BSTR *pbstrProxyName)
{
    WindowsMediaPlayer *This = impl_from_IWMPNetwork(iface);
    FIXME("(%p)->(%s, %p)\n", This, debugstr_w(bstrProtocol), pbstrProxyName);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPNetwork_setProxyName(IWMPNetwork *iface, BSTR bstrProtocol, BSTR bstrProxyName)
{
    WindowsMediaPlayer *This = impl_from_IWMPNetwork(iface);
    FIXME("(%p)->(%s, %s)\n", This, debugstr_w(bstrProtocol), debugstr_w(bstrProxyName));
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPNetwork_getProxyPort(IWMPNetwork *iface, BSTR bstrProtocol, LONG *plProxyPort)
{
    WindowsMediaPlayer *This = impl_from_IWMPNetwork(iface);
    FIXME("(%p)->(%s, %p)\n", This, debugstr_w(bstrProtocol), plProxyPort);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPNetwork_setProxyPort(IWMPNetwork *iface, BSTR bstrProtocol, LONG lProxyPort)
{
    WindowsMediaPlayer *This = impl_from_IWMPNetwork(iface);
    FIXME("(%p)->(%s, %d)\n", This, debugstr_w(bstrProtocol), lProxyPort);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPNetwork_getProxyExceptionList(IWMPNetwork *iface, BSTR bstrProtocol, BSTR *pbstrExceptionList)
{
    WindowsMediaPlayer *This = impl_from_IWMPNetwork(iface);
    FIXME("(%p)->(%s, %p)\n", This, debugstr_w(bstrProtocol), pbstrExceptionList);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPNetwork_setProxyExceptionList(IWMPNetwork *iface, BSTR bstrProtocol, BSTR bstrExceptionList)
{
    WindowsMediaPlayer *This = impl_from_IWMPNetwork(iface);
    FIXME("(%p)->(%s, %s)\n", This, debugstr_w(bstrProtocol), debugstr_w(bstrExceptionList));
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPNetwork_getProxyBypassForLocal(IWMPNetwork *iface, BSTR bstrProtocol, VARIANT_BOOL *pfBypassForLocal)
{
    WindowsMediaPlayer *This = impl_from_IWMPNetwork(iface);
    FIXME("(%p)->(%s, %p)\n", This, debugstr_w(bstrProtocol), pfBypassForLocal);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPNetwork_setProxyBypassForLocal(IWMPNetwork *iface, BSTR bstrProtocol, VARIANT_BOOL fBypassForLocal)
{
    WindowsMediaPlayer *This = impl_from_IWMPNetwork(iface);
    FIXME("(%p)->(%s, %d)\n", This, debugstr_w(bstrProtocol), fBypassForLocal);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPNetwork_get_maxBandwidth(IWMPNetwork *iface, LONG *plMaxBandwidth)
{
    WindowsMediaPlayer *This = impl_from_IWMPNetwork(iface);
    FIXME("(%p)->(%p)\n", This, plMaxBandwidth);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPNetwork_put_maxBandwidth(IWMPNetwork *iface, LONG lMaxBandwidth)
{
    WindowsMediaPlayer *This = impl_from_IWMPNetwork(iface);
    FIXME("(%p)->(%d)\n", This, lMaxBandwidth);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPNetwork_get_downloadProgress(IWMPNetwork *iface, LONG *plDownloadProgress)
{
    WindowsMediaPlayer *This = impl_from_IWMPNetwork(iface);
    FIXME("(%p)->(%p)\n", This, plDownloadProgress);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPNetwork_get_encodedFrameRate(IWMPNetwork *iface, LONG *plFrameRate)
{
    WindowsMediaPlayer *This = impl_from_IWMPNetwork(iface);
    FIXME("(%p)->(%p)\n", This, plFrameRate);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPNetwork_get_framesSkipped(IWMPNetwork *iface, LONG *plFrames)
{
    WindowsMediaPlayer *This = impl_from_IWMPNetwork(iface);
    FIXME("(%p)->(%p)\n", This, plFrames);
    return E_NOTIMPL;
}

static const IWMPNetworkVtbl WMPNetworkVtbl = {
    WMPNetwork_QueryInterface,
    WMPNetwork_AddRef,
    WMPNetwork_Release,
    WMPNetwork_GetTypeInfoCount,
    WMPNetwork_GetTypeInfo,
    WMPNetwork_GetIDsOfNames,
    WMPNetwork_Invoke,
    WMPNetwork_get_bandWidth,
    WMPNetwork_get_recoveredPackets,
    WMPNetwork_get_sourceProtocol,
    WMPNetwork_get_receivedPackets,
    WMPNetwork_get_lostPackets,
    WMPNetwork_get_receptionQuality,
    WMPNetwork_get_bufferingCount,
    WMPNetwork_get_bufferingProgress,
    WMPNetwork_get_bufferingTime,
    WMPNetwork_put_bufferingTime,
    WMPNetwork_get_frameRate,
    WMPNetwork_get_maxBitRate,
    WMPNetwork_get_bitRate,
    WMPNetwork_getProxySettings,
    WMPNetwork_setProxySettings,
    WMPNetwork_getProxyName,
    WMPNetwork_setProxyName,
    WMPNetwork_getProxyPort,
    WMPNetwork_setProxyPort,
    WMPNetwork_getProxyExceptionList,
    WMPNetwork_setProxyExceptionList,
    WMPNetwork_getProxyBypassForLocal,
    WMPNetwork_setProxyBypassForLocal,
    WMPNetwork_get_maxBandwidth,
    WMPNetwork_put_maxBandwidth,
    WMPNetwork_get_downloadProgress,
    WMPNetwork_get_encodedFrameRate,
    WMPNetwork_get_framesSkipped,
};

static HRESULT WINAPI WMPControls_QueryInterface(IWMPControls *iface, REFIID riid, void **ppv)
{
    if(IsEqualGUID(riid, &IID_IDispatch)) {
        *ppv = iface;
    }else if(IsEqualGUID(riid, &IID_IWMPControls)) {
        *ppv = iface;
    }else {
        WARN("Unsupported interface (%s)\n", wine_dbgstr_guid(riid));
        *ppv = NULL;
        return E_NOINTERFACE;
    }

    IUnknown_AddRef((IUnknown*)*ppv);
    return S_OK;
}

static ULONG WINAPI WMPControls_AddRef(IWMPControls *iface)
{
    WindowsMediaPlayer *This = impl_from_IWMPControls(iface);
    return IOleObject_AddRef(&This->IOleObject_iface);
}

static ULONG WINAPI WMPControls_Release(IWMPControls *iface)
{
    WindowsMediaPlayer *This = impl_from_IWMPControls(iface);
    return IOleObject_Release(&This->IOleObject_iface);
}

static HRESULT WINAPI WMPControls_GetTypeInfoCount(IWMPControls *iface, UINT *pctinfo)
{
    WindowsMediaPlayer *This = impl_from_IWMPControls(iface);
    FIXME("(%p)->(%p)\n", This, pctinfo);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPControls_GetTypeInfo(IWMPControls *iface, UINT iTInfo,
        LCID lcid, ITypeInfo **ppTInfo)
{
    WindowsMediaPlayer *This = impl_from_IWMPControls(iface);
    FIXME("(%p)->(%u %d %p)\n", This, iTInfo, lcid, ppTInfo);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPControls_GetIDsOfNames(IWMPControls *iface, REFIID riid,
        LPOLESTR *rgszNames, UINT cNames, LCID lcid, DISPID *rgDispId)
{
    WindowsMediaPlayer *This = impl_from_IWMPControls(iface);
    FIXME("(%p)->(%s %p %u %d %p)\n", This, debugstr_guid(riid), rgszNames, cNames, lcid, rgDispId);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPControls_Invoke(IWMPControls *iface, DISPID dispIdMember,
        REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS *pDispParams, VARIANT *pVarResult,
        EXCEPINFO *pExcepInfo, UINT *puArgErr)
{
    WindowsMediaPlayer *This = impl_from_IWMPControls(iface);
    FIXME("(%p)->(%d %s %d %x %p %p %p %p)\n", This, dispIdMember, debugstr_guid(riid), lcid,
          wFlags, pDispParams, pVarResult, pExcepInfo, puArgErr);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPControls_get_isAvailable(IWMPControls *iface, BSTR bstrItem, VARIANT_BOOL *pIsAvailable)
{
    WindowsMediaPlayer *This = impl_from_IWMPControls(iface);
    FIXME("(%p)->(%s)\n", This, debugstr_w(bstrItem));
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPControls_play(IWMPControls *iface)
{
    WindowsMediaPlayer *This = impl_from_IWMPControls(iface);
    FIXME("(%p)\n", This);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPControls_stop(IWMPControls *iface)
{
    WindowsMediaPlayer *This = impl_from_IWMPControls(iface);
    FIXME("(%p)\n", This);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPControls_pause(IWMPControls *iface)
{
    WindowsMediaPlayer *This = impl_from_IWMPControls(iface);
    FIXME("(%p)\n", This);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPControls_fastForward(IWMPControls *iface)
{
    WindowsMediaPlayer *This = impl_from_IWMPControls(iface);
    FIXME("(%p)\n", This);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPControls_fastReverse(IWMPControls *iface)
{
    WindowsMediaPlayer *This = impl_from_IWMPControls(iface);
    FIXME("(%p)\n", This);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPControls_get_currentPosition(IWMPControls *iface, DOUBLE *pdCurrentPosition)
{
    WindowsMediaPlayer *This = impl_from_IWMPControls(iface);
    FIXME("(%p)->(%p)\n", This, pdCurrentPosition);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPControls_put_currentPosition(IWMPControls *iface, DOUBLE dCurrentPosition)
{
    WindowsMediaPlayer *This = impl_from_IWMPControls(iface);
    FIXME("(%p)->(%f)\n", This, dCurrentPosition);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPControls_get_currentPositionString(IWMPControls *iface, BSTR *pbstrCurrentPosition)
{
    WindowsMediaPlayer *This = impl_from_IWMPControls(iface);
    FIXME("(%p)->(%p)\n", This, pbstrCurrentPosition);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPControls_next(IWMPControls *iface)
{
    WindowsMediaPlayer *This = impl_from_IWMPControls(iface);
    FIXME("(%p)\n", This);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPControls_previous(IWMPControls *iface)
{
    WindowsMediaPlayer *This = impl_from_IWMPControls(iface);
    FIXME("(%p)\n", This);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPControls_get_currentItem(IWMPControls *iface, IWMPMedia **ppIWMPMedia)
{
    WindowsMediaPlayer *This = impl_from_IWMPControls(iface);
    FIXME("(%p)->(%p)\n", This, ppIWMPMedia);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPControls_put_currentItem(IWMPControls *iface, IWMPMedia *pIWMPMedia)
{
    WindowsMediaPlayer *This = impl_from_IWMPControls(iface);
    FIXME("(%p)->(%p)\n", This, pIWMPMedia);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPControls_get_currentMarker(IWMPControls *iface, LONG *plMarker)
{
    WindowsMediaPlayer *This = impl_from_IWMPControls(iface);
    FIXME("(%p)->(%p)\n", This, plMarker);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPControls_put_currentMarker(IWMPControls *iface, LONG lMarker)
{
    WindowsMediaPlayer *This = impl_from_IWMPControls(iface);
    FIXME("(%p)->(%d)\n", This, lMarker);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPControls_playItem(IWMPControls *iface, IWMPMedia *pIWMPMedia)
{
    WindowsMediaPlayer *This = impl_from_IWMPControls(iface);
    FIXME("(%p)->(%p)\n", This, pIWMPMedia);
    return E_NOTIMPL;
}

static const IWMPControlsVtbl WMPControlsVtbl = {
    WMPControls_QueryInterface,
    WMPControls_AddRef,
    WMPControls_Release,
    WMPControls_GetTypeInfoCount,
    WMPControls_GetTypeInfo,
    WMPControls_GetIDsOfNames,
    WMPControls_Invoke,
    WMPControls_get_isAvailable,
    WMPControls_play,
    WMPControls_stop,
    WMPControls_pause,
    WMPControls_fastForward,
    WMPControls_fastReverse,
    WMPControls_get_currentPosition,
    WMPControls_put_currentPosition,
    WMPControls_get_currentPositionString,
    WMPControls_next,
    WMPControls_previous,
    WMPControls_get_currentItem,
    WMPControls_put_currentItem,
    WMPControls_get_currentMarker,
    WMPControls_put_currentMarker,
    WMPControls_playItem,
};

static HRESULT WINAPI WMPMedia_QueryInterface(IWMPMedia *iface, REFIID riid, void **ppv)
{
    WMPMedia *This = impl_from_IWMPMedia(iface);
    TRACE("(%p)\n", This);
    if(IsEqualGUID(&IID_IUnknown, riid)) {
        TRACE("(%p)->(IID_IUnknown %p)\n", This, ppv);
        *ppv = &This->IWMPMedia_iface;
    }else if(IsEqualGUID(&IID_IDispatch, riid)) {
        TRACE("(%p)->(IID_IDispatch %p)\n", This, ppv);
        *ppv = &This->IWMPMedia_iface;
    }else if(IsEqualGUID(&IID_IWMPMedia, riid)) {
        TRACE("(%p)->(IID_IWMPMedia %p)\n", This, ppv);
        *ppv = &This->IWMPMedia_iface;
    }else {
        WARN("Unsupported interface %s\n", debugstr_guid(riid));
        *ppv = NULL;
        return E_NOINTERFACE;
    }

    IUnknown_AddRef((IUnknown*)*ppv);
    return S_OK;
}

static ULONG WINAPI WMPMedia_AddRef(IWMPMedia *iface)
{
    WMPMedia *This = impl_from_IWMPMedia(iface);
    LONG ref = InterlockedIncrement(&This->ref);

    TRACE("(%p) ref=%d\n", This, ref);

    return ref;
}

static ULONG WINAPI WMPMedia_Release(IWMPMedia *iface)
{
    WMPMedia *This = impl_from_IWMPMedia(iface);
    LONG ref = InterlockedDecrement(&This->ref);

    TRACE("(%p) ref=%d\n", This, ref);

    if(!ref) {
        heap_free(This->url);
        heap_free(This);
    }

    return ref;
}

static HRESULT WINAPI WMPMedia_GetTypeInfoCount(IWMPMedia *iface, UINT *pctinfo)
{
    WMPMedia *This = impl_from_IWMPMedia(iface);
    FIXME("(%p)->(%p)\n", This, pctinfo);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPMedia_GetTypeInfo(IWMPMedia *iface, UINT iTInfo,
        LCID lcid, ITypeInfo **ppTInfo)
{
    WMPMedia *This = impl_from_IWMPMedia(iface);
    FIXME("(%p)->(%u %d %p)\n", This, iTInfo, lcid, ppTInfo);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPMedia_GetIDsOfNames(IWMPMedia *iface, REFIID riid,
        LPOLESTR *rgszNames, UINT cNames, LCID lcid, DISPID *rgDispId)
{
    WMPMedia *This = impl_from_IWMPMedia(iface);
    FIXME("(%p)->(%s %p %u %d %p)\n", This, debugstr_guid(riid), rgszNames, cNames, lcid, rgDispId);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPMedia_Invoke(IWMPMedia *iface, DISPID dispIdMember,
        REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS *pDispParams, VARIANT *pVarResult,
        EXCEPINFO *pExcepInfo, UINT *puArgErr)
{
    WMPMedia *This = impl_from_IWMPMedia(iface);
    FIXME("(%p)->(%d %s %d %x %p %p %p %p)\n", This, dispIdMember, debugstr_guid(riid), lcid,
          wFlags, pDispParams, pVarResult, pExcepInfo, puArgErr);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPMedia_get_isIdentical(IWMPMedia *iface, IWMPMedia *other, VARIANT_BOOL *pvBool)
{
    WMPMedia *This = impl_from_IWMPMedia(iface);
    FIXME("(%p)->(%p, %p)\n", This, other, pvBool);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPMedia_get_sourceURL(IWMPMedia *iface, BSTR *pbstrSourceUrl)
{
    WMPMedia *This = impl_from_IWMPMedia(iface);
    BSTR url;
    TRACE("(%p)->(%p)\n", This, pbstrSourceUrl);
    url = SysAllocString(This->url);
    if (url) {
        *pbstrSourceUrl = url;
        return S_OK;
    }
    return E_OUTOFMEMORY;
}

static HRESULT WINAPI WMPMedia_get_name(IWMPMedia *iface, BSTR *pbstrName)
{
    WMPMedia *This = impl_from_IWMPMedia(iface);
    FIXME("(%p)->(%p)\n", This, pbstrName);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPMedia_put_name(IWMPMedia *iface, BSTR pbstrName)
{
    WMPMedia *This = impl_from_IWMPMedia(iface);
    FIXME("(%p)->(%s)\n", This, debugstr_w(pbstrName));
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPMedia_get_imageSourceWidth(IWMPMedia *iface, LONG *pWidth)
{
    WMPMedia *This = impl_from_IWMPMedia(iface);
    FIXME("(%p)->(%p)\n", This, pWidth);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPMedia_get_imageSourceHeight(IWMPMedia *iface, LONG *pHeight)
{
    WMPMedia *This = impl_from_IWMPMedia(iface);
    FIXME("(%p)->(%p)\n", This, pHeight);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPMedia_get_markerCount(IWMPMedia *iface, LONG* pMarkerCount)
{
    WMPMedia *This = impl_from_IWMPMedia(iface);
    FIXME("(%p)->(%p)\n", This, pMarkerCount);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPMedia_getMarkerTime(IWMPMedia *iface, LONG MarkerNum, DOUBLE *pMarkerTime)
{
    WMPMedia *This = impl_from_IWMPMedia(iface);
    FIXME("(%p)->(%d, %p)\n", This, MarkerNum, pMarkerTime);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPMedia_getMarkerName(IWMPMedia *iface, LONG MarkerNum, BSTR *pbstrMarkerName)
{
    WMPMedia *This = impl_from_IWMPMedia(iface);
    FIXME("(%p)->(%d, %p)\n", This, MarkerNum, pbstrMarkerName);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPMedia_get_duration(IWMPMedia *iface, DOUBLE *pDuration)
{
    WMPMedia *This = impl_from_IWMPMedia(iface);
    FIXME("(%p)->(%p)\n", This, pDuration);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPMedia_get_durationString(IWMPMedia *iface, BSTR *pbstrDuration)
{
    WMPMedia *This = impl_from_IWMPMedia(iface);
    FIXME("(%p)->(%p)\n", This, pbstrDuration);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPMedia_get_attributeCount(IWMPMedia *iface, LONG *plCount)
{
    WMPMedia *This = impl_from_IWMPMedia(iface);
    FIXME("(%p)->(%p)\n", This, plCount);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPMedia_getAttributeName(IWMPMedia *iface, LONG lIndex, BSTR *pbstrItemName)
{
    WMPMedia *This = impl_from_IWMPMedia(iface);
    FIXME("(%p)->(%d, %p)\n", This, lIndex, pbstrItemName);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPMedia_getItemInfo(IWMPMedia *iface, BSTR bstrItemName, BSTR *pbstrVal)
{
    WMPMedia *This = impl_from_IWMPMedia(iface);
    FIXME("(%p)->(%s, %p)\n", This, debugstr_w(bstrItemName), pbstrVal);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPMedia_setItemInfo(IWMPMedia *iface, BSTR bstrItemName, BSTR bstrVal)
{
    WMPMedia *This = impl_from_IWMPMedia(iface);
    FIXME("(%p)->(%s, %s)\n", This, debugstr_w(bstrItemName), debugstr_w(bstrVal));
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPMedia_getItemInfoByAtom(IWMPMedia *iface, LONG lAtom, BSTR *pbstrVal)
{
    WMPMedia *This = impl_from_IWMPMedia(iface);
    FIXME("(%p)->(%d, %p)\n", This, lAtom, pbstrVal);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPMedia_isMemberOf(IWMPMedia *iface, IWMPPlaylist *pPlaylist, VARIANT_BOOL *pvarfIsMemberOf)
{
    WMPMedia *This = impl_from_IWMPMedia(iface);
    FIXME("(%p)->(%p, %p)\n", This, pPlaylist, pvarfIsMemberOf);
    return E_NOTIMPL;
}

static HRESULT WINAPI WMPMedia_isReadOnlyItem(IWMPMedia *iface, BSTR bstrItemName, VARIANT_BOOL *pvarfIsReadOnly)
{
    WMPMedia *This = impl_from_IWMPMedia(iface);
    FIXME("(%p)->(%s, %p)\n", This, debugstr_w(bstrItemName), pvarfIsReadOnly);
    return E_NOTIMPL;
}

static const IWMPMediaVtbl WMPMediaVtbl = {
    WMPMedia_QueryInterface,
    WMPMedia_AddRef,
    WMPMedia_Release,
    WMPMedia_GetTypeInfoCount,
    WMPMedia_GetTypeInfo,
    WMPMedia_GetIDsOfNames,
    WMPMedia_Invoke,
    WMPMedia_get_isIdentical,
    WMPMedia_get_sourceURL,
    WMPMedia_get_name,
    WMPMedia_put_name,
    WMPMedia_get_imageSourceWidth,
    WMPMedia_get_imageSourceHeight,
    WMPMedia_get_markerCount,
    WMPMedia_getMarkerTime,
    WMPMedia_getMarkerName,
    WMPMedia_get_duration,
    WMPMedia_get_durationString,
    WMPMedia_get_attributeCount,
    WMPMedia_getAttributeName,
    WMPMedia_getItemInfo,
    WMPMedia_setItemInfo,
    WMPMedia_getItemInfoByAtom,
    WMPMedia_isMemberOf,
    WMPMedia_isReadOnlyItem
};

void init_player(WindowsMediaPlayer *wmp)
{
    wmp->IWMPPlayer4_iface.lpVtbl = &WMPPlayer4Vtbl;
    wmp->IWMPPlayer_iface.lpVtbl = &WMPPlayerVtbl;
    wmp->IWMPSettings_iface.lpVtbl = &WMPSettingsVtbl;
    wmp->IWMPControls_iface.lpVtbl = &WMPControlsVtbl;
    wmp->IWMPNetwork_iface.lpVtbl = &WMPNetworkVtbl;

    wmp->invoke_urls = VARIANT_TRUE;
    wmp->auto_start = VARIANT_TRUE;
}

void destroy_player(WindowsMediaPlayer *wmp)
{
    if(wmp->wmpmedia)
        IWMPMedia_Release(wmp->wmpmedia);
}

IWMPMedia* create_media_from_url(BSTR url){

    WMPMedia *media = heap_alloc_zero(sizeof(WMPMedia));
    media->IWMPMedia_iface.lpVtbl = &WMPMediaVtbl;
    media->url = heap_strdupW(url);
    media->ref = 1;

    return &media->IWMPMedia_iface;
}
