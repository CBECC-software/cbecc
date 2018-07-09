/****************************************************************************
 **
 ** Copyright (C) 2013 Ivan Vizir <define-true-false@yandex.com>
 ** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
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

#ifndef QWINJUMPLIST_P_H
#define QWINJUMPLIST_P_H

#include "qwinjumplist.h"
#include "winshobjidl_p.h"

QT_BEGIN_NAMESPACE

class QWinJumpListPrivate
{
    Q_DECLARE_PUBLIC(QWinJumpList)

public:
    QWinJumpListPrivate();

    static QWinJumpListPrivate *get(QWinJumpList *list)
    {
        return list->d_func();
    }

    static void warning(const char *function, HRESULT hresult);
    static QString iconsDirPath();

    void invalidate();
    void _q_rebuild();
    void destroy();

    bool beginList();
    bool commitList();

    void appendKnownCategory(KNOWNDESTCATEGORY category);
    void appendCustomCategory(QWinJumpListCategory *category);
    void appendTasks(const QList<QWinJumpListItem *> &items);

    static QList<QWinJumpListItem *> fromComCollection(IObjectArray *array);
    static IObjectCollection *toComCollection(const QList<QWinJumpListItem *> &list);
    static QWinJumpListItem *fromIShellLink(IShellLinkW *link);
    static QWinJumpListItem *fromIShellItem(IShellItem2 *shellitem);
    static IUnknown *toICustomDestinationListItem(const QWinJumpListItem *item);
    static IShellLinkW *toIShellLink(const QWinJumpListItem *item);
    static IShellItem2 *toIShellItem(const QWinJumpListItem *item);
    static IShellLinkW *makeSeparatorShellItem();

    QWinJumpList *q_ptr;
    ICustomDestinationList *pDestList;
    QWinJumpListCategory *recent;
    QWinJumpListCategory *frequent;
    QWinJumpListCategory *tasks;
    QList<QWinJumpListCategory *> categories;
    QString identifier;
    bool dirty;
};

QT_END_NAMESPACE

#endif // QWINJUMPLIST_P_H
