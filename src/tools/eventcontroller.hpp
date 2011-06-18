//author 0xd0d9e
//encoding utf-8
#ifndef __Tools_EventController__
#define __Tools_EventController__

#include <QPoint>
#include <QtCore/QObject>
#include <QtCore/QMap>

class QEvent;
class QMouseEvent;
class QKeyEvent;

namespace Tools
{

class AbstractEventProcessor
{
public:
    virtual void prepare( QEvent * event ) = 0;

};

template < class ProcessorType, class EventType >
class EventProcessor : public AbstractEventProcessor
{
public:
    typedef void (ProcessorType::*PrepareMethod)( EventType * event );

    EventProcessor( ProcessorType * processor, PrepareMethod method )
        : processor_(processor), method_(method) {}

    void prepare( QEvent * event )
    {
        if ( processor_ && method_ && event )
            (processor_->*method_)( dynamic_cast<EventType*>(event) );
    }

private:
    ProcessorType * processor_;
    PrepareMethod method_;

};

class EventController : public QObject
{
public:
    explicit EventController( QObject * target = 0, QObject * parent = 0 );

    QList<QObject*> targets() const;
    bool isEnabled() const;

    void addTarget( QObject * target );
    void removeTarget( QObject * target );
    void setEnabled( const bool enabled );
    void addProcessor( int eventType, AbstractEventProcessor * processor );
    void removeProcessor( int eventType );

private:
    bool eventFilter( QObject * object, QEvent * event );

    QMap<int,AbstractEventProcessor*> processors;
    QList<QObject*> targets_;
    bool enabled_;

};

class KeyProcessor
{
public:
    typedef EventProcessor<KeyProcessor,QKeyEvent> KeyEventProcessor;
    KeyProcessor();
    virtual ~KeyProcessor();

    void install( EventController * controller );
    void uninstall( EventController * controller );
    virtual void keyPressEvent( QKeyEvent * event );
    virtual void keyReleaseEvent( QKeyEvent * event );
    bool isPressed( int key ) const;

private:
    QList<int> keys_;
    KeyEventProcessor * pressKeyEventProcessor,
                      * releaseKeyEventProcessor;

};

class MouseProcessor
{
public:
    typedef EventProcessor<MouseProcessor,QMouseEvent> MouseEventProcessor;
    MouseProcessor();
    virtual ~MouseProcessor();

    void install( EventController * controller );
    void uninstall( EventController * controller );
    virtual void mousePressEvent( QMouseEvent * event );
    virtual void mouseMoveEvent( QMouseEvent * event );
    virtual void mouseReleaseEvent( QMouseEvent * event );

    int pressedButtons() const { return pressedButtons_; }
    QPoint pressPos() const { return pressPos_; }
    QPoint moveOffset() const { return moveOffset_; }
    QPoint lastMovePos() const { return lastMovePos_; }

private:
    int pressedButtons_;
    QPoint pressPos_,
           moveOffset_,
           lastMovePos_;
    MouseEventProcessor * pressMouseEventProcessor,
                        * moveMouseEventProcessor,
                        * releaseMouseEventProcessor;

};

}//namespace Tools

#endif//__Tools_EventController__
