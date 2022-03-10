

/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from SellNovel_.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Connext distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Connext manual.
*/

#ifndef SellNovel__1706009050_h
#define SellNovel__1706009050_h

#ifndef NDDS_STANDALONE_TYPE
#ifndef ndds_cpp_h
#include "ndds/ndds_cpp.h"
#endif
#else
#include "ndds_standalone_type.h"
#endif

namespace village_interfaces {
    namespace srv {
        namespace dds_ {

            extern const char *SellNovel_Request_TYPENAME;

            struct SellNovel_Request_Seq;
            #ifndef NDDS_STANDALONE_TYPE
            class SellNovel_Request_TypeSupport;
            class SellNovel_Request_DataWriter;
            class SellNovel_Request_DataReader;
            #endif

            class SellNovel_Request_ 
            {
              public:
                typedef struct SellNovel_Request_Seq Seq;
                #ifndef NDDS_STANDALONE_TYPE
                typedef SellNovel_Request_TypeSupport TypeSupport;
                typedef SellNovel_Request_DataWriter DataWriter;
                typedef SellNovel_Request_DataReader DataReader;
                #endif

                DDS_UnsignedLong   money_ ;

            };
            #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
            /* If the code is building on Windows, start exporting symbols.
            */
            #undef NDDSUSERDllExport
            #define NDDSUSERDllExport __declspec(dllexport)
            #endif

            NDDSUSERDllExport DDS_TypeCode* SellNovel_Request__get_typecode(void); /* Type code */

            DDS_SEQUENCE(SellNovel_Request_Seq, SellNovel_Request_);

            NDDSUSERDllExport
            RTIBool SellNovel_Request__initialize(
                SellNovel_Request_* self);

            NDDSUSERDllExport
            RTIBool SellNovel_Request__initialize_ex(
                SellNovel_Request_* self,RTIBool allocatePointers,RTIBool allocateMemory);

            NDDSUSERDllExport
            RTIBool SellNovel_Request__initialize_w_params(
                SellNovel_Request_* self,
                const struct DDS_TypeAllocationParams_t * allocParams);  

            NDDSUSERDllExport
            void SellNovel_Request__finalize(
                SellNovel_Request_* self);

            NDDSUSERDllExport
            void SellNovel_Request__finalize_ex(
                SellNovel_Request_* self,RTIBool deletePointers);

            NDDSUSERDllExport
            void SellNovel_Request__finalize_w_params(
                SellNovel_Request_* self,
                const struct DDS_TypeDeallocationParams_t * deallocParams);

            NDDSUSERDllExport
            void SellNovel_Request__finalize_optional_members(
                SellNovel_Request_* self, RTIBool deletePointers);  

            NDDSUSERDllExport
            RTIBool SellNovel_Request__copy(
                SellNovel_Request_* dst,
                const SellNovel_Request_* src);

            #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
            /* If the code is building on Windows, stop exporting symbols.
            */
            #undef NDDSUSERDllExport
            #define NDDSUSERDllExport
            #endif
        } /* namespace dds_  */
    } /* namespace srv  */
} /* namespace village_interfaces  */
namespace village_interfaces {
    namespace srv {
        namespace dds_ {

            extern const char *SellNovel_Response_TYPENAME;

            struct SellNovel_Response_Seq;
            #ifndef NDDS_STANDALONE_TYPE
            class SellNovel_Response_TypeSupport;
            class SellNovel_Response_DataWriter;
            class SellNovel_Response_DataReader;
            #endif

            class SellNovel_Response_ 
            {
              public:
                typedef struct SellNovel_Response_Seq Seq;
                #ifndef NDDS_STANDALONE_TYPE
                typedef SellNovel_Response_TypeSupport TypeSupport;
                typedef SellNovel_Response_DataWriter DataWriter;
                typedef SellNovel_Response_DataReader DataReader;
                #endif

                DDS_StringSeq  novels_ ;

            };
            #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
            /* If the code is building on Windows, start exporting symbols.
            */
            #undef NDDSUSERDllExport
            #define NDDSUSERDllExport __declspec(dllexport)
            #endif

            NDDSUSERDllExport DDS_TypeCode* SellNovel_Response__get_typecode(void); /* Type code */

            DDS_SEQUENCE(SellNovel_Response_Seq, SellNovel_Response_);

            NDDSUSERDllExport
            RTIBool SellNovel_Response__initialize(
                SellNovel_Response_* self);

            NDDSUSERDllExport
            RTIBool SellNovel_Response__initialize_ex(
                SellNovel_Response_* self,RTIBool allocatePointers,RTIBool allocateMemory);

            NDDSUSERDllExport
            RTIBool SellNovel_Response__initialize_w_params(
                SellNovel_Response_* self,
                const struct DDS_TypeAllocationParams_t * allocParams);  

            NDDSUSERDllExport
            void SellNovel_Response__finalize(
                SellNovel_Response_* self);

            NDDSUSERDllExport
            void SellNovel_Response__finalize_ex(
                SellNovel_Response_* self,RTIBool deletePointers);

            NDDSUSERDllExport
            void SellNovel_Response__finalize_w_params(
                SellNovel_Response_* self,
                const struct DDS_TypeDeallocationParams_t * deallocParams);

            NDDSUSERDllExport
            void SellNovel_Response__finalize_optional_members(
                SellNovel_Response_* self, RTIBool deletePointers);  

            NDDSUSERDllExport
            RTIBool SellNovel_Response__copy(
                SellNovel_Response_* dst,
                const SellNovel_Response_* src);

            #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
            /* If the code is building on Windows, stop exporting symbols.
            */
            #undef NDDSUSERDllExport
            #define NDDSUSERDllExport
            #endif
        } /* namespace dds_  */
    } /* namespace srv  */
} /* namespace village_interfaces  */

#endif /* SellNovel_ */

