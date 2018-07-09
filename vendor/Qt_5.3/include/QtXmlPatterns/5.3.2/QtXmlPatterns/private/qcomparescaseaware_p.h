/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtXmlPatterns module of the Qt Toolkit.
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

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef Patternist_ComparesCaseAware_H
#define Patternist_ComparesCaseAware_H

#include <private/qfunctioncall_p.h>

QT_BEGIN_NAMESPACE

namespace QPatternist
{
    /**
     * @short Base-class for functions that compares strings and provides
     * an opportunity to optimize compares intended to be case insensitive.
     *
     * @ingroup Patternist_functions
     * @author Frans Englich <frans.englich@nokia.com>
     */
    class ComparesCaseAware : public FunctionCall
    {
    public:
        /**
         * Performs initialization.
         */
        ComparesCaseAware();

        virtual Expression::Ptr compress(const StaticContext::Ptr &context);

        /**
         * Tells whether the return value of the two operands must be compared
         * case insensitively or not.
         */
        inline Qt::CaseSensitivity caseSensitivity() const
        {
            return m_caseSensitivity;
        }

    private:
        Qt::CaseSensitivity m_caseSensitivity;
    };
}

QT_END_NAMESPACE

#endif
