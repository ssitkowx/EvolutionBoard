#pragma once 

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// INCLUDES /////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include <queue>
#include <stdint.h>

///////////////////////////////////////////////////////////////////////////////
/////////////////////////// CLASSES/STRUCTURES ////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class SystemEvents final
{
	public:
        void     Add     (uint16_t v_eventId);
        bool     IsEmpty (void);
        uint16_t Remove  (void);
		
		static SystemEvents & GetInstance (void)
		{
			static SystemEvents instance;
			return instance;
		}
		
	private:
	    std::queue <uint16_t> queue;
	    SystemEvents () = default;
};

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// END OF FILE ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
