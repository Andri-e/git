/* This work is licensed under a Creative Commons CCZero 1.0 Universal License.
 * See http://creativecommons.org/publicdomain/zero/1.0/ for more information. */

/**
 * Working with Objects and Object Types
 * -------------------------------------
 *
 * Using objects to structure information models
 * ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
 * Assume a situation where we want to model a set of pumps and their runtime
 * state in an OPC UA information model. Of course, all pump representations
 * should follow the same basic structure, For example, we might have graphical
 * representation of pumps in a SCADA visualisation that shall be resuable for
 * all pumps.
 *
 * Following the object-oriented programming paradigm, every pump is represented
 * by an object with the following layout:
 *
 * .. graphviz::
 *
 *    digraph tree {
 *
 *    fixedsize=true;
 *    node [width=2, height=0, shape=box, fillcolor="#E5E5E5", concentrate=true]
 *
 *    node_root [label=< <I>ObjectNode</I><BR/>Pump >]
 *
 *    { rank=same
 *      point_1 [shape=point]
 *      node_1 [label=< <I>VariableNode</I><BR/>ManufacturerName >] }
 *    node_root -> point_1 [arrowhead=none]
 *    point_1 -> node_1 [label="hasComponent"]
 *
 *    { rank=same
 *      point_2 [shape=point]
 *      node_2 [label=< <I>VariableNode</I><BR/>ModelName >] }
 *    point_1 -> point_2 [arrowhead=none]
 *    point_2 -> node_2 [label="hasComponent"]
 *
 *    {  rank=same
 *       point_4 [shape=point]
 *       node_4 [label=< <I>VariableNode</I><BR/>Status >] }
 *    point_2 -> point_4 [arrowhead=none]
 *    point_4 -> node_4 [label="hasComponent"]
 *
 *    {  rank=same
 *       point_5 [shape=point]
 *       node_5 [label=< <I>VariableNode</I><BR/>MotorRPM >] }
 *    point_4 -> point_5 [arrowhead=none]
 *    point_5 -> node_5 [label="hasComponent"]
 *
 *    }
 *
 * The following code manually defines a pump and its member variables. We omit
 * setting constraints on the variable values as this is not the focus of this
 * tutorial and was already covered. */

#include "open62541.h"

#include <signal.h>


static void powerlinkNode(UA_Server *server)
{
    // OPC UA 
    UA_NodeId FolderType;
    UA_NodeId FunctionGroupType;

    // OPC UA DI 
    UA_NodeId BaseObjectType;
    UA_NodeId TopologyElementType;
    UA_NodeId NetworkType;
    UA_NodeId ProtocolType;
    UA_NodeId DeviceType;
    UA_NodeId ConnectionPointType;

    // OPC UA - POWERLINK
    UA_NodeId PowerlinkDeviceProfileType;
    UA_NodeId PowerlinkDeviceType;
    UA_NodeId PowerlinkConnectionPointType;
    UA_NodeId PowerlinkProtocoltype;
    UA_NodeId PowerlinkCnConnectionPointType;
    UA_NodeId PowerlinkMnConnectionPointType;
    UA_NodeId LogicalDeviceName;

    UA_ObjectAttributes oAttr = UA_ObjectAttributes_default;    
    // Folder Type - OPC UA Part 5 
    oAttr.displayName = UA_LOCALIZEDTEXT("en-US", "Folder Type - OPC UA Part 5");
    UA_Server_addObjectNode(server, UA_NODEID_NULL,
                            UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
                            UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
                            UA_QUALIFIEDNAME(1, "FolderType"), 
                            UA_NODEID_NUMERIC(0, UA_NS0ID_BASEOBJECTTYPE),
                            oAttr, NULL, &FolderType);
    // Base Object Type - OPC UA Part 5
    oAttr.displayName = UA_LOCALIZEDTEXT("en-US", "Base Object Type - OPC UA Part 5");
    UA_Server_addObjectNode(server, UA_NODEID_NULL,
                            UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
                            UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
                            UA_QUALIFIEDNAME(1, "BaseObjectType"), 
                            UA_NODEID_NUMERIC(0, UA_NS0ID_BASEOBJECTTYPE),
                            oAttr, NULL, &BaseObjectType);


    // Function Group Type - OPC UA DI 
    oAttr.displayName = UA_LOCALIZEDTEXT("en-US", "Function Group Type - OPC UA DI");
    UA_Server_addObjectNode(server, UA_NODEID_NULL,
                            FolderType,
                            UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
                            UA_QUALIFIEDNAME(1, "FunctionGroupType"), 
                            UA_NODEID_NUMERIC(0, UA_NS0ID_BASEOBJECTTYPE),
                            oAttr, NULL, &FunctionGroupType);
    // Topology Element Type - OPC UA DI 
    oAttr.displayName = UA_LOCALIZEDTEXT("en-US", "Topology Element Type - OPC UA DI");
    UA_Server_addObjectNode(server, UA_NODEID_NULL,
                            BaseObjectType,
                            UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
                            UA_QUALIFIEDNAME(1, "TopologyElementType"), 
                            UA_NODEID_NUMERIC(0, UA_NS0ID_BASEOBJECTTYPE),
                            oAttr, NULL, &TopologyElementType);
    // Device Type - OPC UA DI
    oAttr.displayName = UA_LOCALIZEDTEXT("en-US", "Device Type - OPC UA DI");
    UA_Server_addObjectNode(server, UA_NODEID_NULL,
                            TopologyElementType,
                            UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
                            UA_QUALIFIEDNAME(1, "DeviceType"), 
                            UA_NODEID_NUMERIC(0, UA_NS0ID_BASEOBJECTTYPE),
                            oAttr, NULL, &DeviceType);
    // Connection Point Type - OPC UA DI
    oAttr.displayName = UA_LOCALIZEDTEXT("en-US", "Connection Point Type - OPC UA DI");
    UA_Server_addObjectNode(server, UA_NODEID_NULL,
                            TopologyElementType,
                            UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
                            UA_QUALIFIEDNAME(1, "ConnectionPointType"), 
                            UA_NODEID_NUMERIC(0, UA_NS0ID_BASEOBJECTTYPE),
                            oAttr, NULL, &ConnectionPointType);
    // Network Type - OPC UA DI 
    oAttr.displayName = UA_LOCALIZEDTEXT("en-US", "Network Type - OPC UA DI");
    UA_Server_addObjectNode(server, UA_NODEID_NULL,
                            BaseObjectType,
                            UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
                            UA_QUALIFIEDNAME(1, "NetworkType"), 
                            UA_NODEID_NUMERIC(0, UA_NS0ID_BASEOBJECTTYPE),
                            oAttr, NULL, &NetworkType);
    // Protocol Type - OPC UA DI
    oAttr.displayName = UA_LOCALIZEDTEXT("en-US", "Protocol Type - OPC UA DI");
    UA_Server_addObjectNode(server, UA_NODEID_NULL,
                            BaseObjectType,
                            UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
                            UA_QUALIFIEDNAME(1, "ProcotolType"), 
                            UA_NODEID_NUMERIC(0, UA_NS0ID_BASEOBJECTTYPE),
                            oAttr, NULL, &ProtocolType);
    // Device Type - OPC UA DI
    oAttr.displayName = UA_LOCALIZEDTEXT("en-US", "Device Type - OPC UA DI");
    UA_Server_addObjectNode(server, UA_NODEID_NULL,
                            TopologyElementType,
                            UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
                            UA_QUALIFIEDNAME(1, "Pump (Manual)"), 
                            UA_NODEID_NUMERIC(0, UA_NS0ID_BASEOBJECTTYPE),
                            oAttr, NULL, &DeviceType);
    

    // Powerlink Device Profile Type - OPC UA POWERLINK
    oAttr.displayName = UA_LOCALIZEDTEXT("en-US", "Powerlink Device Profile Type - OPC UA POWERLINK");
    UA_Server_addObjectNode(server, UA_NODEID_NULL,
                            TopologyElementType,
                            UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
                            UA_QUALIFIEDNAME(1, "PowerlinkDeviceProfileType"), 
                            UA_NODEID_NUMERIC(0, UA_NS0ID_BASEOBJECTTYPE),
                            oAttr, NULL, &PowerlinkConnectionPointType);
    // Powerlink Device Type - OPC UA POWERLINK
    oAttr.displayName = UA_LOCALIZEDTEXT("en-US", "Powerlink Device Type - OPC UA POWERLINK");
    UA_Server_addObjectNode(server, UA_NODEID_NULL,
                            DeviceType,
                            UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
                            UA_QUALIFIEDNAME(1, "PowerlinkDeviceType"), 
                            UA_NODEID_NUMERIC(0, UA_NS0ID_BASEOBJECTTYPE),
                            oAttr, NULL, &PowerlinkDeviceType);
    // Powerlink Connection Point Type - OPC UA POWERLINK
    oAttr.displayName = UA_LOCALIZEDTEXT("en-US", "Powerlink Connection Point Type - OPC UA POWERLINK");
    UA_Server_addObjectNode(server, UA_NODEID_NULL,
                            ConnectionPointType,
                            UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
                            UA_QUALIFIEDNAME(1, "PowerlinkConnectionPointType"), 
                            UA_NODEID_NUMERIC(0, UA_NS0ID_BASEOBJECTTYPE),
                            oAttr, NULL, &PowerlinkConnectionPointType);
    // Powerlink Cn ConnectionPoint Type - OPC UA POWERLINK
    oAttr.displayName = UA_LOCALIZEDTEXT("en-US", "Powerlink Cn Connection Point Type - OPC UA POWERLINK");
    UA_Server_addObjectNode(server, UA_NODEID_NULL,
                            PowerlinkConnectionPointType,
                            UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
                            UA_QUALIFIEDNAME(1, "PowerlinkCnConnectionPointType"), 
                            UA_NODEID_NUMERIC(0, UA_NS0ID_BASEOBJECTTYPE),
                            oAttr, NULL, &PowerlinkCnConnectionPointType);
    // Powerlink Mn ConnectionPoint Type - OPC UA POWERLINK
    oAttr.displayName = UA_LOCALIZEDTEXT("en-US", "Powerlink Mn Connection Point Type - OPC UA POWERLINK");
    UA_Server_addObjectNode(server, UA_NODEID_NULL,
                            PowerlinkConnectionPointType,
                            UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
                            UA_QUALIFIEDNAME(1, "PowerlinkMnConnectionPointType"), 
                            UA_NODEID_NUMERIC(0, UA_NS0ID_BASEOBJECTTYPE),
                            oAttr, NULL, &PowerlinkMnConnectionPointType);
    // Powerlink Protocol Type - OPC UA POWERLINK
    oAttr.displayName = UA_LOCALIZEDTEXT("en-US", "Powerlink Protocol type - OPC UA POWERLINK");
    UA_Server_addObjectNode(server, UA_NODEID_NULL,
                            ProtocolType,
                            UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
                            UA_QUALIFIEDNAME(1, "PowerlinkProtocolType"), 
                            UA_NODEID_NUMERIC(0, UA_NS0ID_BASEOBJECTTYPE),
                            oAttr, NULL, &PowerlinkProtocoltype);

    // Variable setup 
    UA_VariableAttributes varAttr = UA_VariableAttributes_default;
    
    // Powerlink Device Type - Manufacturer
    UA_String manName = UA_STRING("The Name of the Manufacturer");
    UA_Variant_setScalar(&varAttr.value, &manName, &UA_TYPES[UA_TYPES_STRING]);
    varAttr.displayName = UA_LOCALIZEDTEXT("en-US", "Manufacturer");
    UA_Server_addVariableNode(server, UA_NODEID_NULL, 
                              PowerlinkDeviceType,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(1, "Manufacturer"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), varAttr, NULL, NULL);
    // Powerlink Device Type - Model
    UA_String modName = UA_STRING("Model");
    UA_Variant_setScalar(&varAttr.value, &modName, &UA_TYPES[UA_TYPES_STRING]);
    varAttr.displayName = UA_LOCALIZEDTEXT("en-US", "Model");
    UA_Server_addVariableNode(server, UA_NODEID_NULL, 
                              PowerlinkDeviceType,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(1, "Model"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), varAttr, NULL, NULL);

    // Functional Group Type - Identification 
    UA_String idName = UA_STRING("Indentifacation");
    UA_Variant_setScalar(&varAttr.value, &idName, &UA_TYPES[UA_TYPES_STRING]);
    varAttr.displayName = UA_LOCALIZEDTEXT("en-US", "Identification");
    UA_Server_addVariableNode(server, UA_NODEID_NULL, 
                              FunctionGroupType,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(1, "Identification"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), varAttr, NULL, NULL);
    // Powerlink Cn Connection Point Type 
    UA_String conName = UA_STRING("ControlledNode");
    UA_Variant_setScalar(&varAttr.value, &modName, &UA_TYPES[UA_TYPES_STRING]);
    varAttr.displayName = UA_LOCALIZEDTEXT("en-US", "ControlledNode");
    UA_Server_addVariableNode(server, UA_NODEID_NULL, 
                              PowerlinkDeviceType,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(1, "ControlledNode"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), varAttr, NULL, NULL);

    // Hmmm not sure if this is the correct thing.. 

/*
    UA_VariableAttributes tsAttr = UA_VariableAttributes_default;
    UA_Variant_setScalar(&tsAttr.value, &timeStamp, &UA_TYPES[UA_TYPES_DATETIME]);
    UA_Server_addVariableNode(server, UA_NODEID_STRING(2, "testTimeStamp"), 
                            testObjectId,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(2, "timeStamp"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), tsAttr, NULL, NULL);	
*/
}

static void powerlinkNode2(UA_Server *server)
{
    
    // OPC UA - POWERLINK
    UA_NodeId DeviceType;
    UA_NodeId PowerlinkDeviceType;
    UA_NodeId DeviceTypeObj;
    UA_NodeId FunctionalGroupType;
    UA_NodeId PowerlinkCnConnectionPointType;
    UA_NodeId MnControlledNodeObj;


    UA_ObjectAttributes oAttr = UA_ObjectAttributes_default;    
    // Device Type node 
    oAttr.displayName = UA_LOCALIZEDTEXT("en-US", "Device Type");
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
    oAttr.displayName = UA_LOCALIZEDTEXT("en-US", "Powerlink CnC onnection Point Type");
    UA_Server_addObjectNode(server, UA_NODEID_NULL,
                            PowerlinkDeviceType,
                            UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
                            UA_QUALIFIEDNAME(1, "PowerlinkCnConnectionPointType"), 
                            UA_NODEID_NUMERIC(0, UA_NS0ID_BASEOBJECTTYPE),
                            oAttr, NULL, &PowerlinkCnConnectionPointType);
    // Powerlink Managing Node, Powerlink Mn Connection point type
    oAttr.displayName = UA_LOCALIZEDTEXT("en-US", "Mn Connection Point Type");
    UA_Server_addObjectNode(server, UA_NODEID_NULL,
                            PowerlinkDeviceType,
                            UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES),
                            UA_QUALIFIEDNAME(1, "Mn ConnectionPointType"), 
                            UA_NODEID_NUMERIC(0, UA_NS0ID_BASEOBJECTTYPE),
                            oAttr, NULL, &MnControlledNodeObj);

    // ------------------------------ DeviceType Mapping - Pages 34 ----------------------------------------------
    // Serial number - String 
    UA_VariableAttributes dtAttr = UA_VariableAttributes_default;
    UA_String SerialNumber = "ABC - 12345";
    UA_Variant_setScalar(&dtAttr.value, &SerialNumber, &UA_TYPES[UA_TYPES_STRING]);
    UA_Server_addVariableNode(server, UA_NODEID_STRING(2, "Serial Number"), 
                              DeviceTypeObj,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(2, "SerialNumber"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), dtAttr, NULL, NULL);	
    // Revision Counter - Int32
    UA_Int32 RevisionCounter = 0;
    UA_Variant_setScalar(&dtAttr.value, &RevisionCounter, &UA_TYPES[UA_TYPES_INT32]);
    UA_Server_addVariableNode(server, UA_NODEID_STRING(2, "RevisionCounter"), 
                              DeviceTypeObj,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(2, "RevisionCounter"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), dtAttr, NULL, NULL);	

    // Manufacturer - Localized Text 
    UA_LocalizedText Manufacturer = Andri;
    UA_Variant_setScalar(&dtAttr.value, &Manufacturer, &UA_TYPES[UA_TYPES_LOCALIZEDTEXT]);
    UA_Server_addVariableNode(server, UA_NODEID_STRING(2, "Manufacturer"), 
                              DeviceTypeObj,
                              UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                              UA_QUALIFIEDNAME(2, "Manufacturer"),
                              UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE), dtAttr, NULL, NULL);	

    // Model - Localized Text 

    // Device Manual - String 

    // Device Revision - String 

    // Software Reversion - String 

    // Hardware Revision - String 

    // Device Class - String 




    // Functional Group Variables - NetworkAddress, Identification, Diagnostics, Configuration, Control, Status 
    // Need to find more info on this. 

    // PowerlinkCnConnectionPointType - Page 38 

    // PowerlinkMnConnectionPointType - Page 40  


}



static volatile UA_Boolean running = true;
static void stopHandler(int sign) 
{
    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "received ctrl-c");
    running = false;
}

int main(void) {
    signal(SIGINT, stopHandler);
    signal(SIGTERM, stopHandler);

    UA_Server *server = UA_Server_new();
    UA_ServerConfig_setDefault(UA_Server_getConfig(server));

    powerlinkNode(server);
    powerlinkNode2(server);

    UA_StatusCode retval = UA_Server_run(server, &running);

    UA_Server_delete(server);
    return retval == UA_STATUSCODE_GOOD ? EXIT_SUCCESS : EXIT_FAILURE;
}
