#ifndef STAGELOADER_H_INCLUDED
#define STAGELOADER_H_INCLUDED

#include <map>
#include <string>
#include <fstream>
#include "IncludeObjects.h"

/*! The StageLoader class parses stage files to create levels at runtime.
 */
class StageLoader {

    private:

        std::string fileName;   //!< Stage file path.
        int lineNo;             //!< Current line number.
        std::string curLine;    //!< Current line being parsed.
        std::string line;       //!< Current line being parsed, stripped of whitespace
        std::ifstream inFile;   //!< File stream of the input file
        std::map<std::string, std::string> stageInfo;   //!< Map that stores stage information

        //! Strips all whitespace from string.
        /*!
          \param str The string to be stripped.
          \return Whitespace stripped string.
        */
        std::string stripWhitespace(std::string str);

        //! Checks if stageInfo contains a key;  if not reports error.
        /*!
          \param field The field to be checked.
          \return The value paired with the key.
        */
        std::string checkField(std::string field);

        //! Reports error at current line
        void reportError();

        //! Retrieves next line
        void getNextLine();



    public:

        //! StageLoader constructor.
        /*!
          \param fileName The path to the stage file.
          \param physicsObjects Reference to vector to be filled with physics objects.
          \param kinematicObjects Reference to vector to be filled with kinematic objects.
          \param standardObjects Reference to vector to be filled with standard objects.
          \param skybox Reference to Skybox to be populated by skybox object.
          \param boundary Reference to Boundary to be populated by boundary object.
          \param userControlObject Reference to Hero to be populated with the hero object.
        */
        StageLoader(std::string fileName, std::vector<PhysicsObject*>& physicsObjects, std::vector<KinematicObject*>& kinematicObjects, std::vector<StandardObject*>& standardObjects, Skybox*& skybox, Boundary*& boundary, Hero*& userControlObject);

};

#endif // STAGELOADER_H_INCLUDED
