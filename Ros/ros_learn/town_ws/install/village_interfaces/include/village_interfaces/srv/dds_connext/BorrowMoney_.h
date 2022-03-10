

/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from BorrowMoney_.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Connext distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Connext manual.
*/

#ifndef BorrowMoney__1906956066_h
#define BorrowMoney__1906956066_h

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

            extern const char *BorrowMoney_Request_TYPENAME;

            struct BorrowMoney_Request_Seq;
            #ifndef NDDS_STANDALONE_TYPE
            class BorrowMoney_Request_TypeSupport;
            class BorrowMoney_Request_DataWriter;
            class BorrowMoney_Request_DataReader;
            #endif

            class BorrowMoney_Request_ 
            {
              public:
                typedef struct BorrowMoney_Request_Seq Seq;
                #ifndef NDDS_STANDALONE_TYPE
                typedef BorrowMoney_Request_TypeSupport TypeSupport;
                typedef BorrowMoney_Request_DataWriter DataWriter;
                typedef BorrowMoney_Request_DataReader DataReader;
                #endif

                DDS_Char *   name_ ;
                DDS_UnsignedLong   money_ ;

            };
            #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
            /* If the code is building on Windows, start exporting symbols.
            */
            #undef NDDSUSERDllExport
            #define NDDSUSERDllExport __declspec(dllexport)
            #endif

            NDDSUSERDllExport DDS_TypeCode* BorrowMoney_Request__get_typecode(void); /* Type code */

            DDS_SEQUENCE(BorrowMoney_Request_Seq, BorrowMoney_Request_);

            NDDSUSERDllExport
            RTIBool BorrowMoney_Request__initialize(
                BorrowMoney_Request_* self);

            NDDSUSERDllExport
            RTIBool BorrowMoney_Request__initialize_ex(
                BorrowMoney_Request_* self,RTIBool allocatePointers,RTIBool allocateMemory);

            NDDSUSERDllExport
            RTIBool BorrowMoney_Request__initialize_w_params(
                BorrowMoney_Request_* self,
                const struct DDS_TypeAllocationParams_t * allocParams);  

            NDDSUSERDllExport
            void BorrowMoney_Request__finalize(
                BorrowMoney_Request_* self);

            NDDSUSERDllExport
            void BorrowMoney_Request__finalize_ex(
                BorrowMoney_Request_* self,RTIBool deletePointers);

            NDDSUSERDllExport
            void BorrowMoney_Request__finalize_w_params(
                BorrowMoney_Request_* self,
                const struct DDS_TypeDeallocationParams_t * deallocParams);

            NDDSUSERDllExport
            void BorrowMoney_Request__finalize_optional_members(
                BorrowMoney_Request_* self, RTIBool deletePointers);  

            NDDSUSERDllExport
            RTIBool BorrowMoney_Request__copy(
                BorrowMoney_Request_* dst,
                const BorrowMoney_Request_* src);

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

            extern const char *BorrowMoney_Response_TYPENAME;

            struct BorrowMoney_Response_Seq;
            #ifndef NDDS_STANDALONE_TYPE
            class BorrowMoney_Response_TypeSupport;
            class BorrowMoney_Response_DataWriter;
            class BorrowMoney_Response_DataReader;
            #endif

            class BorrowMoney_Response_ 
            {
              public:
                typedef struct BorrowMoney_Response_Seq Seq;
                #ifndef NDDS_STANDALONE_TYPE
                typedef BorrowMoney_Response_TypeSupport TypeSupport;
                typedef BorrowMoney_Response_DataWriter DataWriter;
                typedef BorrowMoney_Response_DataReader DataReader;
                #endif

                DDS_Boolean   success_ ;
                DDS_UnsignedLong   money_ ;

            };
            #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
            /* If the code is building on Windows, start exporting symbols.
            */
            #undef NDDSUSERDllExport
            #define NDDSUSERDllExport __declspec(dllexport)
            #endif

            NDDSUSERDllExport DDS_TypeCode* BorrowMoney_Response__get_typecode(void); /* Type code */

            DDS_SEQUENCE(BorrowMoney_Response_Seq, BorrowMoney_Response_);

            NDDSUSERDllExport
            RTIBool BorrowMoney_Response__initialize(
                BorrowMoney_Response_* self);

            NDDSUSERDllExport
            RTIBool BorrowMoney_Response__initialize_ex(
                BorrowMoney_Response_* self,RTIBool allocatePointers,RTIBool allocateMemory);

            NDDSUSERDllExport
            RTIBool BorrowMoney_Response__initialize_w_params(
                BorrowMoney_Response_* self,
                const struct DDS_TypeAllocationParams_t * allocParams);  

            NDDSUSERDllExport
            void BorrowMoney_Response__finalize(
                BorrowMoney_Response_* self);

            NDDSUSERDllExport
            void BorrowMoney_Response__finalize_ex(
                BorrowMoney_Response_* self,RTIBool deletePointers);

            NDDSUSERDllExport
            void BorrowMoney_Response__finalize_w_params(
                BorrowMoney_Response_* self,
                const struct DDS_TypeDeallocationParams_t * deallocParams);

            NDDSUSERDllExport
            void BorrowMoney_Response__finalize_optional_members(
                BorrowMoney_Response_* self, RTIBool deletePointers);  

            NDDSUSERDllExport
            RTIBool BorrowMoney_Response__copy(
                BorrowMoney_Response_* dst,
                const BorrowMoney_Response_* src);

            #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
            /* If the code is building on Windows, stop exporting symbols.
            */
            #undef NDDSUSERDllExport
            #define NDDSUSERDllExport
            #endif
        } /* namespace dds_  */
    } /* namespace srv  */
} /* namespace village_interfaces  */

#endif /* BorrowMoney_ */

