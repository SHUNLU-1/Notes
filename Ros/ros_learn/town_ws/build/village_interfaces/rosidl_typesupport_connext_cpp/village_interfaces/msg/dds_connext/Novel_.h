

/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from Novel_.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Connext distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Connext manual.
*/

#ifndef Novel__910771786_h
#define Novel__910771786_h

#ifndef NDDS_STANDALONE_TYPE
#ifndef ndds_cpp_h
#include "ndds/ndds_cpp.h"
#endif
#else
#include "ndds_standalone_type.h"
#endif

#include "sensor_msgs/msg/dds_connext/Image_.h"
namespace village_interfaces {
    namespace msg {
        namespace dds_ {

            extern const char *Novel_TYPENAME;

            struct Novel_Seq;
            #ifndef NDDS_STANDALONE_TYPE
            class Novel_TypeSupport;
            class Novel_DataWriter;
            class Novel_DataReader;
            #endif

            class Novel_ 
            {
              public:
                typedef struct Novel_Seq Seq;
                #ifndef NDDS_STANDALONE_TYPE
                typedef Novel_TypeSupport TypeSupport;
                typedef Novel_DataWriter DataWriter;
                typedef Novel_DataReader DataReader;
                #endif

                DDS_Char *   content_ ;
                sensor_msgs::msg::dds_::Image_   image_ ;

            };
            #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
            /* If the code is building on Windows, start exporting symbols.
            */
            #undef NDDSUSERDllExport
            #define NDDSUSERDllExport __declspec(dllexport)
            #endif

            NDDSUSERDllExport DDS_TypeCode* Novel__get_typecode(void); /* Type code */

            DDS_SEQUENCE(Novel_Seq, Novel_);

            NDDSUSERDllExport
            RTIBool Novel__initialize(
                Novel_* self);

            NDDSUSERDllExport
            RTIBool Novel__initialize_ex(
                Novel_* self,RTIBool allocatePointers,RTIBool allocateMemory);

            NDDSUSERDllExport
            RTIBool Novel__initialize_w_params(
                Novel_* self,
                const struct DDS_TypeAllocationParams_t * allocParams);  

            NDDSUSERDllExport
            void Novel__finalize(
                Novel_* self);

            NDDSUSERDllExport
            void Novel__finalize_ex(
                Novel_* self,RTIBool deletePointers);

            NDDSUSERDllExport
            void Novel__finalize_w_params(
                Novel_* self,
                const struct DDS_TypeDeallocationParams_t * deallocParams);

            NDDSUSERDllExport
            void Novel__finalize_optional_members(
                Novel_* self, RTIBool deletePointers);  

            NDDSUSERDllExport
            RTIBool Novel__copy(
                Novel_* dst,
                const Novel_* src);

            #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
            /* If the code is building on Windows, stop exporting symbols.
            */
            #undef NDDSUSERDllExport
            #define NDDSUSERDllExport
            #endif
        } /* namespace dds_  */
    } /* namespace msg  */
} /* namespace village_interfaces  */

#endif /* Novel_ */

