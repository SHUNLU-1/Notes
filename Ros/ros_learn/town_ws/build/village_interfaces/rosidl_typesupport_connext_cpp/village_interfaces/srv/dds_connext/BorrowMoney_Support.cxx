
/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from BorrowMoney_.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Connext distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Connext manual.
*/

#include "BorrowMoney_Support.h"
#include "BorrowMoney_Plugin.h"

#ifndef dds_c_log_impl_h              
#include "dds_c/dds_c_log_impl.h"                                
#endif        

namespace village_interfaces {
    namespace srv {
        namespace dds_ {

            /* ========================================================================= */
            /**
            <<IMPLEMENTATION>>

            Defines:   TData,
            TDataWriter,
            TDataReader,
            TTypeSupport

            Configure and implement 'BorrowMoney_Request_' support classes.

            Note: Only the #defined classes get defined
            */

            /* ----------------------------------------------------------------- */
            /* DDSDataWriter
            */

            /**
            <<IMPLEMENTATION >>

            Defines:   TDataWriter, TData
            */

            /* Requires */
            #define TTYPENAME   BorrowMoney_Request_TYPENAME

            /* Defines */
            #define TDataWriter BorrowMoney_Request_DataWriter
            #define TData       village_interfaces::srv::dds_::BorrowMoney_Request_

            #include "dds_cpp/generic/dds_cpp_data_TDataWriter.gen"

            #undef TDataWriter
            #undef TData

            #undef TTYPENAME

            /* ----------------------------------------------------------------- */
            /* DDSDataReader
            */

            /**
            <<IMPLEMENTATION >>

            Defines:   TDataReader, TDataSeq, TData
            */

            /* Requires */
            #define TTYPENAME   BorrowMoney_Request_TYPENAME

            /* Defines */
            #define TDataReader BorrowMoney_Request_DataReader
            #define TDataSeq    BorrowMoney_Request_Seq
            #define TData       village_interfaces::srv::dds_::BorrowMoney_Request_

            #include "dds_cpp/generic/dds_cpp_data_TDataReader.gen"

            #undef TDataReader
            #undef TDataSeq
            #undef TData

            #undef TTYPENAME

            /* ----------------------------------------------------------------- */
            /* TypeSupport

            <<IMPLEMENTATION >>

            Requires:  TTYPENAME,
            TPlugin_new
            TPlugin_delete
            Defines:   TTypeSupport, TData, TDataReader, TDataWriter
            */

            /* Requires */
            #define TTYPENAME    BorrowMoney_Request_TYPENAME
            #define TPlugin_new  village_interfaces::srv::dds_::BorrowMoney_Request_Plugin_new
            #define TPlugin_delete  village_interfaces::srv::dds_::BorrowMoney_Request_Plugin_delete

            /* Defines */
            #define TTypeSupport BorrowMoney_Request_TypeSupport
            #define TData        village_interfaces::srv::dds_::BorrowMoney_Request_
            #define TDataReader  BorrowMoney_Request_DataReader
            #define TDataWriter  BorrowMoney_Request_DataWriter
            #define TGENERATE_SER_CODE
            #define TGENERATE_TYPECODE

            #include "dds_cpp/generic/dds_cpp_data_TTypeSupport.gen"

            #undef TTypeSupport
            #undef TData
            #undef TDataReader
            #undef TDataWriter
            #undef TGENERATE_TYPECODE
            #undef TGENERATE_SER_CODE
            #undef TTYPENAME
            #undef TPlugin_new
            #undef TPlugin_delete

        } /* namespace dds_  */
    } /* namespace srv  */
} /* namespace village_interfaces  */
namespace village_interfaces {
    namespace srv {
        namespace dds_ {

            /* ========================================================================= */
            /**
            <<IMPLEMENTATION>>

            Defines:   TData,
            TDataWriter,
            TDataReader,
            TTypeSupport

            Configure and implement 'BorrowMoney_Response_' support classes.

            Note: Only the #defined classes get defined
            */

            /* ----------------------------------------------------------------- */
            /* DDSDataWriter
            */

            /**
            <<IMPLEMENTATION >>

            Defines:   TDataWriter, TData
            */

            /* Requires */
            #define TTYPENAME   BorrowMoney_Response_TYPENAME

            /* Defines */
            #define TDataWriter BorrowMoney_Response_DataWriter
            #define TData       village_interfaces::srv::dds_::BorrowMoney_Response_

            #include "dds_cpp/generic/dds_cpp_data_TDataWriter.gen"

            #undef TDataWriter
            #undef TData

            #undef TTYPENAME

            /* ----------------------------------------------------------------- */
            /* DDSDataReader
            */

            /**
            <<IMPLEMENTATION >>

            Defines:   TDataReader, TDataSeq, TData
            */

            /* Requires */
            #define TTYPENAME   BorrowMoney_Response_TYPENAME

            /* Defines */
            #define TDataReader BorrowMoney_Response_DataReader
            #define TDataSeq    BorrowMoney_Response_Seq
            #define TData       village_interfaces::srv::dds_::BorrowMoney_Response_

            #include "dds_cpp/generic/dds_cpp_data_TDataReader.gen"

            #undef TDataReader
            #undef TDataSeq
            #undef TData

            #undef TTYPENAME

            /* ----------------------------------------------------------------- */
            /* TypeSupport

            <<IMPLEMENTATION >>

            Requires:  TTYPENAME,
            TPlugin_new
            TPlugin_delete
            Defines:   TTypeSupport, TData, TDataReader, TDataWriter
            */

            /* Requires */
            #define TTYPENAME    BorrowMoney_Response_TYPENAME
            #define TPlugin_new  village_interfaces::srv::dds_::BorrowMoney_Response_Plugin_new
            #define TPlugin_delete  village_interfaces::srv::dds_::BorrowMoney_Response_Plugin_delete

            /* Defines */
            #define TTypeSupport BorrowMoney_Response_TypeSupport
            #define TData        village_interfaces::srv::dds_::BorrowMoney_Response_
            #define TDataReader  BorrowMoney_Response_DataReader
            #define TDataWriter  BorrowMoney_Response_DataWriter
            #define TGENERATE_SER_CODE
            #define TGENERATE_TYPECODE

            #include "dds_cpp/generic/dds_cpp_data_TTypeSupport.gen"

            #undef TTypeSupport
            #undef TData
            #undef TDataReader
            #undef TDataWriter
            #undef TGENERATE_TYPECODE
            #undef TGENERATE_SER_CODE
            #undef TTYPENAME
            #undef TPlugin_new
            #undef TPlugin_delete

        } /* namespace dds_  */
    } /* namespace srv  */
} /* namespace village_interfaces  */

