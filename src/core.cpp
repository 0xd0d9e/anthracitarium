//encoding utf-8
//author dodge
#include <QtCore>
#include <QtOpenGL>

#include "core.hpp"

namespace Anthracitarium
{

Core::Core()
    : cameraController(&camera),
    camera( Math::Vector3( 0, 0, -50 ), Math::Vector3( 0, 0, 0 ), Math::Vector3( 0, 0, 0 ) )
{
    srand( QDateTime::currentDateTime().toTime_t() );

//     Space::Terrain::test();
//     Space::BlockWalker::test();

    view.setScene(&scene);
    view.show();
    view.resize( 640, 480 );
    view.setUpdateInterval(1000/30.0);

    scene.objects.append( new Render::Axis );
    scene.objects.append(&terrainRender);
    scene.setCamera(&camera);

    cameraController.addTarget( view.viewport() );
    cameraController.addTarget(&view);
    cameraController.setEnabled(true);


    terrain.setChunkSize( Space::Size( 16, 16, 128 ) );
    terrain.setVisibleRect( QRect( -5, -5, 20, 20 ) );
    terrainRender.setTerrain(&terrain);

}

Core::~Core()
{
}

}//namespace Anthracitarium
