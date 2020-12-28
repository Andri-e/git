#ifndef MYEVENT_H
#define MYEVENT_H

UA_StatusCode addNewEventType(UA_Server *server);

UA_StatusCode generateEventMethodCallback(UA_Server *server,
                         const UA_NodeId *sessionId, void *sessionHandle,
                         const UA_NodeId *methodId, void *methodContext,
                         const UA_NodeId *objectId, void *objectContext,
                         size_t inputSize, const UA_Variant *input,
                         size_t outputSize, UA_Variant *output);

void addGenerateEventMethod(UA_Server *server);

#endif
