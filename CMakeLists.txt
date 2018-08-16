# Trial with Qt

cmake_minimum_required(VERSION 3.0.2)

set (PROJECT_NAME Corion)
project (${PROJECT_NAME})

# for C++ 11
set (CMAKE_CXX_STANDARD 11)
# build type
set (CMAKE_BUILD_TYPE Release)

add_definitions(-DCORION)

# Widgets finds its own dependencies (QtGui and QtCore).
find_package(Qt5Widgets REQUIRED)

INCLUDE_DIRECTORIES(/usr/local/include /usr/local/include/pocketsphinx /usr/local/include/sphinxbase)
INCLUDE_DIRECTORIES(/usr/local/include/opencv)
include(/home/bob/dlib-19.4/dlib/cmake)

LINK_DIRECTORIES(/usr/local/lib)

set ( SPEECH_LIBRARIES
    -lpocketsphinx 
    -lsphinxbase 
    -lsphinxad 
    -lpulse 
    -lpulse-simple 
)

set (OPENCV_LIBRARIES
-lopencv_calib3d 
-lopencv_contrib 
-lopencv_core 
-lopencv_features2d 
-lopencv_flann 
-lopencv_gpu 
-lopencv_highgui 
-lopencv_imgproc 
-lopencv_legacy 
-lopencv_ml 
-lopencv_nonfree 
-lopencv_objdetect 
-lopencv_ocl 
-lopencv_photo 
-lopencv_stitching 
-lopencv_superres 
-lopencv_ts 
-lopencv_video 
-lopencv_videostab 
-latomic 
-ltbb 
-lrt 
-ldl
)

set (MUTUAL_LIBRARIES
    -lpthread 
    -lm
)


# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(${Qt5Widgets_INCLUDES})

add_definitions(${Qt5Widgets_DEFINITIONS})

#set(CMAKE_CXX_FLAGS "${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")

#
set ( SOURCES
./src/logger/Logger.cpp
./src/config/NeoCommands.cpp
./src/config/MotionModes.cpp
./src/config/Constants.cpp
./src/vision/CVisionController.cpp
./src/vision/CObjectDatabase.cpp
./src/vision/CObjectDetector.cpp
./src/state_events/CEventBuffer.cpp
./src/communication/CSocketClient.cpp
./src/Cerebrum.cpp
./src/Corion_v1.0.cpp
./src/messages/CBuffer.cpp
./src/messages/CNeoMessage.cpp
./src/CRobotController.cpp
./src/speech/CSpeechRecog.cpp

)

set ( HEADERS
./src/logger/Logger.h
./src/config/Types.h
./src/config/MotionModes.h
./src/config/Constants.h
./src/config/NeoCommands.h
./src/vision/CVisionController.h
./src/vision/CObjectDatabase.h
./src/vision/CObjectDetector.h
./src/Cerebrum.h
./src/interfaces/GuiInterface.h
./src/interfaces/CtypeThread.h
./src/state_events/CEventBuffer.h
./src/state_events/EventTypes.h
./src/communication/CSocketClient.h
./src/messages/CBuffer.h
./src/messages/CNeoMessage.h
./src/CRobotController.h
./src/speech/CSpeechRecogForUI.h
./src/speech/CSpeechRecog.h
)

set ( UI_SOURCES
./src/ui/CHelper.cpp
./src/ui/GuiLauncher.cpp
./src/ui/CObjectXmlParser.cpp
./src/ui/CRubberBand.cpp
./src/ui/CDialogBox.cpp
./src/ui/CMainWindow.cpp
./src/ui/CObjectDetails.cpp
./src/ui/CDrawingBoard.cpp
./src/ui/CToastMsg.cpp
)

set ( UI_MOC_HEADERS
./src/ui/CObjectXmlParser.h
./src/ui/CHelper.h
./src/ui/GuiLauncher.h
./src/ui/CDialogBox.h
./src/ui/CRubberBand.h
./src/ui/CObjectDetails.h
./src/ui/CMainWindow.h
./src/ui/CDrawingBoard.h
./src/ui/CToastMsg.h
)

set ( UIS
    src/ui/mainwindow.ui
)


# Next, using precompiler, compiler and linker

# using Qt meta-system (precompiler)
qt5_wrap_ui( UI_HEADERS ${UIS} )
qt5_wrap_cpp( UI_MOC_SRCS ${UI_MOC_HEADERS} )

# compile
#add_executable( PROJECT_NAME ${SOURCES} ${MOC_SRCS} ${UI_HEADERS} )

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${UI_SOURCES} ${UI_MOC_SRCS} ${UI_HEADERS})


# build it (link libraries)
target_link_libraries( ${PROJECT_NAME} Qt5::Widgets ${SPEECH_LIBRARIES} ${OPENCV_LIBRARIES} ${MUTUAL_LIBRARIES} dlib::dlib)

