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


#ifndef KEYEVENTHANDLER_H
#define KEYEVENTHANDLER_H

#include <QObject>
#include <QKeyEvent>
#include <QPoint>

class KeyButtonArea;
class KeyEvent;
class IKeyButton;
class QString;

/*!
 * \class KeyEventHandler
 * \brief Logic class to convert signals generated by buttons from
 * raw information into KeyEvent. Also filters clicks from shift button.
 */
class KeyEventHandler : public QObject
{
    Q_OBJECT

public:
    //! Constructs new instance of KeyEventHandler with given \a parent
    explicit KeyEventHandler(QObject *parent = 0);

    //! Connects this object to signals from given \a source
    void addEventSource(KeyButtonArea *eventSource);

signals:
    /*!
     * \brief Emitted when key is pressed
     *
     * Note that this happens also when user keeps finger down/mouse
     * button pressed and moves over another key (event is about the new key)
     * \param event key event
     */
    void keyPressed(const KeyEvent &event);

    /*!
     * \brief Emitted when key is released
     *
     * Note that this happens also when user keeps finger down/mouse
     * button pressed and moves over another key (event is about the old key)
     * \param event key event
     */
    void keyReleased(const KeyEvent &event);

    /*!
     * \brief Emitted when user releases mouse button/lifts finger
     *
     * Except when done on a dead key
     * \param event key event
     */
    void keyClicked(const KeyEvent &event);

    /*!
     * \brief Emitted when shift key is pressed or released
     * \param state Contains true is key is pressed
     */
    void shiftPressed(bool state);

private slots:
    /*!
     * \brief Generates KeyEvent for given \a key and emits keyPressed
     */
    void handleKeyPress(const IKeyButton *key, const QString &accent, bool upperCase);

    /*!
     * \brief Generates KeyEvent for given \a key and emits keyReleased
     */
    void handleKeyRelease(const IKeyButton *key, const QString &accent, bool upperCase);

    /*!
     * \brief Generates KeyEvent for given \a key and emits keyClicked
     */
    void handleKeyClick(const IKeyButton *key, const QString &accent, bool upperCase, const QPoint &touchPoint);

private:
    //! Turn key button into a KeyEvent, considering current accent and modifier state
    KeyEvent keyToKeyEvent(const IKeyButton &key, QKeyEvent::Type eventType,
                           const QString &accent, bool upperCase, const QPoint &touchPoint = QPoint()) const;

private:
    //! Keeps track of shift up/down status.
    bool shiftHeldDown;

    //! When this is set true the next shift click is ignored.
    bool ignoreShiftClick;

#ifdef UNIT_TEST
    friend class Ut_KeyEventHandler;
#endif
};

#endif

