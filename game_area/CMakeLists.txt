cmake_minimum_required(VERSION 3.2)
project(
    ${PROJECT_DEVELOP_NAME}_application_game_area
    VERSION 0.0.0.1
    LANGUAGES C CXX 
)

### 设置缺省构建类型
if (NOT CMAKE_BUILD_TYPE)
#SET(CMAKE_BUILD_TYPE "Release")
set(CMAKE_BUILD_TYPE Debug)
endif(NOT CMAKE_BUILD_TYPE)

file(GLOB_RECURSE ${PROJECT_NAME}_SOURCES "*.h" "*.hpp" "*.cpp" "*.cxx" "*.cc" )


# ADD_LIBRARY(${libname} MODULE ${src_list})
# ADD_LIBRARY(${libname} SHARED ${src_list})
# ADD_LIBRARY(${PROJECT_NAME} STATIC ${SRC_LIST})
ADD_EXECUTABLE(${PROJECT_NAME} ${${PROJECT_NAME}_SOURCES} )

## 设置项目头文件包含路径
target_include_directories(${PROJECT_NAME} 
  PUBLIC
  ${Boost_INCLUDE_DIRS}
  ${LZO_INCLUDE_DIRS}
  ${PROTOBUF_INCLUDE_DIRS}
  ${${PROJECT_DEVELOP_NAME}_MODULE_INC}
)

## 设置项目链接库
list(APPEND ${PROJECT_NAME}_LINK_LIBRARIES     
${Boost_LIBRARIES}
${CRUCIS_DEVELOP_NAME}_base
${MARIADBCLIENT_LIBRARIES}
${LZO_LIBRARIES}
${Behaviac_LIBRARIES}
${BULLET_LIBRARIES}
protobuf::libprotobuf protobuf::libprotobuf-lite
fmt::fmt
spdlog::spdlog
flatbuffers::flatbuffers
gRPC::gpr
gRPC::grpc++
gRPC::grpc++_cronet
gRPC::grpc++_unsecure
crossguid
)

if (MSVC)
	if(${MSVC_RUNTIME} STREQUAL "static")
		message(STATUS "${PROJECT_NAME}_LINK_LIBRARIES:${${PROJECT_NAME}_LINK_LIBRARIES}")
		list(APPEND ${PROJECT_NAME}_LINK_LIBRARIES  Shlwapi)
		message(STATUS "${PROJECT_NAME}_LINK_LIBRARIES:${${PROJECT_NAME}_LINK_LIBRARIES}")
	endif()
endif()

TARGET_LINK_LIBRARIES(
	${PROJECT_NAME}
	${${PROJECT_NAME}_LINK_LIBRARIES}
	${CRUCIS_DEVELOP_NAME}_base
    ${PROJECT_DEVELOP_NAME}_module_game_center
    ${PROJECT_DEVELOP_NAME}_module_game_world
    ${PROJECT_DEVELOP_NAME}_module_public
)

# 添加项目的预编译支持
#cotire(${PROJECT_NAME})
