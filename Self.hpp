
#ifndef Self_hpp
	#define Self_hpp

	#include "MemoryHolder.hpp"
    #include "StaticManagerInstance.hpp"
    #include "SelfMemoryAllocator.hpp"

	#if defined(pankey_Log) && (defined(Self_Log) || defined(pankey_Global_Log) || defined(pankey_HolderSystem_Log))
		#include "Logger_status.hpp"
		#define SelfLog(status,method,mns) pankey_Log(status,"Self",method,mns)
	#else
		#define SelfLog(status,method,mns)
	#endif

	namespace pankey{

		namespace HolderSystem{

			template<class P, class H, class M>
			class Self : public MemoryHolder<H>{
				public:
					using SELF_TYPE = P;
					using MANAGER_TYPE = typename MemoryHolder<H>::MANAGER_TYPE;
					using VOID_TYPE = typename MemoryHolder<H>::VOID_TYPE;
					using HOLDER_TYPE = typename MemoryHolder<H>::HOLDER_TYPE;

					Self(SELF_TYPE* a_Self){
						SelfLog(pankey_Log_StartMethod, "Contructor", "const SELF_TYPE &a_Self");
						this->m_holder = MemoryHolderManager<H>::newInstance(this->getManager(), Base::ClassCount<P>::get(), new Base::SelfMemoryAllocator<P>(a_Self));
						MemoryHolderManager<H>::add(this->getManager(), this->m_holder);
						MemoryHolderManager<H>::setManageableCheck(this->getManager(), this->m_holder, false);
						SelfLog(pankey_Log_EndMethod, "Contructor", "");
					}

					virtual ~Self(){
						SelfLog(pankey_Log_StartMethod, "Destructor", "");
						this->destroy();
						SelfLog(pankey_Log_EndMethod, "Destructor", "");
					}

					virtual MANAGER_TYPE getManager()const{
						MemberLog(pankey_Log_StartMethod, "getManager", "");
						MemberLog(pankey_Log_EndMethod, "getManager", "");
						return StaticManagerInstance<H,M>::getManager();
					}

					//if theres no manager, this method crashs, always check for null
					virtual SELF_TYPE& getSelf(){
						SelfLog(pankey_Log_StartMethod, "getSelf", "");
						VOID_TYPE i_pointer = this->getRawPointer();
						SelfLog(pankey_Log_EndMethod, "getSelf", "");
						return *((SELF_TYPE*)i_pointer);
					}

					virtual void setHolder(HOLDER_TYPE a_holder){
						SelfLog(pankey_Log_StartMethod, "setHolder", "");
						SelfLog(pankey_Log_EndMethod, "setHolder", "");
					}

					virtual bool operator==(const Self<P,H,M>& a_self)const{
						return a_self.getHolder() == this->getHolder();
					}
					
					virtual bool operator!=(const Self<P,H,M>& a_self)const{
						return a_self.getHolder() == this->getHolder();
					}

				protected:
			};

		}

	}

#endif