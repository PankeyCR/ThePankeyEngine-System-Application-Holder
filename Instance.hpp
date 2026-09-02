
#ifndef Instance_hpp
	#define Instance_hpp

    #include "Pointer.hpp"

	#if defined(pankey_Log) && (defined(Instance_Log) || defined(pankey_Global_Log) || defined(pankey_HolderSystem_Log))
		#include "Logger_status.hpp"
		#define InstanceLog(status,method,mns) pankey_Log(status,"Instance",method,mns)
	#else
		#define InstanceLog(status,method,mns)
	#endif

	namespace pankey{

		namespace HolderSystem{

			template<class P, class H, class M>
			class Instance : public Pointer<P,H,M>{
				public:
					
					Instance(){
						InstanceLog(pankey_Log_StartMethod, "Contructor", "");
						this->create();
						InstanceLog(pankey_Log_EndMethod, "Contructor", "");
					}

					Instance(const MemoryHolder<H>& a_instance){
						InstanceLog(pankey_Log_StartMethod, "Contructor", "const Instance &a_instance");
						if(!this->isMember(a_instance)){
							InstanceLog(pankey_Log_EndMethod, "Constructor", "");
							return;
						}
						this->setHolder(a_instance.getHolder());
						InstanceLog(pankey_Log_EndMethod, "Contructor", "");
					}

					Instance(const Member<H,M>& a_instance){
						InstanceLog(pankey_Log_StartMethod, "Contructor", "const Instance &a_instance");
						if(!this->sameType(a_instance.getType())){
							InstanceLog(pankey_Log_EndMethod, "Constructor", "");
							return;
						}
						this->setHolder(a_instance.getHolder());
						InstanceLog(pankey_Log_EndMethod, "Contructor", "");
					}

					Instance(const Instance<P,H,M>& a_instance){
						InstanceLog(pankey_Log_StartMethod, "Contructor", "const Instance &a_instance");
						this->setHolder(a_instance.getHolder());
						InstanceLog(pankey_Log_EndMethod, "Contructor", "");
					}

					Instance(const Pointer<P,H,M>& a_instance){
						InstanceLog(pankey_Log_StartMethod, "Contructor", "const Instance &a_instance");
						this->setHolder(a_instance.getHolder());
						InstanceLog(pankey_Log_EndMethod, "Contructor", "");
					}

					virtual ~Instance(){
						InstanceLog(pankey_Log_StartMethod, "Destructor", "");
						InstanceLog(pankey_Log_EndMethod, "Destructor", "");
					}
			};

		}

	}

#endif