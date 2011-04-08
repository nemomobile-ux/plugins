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

#ifndef MIMABSTRACTKEYAREA_H
#define MIMABSTRACTKEYAREA_H

#include "mkeyboardcommon.h"
#include "mimabstractkey.h"
#include "mimabstractkeyareastyle.h"
#include "layoutdata.h"

#include <MStylableWidget>
#include <MFeedback>
#include <QList>
#include <QStringList>
#include <QTouchEvent>
#include <QTimer>
#include <QTime>

class FlickGesture;
class MReactionMap;
class PopupBase;
class MKeyOverride;
class MImAbstractKeyAreaPrivate;

//! \brief MImAbstractKeyArea is a view for virtual keyboard layout represented by LayoutModel
class MImAbstractKeyArea
    : public MStylableWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(MImAbstractKeyArea)

public:
    //! \brief Constructor
    //! \brief privateData Pointer to private class.
    //! MImAbstractKeyArea takes ownership on private data class, so derived classes
    //! should NOT delete private objects.
    //! \param usePopup Whether popup should be used
    //! \param parent Key area's parent.
    explicit MImAbstractKeyArea(MImAbstractKeyAreaPrivate *privateData,
                                bool usePopup = true,
                                QGraphicsWidget *parent = 0);

    //! \brief Destructor
    virtual ~MImAbstractKeyArea();

    //! \brief Returns section shown by this key area.
    const LayoutData::SharedLayoutSection &sectionModel() const;

    //! \brief Returns current level of this layout.
    int level() const;

    //! \brief Exposes style used by this key area.
    const MImAbstractKeyAreaStyleContainer &baseStyle() const;

    //! \brief Sets input method mode for all MImAbstractKeyArea instances.
    //! \param inputMethodMode the new input method mode
    static void setInputMethodMode(M::InputMethodMode inputMethodMode);

    //! \brief Returns relative button base width
    qreal relativeKeyBaseWidth() const;

    //! \brief Returns all keys from this key area.
    virtual QList<const MImAbstractKey *> keys() const = 0;

    //! \brief Returns key with given \a id
    virtual MImAbstractKey * findKey(const QString &id) = 0;

    //! \brief Notification for derived classes about button modifier change.
    //!
    //! Derived classes should not change the level of selected dead keys. This is to
    //! ensure all dead keys can be used with all characters in every level.
    //! \param shift whether shift modifier is enabled
    //! \param accent which accented version should be used, for a key
    virtual void modifiersChanged(bool shift,
                                  const QChar &accent = QChar());

    //! \brief Resets active keys belongs to this key area to normal state.
    virtual void resetActiveKeys() = 0;

    //! \brief Enable or disable horizontal gesture recognition.
    virtual void enableHorizontalFlick(bool enable);

public slots:
    //! \brief Tell key area to switch levels for all keys.
    //! \param level the new level
    void switchLevel(int level);

    //! \brief Set shift state.
    //! \param shiftState the new shift state
    virtual void setShiftState(ModifierState shiftState);

    //! \brief Draw reactive areas for all keys.
    //! \param reactionMap the reaction map to draw onto
    //! \param view the view to be used
    virtual void drawReactiveAreas(MReactionMap *reactionMap,
                                   QGraphicsView *view);

    //! \brief Unlock all locked dead keys.
    //! \param deadKey the corresponding dead key
    void unlockDeadKeys(MImAbstractKey *deadKey);

    //! \brief Hide popup
    void hidePopup();

    /*!
     * \brief Resets keyboard and release active keys.
     * \param resetCapsLock whether to reset shift key when in caps-lock mode.
     *        By default, always resets shift key.
     */
    void reset(bool resetCapsLock = false);

    /*!
     * \brief Uses custom key overrides which is defined by \a overrides.
     */
    virtual void setKeyOverrides(const QMap<QString, QSharedPointer<MKeyOverride> > &overrides) = 0;

    /*!
     * \brief Sets the current content type (handles email/url overrides).
     */
    virtual void setContentType(M::TextContentType type) = 0;

    /*!
     * \brief Sets the state of on off toggle key.
     */
    virtual void setToggleKeyState(bool on) = 0;

    /*!
     * \brief Sets the state of compose key.
     */
    virtual void setComposeKeyState(bool isComposing) = 0;

signals:
    //! \brief Emitted when key is pressed
    //!
    //! Note that this happens also when user keeps finger down/mouse
    //! button pressed and moves over another key (event is about the new key)
    //! \param key describes pressed button
    //! \param accent label of pressed dead key if any
    //! \param upperCase contains true if key is in uppercase state
    void keyPressed(const MImAbstractKey *key,
                    const QString &accent,
                    bool upperCase);

    //! \brief Emitted when key is released.
    //!
    //! Note that this happens also when user keeps finger down/mouse
    //! button pressed and moves over another key (event is about the old key)
    //! \param key describes released button
    //! \param accent label of pressed dead key if any
    //! \param upperCase contains true if key is in uppercase state
    void keyReleased(const MImAbstractKey *key,
                     const QString &accent,
                     bool upperCase);

    //! \brief Emitted when user releases mouse button/lifts finger.
    //!
    //! Except when done on a dead key
    //! \param key describes clicked button
    //! \param accent label of pressed dead key if any
    //! \param upperCase contains true if key is in uppercase state
    //! \param touchPoint the touch point for the key
    void keyClicked(const MImAbstractKey *key,
                    const QString &accent, bool upperCase,
                    const QPoint &touchPoint);

    //! \brief Emitted when long press is detected.
    //!
    //! Long press detection is:
    //! - cancelled when latest pressed key is released;
    //! - restarted when finger is moved to other key;
    //! - restarted when new touch point is recognized by MImAbstractKeyArea.
    //! \param key describes pressed button
    //! \param accent active accent in MImAbstractKeyArea at the time of long press occured
    //! \param upperCase upper case state in MImAbstractKeyArea at the time of long press occured
    void longKeyPressed(const MImAbstractKey *key,
                        const QString &accent,
                        bool upperCase);

    //! \brief Emitted when key area is flicked right.
    void flickRight();

    //! \brief Emitted when key area is flicked left.
    void flickLeft();

    //! \brief Emitted when key area is flicked down.
    void flickDown();

    //! \brief Emitted when key area is flicked up.
    //! \param binding Information about the key where mouse button was pressed
    void flickUp(const MImKeyBinding &binding);

    //! \brief Emitted if button width has changed
    //! \param baseWidth base width used for relative button widths
    void relativeKeyBaseWidthChanged(qreal baseWidth);

protected:
    //! \reimp
    virtual void resizeEvent(QGraphicsSceneResizeEvent *event);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    virtual QVariant itemChange(GraphicsItemChange change,
                                const QVariant &value);

    virtual void grabMouseEvent(QEvent *event);
    virtual void ungrabMouseEvent(QEvent *event);
    virtual bool event(QEvent *event);
    //! \reimp_end

    //! \brief Called when key area's visibility changed.
    //! \param visible the new visbility status
    virtual void handleVisibilityChanged(bool visible);

    //! Shows popup and updates its content and position.
    //! \param key current key
    void updatePopup(MImAbstractKey *key = 0);

    //! \brief Get maximum number of columns in this key area.
    int maxColumns() const;

    //! \brief Get number of rows in this key area.
    int rowCount() const;

    //! \brief Updates button labels and/or icons according to current level
    //!        and deadkey.
    //! \param accent the accent version of a dead key.
    void updateKeyModifiers(const QChar &accent = QChar());

    //! \brief Returns key at given \a pos.
    //!
    //! Accepts positions outside widget geometry because
    //! of reactive margins.
    //! \param pos the position (in key area space) to look up key
    virtual MImAbstractKey *keyAt(const QPoint &pos) const = 0;

    //! \brief Updates key (and row) geometry based on given \a availableWidth.
    //! \param availableWidth with of the key area
    virtual void updateKeyGeometries(int availableWidth) = 0;

    //! \brief Returns popup
    const PopupBase &popup() const;

    //! \brief Log touch point information to
    //!        $HOME/.meego-im/vkb-touchpoints.log, for debugging purposes.
    //! \param tp the touch point
    //! \param key key underneath touch point
    //! \param lastKey last key that was associated to the touch point
    void logTouchPoint(const QTouchEvent::TouchPoint &tp,
                       const MImAbstractKey *key,
                       const MImAbstractKey *lastKey = 0) const;

    qreal mRelativeKeyBaseWidth; //!< Relative key base width in currently active layout
    bool debugTouchPoints; //!< Whether touch point debugging is enabled

    //! Correct the vertical offset of a touchpoint
    //! \param scenePos Input position in scene coordinates.
    //! \returns the corrected position in item coordinates.
    QPoint correctedTouchPoint(const QPointF &scenePos) const;

    //! Correct the reaction rects for the vertical offset of a touchpoint
    //! \param originalRect Original rectangle in item coordinates.
    //! \returns the corrected rectangle in item coordinates.
    QRectF correctedReactionRect(const QRectF &originalRect) const;

protected slots:
    //! Update background images, text layouts, etc. when the theme changed.
    virtual void onThemeChangeCompleted();

    //! Handle long press on the key
    virtual void handleLongKeyPressed();

    //! Handle idle VKB
    virtual void handleIdleVkb();

protected:
    Q_DECLARE_PRIVATE(MImAbstractKeyArea);
    MImAbstractKeyAreaPrivate * const d_ptr;

private:
    M_STYLABLE_WIDGET(MImAbstractKeyAreaStyle)

#ifdef UNIT_TEST
    friend class MReactionMapTester;
    friend class Ut_MImAbstractKeyArea;
    friend class Ut_SymbolView;
    friend class Ut_MVirtualKeyboard;
    friend class Bm_MImAbstractKeyArea; //benchmarks
    friend class Bm_Painting;
#endif
};

#endif
