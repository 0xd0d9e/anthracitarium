//author 0xd0d9e
//encoding utf-8
#include <QtCore/QEvent>
#include <QtGui/QKeyEvent>

#include "dbg/dbg.hpp"
#include "eventcontroller.hpp"

namespace Tools
{

EventController::EventController( QObject * target, QObject * parent )
    : QObject( parent ? parent : target ),
    enabled_(false)
{
    if (target)
        addTarget(target);
}

QList<QObject*> EventController::targets() const
{
    return targets_;
}

bool EventController::isEnabled() const
{
    return enabled_;
}

void EventController::addTarget( QObject * target )
{
    target->installEventFilter(this);
    targets_.append(target);
}

void EventController::removeTarget( QObject * target )
{
    target->removeEventFilter(this);
    targets_.removeOne(target);
}

void EventController::setEnabled( const bool enabled )
{
    if ( enabled_ != enabled )
    {
        enabled_ = enabled;
    }
}

void EventController::addProcessor( int eventType, AbstractEventProcessor * processor )
{
    processors[eventType] = processor;
}

void EventController::removeProcessor( int eventType )
{
    processors.remove(eventType);
}

bool EventController::eventFilter( QObject * object, QEvent * event )
{
    if (enabled_)
    {
        const int type = event->type();
        if ( processors.contains(type) )
        {
            processors[type]->prepare(event);
        }
    }
    return QObject::eventFilter( object, event );
}

//--------------------------------------------------------------------------------------------------

KeyProcessor::KeyProcessor()
{
    pressKeyEventProcessor = new KeyEventProcessor( this, &KeyProcessor::keyPressEvent );
    releaseKeyEventProcessor = new KeyEventProcessor( this, &KeyProcessor::keyReleaseEvent );
}

KeyProcessor::~KeyProcessor()
{
    delete pressKeyEventProcessor;
    delete releaseKeyEventProcessor;
}

void KeyProcessor::install( EventController * controller )
{
    if (!controller)
        return;
    controller->addProcessor( QEvent::KeyPress, pressKeyEventProcessor );
    controller->addProcessor( QEvent::KeyRelease, releaseKeyEventProcessor );
}

void KeyProcessor::uninstall( EventController * controller )
{
    if (!controller)
        return;
    controller->removeProcessor(QEvent::KeyPress);
    controller->removeProcessor(QEvent::KeyRelease);
}

void KeyProcessor::keyPressEvent( QKeyEvent * event )
{
    keys_.append( event->key() );
}

void KeyProcessor::keyReleaseEvent( QKeyEvent * event )
{
    keys_.removeAll( event->key() );
}

bool KeyProcessor::isPressed( int key ) const
{
    return keys_.contains(key);
}

//--------------------------------------------------------------------------------------------------

MouseProcessor::MouseProcessor()
    : pressedButtons_(Qt::NoButton)
{
    pressMouseEventProcessor = new MouseEventProcessor( this, &MouseProcessor::mousePressEvent );
    moveMouseEventProcessor = new MouseEventProcessor( this, &MouseProcessor::mouseMoveEvent );
    releaseMouseEventProcessor = new MouseEventProcessor( this, &MouseProcessor::mouseReleaseEvent );
}

MouseProcessor::~MouseProcessor()
{
    delete pressMouseEventProcessor;
    delete moveMouseEventProcessor;
    delete releaseMouseEventProcessor;
}

void MouseProcessor::install( EventController * controller )
{
    if (!controller)
        return;
    controller->addProcessor( QEvent::MouseButtonPress, pressMouseEventProcessor );
    controller->addProcessor( QEvent::MouseMove, moveMouseEventProcessor );
    controller->addProcessor( QEvent::MouseButtonRelease, releaseMouseEventProcessor );
}

void MouseProcessor::uninstall( EventController * controller )
{
    if (!controller)
        return;
    controller->removeProcessor(QEvent::MouseButtonPress);
    controller->removeProcessor(QEvent::MouseMove);
    controller->removeProcessor(QEvent::MouseButtonRelease);
}

void MouseProcessor::mousePressEvent( QMouseEvent * event )
{
    pressedButtons_ = event->buttons();
    pressPos_ = event->pos();
    lastMovePos_ = pressPos_;
}

void MouseProcessor::mouseMoveEvent( QMouseEvent * event )
{
    moveOffset_ = lastMovePos_ - event->pos();
    lastMovePos_ = event->pos();
}

void MouseProcessor::mouseReleaseEvent( QMouseEvent * event )
{
    pressedButtons_ = Qt::NoButton;
}

}//namespace Tools
//--------------------------------------------------------------------------------------------------
