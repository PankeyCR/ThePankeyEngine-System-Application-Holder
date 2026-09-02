
#ifndef Data_hpp
	#define Data_hpp

    #include "MemoryHolder.hpp"

	#if defined(pankey_Log) && (defined(Data_Log) || defined(pankey_Global_Log) || defined(pankey_HolderSystem_Log))
	    #include "Logger_status.hpp"
        #define DataLog(status,method,mns) pankey_Log(status,"Data",method,mns)
    #else
        #define DataLog(status,method,mns)
    #endif

	namespace pankey{

		namespace HolderSystem{

            template<class H>
            class Data : public MemoryHolder<H>{
                public:

                    using MANAGER_TYPE = typename MemoryHolder<H>::MANAGER_TYPE;
                    using HOLDER_TYPE = typename MemoryHolder<H>::HOLDER_TYPE;
                    
                    MANAGER_TYPE m_manager = nullptr;

                    Data(){
                        DataLog(pankey_Log_StartMethod, "Constructor", "");
                        DataLog(pankey_Log_EndMethod, "Constructor", "");
                    }

                    Data(const MemoryHolder<H>& a_holder){
                        DataLog(pankey_Log_StartMethod, "Constructor", "const MemoryHolder<H>& a_holder");
                        auto i_manager = a_holder.getManager();
                        if(i_manager == nullptr){
                            DataLog(pankey_Log_Statement, "Constructor", "i_manager == nullptr");
                            DataLog(pankey_Log_EndMethod, "Constructor", "");
                            return;
                        }
                        this->setManager(i_manager);
                        this->setHolder(a_holder.getHolder());
                        DataLog(pankey_Log_EndMethod, "Constructor", "");
                    }

                    Data(const Data<H>& a_holder){
                        DataLog(pankey_Log_StartMethod, "Constructor", "const Data<H>& a_holder");
                        auto i_manager = a_holder.getManager();
                        if(i_manager == nullptr){
                            DataLog(pankey_Log_Statement, "Constructor", "i_manager == nullptr");
                            DataLog(pankey_Log_EndMethod, "Constructor", "");
                            return;
                        }
                        this->setManager(i_manager);
                        this->setHolder(a_holder.getHolder());
                        DataLog(pankey_Log_EndMethod, "Constructor", "");
                    }

                    Data(HOLDER_TYPE a_holder, MANAGER_TYPE a_Manager){
                        DataLog(pankey_Log_StartMethod, "Constructor", "HOLDER_TYPE a_holder, MANAGER_TYPE a_Manager");
                        this->setManager(a_Manager);
                        this->setHolder(a_holder);
                        DataLog(pankey_Log_EndMethod, "Constructor", "");
                    }
                    
                    virtual ~Data(){
                        DataLog(pankey_Log_StartMethod, "Destructor", "");
                        this->remove();
                        DataLog(pankey_Log_EndMethod, "Destructor", "");
                    }
                        
                    virtual void setManager(MANAGER_TYPE a_llocator){
                        DataLog(pankey_Log_StartMethod, "setManager", "");
                        m_manager = a_llocator;
                        DataLog(pankey_Log_EndMethod, "setManager", "");
                    }

                    virtual MANAGER_TYPE getManager()const{
                        DataLog(pankey_Log_StartMethod, "getManager", "");
                        DataLog(pankey_Log_Statement, "getManager", "Is Null?");
                        DataLog(pankey_Log_Statement, "getManager", m_manager == nullptr);
                        DataLog(pankey_Log_EndMethod, "getManager", "");
                        return m_manager;
                    }

                    virtual void operator=(const MemoryHolder<H>& a_holder){
                        DataLog(pankey_Log_StartMethod, "operator=", "");
                        auto i_manager = a_holder.getManager();
                        if(i_manager == nullptr){
                            DataLog(pankey_Log_EndMethod, "operator=", "");
                            return;
                        }
                        this->setManager(i_manager);
                        this->setHolder(a_holder.getHolder());
                        DataLog(pankey_Log_EndMethod, "operator=", "");
                    }
                
            };

        }

	}

#endif