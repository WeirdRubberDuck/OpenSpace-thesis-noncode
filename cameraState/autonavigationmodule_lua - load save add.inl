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
#include <iomanip>

namespace openspace::autonavigation::luascriptfunctions {

   

    struct CameraKeyframe {

        CameraKeyframe() {}
        CameraKeyframe(glm::dvec3 pos, glm::dquat rot) : _position(pos),_rotation(rot) {}

        glm::dvec3 _position;
        glm::dquat _rotation;

        void write(std::ostream &os)
        {
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
               << _rotation.w << ' ';

            os << std::endl;
        }

        void read(std::istream &is)
        {
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
      
    };
    
    // TODO: Change to private member that knows what it contains
    std::vector<CameraKeyframe> kframes;


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

    // ToDO add function for moving camera to next keyframe
       // camera->setPositionVec3(kf._position);
      //  camera->setRotation(kf._rotation);

    int addCameraKeyframe(lua_State* L) {
        ghoul::lua::checkArgumentsAndThrow(L, 0, "lua::retargetAim");

        Camera* c;
        if (!c) return -1;

        CameraKeyframe newkf(c->positionVec3(), c->rotationQuaternion());
        kframes.push_back(newkf);

        ghoul_assert(lua_gettop(L) == 0, "Incorrect number of items left on stack");
        return 0;
    }
    
    // Save all keyframes to file (overwrite)
    int saveCameraKeyframes(lua_State* L) {

        ghoul::lua::checkArgumentsAndThrow(L, 1, "lua::saveCameraKeyframes");
        const std::string filename = ghoul::lua::value<std::string>(L, 1); 

        std::ofstream recordFile;
        recordFile.open(filename);
        if (!recordFile.is_open() || !recordFile.good()) {
          /*  LERROR(fmt::format(
                "Unable to open file {} for keyframe recording", absFilename.c_str()
            ));*/
            return -1;
        }

        for (auto kf : kframes)
        {  
            kf.write(recordFile);
        }

        recordFile.close();
        lua_settop(L, 0);
        ghoul_assert(lua_gettop(L) == 0, "Incorrect number of items left on stack");
        return 0;
    }

    int loadCameraKeyframes(lua_State* L) {

        ghoul::lua::checkArgumentsAndThrow(L, 1, "lua::loadCameraKeyframes");
        const std::string filename = ghoul::lua::value<std::string>(L, 1);

        std::ifstream recordFile;
        recordFile.open(filename);
        if (!recordFile.is_open() || !recordFile.good()) {
            /*  LERROR(fmt::format(
                  "Unable to open file {} for keyframe recording", absFilename.c_str()
              ));*/
            return -1;
        }
        
        // Add each camera key frame stored as a line in file    
        std::string lineParsing;
        while (std::getline(recordFile, lineParsing)) {

            std::istringstream iss(lineParsing);
            CameraKeyframe kf;
            kf.read(iss);
            kframes.push_back(kf);
        }

        recordFile.close();

        lua_settop(L, 0);
        ghoul_assert(lua_gettop(L) == 0, "Incorrect number of items left on stack");

        return 0;
    }

   
} // namespace openspace::autonavigation::luascriptfunctions
