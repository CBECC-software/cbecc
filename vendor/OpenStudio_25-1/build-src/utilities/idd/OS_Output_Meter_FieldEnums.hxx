/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_OUTPUT_METER_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_OUTPUT_METER_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Output_MeterFields
 *  \brief Enumeration of OS:Output:Meter's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Output_MeterFields, )
#else
class OS_Output_MeterFields: public ::EnumBase<OS_Output_MeterFields> {
 public: 
  enum domain 
  {
Handle, Name, ReportingFrequency, MeterFileOnly, Cumulative,   };
  OS_Output_MeterFields()
   : EnumBase<OS_Output_MeterFields>(Handle) {} 
  OS_Output_MeterFields(const std::string &t_name) 
   : EnumBase<OS_Output_MeterFields>(t_name) {} 
  OS_Output_MeterFields(int t_value) 
   : EnumBase<OS_Output_MeterFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Output_MeterFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Output_MeterFields>::integer_value()); }
   private:
    friend class EnumBase<OS_Output_MeterFields>;
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
{ OS_Output_MeterFields::Handle, "Handle", "Handle"},
{ OS_Output_MeterFields::Name, "Name", "Name"},
{ OS_Output_MeterFields::ReportingFrequency, "ReportingFrequency", "Reporting Frequency"},
{ OS_Output_MeterFields::MeterFileOnly, "MeterFileOnly", "Meter File Only"},
{ OS_Output_MeterFields::Cumulative, "Cumulative", "Cumulative"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Output_MeterFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Output_MeterFields> OptionalOS_Output_MeterFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_OUTPUT_METER_FIELDENUMS_HXX
