// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: scene_area_service.proto

#ifndef PROTOBUF_scene_5farea_5fservice_2eproto__INCLUDED
#define PROTOBUF_scene_5farea_5fservice_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3005000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3005001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/generated_enum_reflection.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

namespace protobuf_scene_5farea_5fservice_2eproto {
// Internal implementation detail -- do not use these members.
struct TableStruct {
  static const ::google::protobuf::internal::ParseTableField entries[];
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[];
  static const ::google::protobuf::internal::ParseTable schema[2];
  static const ::google::protobuf::internal::FieldMetadata field_metadata[];
  static const ::google::protobuf::internal::SerializationTable serialization_table[];
  static const ::google::protobuf::uint32 offsets[];
};
void AddDescriptors();
void InitDefaultsEnterSceneRequestImpl();
void InitDefaultsEnterSceneRequest();
void InitDefaultsEnterSceneResponseImpl();
void InitDefaultsEnterSceneResponse();
inline void InitDefaults() {
  InitDefaultsEnterSceneRequest();
  InitDefaultsEnterSceneResponse();
}
}  // namespace protobuf_scene_5farea_5fservice_2eproto
namespace scenearea {
class EnterSceneRequest;
class EnterSceneRequestDefaultTypeInternal;
extern EnterSceneRequestDefaultTypeInternal _EnterSceneRequest_default_instance_;
class EnterSceneResponse;
class EnterSceneResponseDefaultTypeInternal;
extern EnterSceneResponseDefaultTypeInternal _EnterSceneResponse_default_instance_;
}  // namespace scenearea
namespace scenearea {

enum ResultCode {
  SUCCESS = 0,
  ResultCode_INT_MIN_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32min,
  ResultCode_INT_MAX_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32max
};
bool ResultCode_IsValid(int value);
const ResultCode ResultCode_MIN = SUCCESS;
const ResultCode ResultCode_MAX = SUCCESS;
const int ResultCode_ARRAYSIZE = ResultCode_MAX + 1;

const ::google::protobuf::EnumDescriptor* ResultCode_descriptor();
inline const ::std::string& ResultCode_Name(ResultCode value) {
  return ::google::protobuf::internal::NameOfEnum(
    ResultCode_descriptor(), value);
}
inline bool ResultCode_Parse(
    const ::std::string& name, ResultCode* value) {
  return ::google::protobuf::internal::ParseNamedEnum<ResultCode>(
    ResultCode_descriptor(), name, value);
}
// ===================================================================

class EnterSceneRequest : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:scenearea.EnterSceneRequest) */ {
 public:
  EnterSceneRequest();
  virtual ~EnterSceneRequest();

  EnterSceneRequest(const EnterSceneRequest& from);

  inline EnterSceneRequest& operator=(const EnterSceneRequest& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  EnterSceneRequest(EnterSceneRequest&& from) noexcept
    : EnterSceneRequest() {
    *this = ::std::move(from);
  }

  inline EnterSceneRequest& operator=(EnterSceneRequest&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const EnterSceneRequest& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const EnterSceneRequest* internal_default_instance() {
    return reinterpret_cast<const EnterSceneRequest*>(
               &_EnterSceneRequest_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    0;

  void Swap(EnterSceneRequest* other);
  friend void swap(EnterSceneRequest& a, EnterSceneRequest& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline EnterSceneRequest* New() const PROTOBUF_FINAL { return New(NULL); }

  EnterSceneRequest* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const EnterSceneRequest& from);
  void MergeFrom(const EnterSceneRequest& from);
  void Clear() PROTOBUF_FINAL;
  bool IsInitialized() const PROTOBUF_FINAL;

  size_t ByteSizeLong() const PROTOBUF_FINAL;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) PROTOBUF_FINAL;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const PROTOBUF_FINAL;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const PROTOBUF_FINAL;
  int GetCachedSize() const PROTOBUF_FINAL { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const PROTOBUF_FINAL;
  void InternalSwap(EnterSceneRequest* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const PROTOBUF_FINAL;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // string ip_address = 2;
  void clear_ip_address();
  static const int kIpAddressFieldNumber = 2;
  const ::std::string& ip_address() const;
  void set_ip_address(const ::std::string& value);
  #if LANG_CXX11
  void set_ip_address(::std::string&& value);
  #endif
  void set_ip_address(const char* value);
  void set_ip_address(const char* value, size_t size);
  ::std::string* mutable_ip_address();
  ::std::string* release_ip_address();
  void set_allocated_ip_address(::std::string* ip_address);

  // uint64 player_session = 1;
  void clear_player_session();
  static const int kPlayerSessionFieldNumber = 1;
  ::google::protobuf::uint64 player_session() const;
  void set_player_session(::google::protobuf::uint64 value);

  // uint32 port = 3;
  void clear_port();
  static const int kPortFieldNumber = 3;
  ::google::protobuf::uint32 port() const;
  void set_port(::google::protobuf::uint32 value);

  // uint32 map_id = 4;
  void clear_map_id();
  static const int kMapIdFieldNumber = 4;
  ::google::protobuf::uint32 map_id() const;
  void set_map_id(::google::protobuf::uint32 value);

  // uint32 map_copy_idx = 5;
  void clear_map_copy_idx();
  static const int kMapCopyIdxFieldNumber = 5;
  ::google::protobuf::uint32 map_copy_idx() const;
  void set_map_copy_idx(::google::protobuf::uint32 value);

  // int32 result_code = 6;
  void clear_result_code();
  static const int kResultCodeFieldNumber = 6;
  ::google::protobuf::int32 result_code() const;
  void set_result_code(::google::protobuf::int32 value);

  // int32 target_server_idx = 7;
  void clear_target_server_idx();
  static const int kTargetServerIdxFieldNumber = 7;
  ::google::protobuf::int32 target_server_idx() const;
  void set_target_server_idx(::google::protobuf::int32 value);

  // int32 line_id = 8;
  void clear_line_id();
  static const int kLineIdFieldNumber = 8;
  ::google::protobuf::int32 line_id() const;
  void set_line_id(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:scenearea.EnterSceneRequest)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr ip_address_;
  ::google::protobuf::uint64 player_session_;
  ::google::protobuf::uint32 port_;
  ::google::protobuf::uint32 map_id_;
  ::google::protobuf::uint32 map_copy_idx_;
  ::google::protobuf::int32 result_code_;
  ::google::protobuf::int32 target_server_idx_;
  ::google::protobuf::int32 line_id_;
  mutable int _cached_size_;
  friend struct ::protobuf_scene_5farea_5fservice_2eproto::TableStruct;
  friend void ::protobuf_scene_5farea_5fservice_2eproto::InitDefaultsEnterSceneRequestImpl();
};
// -------------------------------------------------------------------

class EnterSceneResponse : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:scenearea.EnterSceneResponse) */ {
 public:
  EnterSceneResponse();
  virtual ~EnterSceneResponse();

  EnterSceneResponse(const EnterSceneResponse& from);

  inline EnterSceneResponse& operator=(const EnterSceneResponse& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  EnterSceneResponse(EnterSceneResponse&& from) noexcept
    : EnterSceneResponse() {
    *this = ::std::move(from);
  }

  inline EnterSceneResponse& operator=(EnterSceneResponse&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const EnterSceneResponse& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const EnterSceneResponse* internal_default_instance() {
    return reinterpret_cast<const EnterSceneResponse*>(
               &_EnterSceneResponse_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    1;

  void Swap(EnterSceneResponse* other);
  friend void swap(EnterSceneResponse& a, EnterSceneResponse& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline EnterSceneResponse* New() const PROTOBUF_FINAL { return New(NULL); }

  EnterSceneResponse* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const EnterSceneResponse& from);
  void MergeFrom(const EnterSceneResponse& from);
  void Clear() PROTOBUF_FINAL;
  bool IsInitialized() const PROTOBUF_FINAL;

  size_t ByteSizeLong() const PROTOBUF_FINAL;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) PROTOBUF_FINAL;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const PROTOBUF_FINAL;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const PROTOBUF_FINAL;
  int GetCachedSize() const PROTOBUF_FINAL { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const PROTOBUF_FINAL;
  void InternalSwap(EnterSceneResponse* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const PROTOBUF_FINAL;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // .scenearea.ResultCode result = 1;
  void clear_result();
  static const int kResultFieldNumber = 1;
  ::scenearea::ResultCode result() const;
  void set_result(::scenearea::ResultCode value);

  // @@protoc_insertion_point(class_scope:scenearea.EnterSceneResponse)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  int result_;
  mutable int _cached_size_;
  friend struct ::protobuf_scene_5farea_5fservice_2eproto::TableStruct;
  friend void ::protobuf_scene_5farea_5fservice_2eproto::InitDefaultsEnterSceneResponseImpl();
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// EnterSceneRequest

// uint64 player_session = 1;
inline void EnterSceneRequest::clear_player_session() {
  player_session_ = GOOGLE_ULONGLONG(0);
}
inline ::google::protobuf::uint64 EnterSceneRequest::player_session() const {
  // @@protoc_insertion_point(field_get:scenearea.EnterSceneRequest.player_session)
  return player_session_;
}
inline void EnterSceneRequest::set_player_session(::google::protobuf::uint64 value) {
  
  player_session_ = value;
  // @@protoc_insertion_point(field_set:scenearea.EnterSceneRequest.player_session)
}

// string ip_address = 2;
inline void EnterSceneRequest::clear_ip_address() {
  ip_address_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& EnterSceneRequest::ip_address() const {
  // @@protoc_insertion_point(field_get:scenearea.EnterSceneRequest.ip_address)
  return ip_address_.GetNoArena();
}
inline void EnterSceneRequest::set_ip_address(const ::std::string& value) {
  
  ip_address_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:scenearea.EnterSceneRequest.ip_address)
}
#if LANG_CXX11
inline void EnterSceneRequest::set_ip_address(::std::string&& value) {
  
  ip_address_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:scenearea.EnterSceneRequest.ip_address)
}
#endif
inline void EnterSceneRequest::set_ip_address(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  ip_address_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:scenearea.EnterSceneRequest.ip_address)
}
inline void EnterSceneRequest::set_ip_address(const char* value, size_t size) {
  
  ip_address_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:scenearea.EnterSceneRequest.ip_address)
}
inline ::std::string* EnterSceneRequest::mutable_ip_address() {
  
  // @@protoc_insertion_point(field_mutable:scenearea.EnterSceneRequest.ip_address)
  return ip_address_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* EnterSceneRequest::release_ip_address() {
  // @@protoc_insertion_point(field_release:scenearea.EnterSceneRequest.ip_address)
  
  return ip_address_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void EnterSceneRequest::set_allocated_ip_address(::std::string* ip_address) {
  if (ip_address != NULL) {
    
  } else {
    
  }
  ip_address_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ip_address);
  // @@protoc_insertion_point(field_set_allocated:scenearea.EnterSceneRequest.ip_address)
}

// uint32 port = 3;
inline void EnterSceneRequest::clear_port() {
  port_ = 0u;
}
inline ::google::protobuf::uint32 EnterSceneRequest::port() const {
  // @@protoc_insertion_point(field_get:scenearea.EnterSceneRequest.port)
  return port_;
}
inline void EnterSceneRequest::set_port(::google::protobuf::uint32 value) {
  
  port_ = value;
  // @@protoc_insertion_point(field_set:scenearea.EnterSceneRequest.port)
}

// uint32 map_id = 4;
inline void EnterSceneRequest::clear_map_id() {
  map_id_ = 0u;
}
inline ::google::protobuf::uint32 EnterSceneRequest::map_id() const {
  // @@protoc_insertion_point(field_get:scenearea.EnterSceneRequest.map_id)
  return map_id_;
}
inline void EnterSceneRequest::set_map_id(::google::protobuf::uint32 value) {
  
  map_id_ = value;
  // @@protoc_insertion_point(field_set:scenearea.EnterSceneRequest.map_id)
}

// uint32 map_copy_idx = 5;
inline void EnterSceneRequest::clear_map_copy_idx() {
  map_copy_idx_ = 0u;
}
inline ::google::protobuf::uint32 EnterSceneRequest::map_copy_idx() const {
  // @@protoc_insertion_point(field_get:scenearea.EnterSceneRequest.map_copy_idx)
  return map_copy_idx_;
}
inline void EnterSceneRequest::set_map_copy_idx(::google::protobuf::uint32 value) {
  
  map_copy_idx_ = value;
  // @@protoc_insertion_point(field_set:scenearea.EnterSceneRequest.map_copy_idx)
}

// int32 result_code = 6;
inline void EnterSceneRequest::clear_result_code() {
  result_code_ = 0;
}
inline ::google::protobuf::int32 EnterSceneRequest::result_code() const {
  // @@protoc_insertion_point(field_get:scenearea.EnterSceneRequest.result_code)
  return result_code_;
}
inline void EnterSceneRequest::set_result_code(::google::protobuf::int32 value) {
  
  result_code_ = value;
  // @@protoc_insertion_point(field_set:scenearea.EnterSceneRequest.result_code)
}

// int32 target_server_idx = 7;
inline void EnterSceneRequest::clear_target_server_idx() {
  target_server_idx_ = 0;
}
inline ::google::protobuf::int32 EnterSceneRequest::target_server_idx() const {
  // @@protoc_insertion_point(field_get:scenearea.EnterSceneRequest.target_server_idx)
  return target_server_idx_;
}
inline void EnterSceneRequest::set_target_server_idx(::google::protobuf::int32 value) {
  
  target_server_idx_ = value;
  // @@protoc_insertion_point(field_set:scenearea.EnterSceneRequest.target_server_idx)
}

// int32 line_id = 8;
inline void EnterSceneRequest::clear_line_id() {
  line_id_ = 0;
}
inline ::google::protobuf::int32 EnterSceneRequest::line_id() const {
  // @@protoc_insertion_point(field_get:scenearea.EnterSceneRequest.line_id)
  return line_id_;
}
inline void EnterSceneRequest::set_line_id(::google::protobuf::int32 value) {
  
  line_id_ = value;
  // @@protoc_insertion_point(field_set:scenearea.EnterSceneRequest.line_id)
}

// -------------------------------------------------------------------

// EnterSceneResponse

// .scenearea.ResultCode result = 1;
inline void EnterSceneResponse::clear_result() {
  result_ = 0;
}
inline ::scenearea::ResultCode EnterSceneResponse::result() const {
  // @@protoc_insertion_point(field_get:scenearea.EnterSceneResponse.result)
  return static_cast< ::scenearea::ResultCode >(result_);
}
inline void EnterSceneResponse::set_result(::scenearea::ResultCode value) {
  
  result_ = value;
  // @@protoc_insertion_point(field_set:scenearea.EnterSceneResponse.result)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace scenearea

namespace google {
namespace protobuf {

template <> struct is_proto_enum< ::scenearea::ResultCode> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::scenearea::ResultCode>() {
  return ::scenearea::ResultCode_descriptor();
}

}  // namespace protobuf
}  // namespace google

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_scene_5farea_5fservice_2eproto__INCLUDED
