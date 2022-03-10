// generated from rosidl_typesupport_connext_cpp/resource/idl__rosidl_typesupport_connext_cpp.hpp.em
// with input from village_interfaces:msg/Novel.idl
// generated code does not contain a copyright notice


#ifndef VILLAGE_INTERFACES__MSG__NOVEL__ROSIDL_TYPESUPPORT_CONNEXT_CPP_HPP_
#define VILLAGE_INTERFACES__MSG__NOVEL__ROSIDL_TYPESUPPORT_CONNEXT_CPP_HPP_

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "village_interfaces/msg/rosidl_typesupport_connext_cpp__visibility_control.h"
#include "village_interfaces/msg/detail/novel__struct.hpp"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif

#include "village_interfaces/msg/dds_connext/Novel_Support.h"
#include "village_interfaces/msg/dds_connext/Novel_Plugin.h"
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

namespace msg
{
namespace typesupport_connext_cpp
{

DDS_TypeCode *
get_type_code__Novel();

bool
ROSIDL_TYPESUPPORT_CONNEXT_CPP_PUBLIC_village_interfaces
convert_ros_message_to_dds(
  const village_interfaces::msg::Novel & ros_message,
  village_interfaces::msg::dds_::Novel_ & dds_message);

bool
ROSIDL_TYPESUPPORT_CONNEXT_CPP_PUBLIC_village_interfaces
convert_dds_message_to_ros(
  const village_interfaces::msg::dds_::Novel_ & dds_message,
  village_interfaces::msg::Novel & ros_message);

bool
to_cdr_stream__Novel(
  const void * untyped_ros_message,
  ConnextStaticCDRStream * cdr_stream);

bool
to_message__Novel(
  const ConnextStaticCDRStream * cdr_stream,
  void * untyped_ros_message);

}  // namespace typesupport_connext_cpp

}  // namespace msg

}  // namespace village_interfaces


#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CONNEXT_CPP_PUBLIC_village_interfaces
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
  rosidl_typesupport_connext_cpp,
  village_interfaces, msg,
  Novel)();

#ifdef __cplusplus
}
#endif


#endif  // VILLAGE_INTERFACES__MSG__NOVEL__ROSIDL_TYPESUPPORT_CONNEXT_CPP_HPP_
