cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(star-ist)

# Add to path in order to pick up the FindXXX.cmake files included in this project
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

# This project depends on ROOT
find_package(ROOT)

if(NOT ROOT_FOUND)
	message(FATAL_ERROR "Fatal error: ROOT package not found")
endif()

add_definitions(-D__ROOT__)


# Check whether the compiler supports c++11
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()


include_directories(
	${ROOT_INCLUDE_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}
	${STAR_BASE_DIR}
	${STAR_STEVENT_DIR}
	${STAR_STDB_DIR}
	${STAR_TABLES_DIR}
	${STAR_TPC_DIR}
	${STAR_DAQ_DIR}
	${STAR_RTS_DIR}
	${STAR_RTS_DIR}/RTS/src
	${STAR_RTS_DIR}/RTS/include
	${STAR_PAMS_DIR}/global/inc
)


# StIstClusterMaker library
root_generate_linkdef_and_dictionary(StIstClusterMaker
	StIstClusterMaker/StIstClusterMaker.h
	StIstClusterMaker/StIstIClusterAlgo.h
	StIstClusterMaker/StIstScanClusterAlgo.h
	StIstClusterMaker/StIstSimpleClusterAlgo.h
)

add_library(StIstClusterMaker SHARED
	StIstClusterMaker/StIstClusterMaker.cxx
	StIstClusterMaker/StIstIClusterAlgo.cxx
	StIstClusterMaker/StIstScanClusterAlgo.cxx
	StIstClusterMaker/StIstSimpleClusterAlgo.cxx
	StIstClusterMaker_dict.cxx
)


# StIstDbMaker library
root_generate_linkdef_and_dictionary(StIstDbMaker StIstDbMaker/StIstDb.h StIstDbMaker/StIstDbMaker.h)
add_library(StIstDbMaker SHARED StIstDbMaker/StIstDb.cxx StIstDbMaker/StIstDbMaker.cxx StIstDbMaker_dict.cxx)


# StIstHitMaker library
root_generate_linkdef_and_dictionary(StIstHitMaker StIstHitMaker/StIstHitMaker.h)
add_library(StIstHitMaker SHARED StIstHitMaker/StIstHitMaker.cxx StIstHitMaker_dict.cxx)


# StIstRawHitMaker library
root_generate_linkdef_and_dictionary(StIstRawHitMaker StIstRawHitMaker/StIstRawHitMaker.h)
add_library(StIstRawHitMaker SHARED StIstRawHitMaker/StIstRawHitMaker.cxx StIstRawHitMaker_dict.cxx)


# StIstSimMaker library
root_generate_linkdef_and_dictionary(StIstSimMaker StIstSimMaker/StIstFastSimMaker.h)
add_library(StIstSimMaker SHARED StIstSimMaker/StIstFastSimMaker.cxx StIstSimMaker_dict.cxx)


# StIstUtil library
root_generate_linkdef_and_dictionary(StIstUtil
	StIstUtil/StIstClusterCollection.h
	StIstUtil/StIstCluster.h
	StIstUtil/StIstCollection.h
	StIstUtil/StIstConsts.h
	StIstUtil/StIstDigiHit.h
	StIstUtil/StIstRawHitCollection.h
	StIstUtil/StIstRawHit.h
)

add_library(StIstUtil SHARED
	StIstUtil/StIstClusterCollection.cxx
	StIstUtil/StIstCluster.cxx
	StIstUtil/StIstCollection.cxx
	StIstUtil/StIstDigiHit.cxx
	StIstUtil/StIstRawHitCollection.cxx
	StIstUtil/StIstRawHit.cxx
	StIstUtil_dict.cxx
)


# Installation section
set(ADDITIONAL_INSTALL_PREFIX ".")

if(DEFINED ENV{STAR_HOST_SYS})
   set(ADDITIONAL_INSTALL_PREFIX ".$ENV{STAR_HOST_SYS}")
endif()

install(TARGETS StIstClusterMaker StIstDbMaker StIstHitMaker StIstRawHitMaker StIstSimMaker StIstUtil DESTINATION "${ADDITIONAL_INSTALL_PREFIX}/lib")
