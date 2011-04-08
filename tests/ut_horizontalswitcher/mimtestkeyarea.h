/*
 * This file is part of meego-keyboard 
 *
 * Copyright (C) 2010-2011 Nokia Corporation and/or its subsidiary(-ies). All rights reserved.
 *
 * Contact: Mohammad Anwari <Mohammad.Anwari@nokia.com>
 *
 * Redistribution and use in source and binary forms, with or without modification, 
 * are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this list 
 * of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright notice, this list 
 * of conditions and the following disclaimer in the documentation and/or other materials 
 * provided with the distribution.
 * Neither the name of Nokia Corporation nor the names of its contributors may be 
 * used to endorse or promote products derived from this software without specific 
 * prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY 
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL 
 * THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) 
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, 
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS 
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

 */



#ifndef MIMTESKEYAREA_H
#define MIMTESKEYAREA_H

#include "mimabstractkeyarea.h"

class MImAbstractKey;

//! \brief MImTestKeyArea provides minimal implementation of MImAbstractKeyArea for unit testing
class MImTestKeyArea
    : public MImAbstractKeyArea
{
    Q_OBJECT
    Q_DISABLE_COPY(MImTestKeyArea)

public:
    //! \brief Constructor
    //! \param section section that is shown by this key area
    //! \param usePopup whether popup should be used
    //! \param parent key area's parent
    explicit MImTestKeyArea(const LayoutData::SharedLayoutSection &section,
                                bool usePopup = false,
                                QGraphicsWidget *parent = 0);

    //! \brief Destructor
    virtual ~MImTestKeyArea();

    //! \reimp
    virtual QList<const MImAbstractKey *> keys() const;
    virtual MImAbstractKey * findKey(const QString &);
    virtual MImAbstractKey *keyAt(const QPoint &) const;
    virtual void updateKeyGeometries(int);
    virtual void setContentType(M::TextContentType);
    virtual void setToggleKeyState(bool on);
    virtual void setComposeKeyState(bool isComposing);
    virtual void resetActiveKeys();
    //! \reimp_end

    //! Return true if horizontal flick could be used.
    bool allowedHorizontalFlick() const;

public slots:
    //! \reimp
    virtual void setKeyOverrides(const QMap<QString, QSharedPointer<MKeyOverride> > &overrides);
    //! \reimp_end

public:
    int setKeyOverridesCalls; //!< Amount of calls to setKeyOverrides()
    QMap<QString, QSharedPointer<MKeyOverride> > setKeyOverridesParam; //!< Parameter used for last call to setKeyOverrides()
};

#endif

