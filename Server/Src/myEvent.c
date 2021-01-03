#include "../Include/open62541.h"
#include "../Include/myEvent.h"

static UA_NodeId eventType;

UA_StatusCode addNewEventType(UA_Server *server) 
{
    UA_ObjectTypeAttributes attrEvent = UA_ObjectTypeAttributes_default;
    return UA_Server_addObjectTypeNode(server, UA_NODEID_STRING(2, "TestEvent"),
                                       UA_NODEID_NUMERIC(0, UA_NS0ID_BASEEVENTTYPE),
                                       UA_NODEID_NUMERIC(0, UA_NODEID_NULL),
                                       UA_QUALIFIEDNAME(0, "TestEvent"),
                                       attrEvent, 
                                       NULL, &eventType);
}

UA_StatusCode generateEventMethodCallback_On(UA_Server *server,
                         const UA_NodeId *sessionId, void *sessionHandle,
                         const UA_NodeId *methodId, void *methodContext,
                         const UA_NodeId *objectId, void *objectContext,
                         size_t inputSize, const UA_Variant *input,
                         size_t outputSize, UA_Variant *output) 
{
    UA_NodeId onEventNodeId;
    UA_StatusCode retval = UA_Server_createEvent(server, eventType, &onEventNodeId);
    if (retval != UA_STATUSCODE_GOOD) 
    {
        UA_LOG_WARNING(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "Create On event failed.");
        return retval;
    }

    // Set the Event Attributes 
    UA_DateTime eventTime = UA_DateTime_now();
    UA_Server_writeObjectProperty_scalar(server, onEventNodeId, UA_QUALIFIEDNAME(0, "Time"),
                                         &eventTime, &UA_TYPES[UA_TYPES_DATETIME]);

    UA_UInt16 eventSeverity = 100;
    UA_Server_writeObjectProperty_scalar(server, onEventNodeId, UA_QUALIFIEDNAME(0, "Severity"),
                                         &eventSeverity, &UA_TYPES[UA_TYPES_UINT16]);

    UA_LocalizedText eventMessage = UA_LOCALIZEDTEXT("en-US", "An on event has been generated.");
    UA_Server_writeObjectProperty_scalar(server, onEventNodeId, UA_QUALIFIEDNAME(0, "Message"),
                                         &eventMessage, &UA_TYPES[UA_TYPES_LOCALIZEDTEXT]);

    UA_String eventSourceName = UA_STRING("Server");
    UA_Server_writeObjectProperty_scalar(server, onEventNodeId, UA_QUALIFIEDNAME(0, "SourceName"),
                                         &eventSourceName, &UA_TYPES[UA_TYPES_STRING]);

    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "OnEvent Triggerd.");

    // Function to be executed 

    return retval;
}

UA_StatusCode generateEventMethodCallback_Off(UA_Server *server,
                         const UA_NodeId *sessionId, void *sessionHandle,
                         const UA_NodeId *methodId, void *methodContext,
                         const UA_NodeId *objectId, void *objectContext,
                         size_t inputSize, const UA_Variant *input,
                         size_t outputSize, UA_Variant *output) 
{
    
     // set up event
    UA_NodeId offEventNodeId;
    UA_StatusCode retval = UA_Server_createEvent(server, eventType, &offEventNodeId);
    if (retval != UA_STATUSCODE_GOOD) 
    {
        UA_LOG_WARNING(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "Create off event failed.");
        return retval;
    }

    // Set the Event Attributes 
    UA_DateTime eventTime = UA_DateTime_now();
    UA_Server_writeObjectProperty_scalar(server, offEventNodeId, UA_QUALIFIEDNAME(0, "Time"),
                                         &eventTime, &UA_TYPES[UA_TYPES_DATETIME]);

    UA_UInt16 eventSeverity = 100;
    UA_Server_writeObjectProperty_scalar(server, offEventNodeId, UA_QUALIFIEDNAME(0, "Severity"),
                                         &eventSeverity, &UA_TYPES[UA_TYPES_UINT16]);

    UA_LocalizedText eventMessage = UA_LOCALIZEDTEXT("en-US", "An off event has been generated.");
    UA_Server_writeObjectProperty_scalar(server, offEventNodeId, UA_QUALIFIEDNAME(0, "Message"),
                                         &eventMessage, &UA_TYPES[UA_TYPES_LOCALIZEDTEXT]);

    UA_String eventSourceName = UA_STRING("Server");
    UA_Server_writeObjectProperty_scalar(server, offEventNodeId, UA_QUALIFIEDNAME(0, "SourceName"),
                                         &eventSourceName, &UA_TYPES[UA_TYPES_STRING]);

    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "OffEvent Triggerd.");

    // Function to be executed 

    return retval;
    
}

void addGenerateEventMethod(UA_Server *server)
{
    UA_MethodAttributes generateAttr = UA_MethodAttributes_default;
    generateAttr.description = UA_LOCALIZEDTEXT("en-US","Generate an event.");
    generateAttr.displayName = UA_LOCALIZEDTEXT("en-US","Generate Event On");
    generateAttr.executable = true;
    generateAttr.userExecutable = true;
    UA_Server_addMethodNode(server, UA_NODEID_STRING(2, "onEvent"),
                            UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
                            UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                            UA_QUALIFIEDNAME(1, "Generate On Event"),
                            generateAttr, &generateEventMethodCallback_On,
                            0, NULL, 0, NULL, NULL, NULL);

    UA_MethodAttributes generateAttrOff = UA_MethodAttributes_default;
    generateAttrOff.description = UA_LOCALIZEDTEXT("en-US","Generate an event.");
    generateAttrOff.displayName = UA_LOCALIZEDTEXT("en-US","Generate Event Off");
    generateAttrOff.executable = true;
    generateAttrOff.userExecutable = true;
    UA_Server_addMethodNode(server, UA_NODEID_STRING(2, "offEvent"),
                            UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
                            UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                            UA_QUALIFIEDNAME(1, "Generate Off Event"),
                            generateAttrOff, &generateEventMethodCallback_Off,
                            0, NULL, 0, NULL, NULL, NULL);
}
