#pragma once
#ifndef MAX_ARR_LEN
#define MAX_ARR_LEN 64
#endif

int publishedVarCount = 0;

int getPublishedVarID()
{
    int id = publishedVarCount;
    publishedVarCount += 1;
    return id; 
}

template <typename T> 
class publishedVar
{
  T val_;
  T prev_val_;

  uint8_t num_;
  char * name_;
  char * prefix_;
  char valStr_[MAX_ARR_LEN];
  char * id_;
  bool pub_on_change_only_;
  void generateValStr();
  void generateIDStr();

  public:
  publishedVar(T defaultVal, const char * name, bool pub_on_change_only=false)
  : 
      val_(defaultVal),
      prev_val_(defaultVal-1),
      num_(getPublishedVarID()),
      name_(name),
      pub_on_change_only_(pub_on_change_only)
   {
    // Init prefix
    prefix_ = malloc(MAX_ARR_LEN);
    sprintf(prefix_,"${%d:%s:",num_,name_);

    // Init identifier
    id_ = malloc(MAX_ARR_LEN);
    generateIDStr();
   }

  publishedVar& operator =(const T& new_val)
  {
    prev_val_ = val_;
    val_ = new_val;

    if(prev_val_ != val_ || pub_on_change_only_ == false)
    {
        generateValStr();
        Serial.print(prefix_);
        Serial.print(valStr_);
        Serial.println("}");
    }

    return *this;
  }

 bool operator ==(const T& val)
  {
    return val_ == val;
  }
  bool operator !=(const T& val)
  {
    return val_ != val;
  }
  T getValue()
  {
      return val_;
  }
  char * getIdString()
  {
    return id_;  
  }
};

template<>
inline void publishedVar<int>::generateValStr()
{   
   sprintf(valStr_,"%d",val_); 
};

template<>
inline void publishedVar<String>::generateValStr()
{   
   sprintf(valStr_,"%s",val_); 
};

template<>
inline void publishedVar<int>::generateIDStr()
{
    sprintf(id_,",O:%d:INT:%s",num_,name_);
}

template<>
inline void publishedVar<String>::generateIDStr()
{
    sprintf(id_,",O:%d:STR:%s",num_,name_);
}
 
