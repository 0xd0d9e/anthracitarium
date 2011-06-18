//encoding utf-8
//author dodge
#ifndef __Core__
#define __Core__

#include "render/camera.hpp"
#include "render/cameracontroller.hpp"
#include "render/scene.hpp"
#include "render/view.hpp"
#include "space/terrain.hpp"
#include "render/terrainrender.hpp"

namespace Anthracitarium
{

class Core
{
public:
    Core();
    ~Core();

private:
    Render::CameraController cameraController;
    Render::Scene scene;
    Render::View view;
    Render::Camera camera;
    Render::TerrainRender terrainRender;
    Space::Terrain terrain;

};

}//namespace Anthracitarium

#endif//__Core__
