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

#ifndef Patternist_NamedSchemaComponent_H
#define Patternist_NamedSchemaComponent_H

#include <private/qnamepool_p.h>
#include <private/qschemacomponent_p.h>
#include <QXmlName>

QT_BEGIN_NAMESPACE

namespace QPatternist
{
    /**
     * @short Base class for all named components that can appear in a W3C XML Schema.
     *
     * @ingroup Patternist_types
     * @author Tobias Koenig <tobias.koenig@nokia.com>
     */
    class NamedSchemaComponent : public SchemaComponent
    {
        public:
            typedef QExplicitlySharedDataPointer<NamedSchemaComponent> Ptr;

            /**
             * Describes the blocking constraints that are given by the 'block' attributes.
             */
            enum BlockingConstraint
            {
                RestrictionConstraint = 1,
                ExtensionConstraint = 2,
                SubstitutionConstraint = 4
            };
            Q_DECLARE_FLAGS(BlockingConstraints, BlockingConstraint)

            /**
             * Creates a new named schema component.
             */
            NamedSchemaComponent();

            /**
             * Destroys the named schema component.
             */
            virtual ~NamedSchemaComponent();

            /**
             * Sets the @p name of the schema component.
             */
            void setName(const QXmlName &name);

            /**
             * Returns the name of the schema component.
             *
             * @param namePool The name pool the name belongs to.
             */
            virtual QXmlName name(const NamePool::Ptr &namePool) const;

            /**
             * Returns the display name of the schema component.
             *
             * @param namePool The name pool the name belongs to.
             */
            virtual QString displayName(const NamePool::Ptr &namePool) const;

        private:
            QXmlName m_name;
    };

    Q_DECLARE_OPERATORS_FOR_FLAGS(NamedSchemaComponent::BlockingConstraints)
}

QT_END_NAMESPACE

#endif
