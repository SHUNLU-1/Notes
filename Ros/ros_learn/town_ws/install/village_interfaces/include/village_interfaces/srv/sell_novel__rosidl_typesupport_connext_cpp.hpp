// generated from rosidl_typesupport_connext_cpp/resource/idl__rosidl_typesupport_connext_cpp.hpp.em
// with input from village_interfaces:srv/SellNovel.idl
// generated code does not contain a copyright notice


#ifndef VILLAGE_INTERFACES__SRV__SELL_NOVEL__ROSIDL_TYPESUPPORT_CONNEXT_CPP_HPP_
#define VILLAGE_INTERFACES__SRV__SELL_NOVEL__ROSIDL_TYPESUPPORT_CONNEXT_CPP_HPP_

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "village_interfaces/msg/rosidl_typesupport_connext_cpp__visibility_control.h"
#include "village_interfaces/srv/detail/sell_novel__struct.hpp"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif

#include "village_interfaces/srv/dds_connext/SellNovel_Support.h"
#include "village_interfaces/srv/dds_connext/SellNovel_Plugin.h"
#include "ndds/ndds_cpp.h"

#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

// forward declaration of internal CDR Stream
struct ConnextStaticCDRStream;

// forward declaration of DDS types
class DDSDomainParticipant;
class DDSDataWriter;
class DDSDataReader;


namespace village_interfaces
{

namespace srv
{
namespace typesupport_connext_cpp
{

DDS_TypeCode *
get_type_code__SellNovel_Request();

bool
ROSIDL_TYPESUPPORT_CONNEXT_CPP_PUBLIC_village_interfaces
convert_ros_message_to_dds(
  const village_interfaces::srv::SellNovel_Request & ros_message,
  village_interfaces::srv::dds_::SellNovel_Request_ & dds_message);

bool
ROSIDL_TYPESUPPORT_CONNEXT_CPP_PUBLIC_village_interfaces
convert_dds_message_to_ros(
  const village_interfaces::srv::dds_::SellNovel_Request_ & dds_message,
  village_interfaces::srv::SellNovel_Request & ros_message);

bool
to_cdr_stream__SellNovel_Request(
  const void * untyped_ros_message,
  ConnextStaticCDRStream * cdr_stream);

bool
to_message__SellNovel_Request(
  const ConnextStaticCDRStream * cdr_stream,
  void * untyped_ros_message);

}  // namespace typesupport_connext_cpp

}  // namespace srv

}  // namespace village_interfaces


#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CONNEXT_CPP_PUBLIC_village_interfaces
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_connext_cpp,
  village_interfaces, srv,
  SellNovel_Request)();

#ifdef __cplusplus
}
#endif


// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"
// already included above
// #include "village_interfaces/msg/rosidl_typesupport_connext_cpp__visibility_control.h"
// already included above
// #include "village_interfaces/srv/detail/sell_novel__struct.hpp"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif

// already included above
// #include "village_interfaces/srv/dds_connext/SellNovel_Support.h"
// already included above
// #include "village_interfaces/srv/dds_connext/SellNovel_Plugin.h"
// already included above
// #include "ndds/ndds_cpp.h"

#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

// forward declaration of internal CDR Stream
struct ConnextStaticCDRStream;

// forward declaration of DDS types
class DDSDomainParticipant;
class DDSDataWriter;
class DDSDataReader;


namespace village_interfaces
{

namespace srv
{
namespace typesupport_connext_cpp
{

DDS_TypeCode *
get_type_code__SellNovel_Response();

bool
ROSIDL_TYPESUPPORT_CONNEXT_CPP_PUBLIC_village_interfaces
convert_ros_message_to_dds(
  const village_interfaces::srv::SellNovel_Response & ros_message,
  village_interfaces::srv::dds_::SellNovel_Response_ & dds_message);

bool
ROSIDL_TYPESUPPORT_CONNEXT_CPP_PUBLIC_village_interfaces
convert_dds_message_to_ros(
  const village_interfaces::srv::dds_::SellNovel_Response_ & dds_message,
  village_interfaces::srv::SellNovel_Response & ros_message);

bool
to_cdr_stream__SellNovel_Response(
  const void * untyped_ros_message,
  ConnextStaticCDRStream * cdr_stream);

bool
to_message__SellNovel_Response(
  const ConnextStaticCDRStream * cdr_stream,
  void * untyped_ros_message);

}  // namespace typesupport_connext_cpp

}  // namespace srv

}  // namespace village_interfaces


#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CONNEXT_CPP_PUBLIC_village_interfaces
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_connext_cpp,
  village_interfaces, srv,
  SellNovel_Response)();

#ifdef __cplusplus
}
#endif


#include "rmw/types.h"
#include "rosidl_typesupport_cpp/service_type_support.hpp"
// already included above
// #include "rosidl_typesupport_interface/macros.h"
// already included above
// #include "village_interfaces/msg/rosidl_typesupport_connext_cpp__visibility_control.h"

namespace village_interfaces
{
namespace srv
{
namespace typesupport_connext_cpp
{

ROSIDL_TYPESUPPORT_CONNEXT_CPP_PUBLIC_village_interfaces
void *
create_requester__SellNovel(
  void * untyped_participant,
  const char * request_topic_str,
  const char * response_topic_str,
  const void * untyped_datareader_qos,
  const void * untyped_datawriter_qos,
  void ** untyped_reader,
  void ** untyped_writer,
  void * (*allocator)(size_t));

ROSIDL_TYPESUPPORT_CONNEXT_CPP_PUBLIC_village_interfaces
const char *
destroy_requester__SellNovel(
  void * untyped_requester,
  void (* deallocator)(void *));

ROSIDL_TYPESUPPORT_CONNEXT_CPP_PUBLIC_village_interfaces
int64_t
send_request__SellNovel(
  void * untyped_requester,
  const void * untyped_ros_request);

ROSIDL_TYPESUPPORT_CONNEXT_CPP_PUBLIC_village_interfaces
void *
create_replier__SellNovel(
  void * untyped_participant,
  const char * request_topic_str,
  const char * response_topic_str,
  const void * untyped_datareader_qos,
  const void * untyped_datawriter_qos,
  void ** untyped_reader,
  void ** untyped_writer,
  void * (*allocator)(size_t));

ROSIDL_TYPESUPPORT_CONNEXT_CPP_PUBLIC_village_interfaces
const char *
destroy_replier__SellNovel(
  void * untyped_replier,
  void (* deallocator)(void *));

ROSIDL_TYPESUPPORT_CONNEXT_CPP_PUBLIC_village_interfaces
bool
take_request__SellNovel(
  void * untyped_replier,
  rmw_service_info_t * request_header,
  void * untyped_ros_request);

ROSIDL_TYPESUPPORT_CONNEXT_CPP_PUBLIC_village_interfaces
bool
take_response__SellNovel(
  void * untyped_requester,
  rmw_service_info_t * request_header,
  void * untyped_ros_response);

ROSIDL_TYPESUPPORT_CONNEXT_CPP_PUBLIC_village_interfaces
bool
send_response__SellNovel(
  void * untyped_replier,
  const rmw_request_id_t * request_header,
  const void * untyped_ros_response);

ROSIDL_TYPESUPPORT_CONNEXT_CPP_PUBLIC_village_interfaces
void *
get_request_datawriter__SellNovel(void * untyped_requester);

ROSIDL_TYPESUPPORT_CONNEXT_CPP_PUBLIC_village_interfaces
void *
get_reply_datareader__SellNovel(void * untyped_requester);

ROSIDL_TYPESUPPORT_CONNEXT_CPP_PUBLIC_village_interfaces
void *
get_request_datareader__SellNovel(void * untyped_replier);

ROSIDL_TYPESUPPORT_CONNEXT_CPP_PUBLIC_village_interfaces
void *
get_reply_datawriter__SellNovel(void * untyped_replier);

}  // namespace typesupport_connext_cpp
}  // namespace srv
}  // namespace village_interfaces

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CONNEXT_CPP_PUBLIC_village_interfaces
const rosidl_service_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(
  rosidl_typesupport_connext_cpp,
  village_interfaces, srv,
  SellNovel)();

#ifdef __cplusplus
}
#endif

#endif  // VILLAGE_INTERFACES__SRV__SELL_NOVEL__ROSIDL_TYPESUPPORT_CONNEXT_CPP_HPP_
