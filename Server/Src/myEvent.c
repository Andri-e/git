#include "../Include/open62541.h"
#include "../Include/myEvent.h"

static UA_NodeId eventType;

UA_StatusCode addNewEventType(UA_Server *server) 
{
    UA_ObjectTypeAttributes attrOn = UA_ObjectTypeAttributes_default;
    attrOn.displayName = UA_LOCALIZEDTEXT("en-US", "TestEventType");
    attrOn.description = UA_LOCALIZEDTEXT("en-US", "A test event to turn on/off");
    return UA_Server_addObjectTypeNode(server, UA_NODEID_NULL ,
                                       UA_NODEID_NUMERIC(0, UA_NS0ID_BASEEVENTTYPE),
                                       UA_NODEID_NUMERIC(0, UA_NS0ID_HASSUBTYPE),
                                       UA_QUALIFIEDNAME(0, "TestEventType"),
                                       attrOn, 
                                       NULL, &eventType);
}

/**
 * Setting up an event
 * ^^^^^^^^^^^^^^^^^^^
 * In order to set up the event, we can first use ``UA_Server_createEvent`` to give us a node representation of the event.
 * All we need for this is our `EventType`. Once we have our event node, which is saved internally as an `ObjectNode`,
 * we can define the attributes the event has the same way we would define the attributes of an object node. It is not
 * necessary to define the attributes `EventId`, `ReceiveTime`, `SourceNode` or `EventType` since these are set
 * automatically by the server. In this example, we will be setting the fields 'Message' and 'Severity' in addition
 * to `Time` which is needed to make the example UaExpert compliant.
 */
UA_StatusCode setUpEvent(UA_Server *server, UA_NodeId *outId) 
{
    UA_StatusCode retval = UA_Server_createEvent(server, eventType, outId);
    if (retval != UA_STATUSCODE_GOOD) 
    {
        UA_LOG_WARNING(UA_Log_Stdout, UA_LOGCATEGORY_SERVER, "createEvent failed. StatusCode %s", UA_StatusCode_name(retval));
        return retval;
    }

    /* Set the Event Attributes */
    /* Setting the Time is required or else the event will not show up in UAExpert! */
    UA_DateTime eventTime = UA_DateTime_now();
    UA_Server_writeObjectProperty_scalar(server, *outId, UA_QUALIFIEDNAME(0, "Time"),
                                         &eventTime, &UA_TYPES[UA_TYPES_DATETIME]);

    UA_UInt16 eventSeverity = 100;
    UA_Server_writeObjectProperty_scalar(server, *outId, UA_QUALIFIEDNAME(0, "Severity"),
                                         &eventSeverity, &UA_TYPES[UA_TYPES_UINT16]);

    UA_LocalizedText eventMessage = UA_LOCALIZEDTEXT("en-US", "An event has been generated.");
    UA_Server_writeObjectProperty_scalar(server, *outId, UA_QUALIFIEDNAME(0, "Message"),
                                         &eventMessage, &UA_TYPES[UA_TYPES_LOCALIZEDTEXT]);

    UA_String eventSourceName = UA_STRING("Server");
    UA_Server_writeObjectProperty_scalar(server, *outId, UA_QUALIFIEDNAME(0, "SourceName"),
                                         &eventSourceName, &UA_TYPES[UA_TYPES_STRING]);

    return UA_STATUSCODE_GOOD;
}

/**
 * Triggering an event
 * ^^^^^^^^^^^^^^^^^^^
 * First a node representing an event is generated using ``setUpEvent``. Once our event is good to go, we specify
 * a node which emits the event - in this case the server node. We can use ``UA_Server_triggerEvent`` to trigger our
 * event onto said node. Passing ``NULL`` as the second-last argument means we will not receive the `EventId`.
 * The last boolean argument states whether the node should be deleted. */
UA_StatusCode generateEventMethodCallback_On(UA_Server *server,
                         const UA_NodeId *sessionId, void *sessionHandle,
                         const UA_NodeId *methodId, void *methodContext,
                         const UA_NodeId *objectId, void *objectContext,
                         size_t inputSize, const UA_Variant *input,
                         size_t outputSize, UA_Variant *output) 
{
     /* set up event */
    UA_NodeId eventNodeId;
    UA_StatusCode retval = setUpEvent(server, &eventNodeId);
    if(retval != UA_STATUSCODE_GOOD) 
    {
        UA_LOG_WARNING(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Creating event failed. StatusCode %s", UA_StatusCode_name(retval));
        return retval;
    }

    retval = UA_Server_triggerEvent(server, eventNodeId, UA_NODEID_NUMERIC(0, UA_NS0ID_SERVER), NULL, UA_TRUE);
    if(retval != UA_STATUSCODE_GOOD)
    {
        UA_LOG_WARNING(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND,  "Triggering event failed. StatusCode %s", UA_StatusCode_name(retval));
        return retval;
    }

    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Event On Triggerd.");

    // Here we can put in what ever command we want to trigger with the event, for example led on / off or restarting some onboard application. 

    return retval;
}

UA_StatusCode generateEventMethodCallback_Off(UA_Server *server,
                         const UA_NodeId *sessionId, void *sessionHandle,
                         const UA_NodeId *methodId, void *methodContext,
                         const UA_NodeId *objectId, void *objectContext,
                         size_t inputSize, const UA_Variant *input,
                         size_t outputSize, UA_Variant *output) 
{
     /* set up event */
    UA_NodeId eventNodeId;
    UA_StatusCode retval = setUpEvent(server, &eventNodeId);
    if(retval != UA_STATUSCODE_GOOD) 
    {
        UA_LOG_WARNING(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Creating event failed. StatusCode %s", UA_StatusCode_name(retval));
        return retval;
    }

    retval = UA_Server_triggerEvent(server, eventNodeId, UA_NODEID_NUMERIC(0, UA_NS0ID_SERVER), NULL, UA_TRUE);
    if(retval != UA_STATUSCODE_GOOD)
    {
        UA_LOG_WARNING(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND,  "Triggering event failed. StatusCode %s", UA_StatusCode_name(retval));
        return retval;
    }

    UA_LOG_INFO(UA_Log_Stdout, UA_LOGCATEGORY_USERLAND, "Event Off Triggerd.");

    // Here we can put in what ever command we want to trigger with the event, for example led on / off or restarting some onboard application. 

    return retval;
}

/**
 * Now, all that is left to do is to create a method node which uses our callback. We do not
 * require any input and as output we will be using the `EventId` we receive from ``triggerEvent``. The `EventId` is
 * generated by the server internally and is a random unique ID which identifies that specific event.
 *
 * This method node will be added to a basic server setup.
 */

void addGenerateEventMethod(UA_Server *server)
{
    UA_MethodAttributes generateAttr = UA_MethodAttributes_default;
    generateAttr.description = UA_LOCALIZEDTEXT("en-US","Generate an event.");
    generateAttr.displayName = UA_LOCALIZEDTEXT("en-US","Generate Event On");
    generateAttr.executable = true;
    generateAttr.userExecutable = true;
    // UA_Server_addMethodNode(server, UA_NODEID_NUMERIC(1, 62541),
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
    // UA_Server_addMethodNode(server, UA_NODEID_NUMERIC(1, 62541),
    UA_Server_addMethodNode(server, UA_NODEID_STRING(2, "offEvent"),
                            UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER),
                            UA_NODEID_NUMERIC(0, UA_NS0ID_HASCOMPONENT),
                            UA_QUALIFIEDNAME(1, "Generate Off Event"),
                            generateAttrOff, &generateEventMethodCallback_Off,
                            0, NULL, 0, NULL, NULL, NULL);
}
