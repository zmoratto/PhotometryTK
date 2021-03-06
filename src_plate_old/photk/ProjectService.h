// __BEGIN_LICENSE__
// Copyright (C) 2006-2011 United States Government as represented by
// the Administrator of the National Aeronautics and Space Administration.
// All Rights Reserved.
// __END_LICENSE__


#ifndef __PHOTK_PROJECT_SERVICE_H__
#define __PHOTK_PROJECT_SERVICE_H__

#include <vw/Core/Thread.h>
#include <vw/Plate/FundamentalTypes.h>
#include <photk/ProjectFile.pb.h>

#include <google/protobuf/service.h>

namespace photk {

  // Implementation
  //  This is what the server interacts with. Clients just call ProjectService.
  // This server implementation does not ever deal with the creation of project
  // files, but only dishes out their information and allows for modification
  // of their camera information.
  class ProjectServiceImpl : public ProjectService {
    std::string m_root_directory;

    ProjectMeta m_project_meta;
    std::vector<CameraMeta> m_camera_metas;

    vw::Mutex m_mutex;

  public:
    ProjectServiceImpl(std::string root_directory);

    void sync(); // Write to disk

    virtual void OpenRequest(::google::protobuf::RpcController* controller,
                             const ::photk::ProjectOpenRequest* request,
                             ::photk::ProjectOpenReply* response,
                             ::google::protobuf::Closure* done);
    virtual void IterationUpdate(::google::protobuf::RpcController* controller,
				 const ::photk::IterationUpdateRequest* request,
				 ::photk::IterationUpdateReply* response,
				 ::google::protobuf::Closure* done);
    virtual void CameraCreate(::google::protobuf::RpcController* controller,
                              const ::photk::CameraCreateRequest* request,
                              ::photk::CameraCreateReply* response,
                              ::google::protobuf::Closure* done);
    virtual void CameraRead(::google::protobuf::RpcController* controller,
                            const ::photk::CameraReadRequest* request,
                            ::photk::CameraReadReply* response,
                            ::google::protobuf::Closure* done);
    virtual void CameraWrite(::google::protobuf::RpcController* controller,
                             const ::photk::CameraWriteRequest* request,
                             ::photk::CameraWriteReply* response,
                             ::google::protobuf::Closure* done);
    virtual void PixvalAdd(::google::protobuf::RpcController* controller,
			   const ::photk::PixvalAddRequest* request,
			   ::photk::PixvalAddReply* response,
			   ::google::protobuf::Closure* done);
    virtual void PixvalGetAndReset(::google::protobuf::RpcController* controller,
				   const ::photk::PixvalGetAndResetRequest* request,
				   ::photk::PixvalGetAndResetReply* response,
				   ::google::protobuf::Closure* done);

  };

} //end namespace photk

#endif//__PHOTK_PROJECT_SERVICE_H__
