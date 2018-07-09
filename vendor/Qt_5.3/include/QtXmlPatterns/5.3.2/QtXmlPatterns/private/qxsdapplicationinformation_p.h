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

#ifndef Patternist_XsdApplicationInformation_H
#define Patternist_XsdApplicationInformation_H

#include <private/qanytype_p.h>
#include <private/qanyuri_p.h>
#include <private/qnamedschemacomponent_p.h>

QT_BEGIN_NAMESPACE

namespace QPatternist
{
    /**
     * @short Represents a XSD appinfo object.
     *
     * This class represents the <em>appinfo</em> component of an <em>annotation</em> object
     * of a XML schema as described <a href="http://www.w3.org/TR/xmlschema11-1/#cAnnotations">here</a>.
     *
     * @ingroup Patternist_schema
     * @author Tobias Koenig <tobias.koenig@nokia.com>
     */
    class XsdApplicationInformation : public NamedSchemaComponent
    {
        public:
            typedef QExplicitlySharedDataPointer<XsdApplicationInformation> Ptr;
            typedef QList<XsdApplicationInformation::Ptr> List;

            /**
             * Sets the @p source of the application information.
             *
             * The source points to an URL that contains more
             * information.
             */
            void setSource(const AnyURI::Ptr &source);

            /**
             * Returns the source of the application information.
             */
            AnyURI::Ptr source() const;

            /**
             * Sets the @p content of the application information.
             *
             * The content can be of abritrary type.
             */
            void setContent(const QString &content);

            /**
             * Returns the content of the application information.
             */
            QString content() const;

        private:
            AnyURI::Ptr  m_source;
            QString      m_content;
    };
}

QT_END_NAMESPACE

#endif
