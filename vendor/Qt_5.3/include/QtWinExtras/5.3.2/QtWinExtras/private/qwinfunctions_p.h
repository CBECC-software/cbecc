/****************************************************************************
 **
 ** Copyright (C) 2013 Ivan Vizir <define-true-false@yandex.com>
 ** Contact: http://www.qt-project.org/legal
 **
 ** This file is part of the QtWinExtras module of the Qt Toolkit.
 **
 ** $QT_BEGIN_LICENSE:LGPL$
 ** Commercial License Usage
 ** Licensees holding valid commercial Qt licenses may use this file in
 ** accordance with the commercial license agreement provided with the
 ** Software or, alternatively, in accordance with the terms contained in
 ** a written agreement between you and Digia.  For licensing terms and
 ** conditions see http://qt.digia.com/licensing.  For further information
 ** use the contact form at http://qt.digia.com/contact-us.
 **
 ** GNU Lesser General Public License Usage
 ** Alternatively, this file may be used under the terms of the GNU Lesser
 ** General Public License version 2.1 as published by the Free Software
 ** Foundation and appearing in the file LICENSE.LGPL included in the
 ** packaging of this file.  Please review the following information to
 ** ensure the GNU Lesser General Public License version 2.1 requirements
 ** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
 **
 ** In addition, as a special exception, Digia gives you certain additional
 ** rights.  These rights are described in the Digia Qt LGPL Exception
 ** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
 **
 ** GNU General Public License Usage
 ** Alternatively, this file may be used under the terms of the GNU
 ** General Public License version 3.0 as published by the Free Software
 ** Foundation and appearing in the file LICENSE.GPL included in the
 ** packaging of this file.  Please review the following information to
 ** ensure the GNU General Public License version 3.0 requirements will be
 ** met: http://www.gnu.org/copyleft/gpl.html.
 **
 **
 ** $QT_END_LICENSE$
 **
 ****************************************************************************/

#ifndef QWINFUNCTIONS_P_H
#define QWINFUNCTIONS_P_H

#include <QString>
#include <qt_windows.h>
#include <uxtheme.h>

QT_BEGIN_NAMESPACE

enum qt_DWMWINDOWATTRIBUTE
{
    qt_DWMWA_NCRENDERING_ENABLED = 1,
    qt_DWMWA_NCRENDERING_POLICY,
    qt_DWMWA_TRANSITIONS_FORCEDISABLED,
    qt_DWMWA_ALLOW_NCPAINT,
    qt_DWMWA_CAPTION_BUTTON_BOUNDS,
    qt_DWMWA_NONCLIENT_RTL_LAYOUT,
    qt_DWMWA_FORCE_ICONIC_REPRESENTATION,
    qt_DWMWA_FLIP3D_POLICY,
    qt_DWMWA_EXTENDED_FRAME_BOUNDS,
    qt_DWMWA_HAS_ICONIC_BITMAP,
    qt_DWMWA_DISALLOW_PEEK,
    qt_DWMWA_EXCLUDED_FROM_PEEK,
    qt_DWMWA_CLOAK,
    qt_DWMWA_CLOAKED,
    qt_DWMWA_FREEZE_REPRESENTATION,
    qt_DWMWA_LAST
};

enum qt_DWMFLIP3DWINDOWPOLICY {
    qt_DWMFLIP3D_DEFAULT,
    qt_DWMFLIP3D_EXCLUDEBELOW,
    qt_DWMFLIP3D_EXCLUDEABOVE,
    qt_DWMFLIP3D_LAST
};

#include <pshpack1.h>

struct qt_DWM_BLURBEHIND {
    DWORD dwFlags;
    BOOL  fEnable;
    HRGN  hRgnBlur;
    BOOL  fTransitionOnMaximized;
};

#include <poppack.h>

const int qt_DWM_BB_ENABLE                = 0x00000001;
const int qt_DWM_BB_BLURREGION            = 0x00000002;
const int qt_DWM_BB_TRANSITIONONMAXIMIZED = 0x00000004;

HRESULT qt_DwmGetColorizationColor(DWORD *colorization, BOOL *opaqueBlend);
HRESULT qt_DwmSetWindowAttribute(HWND hwnd, DWORD dwAttribute, LPCVOID pvAttribute, DWORD cbAttribute);
HRESULT qt_DwmGetWindowAttribute(HWND hwnd, DWORD dwAttribute, PVOID pvAttribute, DWORD cbAttribute);
HRESULT qt_DwmExtendFrameIntoClientArea(HWND hwnd, const MARGINS *pMarInset);
HRESULT qt_DwmEnableBlurBehindWindow(HWND hwnd, const qt_DWM_BLURBEHIND *blurBehind);
HRESULT qt_DwmIsCompositionEnabled(BOOL *enabled);
HRESULT qt_DwmEnableComposition(UINT enabled);
HRESULT qt_SHCreateItemFromParsingName(PCWSTR, IBindCtx *, REFIID, void **);
HRESULT qt_SetCurrentProcessExplicitAppUserModelID(PCWSTR appId);

inline void qt_qstringToNullTerminated(const QString &src, wchar_t *dst)
{
    dst[src.toWCharArray(dst)] = 0;
}

inline wchar_t *qt_qstringToNullTerminated(const QString &src)
{
    wchar_t *buffer = new wchar_t[src.length() + 1];
    qt_qstringToNullTerminated(src, buffer);
    return buffer;
}

QT_END_NAMESPACE

#endif // QWINFUNCTIONS_P_H
