
#ifndef ArrayList_hpp
	#define ArrayList_hpp

	#include "makeShared.hpp"
	#include "ReferenceCountModel.hpp"
	#include "ArrayRawPointerList.hpp"
	#include "List.hpp"

	#if defined(pankey_Log) && (defined(ArrayList_Log) || defined(pankey_Global_Log) || defined(pankey_HolderSystem_Log))
		#include "Logger_status.hpp"
		#define ArrayListLog(status,method,mns) pankey_Log(status,"ArrayList",method,mns)
	#else
		#define ArrayListLog(status,method,mns)
	#endif

	namespace pankey{

		namespace HolderSystem{

			template<class T, class M = ReferenceCountModel>
			class ArrayList : public List<T,M>{
				public:
					using HOLDER_TYPE = typename M::HOLDER_TYPE;
					using MANAGER_TYPE = typename M::MANAGER_TYPE;

					ArrayList(){
						ArrayListLog(pankey_Log_StartMethod, "Constructor", "");
						m_storage.setPointerDestroyer(destroyShared<M>);
						ArrayListLog(pankey_Log_EndMethod, "Constructor", "");
					}
					
					virtual ~ArrayList(){
						ArrayListLog(pankey_Log_StartMethod, "Destructor", "");
						ArrayListLog(pankey_Log_EndMethod, "Destructor", "");
					}

					virtual bool isEmpty()const{
						return m_storage.isEmpty();
					}

					virtual int length()const{
						return m_storage.length();
					}

                    virtual bool replace(int i, int j){
						return m_storage.replace(i, j);
					}
                    
                    // virtual void addMove(List<T>& a_list){
                    //     ListLog(pankey_Log_StartMethod, "addMove", "");
                    //     for(int x = 0; x < a_list.length(); x++){
                    //         Holder* f_value = a_list.getPointerByIndex(x);
                    //         m_storage.add(f_value);
                    //     }
                    //     a_list.reset();
                    //     ListLog(pankey_Log_EndMethod, "addMove", "");
                    // }
                    
                    // virtual void addDuplicate(const RawList<T>& a_list){
                    //     ListLog(pankey_Log_StartMethod, "addDuplicate", "");
                    //     for(int x = 0; x < a_list.length(); x++){
                    //         shared_ptr<T,M> f_value = a_list.getByIndex(x);
                    //         this->add(f_value);
                    //     }
                    //     ListLog(pankey_Log_EndMethod, "addDuplicate", "");
                    // }

                    virtual void add(const shared_ptr<T,M>& a_value){
						Holder* i_holder = a_value.getHolder();
						m_storage.addPointer(i_holder);
						MANAGER_TYPE::increment(i_holder);
					}
                    
                    // virtual shared_ptr<T,M> put(const shared_ptr<T,M>& a_value){

					// }

                    virtual shared_ptr<T,M> getByIndex(int x)const{
						Holder* i_holder = m_storage.getPointerByIndex(x);
						shared_ptr<T,M> i_shared;
						i_shared.copyHolder(i_holder);
						return i_shared;
					}
					
				protected:
					Base::ArrayRawPointerList<Holder> m_storage;
					
			};

		}

	}

#endif