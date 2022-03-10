

/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from SellNovel_.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Connext distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Connext manual.
*/

#ifndef NDDS_STANDALONE_TYPE
#ifndef ndds_cpp_h
#include "ndds/ndds_cpp.h"
#endif
#ifndef dds_c_log_impl_h              
#include "dds_c/dds_c_log_impl.h"                                
#endif        

#ifndef cdr_type_h
#include "cdr/cdr_type.h"
#endif    

#ifndef osapi_heap_h
#include "osapi/osapi_heap.h" 
#endif
#else
#include "ndds_standalone_type.h"
#endif

#include "SellNovel_.h"

#include <new>

namespace village_interfaces {
    namespace srv {
        namespace dds_ {

            /* ========================================================================= */
            const char *SellNovel_Request_TYPENAME = "village_interfaces::srv::dds_::SellNovel_Request_";

            DDS_TypeCode* SellNovel_Request__get_typecode()
            {
                static RTIBool is_initialized = RTI_FALSE;

                static DDS_TypeCode_Member SellNovel_Request__g_tc_members[1]=
                {

                    {
                        (char *)"money_",/* Member name */
                        {
                            0,/* Representation ID */          
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        1,
                        NULL/* Ignored */
                    }
                };

                static DDS_TypeCode SellNovel_Request__g_tc =
                {{
                        DDS_TK_STRUCT,/* Kind */
                        DDS_BOOLEAN_FALSE, /* Ignored */
                        -1, /*Ignored*/
                        (char *)"village_interfaces::srv::dds_::SellNovel_Request_", /* Name */
                        NULL, /* Ignored */      
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        1, /* Number of members */
                        SellNovel_Request__g_tc_members, /* Members */
                        DDS_VM_NONE  /* Ignored */         
                    }}; /* Type code for SellNovel_Request_*/

                if (is_initialized) {
                    return &SellNovel_Request__g_tc;
                }

                SellNovel_Request__g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_ulong;

                is_initialized = RTI_TRUE;

                return &SellNovel_Request__g_tc;
            }

            RTIBool SellNovel_Request__initialize(
                SellNovel_Request_* sample) {
                return village_interfaces::srv::dds_::SellNovel_Request__initialize_ex(sample,RTI_TRUE,RTI_TRUE);
            }

            RTIBool SellNovel_Request__initialize_ex(
                SellNovel_Request_* sample,RTIBool allocatePointers, RTIBool allocateMemory)
            {

                struct DDS_TypeAllocationParams_t allocParams =
                DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

                allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
                allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

                return village_interfaces::srv::dds_::SellNovel_Request__initialize_w_params(
                    sample,&allocParams);

            }

            RTIBool SellNovel_Request__initialize_w_params(
                SellNovel_Request_* sample, const struct DDS_TypeAllocationParams_t * allocParams)
            {

                if (sample == NULL) {
                    return RTI_FALSE;
                }
                if (allocParams == NULL) {
                    return RTI_FALSE;
                }

                if (!RTICdrType_initUnsignedLong(&sample->money_)) {
                    return RTI_FALSE;
                }

                return RTI_TRUE;
            }

            void SellNovel_Request__finalize(
                SellNovel_Request_* sample)
            {

                village_interfaces::srv::dds_::SellNovel_Request__finalize_ex(sample,RTI_TRUE);
            }

            void SellNovel_Request__finalize_ex(
                SellNovel_Request_* sample,RTIBool deletePointers)
            {
                struct DDS_TypeDeallocationParams_t deallocParams =
                DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

                if (sample==NULL) {
                    return;
                } 

                deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

                village_interfaces::srv::dds_::SellNovel_Request__finalize_w_params(
                    sample,&deallocParams);
            }

            void SellNovel_Request__finalize_w_params(
                SellNovel_Request_* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
            {

                if (sample==NULL) {
                    return;
                }

                if (deallocParams == NULL) {
                    return;
                }

            }

            void SellNovel_Request__finalize_optional_members(
                SellNovel_Request_* sample, RTIBool deletePointers)
            {
                struct DDS_TypeDeallocationParams_t deallocParamsTmp =
                DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;
                struct DDS_TypeDeallocationParams_t * deallocParams =
                &deallocParamsTmp;

                if (sample==NULL) {
                    return;
                } 
                if (deallocParams) {} /* To avoid warnings */

                deallocParamsTmp.delete_pointers = (DDS_Boolean)deletePointers;
                deallocParamsTmp.delete_optional_members = DDS_BOOLEAN_TRUE;

            }

            RTIBool SellNovel_Request__copy(
                SellNovel_Request_* dst,
                const SellNovel_Request_* src)
            {
                try {

                    if (dst == NULL || src == NULL) {
                        return RTI_FALSE;
                    }

                    if (!RTICdrType_copyUnsignedLong (
                        &dst->money_, &src->money_)) { 
                        return RTI_FALSE;
                    }

                    return RTI_TRUE;

                } catch (std::bad_alloc&) {
                    return RTI_FALSE;
                }
            }

            /**
            * <<IMPLEMENTATION>>
            *
            * Defines:  TSeq, T
            *
            * Configure and implement 'SellNovel_Request_' sequence class.
            */
            #define T SellNovel_Request_
            #define TSeq SellNovel_Request_Seq

            #define T_initialize_w_params village_interfaces::srv::dds_::SellNovel_Request__initialize_w_params

            #define T_finalize_w_params   village_interfaces::srv::dds_::SellNovel_Request__finalize_w_params
            #define T_copy       village_interfaces::srv::dds_::SellNovel_Request__copy

            #ifndef NDDS_STANDALONE_TYPE
            #include "dds_c/generic/dds_c_sequence_TSeq.gen"
            #include "dds_cpp/generic/dds_cpp_sequence_TSeq.gen"
            #else
            #include "dds_c_sequence_TSeq.gen"
            #include "dds_cpp_sequence_TSeq.gen"
            #endif

            #undef T_copy
            #undef T_finalize_w_params

            #undef T_initialize_w_params

            #undef TSeq
            #undef T
        } /* namespace dds_  */
    } /* namespace srv  */
} /* namespace village_interfaces  */
namespace village_interfaces {
    namespace srv {
        namespace dds_ {

            /* ========================================================================= */
            const char *SellNovel_Response_TYPENAME = "village_interfaces::srv::dds_::SellNovel_Response_";

            DDS_TypeCode* SellNovel_Response__get_typecode()
            {
                static RTIBool is_initialized = RTI_FALSE;

                static DDS_TypeCode SellNovel_Response__g_tc_novels__string = DDS_INITIALIZE_STRING_TYPECODE(RTI_INT32_MAX);
                static DDS_TypeCode SellNovel_Response__g_tc_novels__sequence = DDS_INITIALIZE_SEQUENCE_TYPECODE(RTI_INT32_MAX,NULL);
                static DDS_TypeCode_Member SellNovel_Response__g_tc_members[1]=
                {

                    {
                        (char *)"novels_",/* Member name */
                        {
                            0,/* Representation ID */          
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        1,
                        NULL/* Ignored */
                    }
                };

                static DDS_TypeCode SellNovel_Response__g_tc =
                {{
                        DDS_TK_STRUCT,/* Kind */
                        DDS_BOOLEAN_FALSE, /* Ignored */
                        -1, /*Ignored*/
                        (char *)"village_interfaces::srv::dds_::SellNovel_Response_", /* Name */
                        NULL, /* Ignored */      
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        1, /* Number of members */
                        SellNovel_Response__g_tc_members, /* Members */
                        DDS_VM_NONE  /* Ignored */         
                    }}; /* Type code for SellNovel_Response_*/

                if (is_initialized) {
                    return &SellNovel_Response__g_tc;
                }

                SellNovel_Response__g_tc_novels__sequence._data._typeCode = (RTICdrTypeCode *)&SellNovel_Response__g_tc_novels__string;

                SellNovel_Response__g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)& SellNovel_Response__g_tc_novels__sequence;

                is_initialized = RTI_TRUE;

                return &SellNovel_Response__g_tc;
            }

            RTIBool SellNovel_Response__initialize(
                SellNovel_Response_* sample) {
                return village_interfaces::srv::dds_::SellNovel_Response__initialize_ex(sample,RTI_TRUE,RTI_TRUE);
            }

            RTIBool SellNovel_Response__initialize_ex(
                SellNovel_Response_* sample,RTIBool allocatePointers, RTIBool allocateMemory)
            {

                struct DDS_TypeAllocationParams_t allocParams =
                DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

                allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
                allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

                return village_interfaces::srv::dds_::SellNovel_Response__initialize_w_params(
                    sample,&allocParams);

            }

            RTIBool SellNovel_Response__initialize_w_params(
                SellNovel_Response_* sample, const struct DDS_TypeAllocationParams_t * allocParams)
            {

                void* buffer = NULL;
                if (buffer) {} /* To avoid warnings */

                if (sample == NULL) {
                    return RTI_FALSE;
                }
                if (allocParams == NULL) {
                    return RTI_FALSE;
                }

                if (allocParams->allocate_memory) {
                    DDS_StringSeq_initialize(&sample->novels_  );
                    DDS_StringSeq_set_absolute_maximum(&sample->novels_ , RTI_INT32_MAX);
                    if (!DDS_StringSeq_set_maximum(&sample->novels_ , (0))) {
                        return RTI_FALSE;
                    }
                    buffer = DDS_StringSeq_get_contiguous_bufferI(
                        &sample->novels_ );

                    if (buffer != NULL) {
                        if (!RTICdrType_initStringArray(buffer, 
                        (0),
                        (0)+1,
                        RTI_CDR_CHAR_TYPE)) {
                            return RTI_FALSE;
                        } 
                    }
                } else { 
                    DDS_StringSeq_set_length(&sample->novels_, 0);
                }
                return RTI_TRUE;
            }

            void SellNovel_Response__finalize(
                SellNovel_Response_* sample)
            {

                village_interfaces::srv::dds_::SellNovel_Response__finalize_ex(sample,RTI_TRUE);
            }

            void SellNovel_Response__finalize_ex(
                SellNovel_Response_* sample,RTIBool deletePointers)
            {
                struct DDS_TypeDeallocationParams_t deallocParams =
                DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

                if (sample==NULL) {
                    return;
                } 

                deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

                village_interfaces::srv::dds_::SellNovel_Response__finalize_w_params(
                    sample,&deallocParams);
            }

            void SellNovel_Response__finalize_w_params(
                SellNovel_Response_* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
            {

                if (sample==NULL) {
                    return;
                }

                if (deallocParams == NULL) {
                    return;
                }

                DDS_StringSeq_finalize(&sample->novels_);

            }

            void SellNovel_Response__finalize_optional_members(
                SellNovel_Response_* sample, RTIBool deletePointers)
            {
                struct DDS_TypeDeallocationParams_t deallocParamsTmp =
                DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;
                struct DDS_TypeDeallocationParams_t * deallocParams =
                &deallocParamsTmp;

                if (sample==NULL) {
                    return;
                } 
                if (deallocParams) {} /* To avoid warnings */

                deallocParamsTmp.delete_pointers = (DDS_Boolean)deletePointers;
                deallocParamsTmp.delete_optional_members = DDS_BOOLEAN_TRUE;

            }

            RTIBool SellNovel_Response__copy(
                SellNovel_Response_* dst,
                const SellNovel_Response_* src)
            {
                try {

                    if (dst == NULL || src == NULL) {
                        return RTI_FALSE;
                    }

                    if (!DDS_StringSeq_copy(&dst->novels_ ,
                    &src->novels_ )) {
                        return RTI_FALSE;
                    }

                    return RTI_TRUE;

                } catch (std::bad_alloc&) {
                    return RTI_FALSE;
                }
            }

            /**
            * <<IMPLEMENTATION>>
            *
            * Defines:  TSeq, T
            *
            * Configure and implement 'SellNovel_Response_' sequence class.
            */
            #define T SellNovel_Response_
            #define TSeq SellNovel_Response_Seq

            #define T_initialize_w_params village_interfaces::srv::dds_::SellNovel_Response__initialize_w_params

            #define T_finalize_w_params   village_interfaces::srv::dds_::SellNovel_Response__finalize_w_params
            #define T_copy       village_interfaces::srv::dds_::SellNovel_Response__copy

            #ifndef NDDS_STANDALONE_TYPE
            #include "dds_c/generic/dds_c_sequence_TSeq.gen"
            #include "dds_cpp/generic/dds_cpp_sequence_TSeq.gen"
            #else
            #include "dds_c_sequence_TSeq.gen"
            #include "dds_cpp_sequence_TSeq.gen"
            #endif

            #undef T_copy
            #undef T_finalize_w_params

            #undef T_initialize_w_params

            #undef TSeq
            #undef T
        } /* namespace dds_  */
    } /* namespace srv  */
} /* namespace village_interfaces  */

