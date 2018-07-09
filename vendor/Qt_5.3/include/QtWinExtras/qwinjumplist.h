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

#ifndef QWINJUMPLIST_H
#define QWINJUMPLIST_H

#include <QtCore/qobject.h>
#include <QtCore/qstringlist.h>
#include <QtCore/qscopedpointer.h>
#include <QtWinExtras/qwinextrasglobal.h>

QT_BEGIN_NAMESPACE

class QWinJumpListItem;
class QWinJumpListPrivate;
class QWinJumpListCategory;

class Q_WINEXTRAS_EXPORT QWinJumpList : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString identifier READ identifier WRITE setIdentifier)

public:
    explicit QWinJumpList(QObject *parent = 0);
    ~QWinJumpList();

    QString identifier() const;
    void setIdentifier(const QString &identifier);

    QWinJumpListCategory *recent() const;
    QWinJumpListCategory *frequent() const;
    QWinJumpListCategory *tasks() const;

    QList<QWinJumpListCategory *> categories() const;
    void addCategory(QWinJumpListCategory *category);
    QWinJumpListCategory *addCategory(const QString &title, const QList<QWinJumpListItem *> items = QList<QWinJumpListItem *>());

public Q_SLOTS:
    void clear();

private:
    Q_DISABLE_COPY(QWinJumpList)
    Q_DECLARE_PRIVATE(QWinJumpList)
    QScopedPointer<QWinJumpListPrivate> d_ptr;

    Q_PRIVATE_SLOT(d_func(), void _q_rebuild())
};

QT_END_NAMESPACE

#endif // QWINJUMPLIST_H
