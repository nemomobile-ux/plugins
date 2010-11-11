/* * This file is part of meego-keyboard *
 *
 * Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
 * All rights reserved.
 * Contact: Nokia Corporation (directui@nokia.com)
 *
 * If you have questions regarding the use of this file, please contact
 * Nokia at directui@nokia.com.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License version 2.1 as published by the Free Software Foundation
 * and appearing in the file LICENSE.LGPL included in the packaging
 * of this file.
 */

#include "minputmethodhoststub.h"

#include <mnamespace.h>
#include <QKeyEvent>

MInputMethodHostStub::MInputMethodHostStub()
{
    clear();
    predictionEnabled_ = true;
    correctionEnabled_ = true;
    autoCapitalizationEnabled_ = true;
    contentType_ = 0;
    inputmethodMode_ = M::InputMethodModeNormal;
    keyRedirectionEnabled = false;
    indicator = MInputMethod::NoIndicator;
}

MInputMethodHostStub::~MInputMethodHostStub()
{
    qDeleteAll(keyEvents);
    keyEvents.clear();
}

void MInputMethodHostStub::clear()
{
    preeditRectangleReturnValue = QRect();
    preedit.clear();
    commit.clear();
    qDeleteAll(keyEvents);
    keyEvents.clear();

    surroundingString.clear();
    cursorPos = 0;

    sendPreeditCalls = 0;
    sendCommitStringCalls = 0;
    sendKeyEventCalls = 0;
    notifyImInitiatedHidingCalls = 0;
    setGlobalCorrectionEnabledCalls = 0;
    predictionEnabledCalls = 0;
    correctionEnabledCalls = 0;
    contentTypeCalls = 0;
    copyCalls = 0;
    pasteCalls = 0;
    textSelected = false;
    keyRedirectionEnabled = false;
    indicator = MInputMethod::NoIndicator;
    setScreenRegionCalls = 0;
    screenRegions.clear();
    setInputMethodAreaCalls = 0;
    inputMethodAreas.clear();
}

void MInputMethodHostStub::sendPreeditString(const QString &string,
                                             MInputMethod::PreeditFace preeditFace)
{
    Q_UNUSED(preeditFace);

    preedit = string;
    ++sendPreeditCalls;
}

void MInputMethodHostStub::sendCommitString(const QString &string)
{
    commit += string;
    ++sendCommitStringCalls;
}


void MInputMethodHostStub::sendKeyEvent(const QKeyEvent &keyEvent_,
                                        MInputMethod::EventRequestType requestType)
{
    Q_UNUSED(requestType);
    keyEvents.append(new QKeyEvent(keyEvent_));
    ++sendKeyEventCalls;
}

void MInputMethodHostStub::notifyImInitiatedHiding()
{
    ++notifyImInitiatedHidingCalls;
}

int MInputMethodHostStub::contentType(bool &val)
{
    val = true;
    return contentType_;
}

bool MInputMethodHostStub::correctionEnabled(bool &val)
{
    val = true;
    return correctionEnabled_;
}

bool MInputMethodHostStub::predictionEnabled(bool &val)
{
    val = true;
    return predictionEnabled_;
}

bool MInputMethodHostStub::surroundingText(QString &text, int &cursorPosition)
{
    text = surroundingString;
    cursorPosition = cursorPos;
    return true;
}

int MInputMethodHostStub::inputMethodMode(bool &valid)
{
    valid = true;
    return inputmethodMode_;
}

bool MInputMethodHostStub::hasSelection(bool &valid)
{
    valid = true;
    return textSelected;
}

QRect MInputMethodHostStub::preeditRectangle(bool &valid)
{
    valid = true;
    return preeditRectangleReturnValue;
}

bool MInputMethodHostStub::autoCapitalizationEnabled(bool &val)
{
    val = true;
    return autoCapitalizationEnabled_;
}

void MInputMethodHostStub::copy()
{
    ++copyCalls;
}

void MInputMethodHostStub::paste()
{
    ++pasteCalls;
}

void MInputMethodHostStub::setGlobalCorrectionEnabled(bool enabled)
{
    globalCorrectionEnabled = enabled;
    ++setGlobalCorrectionEnabledCalls;
}

void MInputMethodHostStub::setRedirectKeys(bool enabled)
{
    keyRedirectionEnabled = enabled;
}

void MInputMethodHostStub::setDetectableAutoRepeat(bool /*enabled*/)
{
}

void MInputMethodHostStub::setInputModeIndicator(MInputMethod::InputModeIndicator newIndicator)
{
    indicator = newIndicator;
}

void MInputMethodHostStub::switchPlugin(MInputMethod::SwitchDirection direction)
{
    Q_UNUSED(direction);
}

void MInputMethodHostStub::switchPlugin(const QString &pluginName)
{
    Q_UNUSED(pluginName);
}

void MInputMethodHostStub::setScreenRegion(const QRegion &region)
{
    setScreenRegionCalls++;
    screenRegions << region;
}

void MInputMethodHostStub::setInputMethodArea(const QRegion &region)
{
    setInputMethodAreaCalls++;
    inputMethodAreas << region;
}

void MInputMethodHostStub::showSettings()
{
}
