/*****************************************************************************************
 *                                                                                       *
 * OpenSpace                                                                             *
 *                                                                                       *
 * Copyright (c) 2014-2019                                                               *
 *                                                                                       *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this  *
 * software and associated documentation files (the "Software"), to deal in the Software *
 * without restriction, including without limitation the rights to use, copy, modify,    *
 * merge, publish, distribute, sublicense, and/or sell copies of the Software, and to    *
 * permit persons to whom the Software is furnished to do so, subject to the following   *
 * conditions:                                                                           *
 *                                                                                       *
 * The above copyright notice and this permission notice shall be included in all copies *
 * or substantial portions of the Software.                                              *
 *                                                                                       *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,   *
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A         *
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT    *
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF  *
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE  *
 * OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                                         *
 ****************************************************************************************/

#include <modules/autonavigation/autonavigationhandler.h>

#include <openspace/engine/globals.h>
#include <openspace/interaction/navigationhandler.h>
#include <openspace/util/camera.h>
#include <ghoul/logging/logmanager.h>
#include <iomanip>


namespace {
    constexpr const char* _loggerCat = "AutoNavigationHandler";

} // namespace

namespace openspace::autonavigation {

AutoNavigationHandler::CameraState::CameraState(glm::dvec3 pos, glm::dquat rot) 
    : _position(pos), _rotation(rot) {}

void AutoNavigationHandler::CameraState::write(std::ostream &os) {
    os << std::fixed << std::setprecision(7) 
        // entryType
        << "camera "
        // camera position
        << _position.x << ' '
        << _position.y << ' '
        << _position.z << ' '
        // camera rotation
        << _rotation.x << ' '
        << _rotation.y << ' '
        << _rotation.z << ' '
        << _rotation.w << ' '
        << std::endl;
}

void AutoNavigationHandler::CameraState::read(std::istream &is) {
    // TODO: read multiple CameraKeyframes
    // TODO: add errors

    std::string entryType;

    if (is >> entryType && entryType != "camera")
        return;

    is >> _position.x
        >> _position.y
        >> _position.z
        >> _rotation.x
        >> _rotation.y
        >> _rotation.z
        >> _rotation.w;
}

AutoNavigationHandler::AutoNavigationHandler()
    : properties::PropertyOwner({ "AutoNavigationHandler" })
{
    // Add the properties
    // TODO
}

AutoNavigationHandler::~AutoNavigationHandler() {} // NOLINT

void AutoNavigationHandler::updateCamera() {
    ghoul_assert(_camera != nullptr, "Camera must not be nullptr");

    // TODO: update the camera
}

Camera* AutoNavigationHandler::camera() const {
    return global::navigationHandler.camera();
}

} // namespace openspace::autonavigation
