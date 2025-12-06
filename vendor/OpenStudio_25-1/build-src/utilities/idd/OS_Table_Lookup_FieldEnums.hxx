/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_TABLE_LOOKUP_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_TABLE_LOOKUP_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Table_LookupFields
 *  \brief Enumeration of OS:Table:Lookup's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Table_LookupFields, )
#else
class OS_Table_LookupFields: public ::EnumBase<OS_Table_LookupFields> {
 public: 
  enum domain 
  {
Handle, Name, IndependentVariableListName, NormalizationMethod, NormalizationDivisor, MinimumOutput, MaximumOutput, OutputUnitType, ExternalFileName, ExternalFileColumnNumber, ExternalFileStartingRowNumber,   };
  OS_Table_LookupFields()
   : EnumBase<OS_Table_LookupFields>(Handle) {} 
  OS_Table_LookupFields(const std::string &t_name) 
   : EnumBase<OS_Table_LookupFields>(t_name) {} 
  OS_Table_LookupFields(int t_value) 
   : EnumBase<OS_Table_LookupFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Table_LookupFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Table_LookupFields>::integer_value()); }
   private:
    friend class EnumBase<OS_Table_LookupFields>;
    typedef std::pair<std::string, int> PT;
    typedef std::vector<PT> VecType;
    static VecType buildStringVec(bool isd)
    {
      struct evalue
      {
        int value; const char *name; const char *description;
      };
      const evalue a[] =
      {
{ OS_Table_LookupFields::Handle, "Handle", "Handle"},
{ OS_Table_LookupFields::Name, "Name", "Name"},
{ OS_Table_LookupFields::IndependentVariableListName, "IndependentVariableListName", "Independent Variable List Name"},
{ OS_Table_LookupFields::NormalizationMethod, "NormalizationMethod", "Normalization Method"},
{ OS_Table_LookupFields::NormalizationDivisor, "NormalizationDivisor", "Normalization Divisor"},
{ OS_Table_LookupFields::MinimumOutput, "MinimumOutput", "Minimum Output"},
{ OS_Table_LookupFields::MaximumOutput, "MaximumOutput", "Maximum Output"},
{ OS_Table_LookupFields::OutputUnitType, "OutputUnitType", "Output Unit Type"},
{ OS_Table_LookupFields::ExternalFileName, "ExternalFileName", "External File Name"},
{ OS_Table_LookupFields::ExternalFileColumnNumber, "ExternalFileColumnNumber", "External File Column Number"},
{ OS_Table_LookupFields::ExternalFileStartingRowNumber, "ExternalFileStartingRowNumber", "External File Starting Row Number"},
        { 0,0,0 }
      };
      VecType v;
      int i = 0;
      while (!(a[i].value == 0 && a[i].name == 0 && a[i].description == 0))
      {
        if (isd)
        {
          std::string description = a[i].description; 
          if (!description.empty())
          {
            v.push_back(PT(description, a[i].value));
          }
        } else {
          v.push_back(PT(a[i].name, a[i].value));
        }
        ++i;
      }
      return v;
    }
  
  };
  inline std::ostream &operator<<(std::ostream &os, const OS_Table_LookupFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Table_LookupFields> OptionalOS_Table_LookupFields ;
#endif

/** \class OS_Table_LookupExtensibleFields
 *  \brief Enumeration of OS:Table:Lookup's Idd and Idf extensible fields
 *  to be used in conjunction with ExtensibleIndex and ExtensibleGroup.
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer ExtensibleIndex.field indices. (The enumeration value names
 *  are more likely to be valid across EnergyPlus and OpenStudio releases, and will break
 *  if they become invalid.)See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Table_LookupExtensibleFields, )
#else
class OS_Table_LookupExtensibleFields: public ::EnumBase<OS_Table_LookupExtensibleFields> {
 public: 
  enum domain 
  {
OutputValue,   };
  OS_Table_LookupExtensibleFields()
   : EnumBase<OS_Table_LookupExtensibleFields>(OutputValue) {} 
  OS_Table_LookupExtensibleFields(const std::string &t_name) 
   : EnumBase<OS_Table_LookupExtensibleFields>(t_name) {} 
  OS_Table_LookupExtensibleFields(int t_value) 
   : EnumBase<OS_Table_LookupExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Table_LookupExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Table_LookupExtensibleFields>::integer_value()); }
   private:
    friend class EnumBase<OS_Table_LookupExtensibleFields>;
    typedef std::pair<std::string, int> PT;
    typedef std::vector<PT> VecType;
    static VecType buildStringVec(bool isd)
    {
      struct evalue
      {
        int value; const char *name; const char *description;
      };
      const evalue a[] =
      {
{ OS_Table_LookupExtensibleFields::OutputValue, "OutputValue", "Output Value"},
        { 0,0,0 }
      };
      VecType v;
      int i = 0;
      while (!(a[i].value == 0 && a[i].name == 0 && a[i].description == 0))
      {
        if (isd)
        {
          std::string description = a[i].description; 
          if (!description.empty())
          {
            v.push_back(PT(description, a[i].value));
          }
        } else {
          v.push_back(PT(a[i].name, a[i].value));
        }
        ++i;
      }
      return v;
    }
  
  };
  inline std::ostream &operator<<(std::ostream &os, const OS_Table_LookupExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Table_LookupExtensibleFields> OptionalOS_Table_LookupExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_TABLE_LOOKUP_FIELDENUMS_HXX
