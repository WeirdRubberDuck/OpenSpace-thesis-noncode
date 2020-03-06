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

#include <openspace/scripting/lualibrary.h>

#include <openspace/util/camera.h>
#include <openspace/engine/globals.h>
#include <openspace/interaction/navigationhandler.h>
#include <ghoul/glm.h>

#include <ghoul/filesystem/file.h>
#include <ghoul/filesystem/filesystem.h>
#include <ghoul/logging/logmanager.h>
#include <ghoul/misc/dictionaryluaformatter.h>

namespace openspace::autonavigation::luascriptfunctions {

    int testMove(lua_State* L) {
        ghoul::lua::checkArgumentsAndThrow(L, 3, "lua::testMove");

        const double v1 = ghoul::lua::value<double>(L, 1);
        const double v2 = ghoul::lua::value<double>(L, 2);
        const double v3 = ghoul::lua::value<double>(L, 3);
        glm::dvec3 diffVec{ v1, v2, v3 };

        Camera* camera = global::navigationHandler.camera();
        if (!camera) return -1;

        camera->setPositionVec3(camera->positionVec3() + diffVec);

        lua_settop(L, 0);
        ghoul_assert(lua_gettop(L) == 0, "Incorrect number of items left on stack");
        return 0;
    }

    int testInterpolation(lua_State* L) {
        ghoul::lua::checkArgumentsAndThrow(L, 3, "lua::testInterpolation");

        const double v1 = ghoul::lua::value<double>(L, 1);
        const double v2 = ghoul::lua::value<double>(L, 2);
        const double v3 = ghoul::lua::value<double>(L, 3);
        glm::dvec3 diffVec{ v1, v2, v3 };

        Camera* camera = global::navigationHandler.camera();
        if (!camera) return -1;

        // TODO: start an interpolation from the startPos along the vector
        //glm::dvec3 newPos = glm::slerp(
        //    localCameraRotation,
        //    targetRotation,
        //    glm::min(t * _retargetAnchorInterpolator.deltaTimeScaled(), 1.0));

        //camera->setPositionVec3(camera->positionVec3() + diffVec);

        lua_settop(L, 0);
        ghoul_assert(lua_gettop(L) == 0, "Incorrect number of items left on stack");
        return 0;
    }

    int testSaveCamera(lua_State* L) {
        ghoul::lua::checkArgumentsAndThrow(L, 1, "lua::testSaveCamera");

        Camera* camera = global::navigationHandler.camera();
        if (!camera) {
            return ghoul::lua::luaError(L, "camera must be set");
        }

        // Save the current camera position to a file
        const std::string& filepath = ghoul::lua::value<std::string>(L, 1);
        if (filepath.empty()) {
            return ghoul::lua::luaError(L, "filepath string is empty");
        }

        std::string absolutePath = absPath(filepath);
        //LINFO(fmt::format("Saving camera position: {}", absolutePath));

        ghoul::Dictionary cameraDict;
        cameraDict.setValue("Position", camera->positionVec3());
        cameraDict.setValue("Rotation", camera->rotationQuaternion());

        ghoul::DictionaryLuaFormatter formatter;

        std::ofstream ofs(absolutePath.c_str());
        ofs << "return " << formatter.format(cameraDict);
        ofs.close();

        lua_settop(L, 0);
        ghoul_assert(lua_gettop(L) == 0, "Incorrect number of items left on stack");
        return 0;
    }

    int testLoadCamera(lua_State* L) {
        ghoul::lua::checkArgumentsAndThrow(L, 1, "lua::testLoadCamera");

        Camera* camera = global::navigationHandler.camera();
        if (!camera) {
            return ghoul::lua::luaError(L, "camera must be set");
        }

        // Save the current camera position to a file
        const std::string& filepath = ghoul::lua::value<std::string>(L, 1);
        if (filepath.empty()) {
            return ghoul::lua::luaError(L, "filepath string is empty");
        }

        std::string absolutePath = absPath(filepath);

        if (!FileSys.fileExists(absolutePath)) {
            throw ghoul::FileNotFoundError(absolutePath, "CameraState");
        }

        ghoul::Dictionary cameraDict;
        ghoul::lua::loadDictionaryFromFile(absolutePath, cameraDict);
        // TODO: test if we managed to read something

        glm::dvec3 newPos = cameraDict.value<glm::dvec3>("Position");
        glm::dvec3 newRot = cameraDict.value<glm::dvec3>("Rotation");

        camera->setPositionVec3(newPos);
        camera->setRotation(newRot);

        lua_settop(L, 0);
        ghoul_assert(lua_gettop(L) == 0, "Incorrect number of items left on stack");
        return 0;
    }

} // namespace openspace::autonavigation::luascriptfunctions
