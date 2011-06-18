//encoding utf-8
#ifndef __View__
#define __View__

#include <QtGui/QGraphicsView>

class QGLWidget;

namespace Render
{

class View : public QGraphicsView
{
    Q_OBJECT
public:
    explicit View( QWidget * parent = 0);

    inline int updateInterval() const;
    inline QGLWidget * viewport() const;
    inline bool isOpenGL() const;

    inline void setUpdateInterval( int interval );

public slots:
    void setOpenGL( const bool enabled );

private:
    void resizeEvent( QResizeEvent * resizeEvent );
    void timerEvent( QTimerEvent * timerEvent );
    void mouseMoveEvent( QMouseEvent * timerEvent );

    int interval_;
    int timerId_;
    QGLWidget * viewport_;
    QWidget * defaultVP_;
    bool hasOpenGL_;

};

inline int View::updateInterval() const
{
    return interval_;
}

inline QGLWidget * View::viewport() const
{
    return viewport_;
}

inline void View::setUpdateInterval( int interval )
{
    interval_ = interval;
    if (timerId_) {
        killTimer(timerId_);
        timerId_ = 0;
    }
    if ( interval_ > 0 )
        timerId_ = startTimer(interval_ );
}

inline bool View::isOpenGL() const
{
    return hasOpenGL_;
}

};

#endif//__View__
