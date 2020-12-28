#include "../Include/open62541.h"
#include "../Include/specNodes.h"

void powerlinkNode(UA_Server *server)
{
    UA_UInt16 UA_THREADSAFE UA_Server_addNamespace(server, Custom_Namespace);

    // OPC UA - POWERLINK
    UA_NodeId DeviceType;
    UA_NodeId PowerlinkDeviceType;
    UA_NodeId DeviceTypeObj;
    UA_NodeId FunctionalGroupType;
    UA_NodeId PowerlinkCnConnectionPointType;
    UA_NodeId CnFunctionalGroupDiagnosticsType; 
    UA_NodeId CnFunctionalGroupConfigurationType; 
    UA_NodeId PowerlinkMnConnectionPointType;   
    UA_NodeId MnFunctionalGroupDiagnosticsType; 
    UA_NodeId MnFunctionalGroupConfigurationType; 


    UA_ObjectAttributes oAttr = UA_ObjectAttributes_default;    
    // Device Type node 
    oAttr.displayName = UA_LOCALIZEDTEXT("en-US", "Device Type - POWERLINK");
    UA_Server_addObjectNode(server, UA_NODEID_NULL,
                            UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
                            UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
                            UA_QUALIFIEDNAME(1, "DeviceType"), 
                            UA_NODEID_NUMERIC(0, UA_NS0ID_BASEOBJECTTYPE),
                            oAttr, NULL, &DeviceType);
    // Powerlink device type object
    oAttr.displayName = UA_LOCALIZEDTEXT("en-US", "Powerlink Device Type");
    UA_Server_addObjectNode(server, UA_NODEID_NULL,
                            DeviceType,
                            UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
                            UA_QUALIFIEDNAME(1, "PowerlinkDeviceType"), 
                            UA_NODEID_NUMERIC(0, UA_NS0ID_BASEOBJECTTYPE),
                            oAttr, NULL, &PowerlinkDeviceType);
    // Device type object 
    oAttr.displayName = UA_LOCALIZEDTEXT("en-US", "Device Type");
    UA_Server_addObjectNode(server, UA_NODEID_NULL,
                            PowerlinkDeviceType,
                            UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
                            UA_QUALIFIEDNAME(1, "DeviceType"), 
                            UA_NODEID_NUMERIC(0, UA_NS0ID_BASEOBJECTTYPE),
                            oAttr, NULL, &DeviceTypeObj);
    // Functional Group Type 
    oAttr.displayName = UA_LOCALIZEDTEXT("en-US", "Functional Group Type");
    UA_Server_addObjectNode(server, UA_NODEID_NULL,
                            PowerlinkDeviceType,
                            UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
                            UA_QUALIFIEDNAME(1, "Functional Group Type"), 
                            UA_NODEID_NUMERIC(0, UA_NS0ID_BASEOBJECTTYPE),
                            oAttr, NULL, &FunctionalGroupType);

    // Powerlink Controlled node, Powerlink Cn Connection Point Type
    oAttr.displayName = UA_LOCALIZEDTEXT("en-US", "Cn Connection Point Type");
    UA_Server_addObjectNode(server, UA_NODEID_NULL,
                            PowerlinkDeviceType,
                            UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
                            UA_QUALIFIEDNAME(1, "PowerlinkCnConnectionPointType"), 
                            UA_NODEID_NUMERIC(0, UA_NS0ID_BASEOBJECTTYPE),
                            oAttr, NULL, &PowerlinkCnConnectionPointType);
    oAttr.displayName = UA_LOCALIZEDTEXT("en-US", "Cn FunctionalGroupDiagnosticsType");
    UA_Server_addObjectNode(server, UA_NODEID_NULL,
                            PowerlinkCnConnectionPointType,
                            UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
                            UA_QUALIFIEDNAME(1, "CnFunctionalGroupDiagnosticsType"), 
                            UA_NODEID_NUMERIC(0, UA_NS0ID_BASEOBJECTTYPE),
                            oAttr, NULL, &CnFunctionalGroupDiagnosticsType);

    oAttr.displayName = UA_LOCALIZEDTEXT("en-US", "Cn FunctionalGroupConfigurationType");
    UA_Server_addObjectNode(server, UA_NODEID_NULL,
                            PowerlinkCnConnectionPointType,
                            UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
                            UA_QUALIFIEDNAME(1, "CnFunctionalGroupConfigurationType"), 
                            UA_NODEID_NUMERIC(0, UA_NS0ID_BASEOBJECTTYPE),
                            oAttr, NULL, &CnFunctionalGroupConfigurationType);

    // Powerlink Managing Node, Powerlink Mn Connection point type
    oAttr.displayName = UA_LOCALIZEDTEXT("en-US", "Mn Connection Point Type");
    UA_Server_addObjectNode(server, UA_NODEID_NULL,
                            PowerlinkDeviceType,
                            UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
                            UA_QUALIFIEDNAME(1, "Mn ConnectionPointType"), 
                            UA_NODEID_NUMERIC(0, UA_NS0ID_BASEOBJECTTYPE),
                            oAttr, NULL, &PowerlinkMnConnectionPointType);
    oAttr.displayName = UA_LOCALIZEDTEXT("en-US", "Mn FunctionalGroupDiagnosticsType");
    UA_Server_addObjectNode(server, UA_NODEID_NULL,
                            PowerlinkMnConnectionPointType,
                            UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
                            UA_QUALIFIEDNAME(1, "MnFunctionalGroupDiagnosticsType"), 
                            UA_NODEID_NUMERIC(0, UA_NS0ID_BASEOBJECTTYPE),
                            oAttr, NULL, &MnFunctionalGroupDiagnosticsType);

    oAttr.displayName = UA_LOCALIZEDTEXT("en-US", "Mn FunctionalGroupConfigurationType");
    UA_Server_addObjectNode(server, UA_NODEID_NULL,
                            PowerlinkMnConnectionPointType,
                            UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
                            UA_QUALIFIEDNAME(1, "MnFunctionalGroupConfigurationType"), 
                            UA_NODEID_NUMERIC(0, UA_NS0ID_BASEOBJECTTYPE),
                            oAttr, NULL, &MnFunctionalGroupConfigurationType);



    // Variable nodes 
    UA_VariableAttributes dtAttr = UA_VariableAttributes_default;
    dtAttr.minimumSamplingInterval = 100;                                   // Optionally, a vendor-specific minimum sampling interval is provided             
    dtAttr.accessLevel = 1;                                                 // The access level for Variables used for type definitions is vendor-specific, for all other Variables defined in this part, the access level shall allow a current read; other settings are vendor specific.
    dtAttr.userAccessLevel = 1;                                             // The value for the UserAccessLevel Attribute is vendor-specific. It is assumed that all Variables can be accessed by at least one user.             
    UA_Variant variant; 
    UA_Int32 integer = 1;
    UA_Variant_setScalar(&variant, &integer, &UA_TYPES[UA_TYPES_INT32]);    // Set the variant to a scalar value that already resides in memory. The value takes on the lifecycle of the variant and is deleted with it.
    dtAttr.value = variant;                                                 // For Variables used as InstanceDeclarations, the value is vendor-specific; otherwise it shall represent the value described in the text.
    dtAttr.arrayDimensionsSize = 0;                                         // If the ValueRank does not identify an array of a specific dimension (i.e. ValueRank <= 0) the ArrayDimensions can either be set to null or the Attribute is missing. This behaviour is vendor-specific.      

    // ------------------------------ DeviceType Mapping - Pages 34 ----------------------------------------------
    // Serial number - String 
    UA_String SerialNumber = UA_STRING("ABC - 12345");
    UA_Variant_setScalar(&dtAttr.value, &SerialNumber, &UA_TYPES[UA_TYPES_STRING]);
    dtAttr.displayName = UA_LOCALIZEDTEXT("en-US", "Serial Number");
    UA_Server_addVariableNode(server, UA_NODEID_NULL, 
                              DeviceTypeObj,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(2, "SerialNumber"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), dtAttr, NULL, NULL);	
    // Revision Counter - Int32
    UA_Int32 RevisionCounter = 0;
    UA_Variant_setScalar(&dtAttr.value, &RevisionCounter, &UA_TYPES[UA_TYPES_INT32]);
    dtAttr.displayName = UA_LOCALIZEDTEXT("en-US", "Revision Counter");
    UA_Server_addVariableNode(server, UA_NODEID_NULL,
                              DeviceTypeObj,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(2, "RevisionCounter"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), dtAttr, NULL, NULL);	

    // Manufacturer - Localized Text 
    UA_LocalizedText Manufacturer = UA_LOCALIZEDTEXT("DE", "SuperCompany");
    UA_Variant_setScalar(&dtAttr.value, &Manufacturer, &UA_TYPES[UA_TYPES_LOCALIZEDTEXT]);
    dtAttr.displayName = UA_LOCALIZEDTEXT("en-US", "Manufacturer");
    UA_Server_addVariableNode(server, UA_NODEID_NULL, 
                              DeviceTypeObj,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(2, "Manufacturer"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), dtAttr, NULL, NULL);	

    // Model - Localized Text 
    UA_LocalizedText Model = UA_LOCALIZEDTEXT("ABC", " 123");
    UA_Variant_setScalar(&dtAttr.value, &Model, &UA_TYPES[UA_TYPES_LOCALIZEDTEXT]);
    dtAttr.displayName = UA_LOCALIZEDTEXT("en-US", "Model");
    UA_Server_addVariableNode(server, UA_NODEID_NULL, 
                              DeviceTypeObj,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(2, "Model"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), dtAttr, NULL, NULL);	

    // Device Manual - String 
    UA_String DeviceManual = UA_STRING("Device Manual : Url");
    UA_Variant_setScalar(&dtAttr.value, &DeviceManual, &UA_TYPES[UA_TYPES_STRING]);
    dtAttr.displayName = UA_LOCALIZEDTEXT("en-US", "Device Manual");
    UA_Server_addVariableNode(server, UA_NODEID_NULL, 
                              DeviceTypeObj,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(2, "DeviceManual"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), dtAttr, NULL, NULL);	

    // Device Revision - String 
    UA_String DeviceRevision = UA_STRING("Device Revision : v0.1");
    UA_Variant_setScalar(&dtAttr.value, &DeviceRevision, &UA_TYPES[UA_TYPES_STRING]);
    dtAttr.displayName = UA_LOCALIZEDTEXT("en-US", "Device Revision");
    UA_Server_addVariableNode(server, UA_NODEID_NULL, 
                              DeviceTypeObj,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(2, "DeviceRevision"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), dtAttr, NULL, NULL);	

    // Software Reversion - String 
    UA_String SoftwareRevision = UA_STRING("v0.1");
    UA_Variant_setScalar(&dtAttr.value, &SoftwareRevision, &UA_TYPES[UA_TYPES_STRING]);
    dtAttr.displayName = UA_LOCALIZEDTEXT("en-US", "Software Revision");
    UA_Server_addVariableNode(server, UA_NODEID_NULL, 
                              DeviceTypeObj,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(2, "Software Revision"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), dtAttr, NULL, NULL);	

    // Hardware Revision - String 
    UA_String HardwareRevision = UA_STRING("v0.1");
    UA_Variant_setScalar(&dtAttr.value, &HardwareRevision, &UA_TYPES[UA_TYPES_STRING]);
    dtAttr.displayName = UA_LOCALIZEDTEXT("en-US", "Hardware Revision");
    UA_Server_addVariableNode(server, UA_NODEID_NULL, 
                              DeviceTypeObj,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(2, "HardwareRevision"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), dtAttr, NULL, NULL);	

    // Device Class - String 
    UA_String DeviceClass = UA_STRING("Class - Something");
    UA_Variant_setScalar(&dtAttr.value, &DeviceClass, &UA_TYPES[UA_TYPES_STRING]);
    dtAttr.displayName = UA_LOCALIZEDTEXT("en-US", "Device Class");
    UA_Server_addVariableNode(server, UA_NODEID_NULL, 
                              DeviceTypeObj,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(2, "DeviceClass"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), dtAttr, NULL, NULL);	



    // Functional Group Variables - The companion Spec does not go that deep into this or define it so not much to be done.. hmm 
    // NetworkAddress - ParameterIdentifier
    UA_UInt32 NetworkAddress = 0;
    UA_Variant_setScalar(&dtAttr.value, &NetworkAddress, &UA_TYPES[UA_TYPES_UINT32]);
    dtAttr.displayName = UA_LOCALIZEDTEXT("en-US", "NetworkAddress");
    UA_Server_addVariableNode(server, UA_NODEID_NULL, 
                              FunctionalGroupType,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(2, "NetworkAddress"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), dtAttr, NULL, NULL);	
    // Identification - NMT_DeviceType_U32
    UA_UInt32 Identification = 0;
    UA_Variant_setScalar(&dtAttr.value, &Identification, &UA_TYPES[UA_TYPES_UINT32]);
    dtAttr.displayName = UA_LOCALIZEDTEXT("en-US", "Identification");
    UA_Server_addVariableNode(server, UA_NODEID_NULL, 
                              FunctionalGroupType,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(2, "NMT_DeviceType_U32"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), dtAttr, NULL, NULL);	
    // Diagnotics - DIA_ERRStatistics_REC 
    UA_UInt32 Diagnotics = 0;
    UA_Variant_setScalar(&dtAttr.value, &Diagnotics, &UA_TYPES[UA_TYPES_UINT32]);
    dtAttr.displayName = UA_LOCALIZEDTEXT("en-US", "Diagnotics");
    UA_Server_addVariableNode(server, UA_NODEID_NULL, 
                              FunctionalGroupType,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(2, "DIA_ERRStatistics_REC "),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), dtAttr, NULL, NULL);	
    // Configuration - CFM_ExpConfDataList_AU32
    UA_UInt32 Configuration = 0;
    UA_Variant_setScalar(&dtAttr.value, &Configuration, &UA_TYPES[UA_TYPES_UINT32]);
    dtAttr.displayName = UA_LOCALIZEDTEXT("en-US", "Configuration");
    UA_Server_addVariableNode(server, UA_NODEID_NULL, 
                              FunctionalGroupType,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(2, "CFM_ExpConfDataList_AU32"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), dtAttr, NULL, NULL);	
    // Control - INP_ProcessImage_REC
    UA_UInt32 Control = 0;
    UA_Variant_setScalar(&dtAttr.value, &Control, &UA_TYPES[UA_TYPES_UINT32]);
    dtAttr.displayName = UA_LOCALIZEDTEXT("en-US", "Control");
    UA_Server_addVariableNode(server, UA_NODEID_NULL, 
                              FunctionalGroupType,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(2, "INP_ProcessImage_REC"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), dtAttr, NULL, NULL);	
    // Status - ParameterIdentifier 
    UA_UInt32 Status = 0;
    UA_Variant_setScalar(&dtAttr.value, &Status, &UA_TYPES[UA_TYPES_UINT32]);
    dtAttr.displayName = UA_LOCALIZEDTEXT("en-US", "Status");
    UA_Server_addVariableNode(server, UA_NODEID_NULL, 
                              FunctionalGroupType,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(2, "ParameterIdentifier"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), dtAttr, NULL, NULL);	


    // --------------------------------- PowerlinkCnConnectionPointType - Page 38, only takeing Mandatory things --------------------------------
    // Functional Group Diagnostics - Powerlink Cn Connection point type   - FunctionalGroupDiagnosticsType
    // DLL_CNCRCError_REC - n/a 
    UA_Int32 DLL_CNCRCError_REC = 0;
    UA_Variant_setScalar(&dtAttr.value, &DLL_CNCRCError_REC, &UA_TYPES[UA_TYPES_INT32]);
    dtAttr.displayName = UA_LOCALIZEDTEXT("en-US", "DLL_CNCRCError_REC");
    UA_Server_addVariableNode(server, UA_NODEID_NULL, 
                              CnFunctionalGroupDiagnosticsType,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(2, "DLL_CNCRCError_REC"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), dtAttr, NULL, NULL);	
    // DLL_CNLossOfSocTolerance_U32 - Uint32
    UA_UInt32 DLL_CNLossOfSocTolerance_U32 = 0;
    UA_Variant_setScalar(&dtAttr.value, &DLL_CNLossOfSocTolerance_U32, &UA_TYPES[UA_TYPES_UINT32]);
    dtAttr.displayName = UA_LOCALIZEDTEXT("en-US", "DLL_CNLossOfSocTolerance_U32");
    UA_Server_addVariableNode(server, UA_NODEID_NULL, 
                              CnFunctionalGroupDiagnosticsType,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(2, "DLL_CNLossOfSocTolerance_U32"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), dtAttr, NULL, NULL);	
    // DLL_CNLossSoC_REC - n/a 
    UA_Int32 DLL_CNLossSoC_REC = 0;
    UA_Variant_setScalar(&dtAttr.value, &DLL_CNLossSoC_REC , &UA_TYPES[UA_TYPES_INT32]);
    dtAttr.displayName = UA_LOCALIZEDTEXT("en-US", "DLL_CNLossSoC_REC");
    UA_Server_addVariableNode(server, UA_NODEID_NULL, 
                              CnFunctionalGroupDiagnosticsType,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(2, "DLL_CNLossSoC_REC"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), dtAttr, NULL, NULL);	


    // Functional Group Configuration - Powerlink Cn connection point type 
    // NMT_CNBasicEthernetTimeout_U32 - Uint32 
    UA_UInt32 NMT_CNBasicEthernetTimeout_U32 = 0;
    UA_Variant_setScalar(&dtAttr.value, &NMT_CNBasicEthernetTimeout_U32, &UA_TYPES[UA_TYPES_UINT32]);
    dtAttr.displayName = UA_LOCALIZEDTEXT("en-US", "NMT_CNBasicEthernetTimeout_U32");
    UA_Server_addVariableNode(server, UA_NODEID_NULL, 
                              CnFunctionalGroupConfigurationType,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(2, "NMT_CNBasicEthernetTimeout_U32"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), dtAttr, NULL, NULL);	







    // ---------------------------------- PowerlinkMnConnectionPointType - Page 40  ---------------------------------
    // Functional Group Diagnostics - Powerlink Mn Connection point type  

    // DLL_MNCNLossPResThrCnt_AU32 - Uint32 []
    UA_UInt32 DLL_MNCNLossPResThrCnt_AU32_U32 = 0;
    UA_Variant_setScalar(&dtAttr.value, &DLL_MNCNLossPResThrCnt_AU32_U32, &UA_TYPES[UA_TYPES_UINT32]);
    dtAttr.displayName = UA_LOCALIZEDTEXT("en-US", "DLL_MNCNLossPResThrCnt_AU32");
    dtAttr.arrayDimensionsSize = 0;
    UA_Server_addVariableNode(server, UA_NODEID_NULL, 
                              MnFunctionalGroupDiagnosticsType,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(2, "DLL_MNCNLossPResThrCnt_AU32"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), dtAttr, NULL, NULL);	
    // DLL_MNCNLossPResThreshold_AU32 - Uint 32 []
    UA_UInt32 DLL_MNCNLossPResThreshold_AU32 = 0;
    UA_Variant_setScalar(&dtAttr.value, &DLL_MNCNLossPResThreshold_AU32, &UA_TYPES[UA_TYPES_UINT32]);
    dtAttr.displayName = UA_LOCALIZEDTEXT("en-US", "DLL_MNCNLossPResThreshold_AU32");
    dtAttr.arrayDimensionsSize = 0;
    UA_Server_addVariableNode(server, UA_NODEID_NULL, 
                              MnFunctionalGroupDiagnosticsType,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(2, "DLL_MNCNLossPResThreshold_AU32"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), dtAttr, NULL, NULL);	
    // DLL_MNCRCError_REC - n/a 
    UA_Int32 DLL_MNCRCError_REC = 0;
    UA_Variant_setScalar(&dtAttr.value, &DLL_MNCRCError_REC, &UA_TYPES[UA_TYPES_INT32]);
    dtAttr.displayName = UA_LOCALIZEDTEXT("en-US", "DLL_MNCRCError_REC");
    dtAttr.arrayDimensionsSize = 0;
    UA_Server_addVariableNode(server, UA_NODEID_NULL, 
                              MnFunctionalGroupDiagnosticsType,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(2, "DLL_MNCRCError_REC"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), dtAttr, NULL, NULL);	
    // DLL_MNLossStatusResThrCnt_AU32 - Uint32 []
    UA_UInt32 DLL_MNLossStatusResThrCnt_AU32 = 0;
    UA_Variant_setScalar(&dtAttr.value, &DLL_MNLossStatusResThrCnt_AU32, &UA_TYPES[UA_TYPES_UINT32]);
    dtAttr.displayName = UA_LOCALIZEDTEXT("en-US", "DLL_MNLossStatusResThrCnt_AU32");
    dtAttr.arrayDimensionsSize = 0;
    UA_Server_addVariableNode(server, UA_NODEID_NULL, 
                              MnFunctionalGroupDiagnosticsType,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(2, "DLL_MNLossStatusResThrCnt_AU32"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), dtAttr, NULL, NULL);	
    // DLL_MNLossStatusResThreshold_AU32 - Uint32 []
    UA_UInt32 DLL_MNLossStatusResThreshold_AU32 = 0;
    UA_Variant_setScalar(&dtAttr.value, &DLL_MNLossStatusResThreshold_AU32, &UA_TYPES[UA_TYPES_UINT32]);
    dtAttr.displayName = UA_LOCALIZEDTEXT("en-US", "DLL_MNLossStatusResThreshold_AU32");
    dtAttr.arrayDimensionsSize = 0;
    UA_Server_addVariableNode(server, UA_NODEID_NULL, 
                              MnFunctionalGroupDiagnosticsType,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(2, "DLL_MNLossStatusResThreshold_AU32"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), dtAttr, NULL, NULL);	
    // NMT_MNNodeCurrState_AU8 - Powerlink, NMTState, Enumeration [] 
    UA_EnumValueType NMT_MNNodeCurrState_AU8;
    NMT_MNNodeCurrState_AU8.value = 1; 
    NMT_MNNodeCurrState_AU8.displayName = UA_LOCALIZEDTEXT("asd", "asd");
    NMT_MNNodeCurrState_AU8.description = UA_LOCALIZEDTEXT("asd", "asdasd");
    UA_Variant_setScalar(&dtAttr.value, &NMT_MNNodeCurrState_AU8, &UA_TYPES[UA_TYPES_ENUMVALUETYPE]);
    dtAttr.displayName = UA_LOCALIZEDTEXT("en-US", "NMT_MNNodeCurrState_AU8");
    dtAttr.arrayDimensionsSize = 0;
    UA_Server_addVariableNode(server, UA_NODEID_NULL, 
                              MnFunctionalGroupDiagnosticsType,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(2, "NMT_MNNodeCurrState_AU8"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), dtAttr, NULL, NULL);	
    // NMT_RequestCmd_REC - n/a 
    UA_Int32 NMT_RequestCmd_REC = 0;
    UA_Variant_setScalar(&dtAttr.value, &NMT_RequestCmd_REC, &UA_TYPES[UA_TYPES_INT32]);
    dtAttr.displayName = UA_LOCALIZEDTEXT("en-US", "NMT_RequestCmd_REC");
    dtAttr.arrayDimensionsSize = 0;
    UA_Server_addVariableNode(server, UA_NODEID_NULL, 
                              MnFunctionalGroupDiagnosticsType,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(2, "NMT_RequestCmd_REC"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), dtAttr, NULL, NULL);	


    // Functional Group Configuration - Powerlink Mn Connection point type  
    // DLL_MNCycleSuspendNumber_U32 - Uint32
    UA_UInt32 DLL_MNCycleSuspendNumber_U32 = 0;
    UA_Variant_setScalar(&dtAttr.value, &DLL_MNCycleSuspendNumber_U32, &UA_TYPES[UA_TYPES_UINT32]);
    dtAttr.displayName = UA_LOCALIZEDTEXT("en-US", "DLL_MNCycleSuspendNumber_U32");
    dtAttr.arrayDimensionsSize = 0;
    UA_Server_addVariableNode(server, UA_NODEID_NULL, 
                              MnFunctionalGroupConfigurationType,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(2, "DLL_MNCycleSuspendNumber_U32"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), dtAttr, NULL, NULL);	
    // NMT_BootTime_REC - n/a 
    UA_Int32 NMT_BootTime_REC = 0;
    UA_Variant_setScalar(&dtAttr.value, &NMT_BootTime_REC, &UA_TYPES[UA_TYPES_INT32]);
    dtAttr.displayName = UA_LOCALIZEDTEXT("en-US", "NMT_BootTime_REC");
    dtAttr.arrayDimensionsSize = 0;
    UA_Server_addVariableNode(server, UA_NODEID_NULL, 
                              MnFunctionalGroupConfigurationType,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(2, "NMT_BootTime_REC"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), dtAttr, NULL, NULL);	
    // NMT_MNCNPResTimeout_AU32 - Uint32 []
    UA_UInt32 NMT_MNCNPResTimeout_AU32 = 0;
    UA_Variant_setScalar(&dtAttr.value, &NMT_MNCNPResTimeout_AU32, &UA_TYPES[UA_TYPES_UINT32]);
    dtAttr.displayName = UA_LOCALIZEDTEXT("en-US", "NMT_MNCNPResTimeout_AU32");
    dtAttr.arrayDimensionsSize = 0;
    UA_Server_addVariableNode(server, UA_NODEID_NULL, 
                              MnFunctionalGroupConfigurationType,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(2, "NMT_MNCNPResTimeout_AU32"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), dtAttr, NULL, NULL);	
    // NMT_MNCycleTiming_REC - n/a 
    UA_Int32 NMT_MNCycleTiming_REC = 0;
    UA_Variant_setScalar(&dtAttr.value, &NMT_MNCycleTiming_REC, &UA_TYPES[UA_TYPES_INT32]);
    dtAttr.displayName = UA_LOCALIZEDTEXT("en-US", "NMT_MNCycleTiming_REC");
    dtAttr.arrayDimensionsSize = 0;
    UA_Server_addVariableNode(server, UA_NODEID_NULL, 
                              MnFunctionalGroupConfigurationType,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(2, "NMT_MNCycleTiming_REC"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), dtAttr, NULL, NULL);	
    // NMT_MNDeviceTypeIdList_AU32 - Uint32 []
    UA_UInt32 NMT_MNDeviceTypeIdList_AU32 = 0;
    UA_Variant_setScalar(&dtAttr.value, &NMT_MNDeviceTypeIdList_AU32, &UA_TYPES[UA_TYPES_UINT32]);
    dtAttr.displayName = UA_LOCALIZEDTEXT("en-US", "NMT_MNDeviceTypeIdList_AU32");
    dtAttr.arrayDimensionsSize = 0;
    UA_Server_addVariableNode(server, UA_NODEID_NULL, 
                              MnFunctionalGroupConfigurationType,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(2, "NMT_MNDeviceTypeIdList_AU32"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), dtAttr, NULL, NULL);	
    // NMT_MNPReqPayloadLimitList_AU16 - Uint16 []
    UA_UInt16 NMT_MNPReqPayloadLimitList_AU16 = 0;
    UA_Variant_setScalar(&dtAttr.value, &NMT_MNPReqPayloadLimitList_AU16, &UA_TYPES[UA_TYPES_UINT16]);
    dtAttr.displayName = UA_LOCALIZEDTEXT("en-US", "NMT_MNPReqPayloadLimitList_AU16");
    dtAttr.arrayDimensionsSize = 0;
    UA_Server_addVariableNode(server, UA_NODEID_NULL, 
                              MnFunctionalGroupConfigurationType,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(2, "NMT_MNPReqPayloadLimitList_AU16"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), dtAttr, NULL, NULL);	
    // NMT_StartUp_U32 - Uint32 
    UA_UInt32 NMT_StartUp_U32 = 0;
    UA_Variant_setScalar(&dtAttr.value, &NMT_StartUp_U32, &UA_TYPES[UA_TYPES_UINT32]);
    dtAttr.displayName = UA_LOCALIZEDTEXT("en-US", "NMT_StartUp_U32");
    dtAttr.arrayDimensionsSize = 0;
    UA_Server_addVariableNode(server, UA_NODEID_NULL, 
                              MnFunctionalGroupConfigurationType,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(2, "NMT_StartUp_U32"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), dtAttr, NULL, NULL);	
}