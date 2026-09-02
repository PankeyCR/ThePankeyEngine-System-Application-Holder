
#ifndef Map_hpp
	#define Map_hpp

	#include "MemoryHolder.hpp"
	#include "shared_ptr.hpp"

	#if defined(pankey_Log) && (defined(Map_Log) || defined(pankey_Global_Log) || defined(pankey_Base_Log))
		#include "Logger_status.hpp"
		#define MapLog(status,method,mns) pankey_Log(status,"Map",method,mns)
	#else
		#define MapLog(status,method,mns)
	#endif

	namespace pankey{

		namespace HolderSystem{

			template <class K, class V, class M>
			class Map{	
				public:
					virtual ~Map(){}
                    
                    virtual bool isEmpty()const=0;
					
                    virtual int length()const=0;

                    virtual void add(const shared_ptr<K,M>& a_key, const shared_ptr<V,M>& a_value)=0;
                    
                    virtual void put(const shared_ptr<K,M>& a_key, const shared_ptr<V,M>& a_value){
						MapLog(pankey_Log_StartMethod, "put", "");
                        if(this->contain(a_key)){
                            return;
                        }
                        this->add(a_key, a_value);
						MapLog(pankey_Log_EndMethod, "put", "");
                    }

                    // virtual shared_ptr<T> set(int a_index, const shared_ptr<T>& a_value)=0;

                    // virtual shared_ptr<T> insert(int a_index, const shared_ptr<T>& a_value)=0;

                    virtual MemoryHolder<M> get(const MemoryHolder<M>& a_key)=0;
                    
                    virtual MemoryHolder<M> getKeyByIndex(int x)const=0;
                    
                    virtual MemoryHolder<M> getValueByIndex(int x)const=0;

                    virtual bool contain(const MemoryHolder<M>& a_key)=0;
                    
                    // virtual int getIndex(const shared_ptr<T>& a_value)=0;

                    // virtual void reset()=0;
                    // virtual void clear()=0;

                    virtual MemoryHolder<M> remove(const MemoryHolder<M>& a_key)=0;

                    virtual MemoryHolder<M> removeByIndex(int a_index)=0;

                    // //special removes
                    // virtual bool destroyFirstIndex(int a_amount)=0;
                    // virtual bool destroyLastIndex(int a_amount)=0;
                    
                    // virtual shared_ptr<T> removeFirst(){
                    //     MapLog(pankey_Log_StartMethod, "removeFirst", "");
                    //     MapLog(pankey_Log_EndMethod, "removeFirst", "");
                    //     return this->removeByIndex(0);
                    // }

                    // virtual shared_ptr<T> removeLast(){
                    //     MapLog(pankey_Log_StartMethod, "removeLast", "");
                    //     MapLog(pankey_Log_EndMethod, "removeLast", "");
                    //     return this->removeByIndex(this->length() - 1);
                    // }

                    // virtual void expand(int a_size)=0;
				private:
			};

		}

	}

#endif