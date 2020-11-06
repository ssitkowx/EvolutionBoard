///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "Json.h"
#include "LoggerHw.h"

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// FUNCTIONS ////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

bool Json::add (const std::string & v_key, const double v_value, cJSON * v_node)
{
	if (cJSON_AddNumberToObject (v_node, v_key.data (), (double &)(v_value)) == NULL) { return false; };
	return true;
}

bool Json::add (const std::string & v_key, const std::string & v_value, cJSON * v_node)
{
	if (cJSON_AddStringToObject (v_node, v_key.data (), v_value.data ()) == NULL) { return false; };
	return true;
}
 
void Json::logWarning (const std::string & v_msg, const std::string & v_functionName, const std::string & v_nodeName)
{
	std::string msg;
	msg.append (v_msg);
	msg.append ("Function name: ");
	msg.append (v_functionName);
	msg.append (". Node name: ");
	msg.append (v_nodeName);
	msg.append (".");
	LOGW (MODULE, msg.c_str ());
}

void Json::isNodeJsonEmpty (const std::string & v_functionName, const std::string & v_nodeName, const cJSON * const v_node)
{
	if (v_node == NULL) { logWarning ("Empty json node. ", v_functionName, v_nodeName); }
}

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


