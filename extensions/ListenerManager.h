//
//  ListenerManager.h
//  TVPortable
//
//  Created by Ruiwei Bu on 6/22/12.
//  Copyright (c) 2012 Studio Symphonie. All rights reserved.
//

#ifndef TVPortable_ListenerManager_h
#define TVPortable_ListenerManager_h

#include <map>
#include <deque>
#include <string>

namespace TVPortable {
    
    // abstract listener manager
    // can manage listeners with custom tag
    template<typename T, typename TAG_TYPE = std::string>
    struct ListenerManager {  
        typedef T ListenerType;
        
        typedef std::map<TAG_TYPE, ListenerType*> ListenerMap;
        typedef std::deque<std::pair<ListenerType*, bool> > ListenerList;
        
        virtual ~ListenerManager() {
            typename ListenerList::iterator it = mListenerList.begin();
            while(it != mListenerList.end()) {
                if(it->second) {
                    delete it->first;
                }
                ++it;
            }
        }
        
        void attachListener(ListenerType* listener, const TAG_TYPE& tag = std::string(), bool autoRelease=false) {
            {
                assert(listener);
                if(!listener)
                    return;
                
                mListenerList.push_back(typename ListenerList::value_type(listener, autoRelease));
                if(!tag.empty()) {
                    typename ListenerMap::const_iterator it = mListenerMap.find(tag);
                    if(it != mListenerMap.end()) {
                        mListenerMap.insert(std::make_pair(tag, listener));
                    }
                }
            }
        }
        
        ListenerType* getListener(const TAG_TYPE& tag) const {
            typename ListenerList::const_iterator it = mListenerList.find(tag);
            if(it != mListenerList.end()) 
                return it->second;
            return NULL;
        }
        
        void publishListenerEvent(void (ListenerType::*Memfun)()) {
            typename ListenerList::iterator it = mListenerList.begin();
            for(; it != mListenerList.end(); ++it) {
                ((it->first)->*Memfun)();
            }
        }
        
        template<typename ARG1>
        void publishListenerEvent(void (ListenerType::*Memfun)(ARG1), ARG1 arg1) {
            typename ListenerList::iterator it = mListenerList.begin();
            for(; it != mListenerList.end(); ++it) {
                ((it->first)->*Memfun)(arg1);
            }
        }
        
        template<typename ARG1, typename ARG2>
        void publishListenerEvent(void (ListenerType::*Memfun)(ARG1, ARG2), ARG1 arg1, ARG2 arg2) {
            typename ListenerList::iterator it = mListenerList.begin();
            for(; it != mListenerList.end(); ++it) {
                ((it->first)->*Memfun)(arg1, arg2);
            }
        }
        
        template<typename ARG1, typename ARG2, typename ARG3>
        void publishListenerEvent(void (ListenerType::*Memfun)(ARG1, ARG2, ARG3), ARG1 arg1, ARG2 arg2, ARG3 arg3) {
            typename ListenerList::iterator it = mListenerList.begin();
            for(; it != mListenerList.end(); ++it) {
                ((it->first)->*Memfun)(arg1, arg2, arg3);
            }
        }
        
        template<typename ARG1, typename ARG2, typename ARG3, typename ARG4>
        void publishListenerEvent(void (ListenerType::*Memfun)(ARG1, ARG2, ARG3, ARG4), ARG1 arg1, ARG2 arg2, ARG3 arg3, ARG4 arg4) {
            typename ListenerList::iterator it = mListenerList.begin();
            for(; it != mListenerList.end(); ++it) {
                ((it->first)->*Memfun)(arg1, arg2, arg3, arg4);
            }
        }
        
        template<typename ARG1, typename ARG2, typename ARG3, typename ARG4, typename ARG5>
        void publishListenerEvent(void (ListenerType::*Memfun)(ARG1, ARG2, ARG3, ARG4, ARG5), ARG1 arg1, ARG2 arg2, ARG3 arg3, ARG4 arg4, ARG5 arg5) {
            typename ListenerList::iterator it = mListenerList.begin();
            for(; it != mListenerList.end(); ++it) {
                ((it->first)->*Memfun)(arg1, arg2, arg3, arg4, arg5);
            }
        }
        
        template<typename ARG1, typename ARG2, typename ARG3, typename ARG4, typename ARG5, typename ARG6>
        void publishListenerEvent(void (ListenerType::*Memfun)(ARG1, ARG2, ARG3, ARG4, ARG5, ARG6), ARG1 arg1, ARG2 arg2, ARG3 arg3, ARG4 arg4, ARG5 arg5, ARG6 arg6) {
            typename ListenerList::iterator it = mListenerList.begin();
            for(; it != mListenerList.end(); ++it) {
                ((it->first)->*Memfun)(arg1, arg2, arg3, arg4, arg5, arg6);
            }
        }
        
    protected:
        ListenerMap mListenerMap;
        
        ListenerList mListenerList;
    };
    
}

#endif
