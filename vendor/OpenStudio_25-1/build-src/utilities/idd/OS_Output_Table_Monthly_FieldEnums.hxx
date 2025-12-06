/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_OUTPUT_TABLE_MONTHLY_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_OUTPUT_TABLE_MONTHLY_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Output_Table_MonthlyFields
 *  \brief Enumeration of OS:Output:Table:Monthly's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Output_Table_MonthlyFields, )
#else
class OS_Output_Table_MonthlyFields: public ::EnumBase<OS_Output_Table_MonthlyFields> {
 public: 
  enum domain 
  {
Handle, Name, DigitsAfterDecimal,   };
  OS_Output_Table_MonthlyFields()
   : EnumBase<OS_Output_Table_MonthlyFields>(Handle) {} 
  OS_Output_Table_MonthlyFields(const std::string &t_name) 
   : EnumBase<OS_Output_Table_MonthlyFields>(t_name) {} 
  OS_Output_Table_MonthlyFields(int t_value) 
   : EnumBase<OS_Output_Table_MonthlyFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Output_Table_MonthlyFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Output_Table_MonthlyFields>::integer_value()); }
   private:
    friend class EnumBase<OS_Output_Table_MonthlyFields>;
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
{ OS_Output_Table_MonthlyFields::Handle, "Handle", "Handle"},
{ OS_Output_Table_MonthlyFields::Name, "Name", "Name"},
{ OS_Output_Table_MonthlyFields::DigitsAfterDecimal, "DigitsAfterDecimal", "Digits After Decimal"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Output_Table_MonthlyFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Output_Table_MonthlyFields> OptionalOS_Output_Table_MonthlyFields ;
#endif

/** \class OS_Output_Table_MonthlyExtensibleFields
 *  \brief Enumeration of OS:Output:Table:Monthly's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(OS_Output_Table_MonthlyExtensibleFields, )
#else
class OS_Output_Table_MonthlyExtensibleFields: public ::EnumBase<OS_Output_Table_MonthlyExtensibleFields> {
 public: 
  enum domain 
  {
VariableorMeterName, AggregationTypeforVariableorMeter,   };
  OS_Output_Table_MonthlyExtensibleFields()
   : EnumBase<OS_Output_Table_MonthlyExtensibleFields>(VariableorMeterName) {} 
  OS_Output_Table_MonthlyExtensibleFields(const std::string &t_name) 
   : EnumBase<OS_Output_Table_MonthlyExtensibleFields>(t_name) {} 
  OS_Output_Table_MonthlyExtensibleFields(int t_value) 
   : EnumBase<OS_Output_Table_MonthlyExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Output_Table_MonthlyExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Output_Table_MonthlyExtensibleFields>::integer_value()); }
   private:
    friend class EnumBase<OS_Output_Table_MonthlyExtensibleFields>;
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
{ OS_Output_Table_MonthlyExtensibleFields::VariableorMeterName, "VariableorMeterName", "Variable or Meter Name"},
{ OS_Output_Table_MonthlyExtensibleFields::AggregationTypeforVariableorMeter, "AggregationTypeforVariableorMeter", "Aggregation Type for Variable or Meter"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Output_Table_MonthlyExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Output_Table_MonthlyExtensibleFields> OptionalOS_Output_Table_MonthlyExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_OUTPUT_TABLE_MONTHLY_FIELDENUMS_HXX
