#ifndef DEBUG_H
#define DEBUG_H

//#define ENABLE_DEBUG 1
#ifdef ENABLE_DEBUG
	#define D(x) x
#else
	#define D(x) 
#endif

#endif /* DEBUG_H */
