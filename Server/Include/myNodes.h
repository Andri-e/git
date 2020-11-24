#include "myNodes.c"

// Setting up the object node and its variables 
static void nodeSetup(UA_Server *server); 

// Time Stamp callback 
static void beforeReadTime(UA_Server *server,
               const UA_NodeId *sessionId, void *sessionContext,
               const UA_NodeId *nodeid, void *nodeContext,
               const UA_NumericRange *range, const UA_DataValue *data);

static void addValueCallbackToCurrentTimeVariable(UA_Server *server);

// CPU Temperature Callback 
static void beforeReadTemperature(UA_Server *server,
               const UA_NodeId *sessionId, void *sessionContext,
               const UA_NodeId *nodeid, void *nodeContext,
               const UA_NumericRange *range, const UA_DataValue *data);

static void addValueCallbackToCurrentTemerature(UA_Server *server) ;


// CPU Not idle Callback  - https://rosettacode.org/wiki/Linux_CPU_utilization - https://www.kgoettler.com/post/proc-stat/ for math n stuff 
static void beforeReadIdle(UA_Server *server,
               const UA_NodeId *sessionId, void *sessionContext,
               const UA_NodeId *nodeid, void *nodeContext,
               const UA_NumericRange *range, const UA_DataValue *data);


static void addValueCallbackToCurrentIdle(UA_Server *server);