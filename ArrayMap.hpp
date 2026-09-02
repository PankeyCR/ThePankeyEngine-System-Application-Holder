
#ifndef ArrayMap_hpp
	#define ArrayMap_hpp

	#include "makeShared.hpp"
	#include "ReferenceCountModel.hpp"
	#include "ArrayRawPointerMap.hpp"
	#include "Map.hpp"
	#include "Holder.hpp"

	#if defined(pankey_Log) && (defined(ArrayMap_Log) || defined(pankey_Global_Log) || defined(pankey_Base_Log))
		#include "Logger_status.hpp"
		#define ArrayMapLog(status,method,mns) pankey_Log(status,"ArrayMap",method,mns)
	#else
		#define ArrayMapLog(status,method,mns)
	#endif

	namespace pankey{

		namespace HolderSystem{

			template<class K, class V, class M = ReferenceCountModel>
			class ArrayMap : public Map<K,V,M>{
				public:
					using HOLDER_TYPE = typename M::HOLDER_TYPE;
					using MANAGER_TYPE = typename M::MANAGER_TYPE;

					ArrayMap(){
						ArrayMapLog(pankey_Log_StartMethod, "Constructor", "");
						m_storage.setKeyPointerDestroyer(destroyShared<M>);
						m_storage.setValuePointerDestroyer(destroyShared<M>);
						ArrayMapLog(pankey_Log_EndMethod, "Constructor", "");
					}
					
					virtual ~ArrayMap(){
						ArrayMapLog(pankey_Log_StartMethod, "Destructor", "");
						ArrayMapLog(pankey_Log_EndMethod, "Destructor", "");
					}

					virtual bool isEmpty()const{
						return m_storage.isEmpty();
					}

					virtual int length()const{
						return m_storage.length();
					}
                    
                    // virtual void addMove(Map<T>& a_Map){
                    //     MapLog(pankey_Log_StartMethod, "addMove", "");
                    //     for(int x = 0; x < a_Map.length(); x++){
                    //         Holder* f_value = a_Map.getPointerByIndex(x);
                    //         m_storage.add(f_value);
                    //     }
                    //     a_Map.reset();
                    //     MapLog(pankey_Log_EndMethod, "addMove", "");
                    // }
                    
                    // virtual void addDuplicate(const RawMap<T>& a_Map){
                    //     MapLog(pankey_Log_StartMethod, "addDuplicate", "");
                    //     for(int x = 0; x < a_Map.length(); x++){
                    //         shared_ptr<T> f_value = a_Map.getByIndex(x);
                    //         this->add(f_value);
                    //     }
                    //     MapLog(pankey_Log_EndMethod, "addDuplicate", "");
                    // }

                    virtual void add(const shared_ptr<K,M>& a_key, const shared_ptr<V,M>& a_value){
						ArrayMapLog(pankey_Log_StartMethod, "add", "");
						Holder* i_key_holder = a_key.getHolder();
						Holder* i_value_holder = a_value.getHolder();
						if(i_key_holder == nullptr){
							ArrayMapLog(pankey_Log_EndMethod, "add", "i_key_holder == nullptr");
							return;
						}
						m_storage.addPointers(i_key_holder, i_value_holder);
						MANAGER_TYPE::increment(i_key_holder);
						MANAGER_TYPE::increment(i_value_holder);
						ArrayMapLog(pankey_Log_EndMethod, "add", "");
					}

                    virtual void addShared(const K& a_key, const shared_ptr<V,M>& a_value){
						ArrayMapLog(pankey_Log_StartMethod, "addShared", "");
						shared_ptr<K,M> i_key = makeShared<K,M>(a_key);
						Holder* i_key_holder = i_key.getHolder();
						Holder* i_value_holder = a_value.getHolder();
						if(i_key_holder == nullptr){
							ArrayMapLog(pankey_Log_EndMethod, "addShared", "i_key_holder == nullptr");
							return;
						}
						m_storage.addPointers(i_key_holder, i_value_holder);
						MANAGER_TYPE::increment(i_key_holder);
						MANAGER_TYPE::increment(i_value_holder);
						ArrayMapLog(pankey_Log_EndMethod, "addShared", "");
					}

                    virtual MemoryHolder<M> get(const MemoryHolder<M>& a_key){
						Holder* i_key_holder = a_key.getHolder();
						Holder* i_value_holder = m_storage.getValuePointerByPointer(i_key_holder);
						MemoryHolder<M> i_memory;
						i_memory.copyHolder(i_value_holder);
						return i_memory;
					}

                    virtual MemoryHolder<M> getValueByKey(const K& a_key){
						for(int x = 0; x < m_storage.length(); x++){
							Holder* f_holder = m_storage.getKeyPointerByIndex(x);
							if(MANAGER_TYPE::isNull(f_holder)){
								continue;
							}
							K* f_key = MANAGER_TYPE::template getPointerType<K>(f_holder);
							if(f_key == nullptr){
								continue;
							}
							if(*f_key == a_key){
								return this->getValueByIndex(x);
							}

						}
						return MemoryHolder<M>();
					}

                    virtual MemoryHolder<M> getKeyByIndex(int x)const{
						Holder* i_holder = m_storage.getKeyPointerByIndex(x);
						MemoryHolder<M> i_memory;
						i_memory.copyHolder(i_holder);
						return i_memory;
					}

                    virtual MemoryHolder<M> getValueByIndex(int x)const{
						Holder* i_holder = m_storage.getValuePointerByIndex(x);
						MemoryHolder<M> i_memory;
						i_memory.copyHolder(i_holder);
						return i_memory;
					}

                    virtual bool contain(const MemoryHolder<M>& a_key){
						Holder* i_key_holder = a_key.getHolder();
						return m_storage.containKeyByPointer(i_key_holder);
					}

                    virtual void clear(){
						m_storage.clear();
					}

                    virtual MemoryHolder<M> remove(const MemoryHolder<M>& a_key){
						Holder* i_key_holder = a_key.getHolder();
						Base::RawMapEntry<Holder,Holder> i_entry = m_storage.removePointersByKeyPointer(i_key_holder);
						MemoryHolder<M> i_memory;
						i_memory.moveHolder(i_entry.getValue());
						return i_memory;
					}

                    virtual MemoryHolder<M> removeByIndex(int a_index){
						Base::RawMapEntry<Holder,Holder> i_entry = m_storage.removePointersByIndex(a_index);
						MemoryHolder<M> i_memory;
						i_memory.moveHolder(i_entry.getValue());
						return i_memory;
					}
					
				protected:
					Base::ArrayRawPointerMap<Holder,Holder> m_storage;
					
			};

		}

	}

#endif